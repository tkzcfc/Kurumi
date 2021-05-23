local M = {}
M.CMD = {
	[800008] = {file = 'Msg_Game.pb', name = 'MSG_EXIT_FIGHT_ACK', msg = 'msg.ExitFightAck'},
	[800009] = {file = 'Msg_Game.pb', name = 'MSG_LOADING_PERCENT_REQ', msg = 'msg.PlayerLoadingReq'},
	[800006] = {file = 'Msg_Game.pb', name = 'MSG_PLAYER_EXIT_FIGHT_NTF', msg = 'msg.PlayerExitFightNotify'},
	[800007] = {file = 'Msg_Game.pb', name = 'MSG_EXIT_FIGHT_REQ', msg = 'msg.ExitFightReq'},
	[800004] = {file = 'Msg_Game.pb', name = 'MSG_RUN_NEXT_FRAME_ACK', msg = 'msg.RunNextFrameAck'},
	[800005] = {file = 'Msg_Game.pb', name = 'MSG_PLAYER_READY_NTF', msg = 'msg.PlayerReadyNotify'},
	[800002] = {file = 'Msg_Game.pb', name = 'MSG_JOIN_FIGHT_ACK', msg = 'msg.JoinFightAck'},
	[800003] = {file = 'Msg_Game.pb', name = 'MSG_RUN_NEXT_FRAME_REQ', msg = 'msg.RunNextFrameReq'},
	[800001] = {file = 'Msg_Game.pb', name = 'MSG_JOIN_FIGHT_REQ', msg = 'msg.JoinFightReq'},
	[900010] = {file = 'Msg_Game.pb', name = 'MSG_EXIT_GAME_NTF', msg = 'msg.ExitGameNtf'},
	[800011] = {file = 'Msg_Game.pb', name = 'MSG_PUSH_FRAME_BEGIN', msg = 'msg.Null'},
	[800010] = {file = 'Msg_Game.pb', name = 'MSG_LOADING_PERCENT_ACK', msg = 'msg.PlayerLoadingAck'},
	[800013] = {file = 'Msg_Game.pb', name = 'MSG_PUSH_FRAME_END', msg = 'msg.Null'},
	[800012] = {file = 'Msg_Game.pb', name = 'MSG_PUSH_FRAME_INPUT', msg = 'msg.PushFrameInput'},
	[900104] = {file = 'Msg_Game.pb', name = 'MSG_START_PVP_ACK', msg = 'msg.StartPVPFightAck'},
	[900105] = {file = 'Msg_Game.pb', name = 'MSG_STOP_PVP_REQ', msg = 'msg.Null'},
	[900106] = {file = 'Msg_Game.pb', name = 'MSG_STOP_PVP_ACK', msg = 'msg.Null'},
	[900101] = {file = 'Msg_Game.pb', name = 'MSG_START_PVE_REQ', msg = 'msg.StartPVEFightReq'},
	[900102] = {file = 'Msg_Game.pb', name = 'MSG_START_PVE_ACK', msg = 'msg.StartPVEFightAck'},
	[900103] = {file = 'Msg_Game.pb', name = 'MSG_START_PVP_REQ', msg = 'msg.StartPVPFightReq'},
	[900001] = {file = 'Msg_Game.pb', name = 'MSG_LOGIN_REQ', msg = 'msg.LoginReq'},
	[900002] = {file = 'Msg_Game.pb', name = 'MSG_LOGIN_ACK', msg = 'msg.LoginAck'},
	[900306] = {file = 'Msg_Game.pb', name = 'MSG_ENTER_GAME_ACK', msg = 'msg.EnterGameAck'},
	[900304] = {file = 'Msg_Game.pb', name = 'MSG_CREATE_ROLE_ACK', msg = 'msg.CreateRoleAck'},
	[900305] = {file = 'Msg_Game.pb', name = 'MSG_ENTER_GAME_REQ', msg = 'msg.EnterGameReq'},
	[100001] = {file = 'Msg_Game.pb', name = 'MSG_LOGIN_GATE_ACK', msg = 'msg.LoginGateAck'},
	[900303] = {file = 'Msg_Game.pb', name = 'MSG_CREATE_ROLE_REQ', msg = 'msg.CreateRoleReq'},
	[900200] = {file = 'Msg_Game.pb', name = 'MSG_START_FIGHT_NTF', msg = 'msg.StartFightNTF'},
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
errCode['NAME_STR_TO_SHORT'] = 100200
errCode['TOKEN_ERR'] = 100006
errCode['EXIT_GAME_PLAYER_REQ'] = 220012
errCode['UNKNOWN'] = 100001
errCode['FIGHT_PLAYER_TOO_MUCH'] = 210004
errCode['WRONG_PASSWORD'] = 200001
errCode['TARGET_REPEAT'] = 100004
errCode['PVP_RIVAL_EXIT'] = 220034
errCode['FIGHT_SVR_BUSY'] = 210100
errCode['GAME_LOGIN_MUT_PID'] = 220001
errCode['PVP_MATCH_SUC'] = 220032
errCode['NAME_STR_TO_LONG'] = 100201
errCode['FIGHT_FRAME_ERR'] = 210007
errCode['ROLE_NOT_EXIST'] = 200002
errCode['NOT_FOUND_FIGHT'] = 210000
errCode['EXIT_GAME_CLIENT_DIS'] = 220011
errCode['GAME_LOGIN_AGAIN'] = 220002
errCode['OVERLOAD'] = 100101
errCode['PARAM_ERROR'] = 100102
errCode['EXIT_GAME_LOGIN_REPEAT'] = 220010
errCode['FIGHT_NOE_FOUND_PLAYER'] = 210002
errCode['FIGHT_INIT_FAIL'] = 210001
errCode['FIGHT_PLAYERID_REPEAT'] = 210005
errCode['FIGHT_LEAVE_GAME'] = 210006
errCode['PVP_MATCH_TIMEOUT'] = 220031
errCode['SUCCESS'] = 0
errCode['GAME_LOGIN_NO_FOUND_PLAYER'] = 220003
errCode['SVR_ERROR'] = 100005
errCode['PVP_MATCHING'] = 220030
errCode['FIGHT_SVR_NOT_FOUND'] = 210102
errCode['PVP_MATCH_SUC_NO_SVR'] = 220033
errCode['NOT_FOUND'] = 100002
errCode['OVERDUE'] = 100003
errCode['FIGHT_PLAYING'] = 210003
errCode['GATE_CONNECT_FAIL'] = 200100
errCode['ACCOUNT_NOT_EXIST'] = 200000
errCode['NO_MEMORY'] = 100100
errCode['NAME_STR_CONTAIN_ILLEGAL_CAHR'] = 100202
errCode['OCC_NOT_FOUND'] = 100007
errCode['FIGHT_SVR_NONE'] = 210101
errCode['NAME_TARGET_REPEAT'] = 100203
errCode['FIGHT_PAST_RECORDS_INC'] = 210008


if cc then
    cc.exports.MessageID = {}
else
    MessageID = {}
end
for k, v in pairs(M.CMD) do
    MessageID[v.name] = k
end

return M