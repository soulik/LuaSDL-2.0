LuaSDL-2.0
===============

Lua binding for libSDL 2.0

Dependencies
------------

- lua 5.1.x or luajit 2.x.x (prefered)
- libSDL2 2.x.x
- libSDL2_mixer 2.x.x
- libSDL2_image 2.x.x
- libSDL2_ttf 2.x.x
- compiler with C++11 support

Only MS Visual C++ 2012 project files are present at the moment.

What works
-------------

### BASIC
- Initialization and Shutdown 5/5
- Configuration Variables 4/4
- Error Handling 3/3
- Log Handling 5/15
- Assertions 0/7
- Querying SDL Version 1/8 - everything is bundled in one table

### VIDEO
- Display and Window Management 53/66
- 2D Accelerated Rendering 42/42
- Pixel Formats and Conversion Routines 7/14
- Rectangle Functions 6/7
- Surface Creation and Simple Drawing 22/33
- Platform-specific Window Management 1/1
- Clipboard Handling 3/3
- Events, timers

### INPUT EVENTS
- Event Handling 8/18
- Keyboard Support 14/14
- Mouse Support 12/12
- Joystick Support 15/17
- Game Controller Support 6/6

### TIMERS EVENTS
- Timer Support 6/6

### AUDIO
- Audio Device Management, Playing and Recording 14/27

### SDL2_mixer
- Everthing except loading functions with SDL_RWops

### SDL2_image
- Everthing except loading functions with SDL_RWops

### SDL2_ttf
- Everthing except loading functions with SDL_RWops

Credits
-------------

This project makes a use of modified version of "Lutok - Lightweight C++ API for Lua" - available at: https://code.google.com/p/lutok/
C++ Class wrapper "LObject" was inspired by "Luna Five" wrapper - available at: http://lua-users.org/wiki/LunaFive

- Stephane Peter and Ryan Gordon - SDL2_mixer
- Mattias Engdegård - SDL2_image
- Sam Lantinga - SDL2_mixer, SDL2_image, SDL2_ttf

License
-------------

The MIT License (MIT)

Copyright (c) 2013 Mário Kašuba

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
