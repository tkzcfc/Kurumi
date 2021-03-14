-- @Author : fangcheng
-- @Date   : 2021-2-22 15:55:05
-- @remark : 自动填充motion内容

local function readFile(filename)
	local fd = io.open(filename, "rb")
	if not fd then return '' end
	local content = fd:read("*a")
	fd:close()
	return content
end

local function writeFile(filename, content)
	local fd = io.open(filename, "wb")
	if not fd then return false end
	local suc = fd:write(content)
	fd:close()
	return suc
end

local inJsonFile = "./animator.json"
local outJsonFile = "./animator_1.json"

local content = readFile(inJsonFile)

content = string.gsub(content, [["state":%s*"(.-)"(.-)"motion": "(.-)"]], [["state":"%1"%2"motion": "ANI_NAME_%1"]])

print("writeFile", outJsonFile, writeFile(outJsonFile, content))

