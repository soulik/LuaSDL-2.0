require 'bit'
local SDL = require "LuaSDL"

SDL.init()
SDL.videoInit()

do
	local window = SDL.createWindow("Video test window", SDL.WINDOWPOS_CENTERED_MASK, SDL.WINDOWPOS_CENTERED_MASK, 640, 480, bit.bor(SDL.WINDOW_OPENGL, SDL.WINDOW_RESIZABLE))
	if window then
		window.title = "Test window title"
		io.read()
	end
end

SDL.quit()