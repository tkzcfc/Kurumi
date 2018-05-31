require "lfs"

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
function getExtension(str)  
    return str:match(".+%.(%w+)$")  
end  
  
  
function fun(rootpath)  
    for entry in lfs.dir(rootpath) do  
        if entry ~= '.' and entry ~= '..' then  
            local path = rootpath .. '\\' .. entry  
            local attr = lfs.attributes(path)  
            print(path)  
            local filename = getFileName(entry)  
  
            if attr.mode ~= 'directory' then  
                local postfix = getExtension(entry)  
                print(filename .. '\t' .. attr.mode .. '\t' .. postfix)  
            else  
                print(filename .. '\t' .. attr.mode)  
                fun(path)  
            end  
        end  
    end  
end  
  
  
fun([[C:\Users\HSJ\Desktop\pbcTest\pbcTest\lua_code]])  