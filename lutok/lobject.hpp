#if !defined(LUTOK_LOBJECT_HPP)
#define LUTOK_LOBJECT_HPP

#include <string>

#include <utility>
#include <map>

#include <lua.hpp>
#include <string> // For strlen
#include <type_traits>

#define LOBJECT_ADD_PROPERTY(CLASSNAME, TYPENAME, LUANAME, GETTER, SETTER) this->properties[(LUANAME)] = LObject<CLASSNAME, TYPENAME>::PropertyPair(&CLASSNAME::GETTER, &CLASSNAME::SETTER)
#define LOBJECT_ADD_METHOD(CLASSNAME, LUANAME, METHOD) this->methods[(LUANAME)] = &CLASSNAME::METHOD
#define LOBJECT_DEFINE_CLASS(CLASSNAME, TYPENAME, LUANAME) CLASSNAME(lutok::state & state) : LObject<CLASSNAME, TYPENAME>::LObject( state, (LUANAME))
#define LOBJECT_INSTANCE(CLASSNAME) reinterpret_cast<CLASSNAME *>(CLASSNAME::getInstance(state).lock().get());
#define LOBJECT_METHOD(METHODNAME, TYPEDEF) METHODNAME(lutok::state & state, TYPEDEF)

template <class C, typename T>
class LObject {
protected:
	lutok::state state;
public:
	typedef std::weak_ptr<C> classWeakPtr;
	typedef std::shared_ptr<C> classSharedPtr;

	typedef std::weak_ptr<T> typeWeakPtr;
	typedef std::shared_ptr<T> typeSharedPtr;

	typedef int (C::*Method) (lutok::state &, T);
	typedef struct std::pair< C *, T> LObjectPair;
	typedef struct std::pair< Method, Method > PropertyPair;

    typedef std::map< std::string, PropertyPair > PropertyType;
	typedef std::map< std::string, Method > FunctionType;

	typedef std::map< int, const PropertyPair *> PropertyCacheType;
	typedef std::map< int, Method > MethodCacheType;

	std::string className;

	int null_method(lutok::state &, T){
		return 0;
	}

protected:
	PropertyType properties;
	FunctionType methods;
	LObject(lutok::state & state, const std::string & className){
		this->state = state;
		this->className = className;
	}

private:
	PropertyCacheType PropertyCache;
	MethodCacheType MethodCache;

	LObjectPair * getObjPair(T obj){
		return new LObjectPair(reinterpret_cast<C*>(this), obj);
	}
public:
	static classWeakPtr getInstance(lutok::state & state){
		assert((std::is_base_of<LObject, C>::value == true));
		static classSharedPtr instance = nullptr;
		if (instance == nullptr){
			instance = classSharedPtr(new C(state));
		}
		return instance;
	}
/*
  @ check
  Arguments:
    * L - Lua State
    * narg - Position to check

  Description:
    Retrieves a wrapped class from the arguments passed to the func, specified by narg (position).
    This func will raise an exception if the argument is not of the correct type.
*/
    T check(int narg)
	{
		LObjectPair ** obj = state.check_userdata<LObjectPair *>(narg, className);
		if ( obj 
			//&& (std::is_class<(*obj)->second>::value == true)
		){
			return (*obj)->second;		// pointer to T object
		}else
			return nullptr; // lightcheck returns nullptr if not found.
	}

/*
  @ Register
  Arguments:
    * L - Lua State
    * namespac - Namespace to load into

  Description:
    Registers your class with Lua.  Leave namespac "" if you want to load it into the global space.
*/

	void refresh_methods(int metatable = 0){
		int i=0;
		for (PropertyType::const_iterator							// Register some properties in it
			iter = properties.begin(); iter != properties.end(); iter++) {

			state.push_string((*iter).first);
			state.push_number(i);
			state.set_table(metatable);
			LObject::PropertyCache[i] = &((*iter).second);
			i++;
		}

		i=0;
		for (FunctionType::const_iterator							// Register some functions in it
			iter = methods.begin(); iter != methods.end(); iter++) {

			state.push_string((*iter).first);
			state.push_number(i | ( 1 << 8 ));
			state.set_table(metatable);
			LObject::MethodCache[i] = (*iter).second;
			i++;
		}
	}

