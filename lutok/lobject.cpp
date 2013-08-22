#ifdef _WIN32
#include <io.h>
#else
extern "C" {
#include <unistd.h>
}
#endif

#include <cassert>
#include <cstring>
#include <typeinfo>

#include "c_gate.hpp"
#include "exceptions.hpp"
#include "state.ipp"
#include "lobject.hpp"


template <typename T>
static void lutok::LObject<T>::commit(state& s) {
	s.new_table();
	int methods = s.get_top();

	luaL_newmetatable(s._pimpl->lua_state, T::s_lunaClassName);
	int metatable = s.get_top();

	s.push_value(methods);
	set(s, LUA_GLOBALSINDEX, T::s_lunaClassName);

	s.push_value(methods);
	set(s, metatable, "__metatable");

	s.push_value(methods);
	set(s, metatable, "__index");

	s.push_cxx_function(tostringT);
	set(s, metatable, "__tostring");

	s.push_cxx_function(gcT);
	set(s, metatable, "__gc");

	s.new_table();
	s.push_cxx_function(newT);
	s.push_value();
	set(s, methods, "new");
	set(s, -3, "__call");
	s.set_metatable(methods);

    for (std::map< std::string, cxx_function >::const_iterator
		iter = T::s_lunaMethods.begin(); iter != T::s_lunaMethods.end(); iter++) {
        s.push_string((*iter).first);
		s.push_lightuserdata(reinterpret_cast<void*>((*iter).second));
		s.push_cxx_closure(thunk, 1);
        s.set_table(methods);
    }

	TypeInfo::commit(s, methods);

	s.pop(2);
}

template <typename T>
static T* lutok::LObject<T>::check(state& s, int narg) {
	Userdata* ud = reinterpret_cast<Userdata*>(luaL_checkudata(s._pimpl->lua_state, narg, T::s_lunaClassName));
	if (!ud) {
		luaL_typerror(l, narg, T::s_lunaClassName);
	}
	return ud->pT;
}

template <typename T>
static void lutok::LObject<T>::TypeInfo::commit(state& s, int methods) {
	s.get_global(typeid(T).name());

	if (s.is_table()) {
		s.set_table(methods);
		return;
	}

	s.new_table();
	int type = s.get_top();

	assert(T::s_lunaTypeInfoPtr);
	s.push_string(T::s_lunaTypeInfoPtr->name());

	set(s, type, "name");

	s.push_value(type);
	set(s, methods, "type");

	s.push_value(methods);
	set(s, LUA_GLOBALSINDEX, T::s_lunaTypeInfoPtr->name());
}

template <typename T>
static int lutok::LObject<T>::thunk(state& s) {
	T* obj = check(s, 1);
	s.remove(1);
	lutok::cxx_function * m = s.to_userdata<lutok::cxx_function>(lua_upvalueindex(1));
	return (obj->*(m))(l);
}

template <typename T>
static int lutok::LObject<T>::newT(state& s) {
	lua_remove(s._pimpl->lua_state, 1);

	T* obj = new T(s);
	Userdata* ud = s.new_userdata<Userdata>();
	ud->pT = obj;
	luaL_getmetatable(s._pimpl->lua_state, T::s_lunaClassName);
	s.set_metatable();
	return 1;
}

template <typename T>
static int lutok::LObject<T>::gcT(state& s) {
	if (luaL_getmetafield(s._pimpl->lua_state, 1, "unmanaged")) {
		s.push_value(1);
		s.get_table();
		if (!s.is_nil()) {
			return 0;
		}
	}

	Userdata* ud = s.to_userdata<UserData>(1);
	T* obj = ud->pT;
	delete obj;
	return 0;
}

template <typename T>
static int lutok::LObject<T>::tostringT(state& s) {
	char buffer[32] = {0, };

	Userdata* ud = s.to_userdata<UserData>(1);
	T* obj = ud->pT;
	snprintf(buffer, sizeof(buffer), "%p", obj);
	lua_pushfstring(s._pimpl->lua_state, "%s (%s)", T::s_lunaClassName, buffer);
	return 1;
}

template <typename T>
static void lutok::LObject<T>::set(state& s, Index table, const std::string& key) {
	s.push_string(key);
	s.insert(-2);
	s.set_table(table);
}

template <typename T>
static void lutok::LObject<T>::weaktable(state& s,  const std::string& mode) {
	s.new_table();
	s.push_value();
	s.set_metatable();

	s.push_literal("__mode");
	s.push_string(mode);
	s.set_table();
}

template <typename T>
static void lutok::LObject<T>::subtable(state& s, Index metatable, const std::string& name,  const std::string& mode) {
	s.push_string(name);
	s.get_table(metatable);

	if (s.is_nil()) {
		s.pop(1);

		lua_checkstack(s._pimpl->lua_state, 3);

		weaktable(s, mode);
		s.push_string(name);
		s.push_value(-2);
		s.set_metatable(metatable);
	}
}

template <typename T>
static typename lutok::LObject<T>::Index lutok::LObject<T>::push(state& s, T* instance, bool gc) {
	if (!instance) {
		s.push_nil();
		return 0;
	}

	luaL_getmetatable(s._pimpl->lua_state, T::s_lunaClassName);
	if (s.is_nil()) {
		luaL_error(s._pimpl->lua_state, "[Luna::%s] Class %s has not been commited!", __func__, T::s_lunaClassName);
		return 0;
	}
	lutok::LObject<T>::Index metatable = s.get_top();

	subtable(s, metatable, "userdata", "v");
	lutok::LObject<T>::Userdata * userdata = allocUserdata(s, metatable, instance);
	if (userdata) {
		userdata->pT = instance;
		s.push_value(metatable);
		s.set_metatable();
		if (!gc) {
			lua_checkstack(s._pimpl->lua_state, 3);
			subtable(s, metatable, "unmanaged", "k");

			s.push_value(-2);
			s.push_boolean(1);
			s.set_table();
			s.pop(1);
		}
	}
	lua_replace(s._pimpl->lua_state, metatable);
	lua_settop(s._pimpl->lua_state, metatable);
	return metatable;
}

template <typename T>
static typename lutok::LObject<T>::Userdata* lutok::LObject<T>::allocUserdata(state& s, Index table, void* key, std::size_t size) {
	lutok::LObject<T>::Userdata* userdata = NULL;

	s.push_lightuserdata(key);
	s.get_table(table);
	if (s.is_nil()) {
		s.pop(1);
		lua_checkstack(s._pimpl->lua_state, 3);
		if (size<=0){
			userdata = s.new_userdata<lutok::LObject<T>::>();
		}else{
			userdata = reinterpret_cast<lutok::LObject<T>::*>s.new_userdata_voidp(size);
		}

		s.push_lightuserdata(key);
		s.push_value(-2);
		s.set_table(-4);
	}
	return userdata;
}
