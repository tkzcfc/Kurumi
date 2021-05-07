-- Auto Generate by Excel 'Emoji.xlsx', Don't try to modify!

local M = {}

M.Data = {}
M.Data[1] = {Emoji = 'bang test\'hahaha\'\n\n', First = 1, Last = 4, Time = 0.32, Color = {255,255,0,100}}
M.Data[2] = {Emoji = 'cry', First = 1, Last = 16, Time = 1.28, Color = {255,255,0,100}}
M.Data[3] = {Emoji = 'nu', First = 1, Last = 2, Time = 0.16, Color = {255,255,0,100}}
M.Data[4] = {Emoji = 'xiao', First = 1, Last = 4, Time = 0.32, Color = {255,255,0,100}}
M.Data[5] = {Emoji = 'xihuan', First = 1, Last = 4, Time = 0.32, Color = {255,255,0,100}}
M.Data[6] = {Emoji = 'han', First = 1, Last = 9, Time = 0.72, Color = {255,255,0,100}}
M.Data[7] = {Emoji = 'yun', First = 1, Last = 6, Time = 0.48, Color = {255,255,0,100}}
M.Data[8] = {Emoji = 'zzz', First = 1, Last = 10, Time = 0.8, Color = {255,255,0,100}}
M.length = 8

function M.getData(key)
    return M.Data[key]
end

function M.getItem(key1, key2)
    if M.Data[key1] == nil then
        print(string.format("错误: 文件'Emoji.lua'中配置'%s'不存在!!!!!!!!!!!!!!!!!!!!!!!", tostring(key1)))
        return
    end
    return M.Data[key1][key2]
end

function M.getAllData()
    return M.Data
end

return M
