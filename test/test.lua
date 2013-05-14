local SDL = require "LuaSDL"

SDL.init()
SDL.videoInit()
local dm = SDL.getDisplayModes()
for d_id, display in pairs(dm) do
	print(string.format("Display #%d",d_id))
	print(string.format("Bounds: (%d, %d, %d, %d)", display.bounds.x, display.bounds.y, display.bounds.w, display.bounds.h))
	print("Modes:")
	for mode_id, mode in ipairs(display.modes) do
		print(string.format("Mode #%d - %dx%d - %s %dHz", mode_id, mode.w, mode.h, SDL.getPixelFormatName(mode.format), mode.refreshRate))
	end
end
print(SDL.getError())
SDL.quit()