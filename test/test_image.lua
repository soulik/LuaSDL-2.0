require 'bit'
local SDL = require "LuaSDL2"


local function init()
	SDL.init()
	local formats = bit.bor(SDL.IMG_INIT_JPG, SDL.IMG_INIT_PNG, SDL.IMG_INIT_TIF, SDL.IMG_INIT_WEBP)
	local i = SDL.imageInit(formats)
	if bit.bxor(i, formats) ~= 0 then
		print(i, formats, bit.bxor(i, formats))
	end
end

local T = 0
local running = true
local events = {
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

local function run()
	local timer = SDL.Timer(1000, function()
		T = T + 1
		if (T > 4) then
			running = false
		end
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

local function quit()
	collectgarbage()
	SDL.imageQuit()
	SDL.quit()
end

init()
run()
quit()
