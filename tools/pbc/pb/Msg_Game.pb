
œ
Msg_Game.protomsg"
Null"
CodeAck
code ("
LoginGateAck
code ("<
LoginReq
token (	
account (	
playerID ("G
PlayerAccountInfo
playerID (
name (	

arrRoleIds ("H
RoleInfo
roleId (
name (	

lv (

occupation ("?
LoginAck
code (%
infos (2.msg.PlayerAccountInfo"?
EnterGameReq
token (	
playerID (
roleID ("=
EnterGameAck
code (
roleinfo (2.msg.RoleInfo"1
CreateRoleReq

occupation (
name (	"-
CreateRoleAck
code (
roleID ("
ExitGameNtf
code ("
PVEFightInfo
roleId ("F
StartPVEFightReq
carbonId ( 
roles (2.msg.PVEFightInfo" 
StartPVEFightAck
code ("!
StartPVPFightReq
foeId (" 
StartPVPFightAck
code ("T
StartFightNTF
code (
	fightUUID (
fightIP (	
	fightPort ("B
JoinFightReq
	fightUUID (
playerID (
frame ("h
FightWorldInfo
frame (

svr_status (
mapId (

randomSeed (
uuidSeed ("D
JoinFightAck
code (&
	worldInfo (2.msg.FightWorldInfo"3
PlayerLoadingReq
percent (
finish ("@
PlayerLoadingAck
pid (
percent (
finish (" 
PlayerReadyNotify
pid ("$
PlayerExitFightNotify
pid (""
FrameInputData
key_down ("R
PlayerFrameInput
pid (
frame ("
input (2.msg.FrameInputData"D
RunNextFrameReq
frame ("
input (2.msg.FrameInputData"K
RunNextFrameAck
	nextFrame (%
frames (2.msg.PlayerFrameInput"J
PushFrameInput
	lastFrame (%
frames (2.msg.PlayerFrameInput"6
PlayerRecords%
frames (2.msg.PlayerFrameInput"!
ExitFightReq
	fightUUID ("
ExitFightAck
code ("
Ping
	timestamp ("
Pong
	timestamp ("%
PingInfo
pid (
ping (",
PushPingInfo
infos (2.msg.PingInfoBH