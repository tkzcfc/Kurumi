
‘

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
frame ("Q
JoinFightAck
code (
mapId (

randomSeed (
uuidSeed (" 
PlayerReadyNotify
pid ("$
PlayerExitFightNotify
pid ("/
RunNextFrameReq
frame (
input (	"0
RunNextFrameAck
frame (
inputs (	"!
ExitFightReq
	fightUUID ("
ExitFightAck
code (BH