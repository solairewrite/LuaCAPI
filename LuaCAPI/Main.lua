--注意前面加";"
--package.cpath = package.cpath .. ";D:/Learn/LuaCAPI/x64/Debug/?.dll"
package.cpath = package.cpath .. ";../x64/Debug/?.dll"

print("sola akuya megumin")

--如何导出带.的多级结构?
local LuaCAPI = require "LuaCAPI"
--LuaCAPI.func1()

--local v1, v2 = LuaCAPI.func2(1, 2)
--print(v1)
--print(v2)

local parts = { LuaCAPI.string_split("Hello, Lua C API", " ", 2) }
print(#parts) --> 2
for i = 1, #parts do
    print(parts[i])
end