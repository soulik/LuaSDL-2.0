require 'bit'
local SDL = require "LuaSDL"

local t1,t2 = SDL.test()

for _,t in ipairs({t1,t2}) do
	print(t)
	print(t.value)
	t.value = "blah"
	print(t.method("12342342345"))
end