LuaSDL-2.0
===============

Lua binding for libSDL 2.0

Dependencies
------------

- lua 5.1.x or luajit 2.x.x (prefered)
- libSDL 2.x.x
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
- Querying SDL Version 1/8

### VIDEO
- Display and Window Management 54/66
- 2D Accelerated Rendering 0/42
- Pixel Formats and Conversion Routines 0/14
- Rectangle Functions 6/7
- Surface Creation and Simple Drawing 1/33
- Platform-specific Window Management 0/1
- Clipboard Handling 3/3

### INPUT EVENTS
- Event Handling
- Keyboard Support
- Mouse Support
- Joystick Support
- Game Controller Support

Notes
-------------

This project makes a use of modified version of "Lutok - Lightweight C++ API for Lua" - available at: https://code.google.com/p/lutok/
C++ Class wrapper "LObject" was inspired by "Luna Five" wrapper - available at: http://lua-users.org/wiki/LunaFive

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
