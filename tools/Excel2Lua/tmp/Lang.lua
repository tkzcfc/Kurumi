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
D[20112] = {"令牌已过期,请重新登录","1.0"}
D[20113] = {"职业未开放","1.0"}
D[20114] = {"请输入昵称","1.0"}
D[20115] = {"昵称过短","1.0"}
D[20116] = {"昵称过长","1.0"}
D[20117] = {"昵称含有非法字符","1.0"}
D[20118] = {"战斗服连接失败","1.0"}
D[20119] = {"","1.0"}
D[20120] = {"","1.0"}
D[20121] = {"","1.0"}
D[20122] = {"","1.0"}
D[20123] = {"","1.0"}
D[20124] = {"","1.0"}
D[20125] = {"","1.0"}
D[20126] = {"","1.0"}
D[100001] = {"未知错误",""}
D[100002] = {"找不到对应目标",""}
D[100003] = {"该目标已过期",""}
D[100004] = {"目标已存在",""}
D[100005] = {"服务器内部错误",""}
D[100006] = {"token错误",""}
D[100007] = {"职业不存在",""}
D[100100] = {"内存不足",""}
D[100101] = {"服务器过载",""}
D[100102] = {"参数错误",""}
D[100200] = {"昵称字符串过短",""}
D[100201] = {"昵称字符串过长",""}
D[100202] = {"昵称字符串含有非法字符",""}
D[100203] = {"昵称重复",""}
D[200000] = {"账号不存在",""}
D[200001] = {"密码错误",""}
D[200002] = {"角色不存在",""}
D[200100] = {"网关连接失败",""}
D[210000] = {"找不到战斗ID",""}
D[210001] = {"服务端战斗初始化失败",""}
D[210002] = {"服务端战斗找不到对应玩家",""}
D[210003] = {"此玩家已经在战斗中",""}
D[210004] = {"玩家数量过多",""}
D[210005] = {"玩家ID有重复的",""}
D[210006] = {"玩家被踢出游戏",""}
D[210007] = {"客户端帧数有问题",""}
D[210008] = {"服务端操作记录无法追溯到对应帧",""}
D[210100] = {"战斗服繁忙",""}
D[210101] = {"游戏服没有可分配的战斗服",""}
D[210102] = {"战斗服不存在",""}
D[220001] = {"玩家登录游戏服时,服务器查询到该账号有多个玩家信息",""}
D[220002] = {"玩家断线重连,服务器让客户端进入登录界面重新登录",""}
D[220003] = {"找不到对应玩家数据",""}
D[220010] = {"退出游戏,此账号在其他地方被人登录",""}
D[220011] = {"退出游戏,客户端与服务器连接中断",""}
D[220012] = {"退出游戏,客户端主动请求退出游戏",""}
D[220030] = {"pvp匹配中",""}
D[220031] = {"pvp匹配超时",""}
D[220032] = {"pvp匹配成功",""}
D[220033] = {"pvp匹配成功后没有战斗服分配",""}
D[220034] = {"pvp匹配成功后对手取消战斗",""}

local M = {}
M.Data = D
M.length = 78
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