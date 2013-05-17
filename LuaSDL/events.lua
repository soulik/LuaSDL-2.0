local cpp_template = [[
		int inline LOBJECT_METHOD({{get_name}}, SDL_Event * event){
			
			return 1;
		}
		int inline LOBJECT_METHOD({{set_name}}, SDL_Event * event){
			
			return 0;
		}
]]
local function template(src, vars)
	return (string.gsub(src, "{{([^}]+)}}", vars))
end

local f = io.open("events.txt","r")
if f then
	for line in f:lines() do
		local get_name, set_name = string.match(line, [[%s*"[%w_]+",%s*([%w_]+),%s*([%w_]+)]])
		if get_name and set_name then
			print(template(cpp_template, {
				get_name = get_name,
				set_name = set_name,
			}))
		end
	end
	--"window_windowID", getWindow_windowID, setWindow_windowID);
end
