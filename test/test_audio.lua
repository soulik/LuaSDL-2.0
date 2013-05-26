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
	audio_spec.channels = 2
	audio_spec.samples = 4096
	audio_spec.padding = 0

	return SDL.AudioDevice(default_device or "test.raw", false, audio_spec)
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

	local function generateTone(pos, length, n, phase, amplitude)
		local fmod = function(n, d)
			return n-math.floor(n/d)*d
		end

		local buffer = audio_device.buffer
		local audiospec = audio_device.audioSpec
		local channels = audiospec.channels
		local tone = (440/12)
		local freq = 440 + (tone*n)
		local pi2 = 2*math.pi
		local factor = freq*(pi2/(audiospec.freq))
		local amplitude = amplitude or 12000
		local phase = phase or 0
		local lphase
		local total_len = length*(audiospec.freq/1000)*channels
		if pos + total_len >= buffer.size - pos - channels then
			pos = buffer.size - pos - channels
		end

		local last_pos = 0

		for i=0, total_len-1 do
			lphase = fmod(phase+i*(factor), pi2)
			local value = math.floor(
				math.sin(
					lphase
				)*amplitude
			)
			if channels>1 then
				for j=0, channels-1 do
					last_pos = pos + i*channels + j
					buffer.setData(last_pos, value)
					--print(string.format("N: %d, Ch: %d, Pos: %d", n, j, last_pos))
				end
			else
				last_pos = pos + i
				buffer.setData(last_pos, value)
			end
		end
		return last_pos+1, fmod(lphase, pi2)--math.fmod(lphase, pi2)
	end

	local function prepareAudioBuffer()
		local buffer = audio_device.buffer

		audio_device.lock()
		io.write("generating...")
		local prev_pos, prev_phase = 0, 0
		local T2 = {0, 2, 4, 5, 7, 9, 11, 12}
		for T=1,8 do
			prev_pos, prev_phase = generateTone(prev_pos, 250, T2[T] or 0, prev_phase)
		end
		io.write(string.format("done (%d/%d elements)\n", prev_pos, buffer.size))
		audio_device.unlock()
	end

	if audio_device then
		local buffer = audio_device.buffer

		local audiospec = audio_device.audioSpec
		buffer.size = 1024*1024--81920
		buffer.format = SDL.AUDIO_S16LSB
		buffer.clear()

		prepareAudioBuffer()

		local T = 0
		local timer = SDL.Timer(500, function()
			T = T + 1
			if (T > 8) then
				running = false
			else
				print(T)
			end
		end)

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
local quit_error = SDL.quit()
if quit_error then
	print(quit_error)
end