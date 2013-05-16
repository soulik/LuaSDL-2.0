local args = {...}

local cpp_template = [[
#include "objects/{{lc_name}}.hpp"
#include <lua.hpp>

void LuaSDL::init_{{lc_name}}(lutok::state & state, moduleDef & module){
	LOBJECT_INSTANCE(LuaSDL::{{class_name}});
}
]]

local hpp_template = [[
#ifndef {{def_name}}
#define {{def_name}}

#include "common.hpp"

namespace LuaSDL {

	class {{class_name}} : public LObject<{{class_name}}, {{type_name}}> {
	public:
		LOBJECT_DEFINE_CLASS({{class_name}}, {{type_name}}, "{{c_name}}") {
			LOBJECT_ADD_METHOD(LuaSDL::{{class_name}}, "", null_method);
			LOBJECT_ADD_PROPERTY(LuaSDL::{{class_name}}, {{type_name}}, "", null_method, null_method);	
		}

		void destructor({{type_name}} {{var_name}}){
		}
	};
}

#endif
]]

local function template(src, vars)
	return string.gsub(src, "{{([^}]+)}}", vars)
end

local function write_file(fname, content)
	local f = io.open(fname, "w")
	if f then
		f:write(content)
		f:close()
	end
end

local function generate_hpp_file(name, vars)
	local fname = string.format("./objects/%s.hpp", name)
	write_file(fname, template(hpp_template, vars))
end

local function generate_cpp_file(name, vars)
	local fname = string.format("./objects/%s.cpp", name)
	write_file(fname, template(cpp_template, vars))
end

local function build(className, typeName)
	local vars = {
		def_name = string.format("LUA_SDL_OBJECTS_%s_H", string.upper(className)),
		class_name = string.format("Lua_SDL_%s", className),
		type_name = typeName,
		var_name = string.lower(string.match(typeName, "([%w_-]+)")),
		lc_name = string.lower(className),
		c_name = string.gsub(className, "^([%w])", string.upper),
	}
	local name = string.lower(className)
	generate_hpp_file(name, vars)
	generate_cpp_file(name, vars)
end

local function show_help()
	io.write(string.format([[
create_obj.lua <class_name> <type_name>
]]))
end

if #args<2 then
	show_help()
else
	build(tostring(args[1]), tostring(args[2]))
end