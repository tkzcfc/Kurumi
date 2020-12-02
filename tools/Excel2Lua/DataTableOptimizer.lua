-- @Author : fangcheng
-- @Date   : 2020-10-09 15:59:59
-- @remark : table表优化

-- 是否优化key
local OPTIMIZATION_KEY = true
-- 是否提取默认值
local OPTIMIZATION_DEFAULT_VALUE = false
-- 是否使用最小生成
local OPTIMIZATION_LEAST = true

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
		count = count + 1
	end
	return count <= #t
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
        local isIndexTab = isIndexTable(lua_table)
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
        	for i = 1, #lua_table do
        		walkTab(i, lua_table[i])
        	end
        else
        	for k, v in pairs(lua_table) do
        		walkTab(k, v)
        	end
    	end
    end
    format_lua_table(tab, 1)

	table_insert(lines, "}")

    return lines
end

-- @brief 格式化lua变量(主要是table)
format_lua_value = function(tab)
	return table.concat( format_lua_value_ex(tab, true), "\n" )
end

format_lua_value_min = function(tab)
	return table.concat( format_lua_value_ex(tab, false), "" )
end


function optimization_run(originTable, outFile)
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
	
	local function walkData(func)
		for _,data in pairs(originTable.Data) do
			for keyName, value in pairs(data) do
				if func(keyName, value, data) then
					break
				end
			end
		end
	end
	
	-- 默认值提取
	local defaultValueSet = {}
	if OPTIMIZATION_DEFAULT_VALUE then
		-- 获取默认值
		local valueInfo = {}
		local keyCount = {}
		for k,key in pairs(keyMap) do
			walkData(function(curKey, curValue)
				if key == curKey then
					if not keyCount[key] then
						keyCount[key] = 1
					else
						keyCount[key] = keyCount[key] + 1
					end
		
					if type(curValue) ~= "table" then
						local uniqueKey = tostring(curValue)
						local info = valueInfo[key]
						if info == nil then
							info = {}
							info[uniqueKey] = {count = 1, value = curValue}
							valueInfo[key] = info
						else
							if info[uniqueKey] then
								info[uniqueKey].count = info[uniqueKey].count + 1
							else
								info[uniqueKey] = {count = 1, value = curValue}
							end
						end
					end
					return true
				end
			end)
		end
		
		-- 获取默认值
		for k,key in pairs(keyMap) do
			if keyCount[key] == originTableLength then
				local info = valueInfo[key]
				local maxValue, maxCount = 0, 0
			
				if info then
					for _, v in pairs(info) do
						if maxCount < v.count then
							maxCount = v.count
							maxValue = v.value
						end
					end
				end
			
				if maxCount > 1 then
					defaultValueSet[key] = maxValue
				end
			end
		end
		
		-- 删除默认值
		for k,v in pairs(defaultValueSet) do
			walkData(function(curKey, curValue, curTable)
				if curKey == k then
					if curValue == v then
						curTable[curKey] = nil
					end
					return true
				end
			end)
		end
	end
	
	if OPTIMIZATION_KEY then
		-- 使用数字代替key
		local newData = {}
		for k,data in pairs(originTable.Data) do
			local copyData = {}
			for keyName, value in pairs(data) do
				copyData[keyMapIndex[keyName]] = value
			end
			newData[k] = copyData
		end
		originTable.Data = newData
	end
	
	local handle = createFileWriter(outFile, "wb")
	
	if OPTIMIZATION_KEY then
		handle.write("local keyMap = ")
		handle.write(format_lua_value(keyMap))
		handle.write("\n\n")
		
		handle.write("local keyMapIndex = ")
		handle.write(format_lua_value(keyMapIndex))
		handle.write("\n\n")
	end
	
	if OPTIMIZATION_DEFAULT_VALUE then
		handle.write("local defaultValueSet = ")
		handle.write(format_lua_value(defaultValueSet))
		handle.write("\n\n")
	end
	
	
	handle.write("\nlocal M = {}\n")
	
	if OPTIMIZATION_LEAST then
		handle.write("\nM.Data = {}\n")
		for k,v in pairs(originTable.Data) do
			if type(k) == 'string' then
				handle.write("M.Data." .. tostring(k) .. " = ")
			else
				handle.write("M.Data[" .. tostring(k) .. "] = ")
			end
			handle.write(format_lua_value_min(v))
			handle.write("\n")
		end
	else
		handle.write("M.Data = ")
		handle.write(format_lua_value(originTable.Data))
	end
	
	handle.write("\nM.length = ", originTableLength)
	handle.write("\n")


	if OPTIMIZATION_KEY then

		handle.write("\nM.keyMapIndex = keyMapIndex")
		handle.write("\nM.keyMap = keyMap")
		handle.write("\n\n")

		if OPTIMIZATION_DEFAULT_VALUE then
			handle.write([[
local meta = {
    __index = function(tab, key)
        local r = rawget(tab, keyMapIndex[key])
        if r ~= nil then
        	return r
        end
        return defaultValueSet[key]
    end
}
for k,v in pairs(M.Data) do
    setmetatable(v, meta)
end]])
		else
			handle.write([[
local meta = {
    __index = function(tab, key)
        return rawget(tab, keyMapIndex[key])
    end
}
for k,v in pairs(M.Data) do
    setmetatable(v, meta)
end]])
		end
	else
		if OPTIMIZATION_DEFAULT_VALUE then
			handle.write([[
defaultValueSet.__index = defaultValueSet
for k,v in pairs(M.Data) do
	setmetatable(v, defaultValueSet)
end]])
		end
	end

	handle.write([[	
function M.getData(Id)
    local data = M.Data[Id]
    if not data then return end
    local t = {}
    for k, v in pairs(keyMapIndex) do
        t[k] = data[v]
    end
    return t
end

function M.getItem(Id, Key)
    local data = M.Data[Id]
    if data then return data[Key] end
    return nil
end

function M.getAllData()
    local dataList = {}
    for k,data in pairs(M.Data) do
        local t = {}
        for k, v in pairs(keyMapIndex) do
            t[k] = data[v]
        end
        dataList[k] = t
    end
    return dataList
end
	]])
	
	handle.write("\nreturn M")
	handle.close()

	return keyMap
end

local function curdir()
	local info = debug.getinfo(1, "S") -- 第二个参数 "S" 表示仅返回 source,short_src等字段， 其他还可以 "n", "f", "I", "L"等 返回不同的字段信息
	local path = info.source
	path = string.sub(path, 2, -1) -- 去掉开头的"@"
	path = string.gsub(path, "\\", "/")
	path = string.match(path, "^.*/") -- 捕获最后一个 "/" 之前的部分 就是我们最终要的目录部分
	return path
end

if arg[1] and arg[2] then
	-- 输入文件
	local inFile = string.gsub(arg[1], "[/\\]+", ".")
	inFile = string.gsub(inFile, "%.lua$", "")

	-- 输出文件
	local outFile = arg[2]
	
	-- 执行优化
	optimization_run(require(inFile), outFile)

	if not OPTIMIZATION_LEAST then
		local exe = curdir() .. "lua-format/win32/lua-format.exe"
		local cmd = string.format("%s %q", exe, outFile)
		os.execute(cmd)
	end
end
