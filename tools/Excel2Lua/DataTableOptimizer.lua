-- @Author : fangcheng
-- @Date   : 2020-10-09 15:59:59
-- @remark : table表优化

-- 是否使用最小生成
local OPTIMIZATION_LEAST = true

---------------------------------------------- 功能函数 ----------------------------------------------

local function createFileWriter( fileName, mode )
	local file = nil
	local indent = 0
	if mode and fileName then
		local _file, err = io.open( fileName )
		if _file ~= nil then
			--print( "remove file "..fileName )
			os.remove( fileName )
		end
		file = io.open( fileName, mode )
	end
	local ret = nil
	if file then
		ret = {
			write = function( ... )
				if indent > 0 then
					for i = 0, indent - 1 do
						file:write( "\t" )
					end
				end
				return file:write( ... )
			end,
			close = function( ... )
				return file:close()
			end
		}
	else
		ret = {
			write = function( ... )
				for i = 0, indent - 1 do
					io.write( "\t" )
				end
				return io.write( ... )
			end,
			close = function( ... )
			end
		}
	end
	ret.indent = function( count )
		count = count or 1
		indent = indent + count or 1
	end
	ret.outdent = function( count )
		count = count or 1
		if indent >= count then
			indent = indent - count
		end
	end
	return ret
end

local function isIndexTable(t)
	if type(t) ~= "table" then
		return false
	end

	local count = 0
	for k,v in pairs(t) do
		if type(k) ~= "number" then return false end
		if k <= 0 then return false end
		if k > count then count = k end
	end
	return true, count
end

-- @brief "a/b/c/d.lua" -> "a.b.c.d"
local function clsLuaPath(filename)
	local inFile = string.gsub(filename, "[/\\]+", ".")
	inFile = string.gsub(inFile, "%.lua$", "")
	return inFile
end

local function read_file(filename)
    local f = io.open(filename, 'r')
    if not f then
    	print(string.format("Cannot open file '%s'", tostring(filename)))
    	return
    end
    local content = f:read("*all")
    f:close()
    return content
end

