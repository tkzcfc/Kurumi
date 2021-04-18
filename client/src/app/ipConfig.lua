-- @Author : fangcheng
-- @Date   : 2020-04-08 21:47:34
-- @remark : 游戏配置


if not _MyG then
	cc.exports._MyG = {}
end

_MyG.startSvrTcpIP = '127.0.0.1'
_MyG.startSvrTcpPort = 7001

print("_MyG.startSvrIP-------------->>", _MyG.startSvrTcpIP)
print("_MyG.startSvrPort", _MyG.startSvrTcpPort)