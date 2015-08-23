local bit = require 'bit'
local SDL = require "LuaSDL2"

local function SDLmain(fn)
	assert(type(fn)=='function')
	SDL.init()
		fn()
	SDL.quit()
end

local function listControllers()
	local controllers = {}

	for index = 1, SDL.numJoysticks() do
	    local object
		if SDL.isGameController(index-1) then
			object = SDL.GameController(index-1)
		else
			object = SDL.Joystick(index-1)
		end
		table.insert(controllers, object)
	end
	return controllers
end

SDLmain(function()
	SDL.videoInit()

	local window = SDL.createWindow("Video test window", SDL.WINDOWPOS_CENTERED_MASK, SDL.WINDOWPOS_CENTERED_MASK, 640, 480, bit.bor(SDL.WINDOW_OPENGL, SDL.WINDOW_RESIZABLE))

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

	local C = listControllers()
	for k,v in pairs(C) do
		print(k, v.name, v.mapping)
	end

	local c = C[1]

	local timer = SDL.Timer(100, function()
		local left = {
			x = c.axis(SDL.CONTROLLER_AXIS_LEFTX),
			y = c.axis(SDL.CONTROLLER_AXIS_LEFTY),
		}
		local right = {
			x = c.axis(SDL.CONTROLLER_AXIS_RIGHTX),
			y = c.axis(SDL.CONTROLLER_AXIS_RIGHTY),
		}
		local trigger = {
			left = c.axis(SDL.CONTROLLER_AXIS_TRIGGERLEFT),
			right = c.axis(SDL.CONTROLLER_AXIS_TRIGGERRIGHT),
		}

		local button = {
			a = c.button(SDL.CONTROLLER_BUTTON_A),
			b = c.button(SDL.CONTROLLER_BUTTON_B),
			x = c.button(SDL.CONTROLLER_BUTTON_X),
			y = c.button(SDL.CONTROLLER_BUTTON_Y),

			back = c.button(SDL.CONTROLLER_BUTTON_BACK),
			guide = c.button(SDL.CONTROLLER_BUTTON_GUIDE),
			start = c.button(SDL.CONTROLLER_BUTTON_START),

			leftStick = c.button(SDL.CONTROLLER_BUTTON_LEFTSTICK),
			rightStick = c.button(SDL.CONTROLLER_BUTTON_RIGHTSTICK),

			leftShoulder = c.button(SDL.CONTROLLER_BUTTON_LEFTSHOULDER),
			rightShoulder = c.button(SDL.CONTROLLER_BUTTON_RIGHTSHOULDER),
			
			up = c.button(SDL.CONTROLLER_BUTTON_DPAD_UP),
			down = c.button(SDL.CONTROLLER_BUTTON_DPAD_DOWN),
			left = c.button(SDL.CONTROLLER_BUTTON_DPAD_LEFT),
			right = c.button(SDL.CONTROLLER_BUTTON_DPAD_RIGHT),
		}

		print(("L(%d, %d) R(%d, %d) S(%d, %d)"):format(left.x, left.y, right.x, right.y, trigger.left, trigger.right))
		print(("Buttons [A%dB%dX%dY%d] Back: %d Guide: %d Start: %d LStick: %d RStick: %d LShoulder: %d RShoulder: %d"):format(button.a, button.b, button.x, button.y, button.back, button.guide, button.start, button.leftStick, button.rightStick, button.leftShoulder, button.rightShoulder))
		print(("U%d D%d L%d R%d"):format(button.up, button.down, button.left, button.right))
		SDL.gameControllerUpdate()
	end)

	while running do
		local event = SDL.Event()
        while (SDL.pollEvent(event)) do
        	local e_fn = events[event.type]
        	if type(e_fn)=="function" then
        		e_fn(event)
        	end
       	end
	end

	timer.stop()
end)