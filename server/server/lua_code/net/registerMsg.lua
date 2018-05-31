require "lfs"
require "lua_code.net.protobuf"

print("----------------------------------------------")

local msglist = require("netmsg.pb.msglist")
for i = 1, #msglist do
    print("register msg file: ", msglist[i])
    protobuf.register_file(msglist[i])
end

print("----------------------------------------------")
print("\n\n")

-- local allMsgFile = {}

-- --get filename  
-- local function getFileName(str)  
--     local idx = str:match(".+()%.%w+$")  
--     if(idx) then  
--         return str:sub(1, idx-1)  
--     else  
--         return str  
--     end  
-- end  
  
-- --get file postfix  
-- local function getExtension(str)  
--     return str:match(".+%.(%w+)$")  
-- end  
  
-- local function findMsgFile(rootpath)  
--     for entry in lfs.dir(rootpath) do  
--         if entry ~= '.' and entry ~= '..' then  
--             local path = rootpath .. '\\' .. entry  
--             local attr = lfs.attributes(path)

--             if attr then  
--                 if attr.mode ~= 'directory' then
--                     local postfix = getExtension(entry)
--                     if postfix == "pb" then
--                         allMsgFile[path] = true
--                         --print(path)
--                     end
--                 else  
--                     findMsgFile(path)  
--                 end  
--             end
--         end  
--     end  
-- end  

-- findMsgFile("src")

-- for k, v in pairs(allMsgFile) do
--     print("register msg file: ", k)
--     protobuf.register_file(k)
-- end
