-- Auto Generate by Excel 'language.xlsx', Don't try to modify!

local keyMap = { "cn", "en" }

local keyMapIndex = {}
for k, v in pairs(keyMap) do keyMapIndex[v] = k end

local D = {}
D[11001] = {"账号不存在是否注册","1.0"}
D[11002] = {"注册成功","1.0"}
D[11003] = {"登陆成功","1.0"}
D[11004] = {"连接服务器失败,是否重试","1.0"}
D[11005] = {"账号在其他地方登录","1.0"}
D[11006] = {"即将退出游戏,错误代码:%d","1.0"}
D[11007] = {"yun","1.0"}
D[11008] = {"zzz","1.0"}
D[20001] = {"未知错误,错误码:%d","1.0"}
D[20002] = {"请求失败,请稍后再试","1.0"}
D[20100] = {"账号不能为空","1.0"}
D[20101] = {"密码不能为空","1.0"}
D[20102] = {"密码超长","1.0"}
D[20103] = {"账号超长","1.0"}
D[20104] = {"密码含有非法字符","1.0"}
D[20105] = {"账号含有非法字符","1.0"}
D[20106] = {"密码错误","1.0"}
D[20107] = {"账号不存在","1.0"}
D[20108] = {"服务器列表拉取失败","1.0"}
D[20109] = {"服务器列表为空","1.0"}
D[20110] = {"没有找到玩家信息","1.0"}
D[20111] = {"有多个玩家信息","1.0"}
D[20112] = {"","1.0"}
D[20113] = {"","1.0"}
D[20114] = {"","1.0"}
D[20115] = {"","1.0"}
D[20116] = {"","1.0"}
D[20117] = {"","1.0"}
D[20118] = {"","1.0"}
D[20119] = {"","1.0"}
D[20120] = {"","1.0"}
D[20121] = {"","1.0"}
D[20122] = {"","1.0"}
D[20123] = {"","1.0"}
D[20124] = {"","1.0"}
D[20125] = {"","1.0"}
D[20126] = {"","1.0"}

local M = {}
M.Data = D
M.length = 37
M.keyMapIndex = keyMapIndex
M.keyMap = keyMap

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

return M