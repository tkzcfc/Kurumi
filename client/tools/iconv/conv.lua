-- @Author : fc
-- @Date   : 2021-11-19 10:56:29
-- @remark : 编码转换

local helper = require("helper")

-- 输入目录
local inDir = lfs.currentdir() .. "/../../kurumi/frameworks/runtime-src/Classes"
-- local inDir = lfs.currentdir() .. "/Classes"

local cacheFile = lfs.currentdir() .. "/cache.txt"
local tmpFile = lfs.currentdir() .. "/tmp.txt"

local iconv = lfs.currentdir() .. "\\iconv.exe"
local bom = lfs.currentdir() .. "\\AddBOM_d.exe"
local code_conv = lfs.currentdir() .. "\\CodeConv_d.exe"



local files = {}
helper.lookup_files(inDir, files)



function os.capture(cmd, raw) 
    local f = assert(io.popen(cmd, 'r')) 
    local s = assert(f:read('*a')) 
    f:close() 
    if raw then return s end 
    s = string.gsub(s, '^%s+', '') 
    s = string.gsub(s, '%s+$', '') 
    s = string.gsub(s, '[\n\r]+', ' ') 
    return s 
end



local function convert(tcode, USE_BOM)
    for k,v in pairs(files) do
        helper.remove_file(tmpFile)
        helper.remove_file(cacheFile)

        helper.file_copy(v, cacheFile)

        local ext = helper.file_extension(v)
        if ext == "h" or ext == "cpp" then

            local ok = false

            -- 获取当前文件编码
            local out = os.capture(string.format("%s %s", code_conv, v))
            local fileCode = string.match(out, "code:(.+)")

            -- 编码获取失败
            if fileCode == nil or fileCode == "" or fileCode == "unknown" then
                if helper.file_length(v) > 0 then
                    print("unknown code:", v)
                end
            else
                -- 文件编码
                fileCode = string.lower(fileCode)

                -- 编码不一致
                if fileCode ~= tcode then
                    -- 删除bom
                    os.execute(string.format("%s -r %s", bom, cacheFile))
                
                    -- 编码转换
                    local cmd = string.format("%s -f %s -t %s %s > %s", iconv, fileCode, tcode, cacheFile, tmpFile)
                    os.execute(cmd)

                    print(string.format("%s -f %s -t %s", iconv, fileCode, tcode))


                    -- 检测转码是否成功
                    ok = true
                    local oldSize = helper.file_length(cacheFile)
                    local newSize = helper.file_length(tmpFile)
                    if oldSize > 0 then
                        if newSize == 0 or newSize < oldSize * 0.5 then
                            print(string.format("conversion of file '%s' failed", v))
                            ok = false
                        end
                    end

                    -- 输出文件替换到源文件
                    if ok then
                        helper.remove_file(v)
                        os.rename(tmpFile, v)
                    end
                else
                    -- 都为utf-8,并且输出编码不带头
                    if tcode == "utf-8" and not USE_BOM then
                        -- 删除bom
                        os.execute(string.format("%s -r %s", bom, v))
                    end
                end

                -- 添加bom
                if ok and tcode == "utf-8" and USE_BOM then
                    os.execute(string.format("%s -a %s", bom, v))
                end
            end
        end
    end

    helper.remove_file(tmpFile)
    helper.remove_file(cacheFile)
end


-- 目标编码
local tcode = "utf-8"
-- utf-8带BOM
local USE_BOM = true

convert(tcode, USE_BOM)
