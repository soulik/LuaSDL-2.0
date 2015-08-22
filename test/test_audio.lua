require 'bit'
local SDL = require "LuaSDL2"

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
	SDL.audioInit("xaudio2");
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

	local function generateTone(t, pos, length, n, phase, amplitude, maxsize)
		local fmod = function(n, d)
			return n-math.floor(n/d)*d
		end

		local intFreq = function(i)
			local base_freq = 263.63
			local intervals = {
				[0]=1, 25/24, 9/8, 6/5, 5/4, 4/3, 45/32, 3/2, 8/5, 5/3, 9/5, 15/8
			}
			local ni = math.floor(i/12)+1
			local mi = i%12
			local int = intervals[mi]
			return base_freq*int*ni
		end

		local audiospec = audio_device.audioSpec
		local channels = audiospec.channels
		local pi2 = 2*math.pi
		local factor = intFreq(n)*(pi2/(audiospec.freq))
		local amplitude = amplitude or 12000
		local phase = phase or 0
		local lphase
		local total_len = length*(audiospec.freq/1000)*channels

		if type(maxsize)=="number" then
			if pos + total_len >= maxsize - pos - channels then
				pos = maxsize - pos - channels
			end
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
					t[(last_pos+1)] = value
				end
			else
				last_pos = pos + i
				t[(last_pos+1)] = value
			end
		end
		return last_pos+1, fmod(lphase, pi2)
	end

	local function prepareAudioBuffer()
		local buffer = audio_device.buffer

		audio_device.lock()
		io.write("generating...")
		local prev_pos, prev_phase = 0, 0
		local scales = {
			full = {0, 2, 4, 5, 7, 9, 11, 12},
		}
		local t = {}
		for i, n in ipairs(scales.full) do
			prev_pos, prev_phase = generateTone(t, prev_pos, 250, n, prev_phase)
		end
		buffer.setData(t)
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

local ret = SDL.init()
if not ret then
    print(SDL.getError())
end
main()

-- This is because of a bug in SDL_malloc/SDL_free on fake_buffer with Disk audio driver! There's something fishy going on SDL_CloseAudio.
local quit_error = SDL.quit()
if quit_error then
	print(quit_error)
end