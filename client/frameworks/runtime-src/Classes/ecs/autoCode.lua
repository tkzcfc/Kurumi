-- @Author : fangcheng
-- @Date   : 2021-01-28 17:14:43
-- @remark : 


require("lfs")

-- @brief 获取目录下所有文件
local function getAllFiles(_rootPath)
	local allFilePath = {}

	local function _getAllFiles(rootPath)
    	for entry in lfs.dir(rootPath) do
    	    if entry~='.' and entry~='..' then
    	        local path = rootPath .. "/" .. entry
    	        local attr = lfs.attributes(path)
    	        assert(type(attr)=="table") --如果获取不到属性表则报错
    	        if(attr.mode == "directory") then
    	            _getAllFiles(path) --自调用遍历子目录
    	        elseif attr.mode=="file" then
    	            attr.path = path
    	            allFilePath[#allFilePath + 1] = attr
    	        end
    	    end
    	end
	end

	_getAllFiles(_rootPath)

	return allFilePath
end

-- @brief 文件读取
function io.readfile(path)
    local file = io.open(path, "r")
    if file then
        local content = file:read("*a")
        io.close(file)
        return content
    end
    return nil
end

-- @brief 文件写入
function io.writefile(path, content, mode)
    mode = mode or "w+b"
    local file = io.open(path, mode)
    if file then
        if file:write(content) == nil then return false end
        io.close(file)
        return true
    else
        return false
    end
end

function table.merge(toTable, t2)
    for k,v in pairs(t2) do
        local contain = false
        for _,vv in pairs(toTable) do
            if v == vv then contain = true break end
        end
        if not contain then
            table.insert(toTable, v)
        end
    end
    return toTable
end

-- @brief 匹配class
-- @param str 文本内容
-- @param superName 匹配的class的父类
local function match_class(str, superName)
    str = string.gsub(str, "(:%s*)(public)(%s+)", ": ")
    local pattern = "class%s+(%w+)"
    if type(superName) == "string" and superName ~= "" then
        pattern = "class%s+(%w+)%s*:%s*%s+" .. superName
    end

    local t = {}
    for k in string.gmatch(str, pattern) do
        t[k] = true
    end

    local classes = {}
    for k,v in pairs(t) do
        table.insert(classes, k)
    end
    return classes
end

-- @brief 循环匹配class
local function match_class_loop(str, superName, classes)
    classes = classes or {}

    table.merge(classes, match_class(str, superName))

    if not superName or superName == "" then return classes end

    local supers = {}
    for k,v in pairs(classes) do
        table.insert(supers, v)
    end

    repeat
        local super = table.remove(supers)
        if super == nil then break end
        local tmp = match_class(str, super)
        for k,v in pairs(tmp) do
            local contain = false
            for _,cname in pairs(classes) do
                if v == cname then contain = true break end
            end
            if not contain then
                table.insert(classes, v)
                table.insert(supers, v)
            end
        end
    until(false)
    return classes
end

local function local_replace(content, text, patternB, patternE)
    local pattern = string.format("([ \t]*)%s(.*)%s", patternB, patternE)
    return string.gsub(content, pattern, function(indent)
        text = string.gsub(text, "^%s*", "")
        text = string.gsub(text, "\n[ \t]+", "\n")
        text = string.gsub(text, "%s*$", "")
        text = string.gsub(text, "\n", "\n" .. indent)

        patternB = string.gsub(patternB, "(//).-([%w_]*)$", "%1 %2")
        patternE = string.gsub(patternE, "(//).-([%w_]*)$", "%1 %2")

        local str = ""
        str = str .. indent .. patternB .. "\n"
        str = str .. indent .. text     .. "\n"
        str = str .. indent .. patternE .. "\n"
        return str
    end)
end

local function clsIncludePath(str)
    local pos = string.find(str, "%w")
    return string.sub(str, pos, -1)
end

local function isContainValue(t, value)
    for k,v in pairs(t) do
        if v == value then
            return true
        end
    end
end

local function doit(clientClass, svrClass)
    local files = getAllFiles("./")
    local contentCache = {}

    local function getFileContent(file)
        if contentCache[file] == nil then
            contentCache[file] = io.readfile(file)
        end
        return contentCache[file]
    end

    local function define_if(className)
        if isContainValue(clientClass, className) then
            return "#if G_TARGET_CLIENT\n"
        elseif isContainValue(svrClass, className) then
            return "#if G_TARGET_SERVER\n"
        end
        return ""
    end
    local function define_endif(className)
        if isContainValue(clientClass, className) then
            return "#endif\n"
        elseif isContainValue(svrClass, className) then
            return "#endif\n"
        end
        return ""
    end

    -- 获取所有class 和对应的文件路径
    local function getAllClass(superName)
        local classes = {}
        local fileSet = {}
        for _,file in pairs(files) do
            local content = getFileContent(file.path)
            local temp = match_class_loop(content, superName, classes)
            table.merge(classes, temp)

            for k,v in pairs(temp) do
                if fileSet[v] == nil then
                    fileSet[v] = file.path
                end
            end
        end
        return classes, fileSet
    end

    local comClasses, comfiles = getAllClass("BaseComponent")
    local sysClasses, sysfiles = getAllClass("anax::System")

    ------------------------------------- ECSDefine.h -------------------------------------
    -- 生成include代码
    local includeStr = ""
    local includeSet = {}
    for k,v in pairs(comfiles) do
        if includeSet[v] == nil then
            includeSet[v] = true
            includeStr = includeStr .. string.format("#include \"%s\"\n", clsIncludePath(v))
        end
    end
    for k,v in pairs(sysfiles) do
        if includeSet[v] == nil then
            includeSet[v] = true
            includeStr = includeStr .. string.format("#include \"%s\"\n", clsIncludePath(v))
        end
    end

    -- 生成定义代码
    local defineStr = ""
    for k,v in pairs(comClasses) do
        defineStr = defineStr .. define_if(v)
        defineStr = defineStr .. string.format("DEFINE_COMPONENT(%s)\n", v)
        defineStr = defineStr .. define_endif(v)
    end
    for k,v in pairs(sysClasses) do
        defineStr = defineStr .. define_if(v)
        defineStr = defineStr .. string.format("DEFINE_SYSTEM(%s)\n", v)
        defineStr = defineStr .. define_endif(v)
    end

    local content = io.readfile("./ECSDefine.h")
    content = local_replace(content, includeStr, "//%s*INCLUDE_BEGIN", "//%s*INCLUDE_END")
    content = local_replace(content, defineStr, "//%s*DEFINE_BEGIN", "//%s*DEFINE_END")

    -- 定义文件写入
    print("write ECSDefine.h", io.writefile("./ECSDefine.h", content, "wb"))


    ------------------------------------- anaxHelper.cpp ------------------------------------- 
    -- 生成实现代码
    local implementStr = ""
    for k,v in pairs(comClasses) do
        implementStr = implementStr .. define_if(v)
        implementStr = implementStr .. string.format("IMPLEMENTATION_COMPONENT(%s);\n", v)
        implementStr = implementStr .. define_endif(v)
    end
    for k,v in pairs(sysClasses) do
        implementStr = implementStr .. define_if(v)
        implementStr = implementStr .. string.format("IMPLEMENTATION_SYSTEM(%s);\n", v)
        implementStr = implementStr .. define_endif(v)
    end
    
    content = io.readfile("./anaxHelper.cpp")
    content = local_replace(content, implementStr, "//%s*IMPLEMENT_BEGIN", "//%s*IMPLEMENT_END")

    -- 定义文件写入
    print("write anaxHelper.cpp", io.writefile("./anaxHelper.cpp", content, "wb"))
end

local clientClass = {
    "ArmatureRenderSystem",
}
local svrClass = {
}
doit(clientClass, svrClass)
