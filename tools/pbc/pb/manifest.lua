local M = {}
M.CMD = {
	[900104] = {file = 'Msg_Game.pb', name = 'MSG_STOP_PVP_REQ', msg = 'msg.Null'},
	[900105] = {file = 'Msg_Game.pb', name = 'MSG_STOP_PVP_ACK', msg = 'msg.Null'},
	[900100] = {file = 'Msg_Game.pb', name = 'MSG_START_PVE_REQ', msg = 'msg.StartPVEFightReq'},
	[900101] = {file = 'Msg_Game.pb', name = 'MSG_START_PVE_ACK', msg = 'msg.StartPVEFightAck'},
	[900102] = {file = 'Msg_Game.pb', name = 'MSG_START_PVP_REQ', msg = 'msg.StartPVPFightReq'},
	[900103] = {file = 'Msg_Game.pb', name = 'MSG_START_PVP_ACK', msg = 'msg.StartPVPFightAck'},
	[900200] = {file = 'Msg_Game.pb', name = 'MSG_START_FIGHT_NTF', msg = 'msg.StartFightNTF'},
	[900001] = {file = 'Msg_Game.pb', name = 'MSG_LOGIN_REQ', msg = 'msg.LoginReq'},
	[900010] = {file = 'Msg_Game.pb', name = 'MSG_EXIT_GAME_NTF', msg = 'msg.ExitGameNtf'},
	[900002] = {file = 'Msg_Game.pb', name = 'MSG_LOGIN_ACK', msg = 'msg.LoginAck'},
	[100001] = {file = 'Msg_Game.pb', name = 'MSG_LOGIN_GATE_ACK', msg = 'msg.LoginGateAck'},
	[800008] = {file = 'Msg_Game.pb', name = 'MSG_EXIT_FIGHT_ACK', msg = 'msg.ExitFightAck'},
	[800006] = {file = 'Msg_Game.pb', name = 'MSG_PLAYER_EXIT_FIGHT_NTF', msg = 'msg.PlayerExitFightNotify'},
	[800007] = {file = 'Msg_Game.pb', name = 'MSG_EXIT_FIGHT_REQ', msg = 'msg.ExitFightReq'},
	[800004] = {file = 'Msg_Game.pb', name = 'MSG_RUN_NEXT_FRAME_ACK', msg = 'msg.RunNextFrameAck'},
	[800005] = {file = 'Msg_Game.pb', name = 'MSG_PLAYER_READY_NTF', msg = 'msg.PlayerReadyNotify'},
	[800002] = {file = 'Msg_Game.pb', name = 'MSG_JOIN_FIGHT_ACK', msg = 'msg.JoinFightAck'},
	[800003] = {file = 'Msg_Game.pb', name = 'MSG_RUN_NEXT_FRAME_REQ', msg = 'msg.RunNextFrameReq'},
	[800001] = {file = 'Msg_Game.pb', name = 'MSG_JOIN_FIGHT_REQ', msg = 'msg.JoinFightReq'},
}
M.pb = {
	'Msg_ID.pb',
	'Msg_Game.pb',
	'Msg_Err.pb',
}

if cc then
    cc.exports.errCode = {}
else
    errCode = {}
end
errCode['EXIT_GAME_PLAYER_REQ'] = 120012
errCode['UNKNOWN'] = 1
errCode['FIGHT_PLAYER_TOO_MUCH'] = 110004
errCode['WRONG_PASSWORD'] = 100001
errCode['PVP_RIVAL_EXIT'] = 120034
errCode['FIGHT_SVR_BUSY'] = 110100
errCode['GAME_LOGIN_MUT_PID'] = 120001
errCode['PVP_MATCH_SUC'] = 120032
errCode['FIGHT_PLAYERID_REPEAT'] = 110005
errCode['NOT_FOUND'] = 2
errCode['NOT_FOUND_FIGHT'] = 110000
errCode['EXIT_GAME_CLIENT_DIS'] = 120011
errCode['GAME_LOGIN_AGAIN'] = 120002
errCode['OVERLOAD'] = 101
errCode['PARAM_ERROR'] = 102
errCode['EXIT_GAME_LOGIN_REPEAT'] = 120010
errCode['FIGHT_NOE_FOUND_PLAYER'] = 110002
errCode['FIGHT_INIT_FAIL'] = 110001
errCode['FIGHT_LEAVE_GAME'] = 110006
errCode['PVP_MATCH_TIMEOUT'] = 120031
errCode['SUCCESS'] = 0
errCode['GAME_LOGIN_NO_FOUND_PLAYER'] = 120003
errCode['FIGHT_SVR_NOT_FOUND'] = 110102
errCode['PVP_MATCH_SUC_NO_SVR'] = 120033
errCode['FIGHT_FRAME_ERR'] = 110007
errCode['OVERDUE'] = 3
errCode['FIGHT_PLAYING'] = 110003
errCode['GATE_CONNECT_FAIL'] = 100100
errCode['ACCOUNT_NOT_EXIST'] = 100000
errCode['NO_MEMORY'] = 100
errCode['FIGHT_SVR_NONE'] = 110101
errCode['PVP_MATCHING'] = 120030
errCode['FIGHT_PAST_RECORDS_INC'] = 110008


if cc then
    cc.exports.MessageID = {}
else
    MessageID = {}
end
for k, v in pairs(M.CMD) do
    MessageID[v.name] = k
end

return M