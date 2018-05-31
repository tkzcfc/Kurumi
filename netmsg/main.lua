require "lfs"


local workRootPath = "netmsg"
local outpbDir = 
{
	"../server/server/netmsg/pb",
	"../client/res/netmsg/pb",
}

-----------------------------------------------------****-----------------------------------------------------
function check_last(p)
    if p == "" then
        return p
    end
    if p:sub(#p, #p + 1) == "/" then
        p = p:sub(1, #p - 1)
    end
    return p
end

function deldir(dirName)
	dirName = check_last(dirName)
	local cmd = [[if exist "]]..dirName..[[" ( rd /s /q "]]..dirName..[[")]]
	print("remove", dirName)
	os.execute(cmd)
end

function copydir(srcdir, desdir)
	srcdir = check_last(srcdir)
	desdir = check_last(desdir)
	local cmd = [[xcopy "]]..srcdir..[[" "]]..desdir..[[" /q /c /e /i]]
	print("copy", srcdir, "to", desdir)
	os.execute(cmd)
end

function mkdir(dir)
	dir = check_last(dir)
	print("create", dir)
	lfs.mkdir(dir)
end

function check(p)
    if p == "" then
        return p
    end
    if p:sub(#p, #p + 1) ~= "/" then
        p = p.."/"
    end
    return p
end

for i = 1, #outpbDir do
	if outpbDir[i] == "" then
		print("outpbDir["..i.."]=null")
		os.execute("pause")
		os.exit(0)
	end
	outpbDir[i] = check(outpbDir[i])
end

local pbDir = "pb"
deldir(pbDir)
mkdir(pbDir)

pbDir = check(pbDir)


--get filename  
function getFileName(str)  
    local idx = str:match(".+()%.%w+$")  
    if(idx) then  
        return str:sub(1, idx-1)  
    else  
        return str  
    end  
end  

--get file postfix  
local function getExtension(str)  
    return str:match(".+%.(%w+)$")  
end  

local curPath = lfs.currentdir().."/"
local fileList = {}
local fileDirList = {}
  
local function changeFile(rootpath)  
    for entry in lfs.dir(rootpath) do  
        if entry ~= '.' and entry ~= '..' then  
            local path = rootpath .. '/' .. entry  
            local attr = lfs.attributes(path)  
            if attr.mode ~= 'directory' then
                local postfix = getExtension(entry)
                if postfix == "proto" then

                    local cmd = "--descriptor_set_out "

                    --proto文件相对路径
                    local pf = string.sub(path, string.len(curPath) + 1, string.len(path))
                    pf = string.sub(pf, 2, string.len(pf))

                    local r = "proto"
                    local p = string.sub(pf, 1, #r)
                    if p == r then
                        p = string.sub(pf, #r + 2, #pf + 1)
                    end
                    local t = getFileName(entry)..".pb"
                    p = string.gsub(p, entry, t)

                    local d = string.gsub(p, t, "")
                    
                    if d ~= "" then
                        d = pbDir..d
                        if not fileDirList[d] then
                            if not lfs.mkdir(d) then
                                print("create directory "..d.." fail")
                                os.execute("pause")
                                os.exit(0)
                            end
                        else
                            fileDirList[d] = true
                            -- print("create", d)
                        end
                    end

                    print(pf, "->", pbDir .. p)

                    cmd = cmd .. pbDir .. p .." "
                    cmd = cmd .. pf
                    cmd = "protoc.exe " .. cmd
                    -- print(cmd)
                    local r = os.execute(cmd)
                    if r ~= 0 then
                       print("fail")
                       os.execute("pause")
                       os.exit(0)
                    end

                    table.insert(fileList, p)
                end
            else  
                changeFile(path)  
            end  
        end  
    end  
end  

changeFile(curPath)

function writefile(path, content, mode)
    mode = mode or "wb+"
    local file = io.open(path, mode)
    if file then
        if file:write(content) == nil then return false end
        io.close(file)
        return true
    end
    return false
end

local script = "local M = {}\n"
for i = 1, #fileList do
    script = script .. string.format("M[%d] = \"%s\"\n", i, workRootPath..pbDir..tostring(fileList[i]))
end
script = script .. "return M"

if writefile(pbDir.."msglist.lua", script, "wb") then
    print("finish")
else
    print("write error")
end

print("\n\n")
for i = 1, #outpbDir do
	deldir(outpbDir[i])
	--mkdir(outpbDir[i])
	copydir(pbDir, outpbDir[i])
	print("------------------------------------------------------\n\n")
end

print("--------------------------end----------------------------")
-----------------------------------------------------****-----------------------------------------------------
