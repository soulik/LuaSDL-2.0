require 'bit'
local SDL = require "LuaSDL"

SDL.init()
SDL.videoInit()

do
	local window = SDL.createWindow("Video test window", SDL.WINDOWPOS_CENTERED_MASK, SDL.WINDOWPOS_CENTERED_MASK, 640, 480, bit.bor(SDL.WINDOW_OPENGL, SDL.WINDOW_RESIZABLE))
	if window then
		window.title = "Test window title"

		local running = true
		while (running) do
			local event = SDL.Event()
	        while (SDL.pollEvent(event)) do
            	if ((event.type == SDL.QUIT) or (event.type == SDL.KEYDOWN)) then
                	running = false
                elseif (event.type == SDL.MOUSEMOTION) then
                	window.title = string.format("Test window title (%d, %d)", tonumber(event.mousemotion_x), tonumber(event.mousemotion_y))
            	end
        	end
		end
	end
end

SDL.quit()