local function encodeEscapeString( s )
	local buf = {}
	buf[#buf + 1] = "\""
	string.gsub( s, ".",
		function ( c )
			if c == '\n' then
				buf[#buf + 1] = "\\n"
			elseif c == '\t' then
				buf[#buf + 1] = "\\t"
			elseif c == '\r' then
				buf[#buf + 1] = "\\r"
			elseif c == '\a' then
				buf[#buf + 1] = "\\a"
			elseif c == '\b' then
				buf[#buf + 1] = "\\b"
			elseif c == '\\' then
				buf[#buf + 1] = "\\\\"
			elseif c == '\"' then
				buf[#buf + 1] = "\\\""
			elseif c == '\'' then
				buf[#buf + 1] = "\\\'"
			elseif c == '\v' then
				buf[#buf + 1] = "\\\v"
			elseif c == '\f' then
				buf[#buf + 1] = "\\\f"
			else
				buf[#buf + 1] = c
			end
		end
	)
	buf[#buf + 1] = "\""
	return table.concat( buf, "" )
end

local table_insert = table.insert
-- @param autoIndent 是否自动缩进
local function format_lua_value_ex(tab, autoIndent)
    if type(tab) ~= "table" then
        return {tostring(tab)}
    end

    local lines = {}
   	table_insert(lines, "{")

    local function format_lua_table (lua_table, indent)
        indent = indent or 0
        local isIndexTab, tabCount = isIndexTable(lua_table)
        local lastIndex = 0
        
        local function walkTab(k, v)
			lastIndex = lastIndex + 1
            local szPrefix = ""
            if autoIndent then
            	szPrefix = string.rep("    ", indent)
            end

            if isIndexTab then
            	repeat
            		if lastIndex >= k then
            			break
            		end
            		table_insert(lines, szPrefix .. "nil,")
            		lastIndex = lastIndex + 1
            	until(false)
            end

            if type(v) == "table" then
            	if type(k) == "string" then
            		table_insert(lines, szPrefix .. k .. " = {")
            	else
            		if isIndexTab then
            			table_insert(lines, "{")
            		else
                		table_insert(lines, szPrefix .. "[" .. k .. "] = {")
                	end
            	end
				format_lua_table(v, indent + 1)
				table_insert(lines, szPrefix .. "},")
            else
				local szValue = ""
                if type(v) == "string" then
                    szValue = encodeEscapeString(v)
                else
                    szValue = tostring(v)
                end
            	if type(k) == "string" then
                	table_insert(lines, szPrefix .. k .. " = " .. szValue .. ",")
                else
            		if isIndexTab then
            			table_insert(lines, szPrefix .. szValue .. ",")
            		else
                		table_insert(lines, szPrefix .."[" .. k .. "] = " .. szValue .. ",")
                	end
            	end
            end
        end
        if isIndexTab then
        	for i = 1, tabCount do
        		walkTab(i, lua_table[i])
        	end
        else
        	for k, v in pairs(lua_table) do
        		walkTab(k, v)
        	end
    	end

	    if #lines > 0 then
	    	lines[#lines] = string.gsub(lines[#lines], ",$", "")
	    end
    end
    format_lua_table(tab, 1)

	table_insert(lines, "}")

    return lines
end

-- @brief 格式化lua变量
format_lua_value = function(tab)
	return table.concat( format_lua_value_ex(tab, true), "\n" )
end


local function curdir()
	local info = debug.getinfo(1, "S") -- 第二个参数 "S" 表示仅返回 source,short_src等字段， 其他还可以 "n", "f", "I", "L"等 返回不同的字段信息
	local path = info.source
	path = string.sub(path, 2, -1) -- 去掉开头的"@"
	path = string.gsub(path, "\\", "/")
	path = string.match(path, "^.*/") -- 捕获最后一个 "/" 之前的部分 就是我们最终要的目录部分
	return path
end

---------------------------------------------- 优化逻辑 ----------------------------------------------


-- @brief 执行优化
-- @param originTable 原始table表
-- @param 优化后输出文件
-- @param 输出文件顶部注释内容
function optimization_run(originTable, outFile, headNotes)
	local originTableLength = originTable.length
	
	local keyMap = {}
	local keyMapIndex = {}
	
	-- 获取所有key
	for k,v in pairs(originTable.Data) do
		local keyMap_tmp = {}
		local keyMapIndex_tmp = {}
		local count = 1
		for keyName, _ in pairs(v) do
			keyMap_tmp[count] = keyName
			keyMapIndex_tmp[keyName] = count
			count = count + 1
		end
	
		if #keyMap < #keyMap_tmp then
			keyMap = keyMap_tmp
			keyMapIndex = keyMapIndex_tmp
		end
	end
	table.sort(keyMap, function(a, b) return a < b end)
	for k,v in pairs(keyMap) do
		keyMapIndex[v] = k
	end
	
	local function walkData(func)
		for _,data in pairs(originTable.Data) do
			for keyName, value in pairs(data) do
				if func(keyName, value, data) then
					break
				end
			end
		end
	end
	
	-- 使用数字索引代替key
	local newData = {}
	for k,data in pairs(originTable.Data) do
		local copyData = {}
		for key,idx in pairs(keyMapIndex) do
			copyData[idx] = data[key]
		end
		newData[k] = copyData
	end
	originTable.Data = newData

	
	local handle = createFileWriter(outFile, "wb")
	
	if type(headNotes) == "string" and headNotes ~= "" then
		handle.write(headNotes)
		handle.write("\n\n")
	end

	handle.write("local keyMap = ")
	if OPTIMIZATION_LEAST then
		handle.write(table.concat( format_lua_value_ex(keyMap), " " ))
	else
		handle.write(format_lua_value(keyMap))
	end
	handle.write("\n\n")
	
	handle.write("local keyMapIndex = {}\n")
	handle.write("for k, v in pairs(keyMap) do keyMapIndex[v] = k end\n")

	
	handle.write("\nlocal D = {}\n")
	
	if OPTIMIZATION_LEAST then
		local datakeys = {}
		for k,v in pairs(originTable.Data) do
			table_insert(datakeys, k)
		end
		table.sort(datakeys, function(a, b) return a < b end)

		-- 保证每次输出顺序一致
		for i = 1, #datakeys do
			local k = datakeys[i]
			local v = originTable.Data[k]
			if type(k) == "number" then
				handle.write("D[" .. tostring(k) .. "] = ")
			else
				handle.write("D." .. tostring(k) .. " = ")
			end
			handle.write(table.concat( format_lua_value_ex(v), "" ))
			handle.write("\n")
		end
	else
		handle.write("D = ")
		handle.write(format_lua_value(originTable.Data))
	end
	
	handle.write("\nlocal M = {}")
	handle.write("\nM.Data = D")
	handle.write("\nM.length = ", originTableLength)
	handle.write("\nM.keyMapIndex = keyMapIndex")
	handle.write("\nM.keyMap = keyMap")
	handle.write("\n\n")

	handle.write([[
local meta = {
    __index = function(tab, key) return rawget(tab, keyMapIndex[key]) end
}
for k, v in pairs(M.Data) do setmetatable(v, meta) end

function M.getData(Id)
    local data = M.Data[Id]
    if not data then return end
    local t = {}
    for k, v in pairs(keyMapIndex) do t[k] = data[v] end
    return t
end

function M.getItem(Id, Key)
    local data = M.Data[Id]
    if data then return data[Key] end
    return nil
end

function M.getAllData()
    local dataList = {}
    for id, data in pairs(M.Data) do
        local t = {}
        for k, v in pairs(keyMapIndex) do t[k] = data[v] end
        dataList[k] = t
    end
    return dataList
end
]])
	
	handle.write("\nreturn M")
	handle.close()

	return keyMap
end

-- @brief 校验内容是否一致
local function check_content(oldFile, newFile)
	package.loaded[oldFile] = nil
	package.loaded[newFile] = nil
	local oldCont = require(oldFile)
	local newCont = require(newFile)

	local keyMap = newCont.keyMap

	for _,data in pairs(oldCont._Data) do
		local id = data.Id
		for _, key in pairs(keyMap) do
			if newCont.getItem(id, key) ~= oldCont.getItem(id, key) then
				print("error:", oldFile, id, key, oldCont.getItem(id, key), newCont.getItem(id, key))
			end
		end
	end
end

if arg[1] then
	-- 提取源文件顶部注释内容
	local content = read_file(arg[1]) or ""
	local headNotes = string.match(content, "^%-%-[^\n]*")

	-- 输入文件
	local inFile = clsLuaPath(arg[1])
	-- 输出文件
	local outFile = arg[2]
	
	-- 执行优化
	optimization_run(require(inFile), outFile, headNotes)

	-- 检查内容是否一致
	-- check_content(inFile, clsLuaPath(outFile))

	-- 代码格式化
	-- 	local exe = curdir() .. "lua-format/win32/lua-format.exe"
	-- 	local cmd = string.format("%s %q", exe, outFile)
	-- 	os.execute(cmd)
	-- end
end
