require 'bit'
local SDL = require "LuaSDL"


local function init()
	SDL.init()
	local formats = bit.bor(SDL.MIX_INIT_MP3, SDL.MIX_INIT_OGG, SDL.MIX_INIT_MODPLUG)
	local i = SDL.mixerInit(formats)
	if bit.bxor(i, formats) ~= 0 then
		print(i, formats, bit.bxor(i, formats))
	end
	assert(SDL.mixerOpenAudio())
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
	local chunk1, chunk2, mus1
	local timer = SDL.Timer(1000, function()
		T = T + 1
		if (T > 4) then
			running = false
		end
	end)

	chunk1 = SDL.mixerLoadWAV([[./SH1AT310.WAV]])
	if not chunk1 then
		print(SDL.mixerGetError())
	end
	chunk2 = SDL.mixerLoadWAV([[./SH1AT312.WAV]])
	if not chunk2 then
		print(SDL.mixerGetError())
	end
	mus1 = SDL.mixerLoadMUS([[dead again.mp3]])
	if not mus1 then
		print(SDL.mixerGetError())
	end

	SDL.mixerSetPanning(1, 25, 5)
	SDL.mixerSetPanning(2, 5, 25)
	chunk1.play(1)
	chunk2.play(2)
	mus1.play()

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

	SDL.mixerHaltChannel()
	SDL.mixerHaltMusic()
end

local function quit()
	collectgarbage()
	SDL.mixerCloseAudio()
	SDL.quit()
end

init()
run()
quit()