    // REGISTER CLASS AS A GLOBAL TABLE 
    void Register(const std::string & namespac = "", bool create_constructor = false) {

		if (create_constructor){
			if ( !namespac.empty() ){
				state.get_global(namespac);
				if( state.is_nil() ) // Create namespace if not present
				{
					state.new_table();
					state.push_value();
					state.set_global(namespac);
				}
				state.push_cxx_function(&constructor);
				state.set_field(-2, className);
				state.pop(1);
			} else {
				state.push_cxx_function(&constructor);
				state.set_global(className);
			}
		}
		
		state.new_metatable(className);
		int             metatable = state.get_top();
		
		state.push_literal("__gc");
		state.push_cxx_function(&gc_obj);
		state.set_table(metatable);
		
		state.push_literal("__tostring");
		state.push_cxx_function(&to_string);
		state.set_table(metatable);

		state.push_literal("__index");
		state.push_cxx_function(&property_getter);
		state.set_table(metatable);

		state.push_literal("__newindex");
		state.push_cxx_function(&property_setter);
		state.set_table(metatable);

		refresh_methods(metatable);
	}


/*
  @ constructor (internal)
  Arguments:
    * L - Lua State
*/
    static int constructor(lutok::state & s){
		return 0;
    }

	void destructor(T obj){
    }

/*
  @ createNew
  Arguments:
    * L - Lua State
	T*	- Instance to push

  Description:
    Loads an instance of the class into the Lua stack, and provides you a pointer so you can modify it.
*/
    void push(T obj){
		if (obj){
			LObjectPair ** a = state.new_userdata<LObjectPair *>(); // Create userdata
			*a = getObjPair(obj);
		
			state.get_metatable(className);
			if (state.is_nil()){
				state.pop(1);
				Register();
			}
		
			state.set_metatable();
		}
    }

/*
  @ property_getter (internal)
  Arguments:
    * L - Lua State
*/
    static int property_getter(lutok::state & s){
		s.get_metatable(1);
		s.push_value(2);
		s.raw_get();
		
		if (s.is_number()) { // Check if we got a valid index
			
			int _index = s.to_integer();

			LObjectPair ** obj = s.to_userdata<LObjectPair *>(1);
			C * thisobj = (*obj)->first;
			s.push_value(3);
			
			if( _index & ( 1 << 8 ) ){ // A func
				s.push_integer(_index ^ ( 1 << 8 )); // Push the right func index
				s.push_lightuserdata(obj);
				s.push_cxx_closure(function_dispatch, 2);
				return 1; // Return a func
			}
			
			s.pop(2);			// Pop metatable and _index
			s.remove(1);		// Remove userdata
			s.remove(1);		// Remove [key]
			
			const PropertyPair * fpairs = thisobj->PropertyCache[_index];
			assert((*obj)->second);
			return (thisobj->*(fpairs->first)) (s, (*obj)->second);
		}
		
		return 1;
    }

/*
  @ property_setter (internal)
  Arguments:
    * L - Lua State
*/
    static int property_setter(lutok::state & s){
		s.get_metatable(1);		// Look up the index from name
		s.push_value(2);
		s.raw_get();
		
		if ( s.is_number() ) // Check if we got a valid index
		{
			
			int _index = s.to_integer();
			
			LObjectPair ** obj = s.to_userdata<LObjectPair *>(1);
			C * thisobj = (*obj)->first;

			if( !obj || !*obj ){
				s.error("Internal error, no object given!");
				return 0;
			}
			
			if( _index >> 8 ){ // Try to set a func
				char c[128];
				sprintf( c , "Trying to set the method [%s] of class [%s]" , s.to_string(2).c_str() , thisobj->className );
				s.error( c );
				return 0;
			}
			
			s.pop(2);			// Pop metatable and _index
			s.remove(1);		// Remove userdata
			s.remove(1);		// Remove [key]

			const PropertyPair * fpairs = thisobj->PropertyCache[_index];
			assert((*obj)->second);
			return (thisobj->*(fpairs->second)) (s, (*obj)->second);
		}
		
		return 0;
    }

/*
  @ function_dispatch (internal)
  Arguments:
    * L - Lua State
*/
    static int function_dispatch(lutok::state & s) {
		int i = s.to_integer(s.upvalue_index(1));
		LObjectPair ** obj = s.to_userdata<LObjectPair *>(s.upvalue_index(2));
		C * thisobj = (*obj)->first;
		assert((*obj)->second);
		return (thisobj->*(thisobj->MethodCache[i])) (s, (*obj)->second);
    }

/*
  @ gc_obj (internal)
  Arguments:
    * L - Lua State
*/
    static int gc_obj(lutok::state & s)	{
		LObjectPair ** obj = s.to_userdata<LObjectPair *>();
		
		if( obj && *obj ){
			C * thisobj = (*obj)->first;
			assert((*obj)->second);
			thisobj->destructor((*obj)->second);
			delete(*obj);
		}
		return 0;
    }
	
	static int to_string(lutok::state & s) {
		LObjectPair ** obj = s.to_userdata<LObjectPair *>();
		C * thisobj = (*obj)->first;
		
		if ( obj ) {
			char c[128];
			sprintf(c,"%s (%p)", thisobj->className.c_str(), (void*)(*obj)->second);
			s.push_string(c);
		} else {
			s.push_string("Empty object");
		}
		
		return 1;
	}

};

#endif