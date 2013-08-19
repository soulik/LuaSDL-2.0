require 'bit'
local SDL = require "LuaSDL"

code1 = [[
	while(1) do
		local a = SDL.thread_receive("a1")
		io.write(a)
		io.write('.')
	end
]]  
code2 = [[
	while(1) do
		SDL.thread_send("a1","+")
	end
]]

SDL.init()

SDL.Thread(code1)
SDL.Thread(code2)

while (1) do
end

SDL.quit()
