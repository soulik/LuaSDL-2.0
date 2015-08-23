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
	local haptic = c.joystick.haptic
	--haptic.rumbleInit()

	--haptic.rumblePlay(1, 1000)
	local iterations = 0
	local maxNumEffects = haptic.numEffects

	local effect1 = SDL.HapticEffect()
	effect1.type = SDL.HAPTIC_LEFTRIGHT
	effect1.largeMagnitude = 0xFFFF
	effect1.smallMagnitude = 0x0
	effect1.length = 5000

	local effectSupported = haptic.effectSupported(effect1)

	if (effectSupported) then
		if effect1.apply(haptic) then
			if not effect1.run(1) then
				print('Cannot run effect', SDL.getError())
			end
		else
			print('Cannot apply effect', SDL.getError())
		end
	end

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
		--[[
		print(("Is haptic: %s Effects: %d Effect supported: %s"):format(tostring(haptic), maxNumEffects, tostring(effectSupported)))
		print(("L(%d, %d) R(%d, %d) S(%d, %d)"):format(left.x, left.y, right.x, right.y, trigger.left, trigger.right))
		print(("Buttons [A%dB%dX%dY%d] Back: %d Guide: %d Start: %d LStick: %d RStick: %d LShoulder: %d RShoulder: %d"):format(button.a, button.b, button.x, button.y, button.back, button.guide, button.start, button.leftStick, button.rightStick, button.leftShoulder, button.rightShoulder))
		print(("U%d D%d L%d R%d"):format(button.up, button.down, button.left, button.right))
		--]]
		SDL.gameControllerUpdate()

		--haptic.rumblePlay((iterations % 101) / 100, 100)
		iterations = iterations + 1
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

	--haptic.rumbleStop()
	haptic = nil
	timer.stop()
	collectgarbage()
end)