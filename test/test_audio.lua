require 'bit'
local SDL = require "LuaSDL"

local function dprint(a, f)
	local f = f or print
	if type(f)=="function" then
		if type(a)=="table" then
			for k,v in pairs(a) do
				f(k,v)
			end
		else
			f(a)
		end
	else
		print(a, f)
	end
end

local function initAudio()
	--SDL.audioInit("disk");
	print("drivers")
	local t1 = SDL.getAudioDrivers()
	dprint(t1, function(a,v)
		print(v.id, v.name)
	end)
	print("Using driver: ",SDL.getCurrentAudioDriver())
	local default_device

	print("devices",SDL.getNumAudioDevices())
	local t2 = SDL.getAudioDevices()
	dprint(t2, function(dtype,devices)
		print(dtype)
		dprint(devices, function(a,v)
			if type(v.name)=="string" and not default_device then
				default_device = v.name
			end
			print(v.id, v.name)
			--print(a,v)
		end)
	end)
	print("Using device: ", default_device)
	
	local audio_spec = SDL.AudioSpec()
	audio_spec.freq = 44100
	audio_spec.format = SDL.AUDIO_S16LSB
	audio_spec.channels = 1
	audio_spec.samples = 4096
	audio_spec.padding = 0

	return SDL.AudioDevice(default_device, false, audio_spec)
end

local function main()
	local running = true
	events = {
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

	local audio_device = initAudio()
	local function generateTone(n, amplitude)
		local buffer = audio_device.buffer
		local audiospec = audio_device.audioSpec
		local tone = (440/12)
		local freq = 440 + (tone*n)
		local factor = (buffer.size/audiospec.freq)*freq
		local amplitude = amplitude or 12000
		local factor2 = (2*math.pi)/buffer.size

		for i=0,buffer.size-1 do
			local value = math.floor(
				math.sin(
					i*factor*factor2
				)*amplitude
			)
			buffer.setData(i, value)
		end
	end

	if audio_device then
		local buffer = audio_device.buffer
		local audiospec = audio_device.audioSpec
		buffer.size = 8192
		buffer.format = SDL.AUDIO_S16LSB
		buffer.clear()

		local T = 1
		local timer = SDL.Timer(1000, function()
			print(string.format("Timer: %d", T))
			T = T + 1
			if (T >= 12) then
				running = false
			else
				audio_device.lock()
				generateTone(T)
				audio_device.unlock()
			end
		end)
		generateTone(0)

		audio_device.play()
		while (running) do
			local event = SDL.Event()
			while (SDL.pollEvent(event)) do
		       	local e_fn = events[event.type]
		       	if type(e_fn)=="function" then
		    		e_fn(event)
		        end
	        end
		end
		audio_device.pause()
		timer.stop()
	else
		print(SDL.getError())
	end
end

SDL.init()
main()
SDL.quit()
