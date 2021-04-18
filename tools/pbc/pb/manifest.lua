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
return M