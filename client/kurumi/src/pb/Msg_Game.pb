
�
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
roleinfo (2


occupation (
name (	"-

code (
roleID ("
ExitGameNtf
code ("
PVEFightInfo
roleId ("]
StartPVEFightReq
carbonId (

roles (2.msg.PVEFightInfo" 
StartPVEFightAck
code ("!
StartPVPFightReq
foeId (" 
StartPVPFightAck
code ("T

code (
	fightUUID (
fightIP (	
	fightPort ("B
JoinFightReq
	fightUUID (
playerID (
frame ("
FightWorldInfo
frame (

svr_status (
mapId (

randomSeed (
uuidSeed (

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
key_down (
PlayerFrameInput
pid (
frame (
input (2.msg.FrameInputData"D
RunNextFrameReq
frame (
input (2.msg.FrameInputData"K
RunNextFrameAck
	nextFrame (
frames (2.msg.PlayerFrameInput"J
PushFrameInput
	lastFrame (
frames (2.msg.PlayerFrameInput"6

frames (2.msg.PlayerFrameInput"!
ExitFightReq
	fightUUID ("
ExitFightAck
code ("
Ping
	timestamp (
Pong
	timestamp (
PingInfo
pid (
ping (",
PushPingInfo
infos (2