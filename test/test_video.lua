require 'bit'
local SDL = require "LuaSDL2"

SDL.init()
SDL.videoInit()

do
	local window = SDL.createWindow("Video test window", SDL.WINDOWPOS_CENTERED_MASK, SDL.WINDOWPOS_CENTERED_MASK, 640, 480, bit.bor(SDL.WINDOW_OPENGL, SDL.WINDOW_RESIZABLE))
	if window then
		window.title = "Test window title"

		local running = true

		events = {
			[SDL.MOUSEMOTION] = function(event)
				window.title = string.format("Test window title (%d, %d)", tonumber(event.mousemotion_x), tonumber(event.mousemotion_y))
			end,
			[SDL.KEYDOWN] = function(event)
				local code = event.keyboard_keysym_sym
				if (code == SDL.K_ESCAPE) then
			    	running = false
			    end
			end,
			[SDL.QUIT] = function(event)
			    running = false
			end,
			[SDL.USEREVENT] = function(event)
				local fn = event.userevent_data1
				if type(fn)=="function" then
					fn()
				end
			end,
		}

		local T = 1
		local timer = SDL.Timer(1000, function()
			print(string.format("Timer: %d", T))
			T = T + 1
		end)

		while (running) do
			local event = SDL.Event()
	        while (SDL.pollEvent(event)) do
	        	local e_fn = events[event.type]
	        	if type(e_fn)=="function" then
	        		e_fn(event)
	        	end
        	end
		end
		timer.stop()
	end
end

SDL.quit()