-- Auto Generate by Excel 'System.xlsx', Don't try to modify!

local M = {}

M.Data = {}
M.Data['MainSys'] = {Lang = 100}
M.length = 1

function M.getData(key)
    return M.Data[key]
end

function M.getItem(key1, key2)
    if M.Data[key1] == nil then
        print(string.format("错误: 文件'System.lua'中配置'%s'不存在!!!!!!!!!!!!!!!!!!!!!!!", tostring(key1)))
        return
    end
    return M.Data[key1][key2]
end

function M.getAllData()
    return M.Data
end

return M
