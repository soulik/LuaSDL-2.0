local lfs = require 'lfs'
require 'lpeg'

os.mkdir = lfs.mkdir

local P = lpeg.P
local C = lpeg.C
local Ct = lpeg.Ct
local Cs = lpeg.Cs
local V = lpeg.V
local S = lpeg.S
local R = lpeg.R
local locale = lpeg.locale()

function io.load(fname)
	local f = io.open(fname)
	if f then
		local buffer = f:read("*a")
		f:close()
		return buffer
	else
		return false
	end
end

function io.save(fname,data)
	local f = io.open(fname,"w")
	if f then
		f:write(data)
		f:close()
		return true
	else
		return false
	end
end

function getFiles(path, match)
	local files = {}
	local match = match or ".+"
	local function r(path)
		for p in lfs.dir(path) do
			if (p~='.' and p~='..') then
				local p2 = path..'/'..p
				local attr = lfs.attributes(p2)
				if (attr) then
					if attr.mode=="directory" then
						r(p2)
					elseif attr.mode=="file" then
						local m = string.match(p,match)
						if m then
							table.insert(files,p2)
						end
					end
				else
					error("Can't read file: '%s'",tostring(p2))
				end
			end
		end
	end
	r(path)
	return files
end

function io.files(path, match)
	return ipairs(getFiles(path, match))
end

local function replace(s, t)
	local pattern

	for p, fn in pairs(t) do
		if not pattern then
			pattern = p / fn
		else
			pattern = pattern + (p / fn)
		end
	end
	pattern = Cs((pattern + 1)^0)
	return pattern:match(s)
end

local content = io.load('objects/renderer.cpp')
local space =  locale.space^1
local space0 =  locale.space^0
local name = (locale.alpha + P'_')^1 

local nullMethod = Cs((P'null_method' / 'nullMethod' + 1)^0)

print(replace(content, {
	-- class def
	[P'class' * space * P'Lua_SDL_' * C(name) * space0 * P':' * space0 * P'public' * space * P'Object<' * space0 * name * space0 * P',' * space0 * C(name) * space0 * P'*' * space0 * P'>'] =
	function(n, t)
		return ('class %s : public Object<%s>'):format(n,t)
	end,
	-- class constructor
	[P'LOBJECT_DEFINE_CLASS(' * space0 * P'Lua_SDL_' * C(name) * space0 * P',' * space0 * C(name) * space0 * P'*' * space0 * P',' * space0 * P'"' * name * P'"' * space0 * P')'] =
	function(n, t)
		return ('explicit %s(State * state) : Object<%s>(state)'):format(n,t)
	end,
	-- method
	[P'LOBJECT_ADD_METHOD(' * space0 * P'LuaSDL::Lua_SDL_' * C(name) * space0 * P',' * space0 * P'"' * C(name) * '"' * space0 * P',' * space0 * C(name) * space0 * P')'] = 
	function(n, ln, fn)
		return ('LUTOK_METHOD("%s", &%s::%s)'):format(ln,n,fn)
	end,
	-- property
	[P'LOBJECT_ADD_PROPERTY(' * space0 * P'LuaSDL::Lua_SDL_' * C(name) * space0 * P',' * space0 * name * space0 * P'*' * space0 * P',' * space0 * P'"' * C(name) * '"' * space0 * P',' * space0 * C(name) * space0 * P',' * space0 * C(name) * space0 * P')'] =
	function(n, ln, gFn, sFn)
		gFn, sFn = nullMethod:match(gFn), nullMethod:match(sFn)
		return ('LUTOK_PROPERTY("%s", &%s::%s, &%s::%s)'):format(ln, n, gFn, n, sFn)
	end,
	-- method def w/o body
	[C(P'int' * space * (name * space)^0) * space0 * P'LOBJECT_METHOD(' * space0 * C(name) * space0 * P',' * space0 * C(name) * space0 * P'*' * space0 * C(name) * space0 * P')' * space0 * P';'] = 
	function(prefix, fn, t, pn)
		return ('%s%s(State & state, %s * %s)'):format(prefix, fn, t, pn)
	end,
	-- method def w body
	[C(P'int' * space * (name * space)^0) * space0 * P'LOBJECT_METHOD(' * space0 * C(name) * space0 * P',' * space0 * C(name) * space0 * P'*' * space0 * C(name) * space0 * P')' * space0 * P'{' * (P' ' + P'\t')^0 * C(P'\n' + P'\n\r') * C(space0)] = 
	function(prefix, fn, t, pn, nl, tt)
		return ('%s%s(State & state, %s * %s) {%s%sStack * stack = state.stack;%s%s'):format(prefix, fn, t, pn, nl, tt, nl, tt)
	end,
	-- destructor def
	[P'void' * space * P'destructor(' * space0 * P'lutok::state' * space0 * P'&' * space0 * name * space0 * P',' * space0 * C(name) * space0 * P'*' * space0 * C(name) * space0 * P')'] =
	function(t, pn)
		return ('void destructor(State & state, %s * %s)'):format(t, pn)
	end,
	-- method implementation
	[C(P'int' * space * (name * space)^0) * space0 * 'LuaSDL::Lua_SDL_' * C(name) * P'::LOBJECT_METHOD(' * space0 * C(name) * space0 * P',' * space0 * C(name) * space0 * P'*' * space0 * C(name) * space0 * P')' * space0 * P'{' * (P' ' + P'\t')^0 * C(P'\n' + P'\n\r') * C(space0)] =
	function(prefix, n, fn, t, pn, nl, tt)
		return ('%s%s::%s(State & state, %s * %s) {%s%sStack * stack = state.stack;%s%s'):format(prefix, n, fn, t, pn, nl, tt, nl, tt)
	end,
	[P'LuaSDL::Lua_SDL_' * C(name) * space0 * P'&' * space0 * name * space0 * P'=' * space0 * P'LOBJECT_INSTANCE(LuaSDL::Lua_SDL_' * name * space0 * P')'] =
	function(n)
		return ('%s * interface%s = state.getInterface<%s>("LuaSDL_%s")'):format(n,n,n,n)
	end,
	[P'state.to_integer'] = 'stack->to<int>',
	[P'state.to_number'] = 'stack->to<LUA_NUMBER>',
	[P'state.to_boolean'] = 'stack->to<bool>',
	[P'state.to_lightuserdata'] = 'stack->to<void*>',
	[P'state.to_string'] = 'stack->to<const std::string>',
	[P'state.push_literal'] = 'stack->push<const std::string &>',
	[P'state.push_number'] = 'stack->push<LUA_NUMBER>',
	[P'state.push_integer'] = 'stack->push<int>',
	[P'state.push_boolean'] = 'stack->push<bool>',
	[P'state.push_lightuserdata'] = 'stack->push<void*>',
	[P'state.push_string'] = 'stack->push<const std::string &>',
	[P'state.obj_len'] = 'stack->objLen'
}))

--[[
for _, f in io.files('.', '%.cpp$') do
	print(f)
end
--]]

