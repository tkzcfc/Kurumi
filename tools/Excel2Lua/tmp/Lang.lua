-- Auto Generate by Excel 'language.xlsx', Don't try to modify!

local M = {}

M.Data = {}
M.Data[11001] = {cn = '账号不存在是否注册', en = '1.0'}
M.Data[11002] = {cn = '注册成功', en = '1.0'}
M.Data[11003] = {cn = '登陆成功', en = '1.0'}
M.Data[11004] = {cn = '连接服务器失败,是否重试', en = '1.0'}
M.Data[11005] = {cn = '账号在其他地方登录', en = '1.0'}
M.Data[11006] = {cn = '即将退出游戏,错误代码:%d', en = '1.0'}
M.Data[11007] = {cn = 'yun', en = '1.0'}
M.Data[11008] = {cn = 'zzz', en = '1.0'}
M.Data[20001] = {cn = '未知错误,错误码:%d', en = '1.0'}
M.Data[20002] = {cn = '请求失败,请稍后再试', en = '1.0'}
M.Data[20100] = {cn = '账号不能为空', en = '1.0'}
M.Data[20101] = {cn = '密码不能为空', en = '1.0'}
M.Data[20102] = {cn = '密码超长', en = '1.0'}
M.Data[20103] = {cn = '账号超长', en = '1.0'}
M.Data[20104] = {cn = '密码含有非法字符', en = '1.0'}
M.Data[20105] = {cn = '账号含有非法字符', en = '1.0'}
M.Data[20106] = {cn = '密码错误', en = '1.0'}
M.Data[20107] = {cn = '账号不存在', en = '1.0'}
M.Data[20108] = {cn = '服务器列表拉取失败', en = '1.0'}
M.Data[20109] = {cn = '服务器列表为空', en = '1.0'}
M.Data[20110] = {cn = '没有找到玩家信息', en = '1.0'}
M.Data[20111] = {cn = '有多个玩家信息', en = '1.0'}
M.Data[20112] = {cn = '令牌已过期,请重新登录', en = '1.0'}
M.Data[20113] = {cn = '', en = '1.0'}
M.Data[20114] = {cn = '', en = '1.0'}
M.Data[20115] = {cn = '', en = '1.0'}
M.Data[20116] = {cn = '', en = '1.0'}
M.Data[20117] = {cn = '', en = '1.0'}
M.Data[20118] = {cn = '', en = '1.0'}
M.Data[20119] = {cn = '', en = '1.0'}
M.Data[20120] = {cn = '', en = '1.0'}
M.Data[20121] = {cn = '', en = '1.0'}
M.Data[20122] = {cn = '', en = '1.0'}
M.Data[20123] = {cn = '', en = '1.0'}
M.Data[20124] = {cn = '', en = '1.0'}
M.Data[20125] = {cn = '', en = '1.0'}
M.Data[20126] = {cn = '', en = '1.0'}
M.length = 37

function M.getData(key)
    return M.Data[key]
end

function M.getItem(key1, key2)
    if M.Data[key1] == nil then
        print(string.format("错误: 文件'Lang.lua'中配置'%s'不存在!!!!!!!!!!!!!!!!!!!!!!!", tostring(key1)))
        return
    end
    return M.Data[key1][key2]
end

function M.getAllData()
    return M.Data
end

return M
