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

SDL.init()
--SDL.audioInit("disk");

print("drivers")
local t1 = SDL.getAudioDrivers()

dprint(t1, function(a,v)
	print(v.id, v.name)
end)
print("Using driver: ",SDL.getCurrentAudioDriver())

print("devices",SDL.getNumAudioDevices())
local t2 = SDL.getAudioDevices()
dprint(t2, function(dtype,devices)
	print(dtype, devices)
	dprint(devices, function(a,v)
		print(v.id, v.name)
		--print(a,v)
	end)
end)

SDL.quit()
