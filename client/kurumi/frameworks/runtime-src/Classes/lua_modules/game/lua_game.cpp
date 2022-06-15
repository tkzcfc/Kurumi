/*
** Lua binding: game
** Generated automatically by tolua++-1.0.92 on 05/29/22 22:06:44.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"
#include "tolua_fix.h"
#include <string>

/* Exported function */
TOLUA_API int  tolua_game_open (lua_State* tolua_S);

#include "lua_function/tolua_ext.h"
#include "net_uv_cc/CCNetClient.h"
#include "mugen/logic/GGameWorld.h"
USING_NS_G;
#include "mugen/GGameDef.h"
#include "mugen/component/GAvatarComponent.h"
#include "mugen/component/GActorComponent.h"
#include "mugen/component/GDataComponent.h"
#include "mugen/act/condition/GScriptCondition.h"
#include "mugen/act/frame/GScriptFrame.h"
#include "foundation/GTools.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_std__vector_GChannel__ (lua_State* tolua_S)
{
 std::vector<GChannel*>* self = (std::vector<GChannel*>*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_GAvatarComponent (lua_State* tolua_S)
{
 GAvatarComponent* self = (GAvatarComponent*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_Vec2 (lua_State* tolua_S)
{
 Vec2* self = (Vec2*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_GGameWorld (lua_State* tolua_S)
{
 GGameWorld* self = (GGameWorld*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_std__vector_GAction__ (lua_State* tolua_S)
{
 std::vector<GAction*>* self = (std::vector<GAction*>*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_std__vector_GFrame__ (lua_State* tolua_S)
{
 std::vector<GFrame*>* self = (std::vector<GFrame*>*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_std__vector_GTimeline__ (lua_State* tolua_S)
{
 std::vector<GTimeline*>* self = (std::vector<GTimeline*>*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"GTools");
 tolua_usertype(tolua_S,"GFixedVec3");
 tolua_usertype(tolua_S,"GComponent");
 tolua_usertype(tolua_S,"Vec2");
 tolua_usertype(tolua_S,"GAction");
 tolua_usertype(tolua_S,"GActorComponent");
 tolua_usertype(tolua_S,"GChannel");
 tolua_usertype(tolua_S,"GSkill");
 tolua_usertype(tolua_S,"GMapLayer");
 tolua_usertype(tolua_S,"cc.Ref");
 tolua_usertype(tolua_S,"GScriptFrame");
 tolua_usertype(tolua_S,"std::vector<GTimeline*>");
 tolua_usertype(tolua_S,"std::vector<GAction*>");
 tolua_usertype(tolua_S,"GCondition");
 tolua_usertype(tolua_S,"GTimeline");
 tolua_usertype(tolua_S,"GVirtualCamera");
 tolua_usertype(tolua_S,"GFixedVec2");
 tolua_usertype(tolua_S,"GRigidBodyComponent");
 tolua_usertype(tolua_S,"GTrack");
 tolua_usertype(tolua_S,"GGameWorld");
 tolua_usertype(tolua_S,"GEntity");
 tolua_usertype(tolua_S,"GScriptCondition");
 tolua_usertype(tolua_S,"std::vector<GFrame*>");
 tolua_usertype(tolua_S,"GEventFrame");
 tolua_usertype(tolua_S,"std::vector<GChannel*>");
 tolua_usertype(tolua_S,"GFrame");
 tolua_usertype(tolua_S,"GAvatarComponent");
 tolua_usertype(tolua_S,"CCNetClient");
 tolua_usertype(tolua_S,"LUA_FUNCTION");
 tolua_usertype(tolua_S,"GDataComponent");
 tolua_usertype(tolua_S,"cc.Node");
 tolua_usertype(tolua_S,"net_uv::Session");
}

/* method: send of class  net_uv::Session */
#ifndef TOLUA_DISABLE_tolua_game_net_uv_Session_send00
static int tolua_game_net_uv_Session_send00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::Session",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::Session* self = (net_uv::Session*)  tolua_tousertype(tolua_S,1,0);
  char* data = ((char*)  tolua_tostring(tolua_S,2,0));
  unsigned int len = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send'", NULL);
#endif
  {
   self->send(data,len);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'send'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disconnect of class  net_uv::Session */
#ifndef TOLUA_DISABLE_tolua_game_net_uv_Session_disconnect00
static int tolua_game_net_uv_Session_disconnect00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::Session",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::Session* self = (net_uv::Session*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disconnect'", NULL);
#endif
  {
   self->disconnect();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSessionID of class  net_uv::Session */
#ifndef TOLUA_DISABLE_tolua_game_net_uv_Session_getSessionID00
static int tolua_game_net_uv_Session_getSessionID00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::Session",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::Session* self = (net_uv::Session*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSessionID'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getSessionID();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSessionID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPort of class  net_uv::Session */
#ifndef TOLUA_DISABLE_tolua_game_net_uv_Session_getPort00
static int tolua_game_net_uv_Session_getPort00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::Session",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::Session* self = (net_uv::Session*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPort'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getPort();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPort'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIp of class  net_uv::Session */
#ifndef TOLUA_DISABLE_tolua_game_net_uv_Session_getIp00
static int tolua_game_net_uv_Session_getIp00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::Session",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::Session* self = (net_uv::Session*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIp'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getIp();
   tolua_pushcppstring(tolua_S,tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCNetClient */
#ifndef TOLUA_DISABLE_tolua_game_NetClient_create00
static int tolua_game_NetClient_create00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCNetClient",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool useKcp = ((bool)  tolua_toboolean(tolua_S,2,0));
  {
   CCNetClient* tolua_ret = (CCNetClient*)  CCNetClient::create(useKcp);
    tolua_ext_object_to_luaval<CCNetClient>(tolua_S,(void*)tolua_ret,"CCNetClient");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: connect of class  CCNetClient */
#ifndef TOLUA_DISABLE_tolua_game_NetClient_connect00
static int tolua_game_NetClient_connect00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNetClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNetClient* self = (CCNetClient*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int port = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned int sessionId = (( unsigned int)  tolua_tonumber(tolua_S,4,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'connect'", NULL);
#endif
  {
   self->connect(ip,port,sessionId);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'connect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeSession of class  CCNetClient */
#ifndef TOLUA_DISABLE_tolua_game_NetClient_removeSession00
static int tolua_game_NetClient_removeSession00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNetClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNetClient* self = (CCNetClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionId = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeSession'", NULL);
#endif
  {
   self->removeSession(sessionId);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeSession'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disconnect of class  CCNetClient */
#ifndef TOLUA_DISABLE_tolua_game_NetClient_disconnect00
static int tolua_game_NetClient_disconnect00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNetClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNetClient* self = (CCNetClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionId = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disconnect'", NULL);
#endif
  {
   self->disconnect(sessionId);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sendMsg of class  CCNetClient */
#ifndef TOLUA_DISABLE_tolua_game_NetClient_sendMsg00
static int tolua_game_NetClient_sendMsg00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNetClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNetClient* self = (CCNetClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int msgID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  char* data = ((char*)  tolua_tostring(tolua_S,4,0));
  unsigned int len = (( unsigned int)  tolua_tonumber(tolua_S,5,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendMsg'", NULL);
#endif
  {
   self->sendMsg(sessionID,msgID,data,len);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setHeartBeatTime of class  CCNetClient */
#ifndef TOLUA_DISABLE_tolua_game_NetClient_setHeartBeatTime00
static int tolua_game_NetClient_setHeartBeatTime00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNetClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNetClient* self = (CCNetClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int value = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setHeartBeatTime'", NULL);
#endif
  {
   self->setHeartBeatTime(value);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setHeartBeatTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setHeartBeatLoseMaxCount of class  CCNetClient */
#ifndef TOLUA_DISABLE_tolua_game_NetClient_setHeartBeatLoseMaxCount00
static int tolua_game_NetClient_setHeartBeatLoseMaxCount00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNetClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNetClient* self = (CCNetClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int value = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setHeartBeatLoseMaxCount'", NULL);
#endif
  {
   self->setHeartBeatLoseMaxCount(value);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setHeartBeatLoseMaxCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: closeClient of class  CCNetClient */
#ifndef TOLUA_DISABLE_tolua_game_NetClient_closeClient00
static int tolua_game_NetClient_closeClient00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNetClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNetClient* self = (CCNetClient*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'closeClient'", NULL);
#endif
  {
   self->closeClient();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'closeClient'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerLuaHandle of class  CCNetClient */
#ifndef TOLUA_DISABLE_tolua_game_NetClient_registerLuaHandle00
static int tolua_game_NetClient_registerLuaHandle00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNetClient",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNetClient* self = (CCNetClient*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  LUA_FUNCTION handle = (  toluafix_ref_function(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerLuaHandle'", NULL);
#endif
  {
   self->registerLuaHandle(name,handle);
   tolua_pushcppstring(tolua_S,name);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerLuaHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  GVirtualCamera */
#ifndef TOLUA_DISABLE_tolua_game_GVirtualCamera_setPosition00
static int tolua_game_GVirtualCamera_setPosition00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GVirtualCamera",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GVirtualCamera* self = (GVirtualCamera*)  tolua_tousertype(tolua_S,1,0);
  Vec2 pos = (  tolua_ext_luaval_to_vec2_value(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
  {
   self->setPosition(pos);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setZoom of class  GVirtualCamera */
#ifndef TOLUA_DISABLE_tolua_game_GVirtualCamera_setZoom00
static int tolua_game_GVirtualCamera_setZoom00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GVirtualCamera",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GVirtualCamera* self = (GVirtualCamera*)  tolua_tousertype(tolua_S,1,0);
  float zoom = ((float)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setZoom'", NULL);
#endif
  {
   self->setZoom(zoom);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setZoom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchorPoint of class  GVirtualCamera */
#ifndef TOLUA_DISABLE_tolua_game_GVirtualCamera_setAnchorPoint00
static int tolua_game_GVirtualCamera_setAnchorPoint00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GVirtualCamera",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GVirtualCamera* self = (GVirtualCamera*)  tolua_tousertype(tolua_S,1,0);
  Vec2 pos = (  tolua_ext_luaval_to_vec2_value(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchorPoint'", NULL);
#endif
  {
   self->setAnchorPoint(pos);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchorPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: validPosition of class  GVirtualCamera */
#ifndef TOLUA_DISABLE_tolua_game_GVirtualCamera_validPosition00
static int tolua_game_GVirtualCamera_validPosition00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GVirtualCamera",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GVirtualCamera* self = (GVirtualCamera*)  tolua_tousertype(tolua_S,1,0);
  Vec2 pos = (  tolua_ext_luaval_to_vec2_value(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'validPosition'", NULL);
#endif
  {
   Vec2 tolua_ret = (Vec2)  self->validPosition(pos);
   {
   tolua_ext_vec2_value_to_luaval(tolua_S, tolua_ret, "Vec2");
   }
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'validPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCameraBoundingBox of class  GVirtualCamera */
#ifndef TOLUA_DISABLE_tolua_game_GVirtualCamera_setCameraBoundingBox00
static int tolua_game_GVirtualCamera_setCameraBoundingBox00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GVirtualCamera",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"Vec2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_ext_check_is_table(tolua_S,3,"Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GVirtualCamera* self = (GVirtualCamera*)  tolua_tousertype(tolua_S,1,0);
  Vec2 min = (  tolua_ext_luaval_to_vec2_value(tolua_S,2,0));
  Vec2 max = (  tolua_ext_luaval_to_vec2_value(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCameraBoundingBox'", NULL);
#endif
  {
   self->setCameraBoundingBox(min,max);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCameraBoundingBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getActorNode of class  GMapLayer */
#ifndef TOLUA_DISABLE_tolua_game_GMapLayer_getActorNode00
static int tolua_game_GMapLayer_getActorNode00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GMapLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GMapLayer* self = (GMapLayer*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getActorNode'", NULL);
#endif
  {
   Node* tolua_ret = (Node*)  self->getActorNode();
    tolua_ext_object_to_luaval<Node>(tolua_S,(void*)tolua_ret,"cc.Node");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getActorNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRootNode of class  GMapLayer */
#ifndef TOLUA_DISABLE_tolua_game_GMapLayer_getRootNode00
static int tolua_game_GMapLayer_getRootNode00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GMapLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GMapLayer* self = (GMapLayer*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRootNode'", NULL);
#endif
  {
   Node* tolua_ret = (Node*)  self->getRootNode();
    tolua_ext_object_to_luaval<Node>(tolua_S,(void*)tolua_ret,"cc.Node");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRootNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVirtualCamera of class  GMapLayer */
#ifndef TOLUA_DISABLE_tolua_game_GMapLayer_getVirtualCamera00
static int tolua_game_GMapLayer_getVirtualCamera00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GMapLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GMapLayer* self = (GMapLayer*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVirtualCamera'", NULL);
#endif
  {
   GVirtualCamera* tolua_ret = (GVirtualCamera*)  self->getVirtualCamera();
    tolua_ext_object_to_luaval<GVirtualCamera>(tolua_S,(void*)tolua_ret,"GVirtualCamera");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVirtualCamera'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  GGameWorld */
#ifndef TOLUA_DISABLE_tolua_game_GGameWorld_delete00
static int tolua_game_GGameWorld_delete00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GGameWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GGameWorld* self = (GGameWorld*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  GGameWorld */
#ifndef TOLUA_DISABLE_tolua_game_GGameWorld_getInstance00
static int tolua_game_GGameWorld_getInstance00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GGameWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GGameWorld* tolua_ret = (GGameWorld*)  GGameWorld::getInstance();
    tolua_ext_object_to_luaval<GGameWorld>(tolua_S,(void*)tolua_ret,"GGameWorld");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  GGameWorld */
#ifndef TOLUA_DISABLE_tolua_game_GGameWorld_create00
static int tolua_game_GGameWorld_create00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GGameWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"cc.Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
   int mapId = ((  int)  tolua_tonumber(tolua_S,2,0));
  unsigned int randomSeed = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  Node* rootNode = ((Node*)  tolua_tousertype(tolua_S,4,0));
  {
   GGameWorld* tolua_ret = (GGameWorld*)  GGameWorld::create(mapId,randomSeed,rootNode);
    tolua_ext_object_to_luaval<GGameWorld>(tolua_S,(void*)tolua_ret,"GGameWorld");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: step of class  GGameWorld */
#ifndef TOLUA_DISABLE_tolua_game_GGameWorld_step00
static int tolua_game_GGameWorld_step00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GGameWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GGameWorld* self = (GGameWorld*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'step'", NULL);
#endif
  {
   self->step();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'step'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: render of class  GGameWorld */
#ifndef TOLUA_DISABLE_tolua_game_GGameWorld_render00
static int tolua_game_GGameWorld_render00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GGameWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GGameWorld* self = (GGameWorld*)  tolua_tousertype(tolua_S,1,0);
  float dt = ((float)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'render'", NULL);
#endif
  {
   self->render(dt);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'render'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: input of class  GGameWorld */
#ifndef TOLUA_DISABLE_tolua_game_GGameWorld_input00
static int tolua_game_GGameWorld_input00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GGameWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GGameWorld* self = (GGameWorld*)  tolua_tousertype(tolua_S,1,0);
  unsigned int entityId = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int frame = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned int keydown = (( unsigned int)  tolua_tonumber(tolua_S,4,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'input'", NULL);
#endif
  {
   self->input(entityId,frame,keydown);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'input'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: spwanActor of class  GGameWorld */
#ifndef TOLUA_DISABLE_tolua_game_GGameWorld_spwanActor00
static int tolua_game_GGameWorld_spwanActor00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GGameWorld",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_ext_check_is_table(tolua_S,3,"GFixedVec3",0,&tolua_err)) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GGameWorld* self = (GGameWorld*)  tolua_tousertype(tolua_S,1,0);
  std::string filename = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  GFixedVec3 pos = (  tolua_ext_luaval_to_fvec3_value(tolua_S,3,0));
  std::string replaceArmatureFile = ((std::string)  tolua_tocppstring(tolua_S,4,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'spwanActor'", NULL);
#endif
  {
   GEntity* tolua_ret = (GEntity*)  self->spwanActor(filename,pos,replaceArmatureFile);
    tolua_ext_object_to_luaval<GEntity>(tolua_S,(void*)tolua_ret,"GEntity");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'spwanActor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: enableDebugDraw of class  GGameWorld */
#ifndef TOLUA_DISABLE_tolua_game_GGameWorld_enableDebugDraw00
static int tolua_game_GGameWorld_enableDebugDraw00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GGameWorld",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GGameWorld* self = (GGameWorld*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'enableDebugDraw'", NULL);
#endif
  {
   self->enableDebugDraw(enable);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'enableDebugDraw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScheduler of class  GGameWorld */
#ifndef TOLUA_DISABLE_tolua_game_GGameWorld_setScheduler00
static int tolua_game_GGameWorld_setScheduler00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GGameWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"cc.Node",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GGameWorld* self = (GGameWorld*)  tolua_tousertype(tolua_S,1,0);
  Node* node = ((Node*)  tolua_tousertype(tolua_S,2,0));
  bool recursive = ((bool)  tolua_toboolean(tolua_S,3,true));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScheduler'", NULL);
#endif
  {
   self->setScheduler(node,recursive);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScheduler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLocalPlayer of class  GGameWorld */
#ifndef TOLUA_DISABLE_tolua_game_GGameWorld_getLocalPlayer00
static int tolua_game_GGameWorld_getLocalPlayer00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GGameWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GGameWorld* self = (GGameWorld*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLocalPlayer'", NULL);
#endif
  {
   GEntity* tolua_ret = (GEntity*)  self->getLocalPlayer();
    tolua_ext_object_to_luaval<GEntity>(tolua_S,(void*)tolua_ret,"GEntity");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLocalPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLocalPlayer of class  GGameWorld */
#ifndef TOLUA_DISABLE_tolua_game_GGameWorld_setLocalPlayer00
static int tolua_game_GGameWorld_setLocalPlayer00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GGameWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GEntity",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GGameWorld* self = (GGameWorld*)  tolua_tousertype(tolua_S,1,0);
  GEntity* entity = ((GEntity*)  tolua_tousertype(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLocalPlayer'", NULL);
#endif
  {
   self->setLocalPlayer(entity);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLocalPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerLuaHandle of class  GGameWorld */
#ifndef TOLUA_DISABLE_tolua_game_GGameWorld_registerLuaHandle00
static int tolua_game_GGameWorld_registerLuaHandle00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GGameWorld",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GGameWorld* self = (GGameWorld*)  tolua_tousertype(tolua_S,1,0);
  std::string name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  LUA_FUNCTION handle = (  toluafix_ref_function(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerLuaHandle'", NULL);
#endif
  {
   self->registerLuaHandle(name,handle);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerLuaHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMapLayer of class  GGameWorld */
#ifndef TOLUA_DISABLE_tolua_game_GGameWorld_getMapLayer00
static int tolua_game_GGameWorld_getMapLayer00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GGameWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GGameWorld* self = (GGameWorld*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMapLayer'", NULL);
#endif
  {
   GMapLayer* tolua_ret = (GMapLayer*)  self->getMapLayer();
    tolua_ext_object_to_luaval<GMapLayer>(tolua_S,(void*)tolua_ret,"GMapLayer");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMapLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getGameLogicFrame of class  GGameWorld */
#ifndef TOLUA_DISABLE_tolua_game_GGameWorld_getGameLogicFrame00
static int tolua_game_GGameWorld_getGameLogicFrame00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GGameWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GGameWorld* self = (GGameWorld*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getGameLogicFrame'", NULL);
#endif
  {
   unsigned int tolua_ret = ( unsigned int)  self->getGameLogicFrame();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getGameLogicFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: G_KEY_NONE */
#ifndef TOLUA_DISABLE_tolua_get_slot_unsigned_G_KEY_NONE
static int tolua_get_slot_unsigned_G_KEY_NONE(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)G_KEY_NONE);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: G_KEY_MOVE_LEFT */
#ifndef TOLUA_DISABLE_tolua_get_slot_unsigned_G_KEY_MOVE_LEFT
static int tolua_get_slot_unsigned_G_KEY_MOVE_LEFT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)G_KEY_MOVE_LEFT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: G_KEY_MOVE_RIGHT */
#ifndef TOLUA_DISABLE_tolua_get_slot_unsigned_G_KEY_MOVE_RIGHT
static int tolua_get_slot_unsigned_G_KEY_MOVE_RIGHT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)G_KEY_MOVE_RIGHT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: G_KEY_MOVE_UP */
#ifndef TOLUA_DISABLE_tolua_get_slot_unsigned_G_KEY_MOVE_UP
static int tolua_get_slot_unsigned_G_KEY_MOVE_UP(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)G_KEY_MOVE_UP);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: G_KEY_MOVE_DOWN */
#ifndef TOLUA_DISABLE_tolua_get_slot_unsigned_G_KEY_MOVE_DOWN
static int tolua_get_slot_unsigned_G_KEY_MOVE_DOWN(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)G_KEY_MOVE_DOWN);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: G_KEY_JUMP */
#ifndef TOLUA_DISABLE_tolua_get_slot_unsigned_G_KEY_JUMP
static int tolua_get_slot_unsigned_G_KEY_JUMP(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)G_KEY_JUMP);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: G_KEY_SKILL_1 */
#ifndef TOLUA_DISABLE_tolua_get_slot_unsigned_G_KEY_SKILL_1
static int tolua_get_slot_unsigned_G_KEY_SKILL_1(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)G_KEY_SKILL_1);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: G_KEY_SKILL_2 */
#ifndef TOLUA_DISABLE_tolua_get_slot_unsigned_G_KEY_SKILL_2
static int tolua_get_slot_unsigned_G_KEY_SKILL_2(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)G_KEY_SKILL_2);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: G_KEY_SKILL_3 */
#ifndef TOLUA_DISABLE_tolua_get_slot_unsigned_G_KEY_SKILL_3
static int tolua_get_slot_unsigned_G_KEY_SKILL_3(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)G_KEY_SKILL_3);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: G_KEY_SKILL_4 */
#ifndef TOLUA_DISABLE_tolua_get_slot_unsigned_G_KEY_SKILL_4
static int tolua_get_slot_unsigned_G_KEY_SKILL_4(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)G_KEY_SKILL_4);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: G_KEY_SKILL_5 */
#ifndef TOLUA_DISABLE_tolua_get_slot_unsigned_G_KEY_SKILL_5
static int tolua_get_slot_unsigned_G_KEY_SKILL_5(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)G_KEY_SKILL_5);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: G_KEY_SKILL_6 */
#ifndef TOLUA_DISABLE_tolua_get_slot_unsigned_G_KEY_SKILL_6
static int tolua_get_slot_unsigned_G_KEY_SKILL_6(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)G_KEY_SKILL_6);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: G_KEY_SKILL_7 */
#ifndef TOLUA_DISABLE_tolua_get_slot_unsigned_G_KEY_SKILL_7
static int tolua_get_slot_unsigned_G_KEY_SKILL_7(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)G_KEY_SKILL_7);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: G_KEY_MAX_COUNT */
#ifndef TOLUA_DISABLE_tolua_get_slot_unsigned_G_KEY_MAX_COUNT
static int tolua_get_slot_unsigned_G_KEY_MAX_COUNT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)G_KEY_MAX_COUNT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: G_KEY_MOVE_MUSTER */
#ifndef TOLUA_DISABLE_tolua_get_slot_unsigned_G_KEY_MOVE_MUSTER
static int tolua_get_slot_unsigned_G_KEY_MOVE_MUSTER(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)G_KEY_MOVE_MUSTER);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: G_KEY_MOVE_X */
#ifndef TOLUA_DISABLE_tolua_get_slot_unsigned_G_KEY_MOVE_X
static int tolua_get_slot_unsigned_G_KEY_MOVE_X(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)G_KEY_MOVE_X);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: G_KEY_MOVE_Y */
#ifndef TOLUA_DISABLE_tolua_get_slot_unsigned_G_KEY_MOVE_Y
static int tolua_get_slot_unsigned_G_KEY_MOVE_Y(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)G_KEY_MOVE_Y);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: addComponent of class  GComponent */
#ifndef TOLUA_DISABLE_tolua_game_GComponent_addComponent00
static int tolua_game_GComponent_addComponent00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GComponent",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GComponent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GComponent* self = (GComponent*)  tolua_tousertype(tolua_S,1,0);
  GComponent* component = ((GComponent*)  tolua_tousertype(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addComponent'", NULL);
#endif
  {
   self->addComponent(component);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeComponent of class  GComponent */
#ifndef TOLUA_DISABLE_tolua_game_GComponent_removeComponent00
static int tolua_game_GComponent_removeComponent00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GComponent",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GComponent* self = (GComponent*)  tolua_tousertype(tolua_S,1,0);
  std::string name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeComponent'", NULL);
#endif
  {
   self->removeComponent(name);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getComponent of class  GComponent */
#ifndef TOLUA_DISABLE_tolua_game_GComponent_getComponent00
static int tolua_game_GComponent_getComponent00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GComponent",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GComponent* self = (GComponent*)  tolua_tousertype(tolua_S,1,0);
  std::string name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getComponent'", NULL);
#endif
  {
   GComponent* tolua_ret = (GComponent*)  self->getComponent(name);
    tolua_ext_object_to_luaval<GComponent>(tolua_S,(void*)tolua_ret,"GComponent");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEntity of class  GComponent */
#ifndef TOLUA_DISABLE_tolua_game_GComponent_getEntity00
static int tolua_game_GComponent_getEntity00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GComponent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GComponent* self = (GComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEntity'", NULL);
#endif
  {
   GEntity* tolua_ret = (GEntity*)  self->getEntity();
    tolua_ext_object_to_luaval<GEntity>(tolua_S,(void*)tolua_ret,"GEntity");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEntity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addComponent of class  GEntity */
#ifndef TOLUA_DISABLE_tolua_game_GEntity_addComponent00
static int tolua_game_GEntity_addComponent00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GEntity",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GComponent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GEntity* self = (GEntity*)  tolua_tousertype(tolua_S,1,0);
  GComponent* component = ((GComponent*)  tolua_tousertype(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addComponent'", NULL);
#endif
  {
   self->addComponent(component);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeComponent of class  GEntity */
#ifndef TOLUA_DISABLE_tolua_game_GEntity_removeComponent00
static int tolua_game_GEntity_removeComponent00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GEntity",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GEntity* self = (GEntity*)  tolua_tousertype(tolua_S,1,0);
  std::string name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeComponent'", NULL);
#endif
  {
   self->removeComponent(name);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getComponent of class  GEntity */
#ifndef TOLUA_DISABLE_tolua_game_GEntity_getComponent00
static int tolua_game_GEntity_getComponent00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GEntity",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GEntity* self = (GEntity*)  tolua_tousertype(tolua_S,1,0);
  std::string name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getComponent'", NULL);
#endif
  {
   GComponent* tolua_ret = (GComponent*)  self->getComponent(name);
    tolua_ext_object_to_luaval<GComponent>(tolua_S,(void*)tolua_ret,"GComponent");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getId of class  GEntity */
#ifndef TOLUA_DISABLE_tolua_game_GEntity_getId00
static int tolua_game_GEntity_getId00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GEntity",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GEntity* self = (GEntity*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getId'", NULL);
#endif
  {
   unsigned int tolua_ret = ( unsigned int)  self->getId();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GAvatarComponent */
#ifndef TOLUA_DISABLE_tolua_game_GAvatarComponent_new00
static int tolua_game_GAvatarComponent_new00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GAvatarComponent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GAvatarComponent* tolua_ret = (GAvatarComponent*)  Mtolua_new((GAvatarComponent)());
    tolua_ext_object_to_luaval<GAvatarComponent>(tolua_S,(void*)tolua_ret,"GAvatarComponent");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GAvatarComponent */
#ifndef TOLUA_DISABLE_tolua_game_GAvatarComponent_new00_local
static int tolua_game_GAvatarComponent_new00_local(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GAvatarComponent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GAvatarComponent* tolua_ret = (GAvatarComponent*)  Mtolua_new((GAvatarComponent)());
    tolua_ext_object_to_luaval<GAvatarComponent>(tolua_S,(void*)tolua_ret,"GAvatarComponent");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRootNode of class  GAvatarComponent */
#ifndef TOLUA_DISABLE_tolua_game_GAvatarComponent_getRootNode00
static int tolua_game_GAvatarComponent_getRootNode00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GAvatarComponent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GAvatarComponent* self = (GAvatarComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRootNode'", NULL);
#endif
  {
   Node* tolua_ret = (Node*)  self->getRootNode();
    tolua_ext_object_to_luaval<Node>(tolua_S,(void*)tolua_ret,"cc.Node");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRootNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSkill of class  GActorComponent */
#ifndef TOLUA_DISABLE_tolua_game_GActorComponent_getSkill00
static int tolua_game_GActorComponent_getSkill00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GActorComponent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GActorComponent* self = (GActorComponent*)  tolua_tousertype(tolua_S,1,0);
   int id = ((  int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSkill'", NULL);
#endif
  {
   GSkill* tolua_ret = (GSkill*)  self->getSkill(id);
    tolua_ext_object_to_luaval<GSkill>(tolua_S,(void*)tolua_ret,"GSkill");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSkill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurSkill of class  GActorComponent */
#ifndef TOLUA_DISABLE_tolua_game_GActorComponent_getCurSkill00
static int tolua_game_GActorComponent_getCurSkill00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GActorComponent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GActorComponent* self = (GActorComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurSkill'", NULL);
#endif
  {
   GSkill* tolua_ret = (GSkill*)  self->getCurSkill();
    tolua_ext_object_to_luaval<GSkill>(tolua_S,(void*)tolua_ret,"GSkill");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurSkill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: doSkill of class  GActorComponent */
#ifndef TOLUA_DISABLE_tolua_game_GActorComponent_doSkill00
static int tolua_game_GActorComponent_doSkill00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GActorComponent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GActorComponent* self = (GActorComponent*)  tolua_tousertype(tolua_S,1,0);
   int id = ((  int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'doSkill'", NULL);
#endif
  {
   self->doSkill(id);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'doSkill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isKeepPress of class  GActorComponent */
#ifndef TOLUA_DISABLE_tolua_game_GActorComponent_isKeepPress00
static int tolua_game_GActorComponent_isKeepPress00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GActorComponent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GActorComponent* self = (GActorComponent*)  tolua_tousertype(tolua_S,1,0);
  unsigned int key = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isKeepPress'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isKeepPress(key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isKeepPress'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isKeyDown of class  GActorComponent */
#ifndef TOLUA_DISABLE_tolua_game_GActorComponent_isKeyDown00
static int tolua_game_GActorComponent_isKeyDown00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GActorComponent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GActorComponent* self = (GActorComponent*)  tolua_tousertype(tolua_S,1,0);
  unsigned int key = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isKeyDown'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isKeyDown(key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isKeyDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isKeyUp of class  GActorComponent */
#ifndef TOLUA_DISABLE_tolua_game_GActorComponent_isKeyUp00
static int tolua_game_GActorComponent_isKeyUp00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GActorComponent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GActorComponent* self = (GActorComponent*)  tolua_tousertype(tolua_S,1,0);
  unsigned int key = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isKeyUp'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isKeyUp(key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isKeyUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  GActorComponent */
#ifndef TOLUA_DISABLE_tolua_game_GActorComponent_setPosition00
static int tolua_game_GActorComponent_setPosition00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GActorComponent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GActorComponent* self = (GActorComponent*)  tolua_tousertype(tolua_S,1,0);
  float posx = ((float)  tolua_tonumber(tolua_S,2,0));
  float posy = ((float)  tolua_tonumber(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
  {
   self->setPosition(posx,posy);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isInAir of class  GActorComponent */
#ifndef TOLUA_DISABLE_tolua_game_GActorComponent_isInAir00
static int tolua_game_GActorComponent_isInAir00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GActorComponent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GActorComponent* self = (GActorComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isInAir'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isInAir();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isInAir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isLeft of class  GActorComponent */
#ifndef TOLUA_DISABLE_tolua_game_GActorComponent_isLeft00
static int tolua_game_GActorComponent_isLeft00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GActorComponent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GActorComponent* self = (GActorComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isLeft'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isLeft();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isLeft'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: moveSpeed of class  GDataComponent */
#ifndef TOLUA_DISABLE_tolua_get_GDataComponent_moveSpeed
static int tolua_get_GDataComponent_moveSpeed(lua_State* tolua_S)
{
  GDataComponent* self = (GDataComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'moveSpeed'",NULL);
#endif
   tolua_ext_fvec2_value_to_luaval(tolua_S,self->moveSpeed,"GFixedVec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: moveSpeed of class  GDataComponent */
#ifndef TOLUA_DISABLE_tolua_set_GDataComponent_moveSpeed
static int tolua_set_GDataComponent_moveSpeed(lua_State* tolua_S)
{
  GDataComponent* self = (GDataComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'moveSpeed'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"GFixedVec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->moveSpeed = (  tolua_ext_luaval_to_fvec2_value(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: force of class  GDataComponent */
#ifndef TOLUA_DISABLE_tolua_get_GDataComponent_force
static int tolua_get_GDataComponent_force(lua_State* tolua_S)
{
  GDataComponent* self = (GDataComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'force'",NULL);
#endif
   tolua_ext_fvec3_value_to_luaval(tolua_S,self->force,"GFixedVec3");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: force of class  GDataComponent */
#ifndef TOLUA_DISABLE_tolua_set_GDataComponent_force
static int tolua_set_GDataComponent_force(lua_State* tolua_S)
{
  GDataComponent* self = (GDataComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'force'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"GFixedVec3",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->force = (  tolua_ext_luaval_to_fvec3_value(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: impulse of class  GDataComponent */
#ifndef TOLUA_DISABLE_tolua_get_GDataComponent_impulse
static int tolua_get_GDataComponent_impulse(lua_State* tolua_S)
{
  GDataComponent* self = (GDataComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'impulse'",NULL);
#endif
   tolua_ext_fvec3_value_to_luaval(tolua_S,self->impulse,"GFixedVec3");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: impulse of class  GDataComponent */
#ifndef TOLUA_DISABLE_tolua_set_GDataComponent_impulse
static int tolua_set_GDataComponent_impulse(lua_State* tolua_S)
{
  GDataComponent* self = (GDataComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'impulse'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"GFixedVec3",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->impulse = (  tolua_ext_luaval_to_fvec3_value(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: linearVelocity of class  GRigidBodyComponent */
#ifndef TOLUA_DISABLE_tolua_get_GRigidBodyComponent_linearVelocity
static int tolua_get_GRigidBodyComponent_linearVelocity(lua_State* tolua_S)
{
  GRigidBodyComponent* self = (GRigidBodyComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'linearVelocity'",NULL);
#endif
   tolua_ext_fvec3_value_to_luaval(tolua_S,self->linearVelocity,"GFixedVec3");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: linearVelocity of class  GRigidBodyComponent */
#ifndef TOLUA_DISABLE_tolua_set_GRigidBodyComponent_linearVelocity
static int tolua_set_GRigidBodyComponent_linearVelocity(lua_State* tolua_S)
{
  GRigidBodyComponent* self = (GRigidBodyComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'linearVelocity'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"GFixedVec3",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->linearVelocity = (  tolua_ext_luaval_to_fvec3_value(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: force of class  GRigidBodyComponent */
#ifndef TOLUA_DISABLE_tolua_get_GRigidBodyComponent_force
static int tolua_get_GRigidBodyComponent_force(lua_State* tolua_S)
{
  GRigidBodyComponent* self = (GRigidBodyComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'force'",NULL);
#endif
   tolua_ext_fvec3_value_to_luaval(tolua_S,self->force,"GFixedVec3");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: force of class  GRigidBodyComponent */
#ifndef TOLUA_DISABLE_tolua_set_GRigidBodyComponent_force
static int tolua_set_GRigidBodyComponent_force(lua_State* tolua_S)
{
  GRigidBodyComponent* self = (GRigidBodyComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'force'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"GFixedVec3",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->force = (  tolua_ext_luaval_to_fvec3_value(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMass of class  GRigidBodyComponent */
#ifndef TOLUA_DISABLE_tolua_game_GRigidBodyComponent_setMass00
static int tolua_game_GRigidBodyComponent_setMass00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GRigidBodyComponent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GRigidBodyComponent* self = (GRigidBodyComponent*)  tolua_tousertype(tolua_S,1,0);
  float mass = ((float)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMass'", NULL);
#endif
  {
   self->setMass(mass);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: appendOffsetOneSecond of class  GRigidBodyComponent */
#ifndef TOLUA_DISABLE_tolua_game_GRigidBodyComponent_appendOffsetOneSecond00
static int tolua_game_GRigidBodyComponent_appendOffsetOneSecond00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GRigidBodyComponent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GRigidBodyComponent* self = (GRigidBodyComponent*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'appendOffsetOneSecond'", NULL);
#endif
  {
   self->appendOffsetOneSecond(x,y);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'appendOffsetOneSecond'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: applyForce of class  GRigidBodyComponent */
#ifndef TOLUA_DISABLE_tolua_game_GRigidBodyComponent_applyForce00
static int tolua_game_GRigidBodyComponent_applyForce00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GRigidBodyComponent",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"GFixedVec3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GRigidBodyComponent* self = (GRigidBodyComponent*)  tolua_tousertype(tolua_S,1,0);
  GFixedVec3 f = (  tolua_ext_luaval_to_fvec3_value(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'applyForce'", NULL);
#endif
  {
   self->applyForce(f);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'applyForce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: applyImpulse of class  GRigidBodyComponent */
#ifndef TOLUA_DISABLE_tolua_game_GRigidBodyComponent_applyImpulse00
static int tolua_game_GRigidBodyComponent_applyImpulse00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GRigidBodyComponent",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"GFixedVec3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GRigidBodyComponent* self = (GRigidBodyComponent*)  tolua_tousertype(tolua_S,1,0);
  GFixedVec3 impulse = (  tolua_ext_luaval_to_fvec3_value(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'applyImpulse'", NULL);
#endif
  {
   self->applyImpulse(impulse);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'applyImpulse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSkill of class  GChannel */
#ifndef TOLUA_DISABLE_tolua_game_GChannel_getSkill00
static int tolua_game_GChannel_getSkill00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GChannel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GChannel* self = (GChannel*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSkill'", NULL);
#endif
  {
   GSkill* tolua_ret = (GSkill*)  self->getSkill();
    tolua_ext_object_to_luaval<GSkill>(tolua_S,(void*)tolua_ret,"GSkill");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSkill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNextSkillId of class  GChannel */
#ifndef TOLUA_DISABLE_tolua_game_GChannel_getNextSkillId00
static int tolua_game_GChannel_getNextSkillId00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GChannel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GChannel* self = (GChannel*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNextSkillId'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getNextSkillId();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNextSkillId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBeginFrame of class  GCondition */
#ifndef TOLUA_DISABLE_tolua_game_GCondition_getBeginFrame00
static int tolua_game_GCondition_getBeginFrame00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GCondition",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GCondition* self = (GCondition*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBeginFrame'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getBeginFrame();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBeginFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFrameLen of class  GCondition */
#ifndef TOLUA_DISABLE_tolua_game_GCondition_getFrameLen00
static int tolua_game_GCondition_getFrameLen00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GCondition",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GCondition* self = (GCondition*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFrameLen'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getFrameLen();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFrameLen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChannel of class  GCondition */
#ifndef TOLUA_DISABLE_tolua_game_GCondition_getChannel00
static int tolua_game_GCondition_getChannel00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GCondition",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GCondition* self = (GCondition*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChannel'", NULL);
#endif
  {
   GChannel* tolua_ret = (GChannel*)  self->getChannel();
    tolua_ext_object_to_luaval<GChannel>(tolua_S,(void*)tolua_ret,"GChannel");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChannel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getType of class  GCondition */
#ifndef TOLUA_DISABLE_tolua_game_GCondition_getType00
static int tolua_game_GCondition_getType00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GCondition",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GCondition* self = (GCondition*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getType'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEntity of class  GCondition */
#ifndef TOLUA_DISABLE_tolua_game_GCondition_getEntity00
static int tolua_game_GCondition_getEntity00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GCondition",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GCondition* self = (GCondition*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEntity'", NULL);
#endif
  {
   GEntity* tolua_ret = (GEntity*)  self->getEntity();
    tolua_ext_object_to_luaval<GEntity>(tolua_S,(void*)tolua_ret,"GEntity");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEntity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getArgStr of class  GScriptCondition */
#ifndef TOLUA_DISABLE_tolua_game_GScriptCondition_getArgStr00
static int tolua_game_GScriptCondition_getArgStr00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GScriptCondition",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GScriptCondition* self = (GScriptCondition*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getArgStr'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getArgStr();
   tolua_pushcppstring(tolua_S,tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getArgStr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTrack of class  GSkill */
#ifndef TOLUA_DISABLE_tolua_game_GSkill_getTrack00
static int tolua_game_GSkill_getTrack00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GSkill",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GSkill* self = (GSkill*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTrack'", NULL);
#endif
  {
   GTrack* tolua_ret = (GTrack*)  self->getTrack();
    tolua_ext_object_to_luaval<GTrack>(tolua_S,(void*)tolua_ret,"GTrack");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTrack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  GSkill */
#ifndef TOLUA_DISABLE_tolua_game_GSkill_getName00
static int tolua_game_GSkill_getName00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GSkill",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GSkill* self = (GSkill*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getName();
   tolua_pushcppstring(tolua_S,tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getId of class  GSkill */
#ifndef TOLUA_DISABLE_tolua_game_GSkill_getId00
static int tolua_game_GSkill_getId00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GSkill",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GSkill* self = (GSkill*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getId'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->getId();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTotalFrame of class  GSkill */
#ifndef TOLUA_DISABLE_tolua_game_GSkill_getTotalFrame00
static int tolua_game_GSkill_getTotalFrame00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GSkill",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GSkill* self = (GSkill*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTotalFrame'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->getTotalFrame();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTotalFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurFrame of class  GSkill */
#ifndef TOLUA_DISABLE_tolua_game_GSkill_getCurFrame00
static int tolua_game_GSkill_getCurFrame00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GSkill",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GSkill* self = (GSkill*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurFrame'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->getCurFrame();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTotalLoopCount of class  GSkill */
#ifndef TOLUA_DISABLE_tolua_game_GSkill_getTotalLoopCount00
static int tolua_game_GSkill_getTotalLoopCount00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GSkill",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GSkill* self = (GSkill*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTotalLoopCount'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->getTotalLoopCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTotalLoopCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurLoopCount of class  GSkill */
#ifndef TOLUA_DISABLE_tolua_game_GSkill_getCurLoopCount00
static int tolua_game_GSkill_getCurLoopCount00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GSkill",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GSkill* self = (GSkill*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurLoopCount'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->getCurLoopCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurLoopCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurAction of class  GSkill */
#ifndef TOLUA_DISABLE_tolua_game_GSkill_getCurAction00
static int tolua_game_GSkill_getCurAction00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GSkill",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GSkill* self = (GSkill*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurAction'", NULL);
#endif
  {
   GAction* tolua_ret = (GAction*)  self->getCurAction();
    tolua_ext_object_to_luaval<GAction>(tolua_S,(void*)tolua_ret,"GAction");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurActionIdx of class  GSkill */
#ifndef TOLUA_DISABLE_tolua_game_GSkill_getCurActionIdx00
static int tolua_game_GSkill_getCurActionIdx00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GSkill",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GSkill* self = (GSkill*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurActionIdx'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->getCurActionIdx();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurActionIdx'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getActions of class  GSkill */
#ifndef TOLUA_DISABLE_tolua_game_GSkill_getActions00
static int tolua_game_GSkill_getActions00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GSkill",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GSkill* self = (GSkill*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getActions'", NULL);
#endif
  {
   std::vector<GAction*> tolua_ret = (std::vector<GAction*>)  self->getActions();
   {
   tolua_ext_object_arr_to_luaval<GAction>(tolua_S, tolua_ret, "std::vector<GAction*>");
   }
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getActions'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChannel of class  GSkill */
#ifndef TOLUA_DISABLE_tolua_game_GSkill_getChannel00
static int tolua_game_GSkill_getChannel00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GSkill",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GSkill* self = (GSkill*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChannel'", NULL);
#endif
  {
   std::vector<GChannel*> tolua_ret = (std::vector<GChannel*>)  self->getChannel();
   {
   tolua_ext_object_arr_to_luaval<GChannel>(tolua_S, tolua_ret, "std::vector<GChannel*>");
   }
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChannel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getActorComponent of class  GSkill */
#ifndef TOLUA_DISABLE_tolua_game_GSkill_getActorComponent00
static int tolua_game_GSkill_getActorComponent00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GSkill",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GSkill* self = (GSkill*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getActorComponent'", NULL);
#endif
  {
   GActorComponent* tolua_ret = (GActorComponent*)  self->getActorComponent();
    tolua_ext_object_to_luaval<GActorComponent>(tolua_S,(void*)tolua_ret,"GActorComponent");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getActorComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEntity of class  GSkill */
#ifndef TOLUA_DISABLE_tolua_game_GSkill_getEntity00
static int tolua_game_GSkill_getEntity00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GSkill",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GSkill* self = (GSkill*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEntity'", NULL);
#endif
  {
   GEntity* tolua_ret = (GEntity*)  self->getEntity();
    tolua_ext_object_to_luaval<GEntity>(tolua_S,(void*)tolua_ret,"GEntity");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEntity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSkill of class  GTimeline */
#ifndef TOLUA_DISABLE_tolua_game_GTimeline_getSkill00
static int tolua_game_GTimeline_getSkill00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GTimeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GTimeline* self = (GTimeline*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSkill'", NULL);
#endif
  {
   GSkill* tolua_ret = (GSkill*)  self->getSkill();
    tolua_ext_object_to_luaval<GSkill>(tolua_S,(void*)tolua_ret,"GSkill");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSkill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTrack of class  GTimeline */
#ifndef TOLUA_DISABLE_tolua_game_GTimeline_getTrack00
static int tolua_game_GTimeline_getTrack00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GTimeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GTimeline* self = (GTimeline*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTrack'", NULL);
#endif
  {
   GTrack* tolua_ret = (GTrack*)  self->getTrack();
    tolua_ext_object_to_luaval<GTrack>(tolua_S,(void*)tolua_ret,"GTrack");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTrack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFrame of class  GTimeline */
#ifndef TOLUA_DISABLE_tolua_game_GTimeline_getFrame00
static int tolua_game_GTimeline_getFrame00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GTimeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GTimeline* self = (GTimeline*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFrame'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getFrame();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurFrame of class  GTimeline */
#ifndef TOLUA_DISABLE_tolua_game_GTimeline_getCurFrame00
static int tolua_game_GTimeline_getCurFrame00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GTimeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GTimeline* self = (GTimeline*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurFrame'", NULL);
#endif
  {
   GFrame* tolua_ret = (GFrame*)  self->getCurFrame();
    tolua_ext_object_to_luaval<GFrame>(tolua_S,(void*)tolua_ret,"GFrame");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFrames of class  GTimeline */
#ifndef TOLUA_DISABLE_tolua_game_GTimeline_getFrames00
static int tolua_game_GTimeline_getFrames00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GTimeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GTimeline* self = (GTimeline*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFrames'", NULL);
#endif
  {
   std::vector<GFrame*> tolua_ret = (std::vector<GFrame*>)  self->getFrames();
   {
   tolua_ext_object_arr_to_luaval<GFrame>(tolua_S, tolua_ret, "std::vector<GFrame*>");
   }
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFrames'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSkill of class  GTrack */
#ifndef TOLUA_DISABLE_tolua_game_GTrack_getSkill00
static int tolua_game_GTrack_getSkill00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GTrack",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GTrack* self = (GTrack*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSkill'", NULL);
#endif
  {
   GSkill* tolua_ret = (GSkill*)  self->getSkill();
    tolua_ext_object_to_luaval<GSkill>(tolua_S,(void*)tolua_ret,"GSkill");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSkill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTimelines of class  GTrack */
#ifndef TOLUA_DISABLE_tolua_game_GTrack_getTimelines00
static int tolua_game_GTrack_getTimelines00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GTrack",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GTrack* self = (GTrack*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTimelines'", NULL);
#endif
  {
   std::vector<GTimeline*> tolua_ret = (std::vector<GTimeline*>)  self->getTimelines();
   {
   tolua_ext_object_arr_to_luaval<GTimeline>(tolua_S, tolua_ret, "std::vector<GTimeline*>");
   }
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTimelines'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStartFrame of class  GFrame */
#ifndef TOLUA_DISABLE_tolua_game_GFrame_getStartFrame00
static int tolua_game_GFrame_getStartFrame00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GFrame* self = (GFrame*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStartFrame'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getStartFrame();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStartFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFrameLen of class  GFrame */
#ifndef TOLUA_DISABLE_tolua_game_GFrame_getFrameLen00
static int tolua_game_GFrame_getFrameLen00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GFrame* self = (GFrame*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFrameLen'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getFrameLen();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFrameLen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTimeline of class  GFrame */
#ifndef TOLUA_DISABLE_tolua_game_GFrame_getTimeline00
static int tolua_game_GFrame_getTimeline00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GFrame* self = (GFrame*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTimeline'", NULL);
#endif
  {
   GTimeline* tolua_ret = (GTimeline*)  self->getTimeline();
    tolua_ext_object_to_luaval<GTimeline>(tolua_S,(void*)tolua_ret,"GTimeline");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTimeline'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEntity of class  GFrame */
#ifndef TOLUA_DISABLE_tolua_game_GFrame_getEntity00
static int tolua_game_GFrame_getEntity00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GFrame* self = (GFrame*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEntity'", NULL);
#endif
  {
   GEntity* tolua_ret = (GEntity*)  self->getEntity();
    tolua_ext_object_to_luaval<GEntity>(tolua_S,(void*)tolua_ret,"GEntity");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEntity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getComponent of class  GFrame */
#ifndef TOLUA_DISABLE_tolua_game_GFrame_getComponent00
static int tolua_game_GFrame_getComponent00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GFrame",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GFrame* self = (GFrame*)  tolua_tousertype(tolua_S,1,0);
  std::string name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getComponent'", NULL);
#endif
  {
   GComponent* tolua_ret = (GComponent*)  self->getComponent(name);
    tolua_ext_object_to_luaval<GComponent>(tolua_S,(void*)tolua_ret,"GComponent");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSkill of class  GFrame */
#ifndef TOLUA_DISABLE_tolua_game_GFrame_getSkill00
static int tolua_game_GFrame_getSkill00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GFrame* self = (GFrame*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSkill'", NULL);
#endif
  {
   GSkill* tolua_ret = (GSkill*)  self->getSkill();
    tolua_ext_object_to_luaval<GSkill>(tolua_S,(void*)tolua_ret,"GSkill");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSkill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTriggerMaxCount of class  GEventFrame */
#ifndef TOLUA_DISABLE_tolua_game_GEventFrame_getTriggerMaxCount00
static int tolua_game_GEventFrame_getTriggerMaxCount00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GEventFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GEventFrame* self = (GEventFrame*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTriggerMaxCount'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getTriggerMaxCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTriggerMaxCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTriggerMaxCount of class  GEventFrame */
#ifndef TOLUA_DISABLE_tolua_game_GEventFrame_setTriggerMaxCount00
static int tolua_game_GEventFrame_setTriggerMaxCount00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GEventFrame",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GEventFrame* self = (GEventFrame*)  tolua_tousertype(tolua_S,1,0);
  int value = ((int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTriggerMaxCount'", NULL);
#endif
  {
   self->setTriggerMaxCount(value);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTriggerMaxCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTriggerInterval of class  GEventFrame */
#ifndef TOLUA_DISABLE_tolua_game_GEventFrame_getTriggerInterval00
static int tolua_game_GEventFrame_getTriggerInterval00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GEventFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GEventFrame* self = (GEventFrame*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTriggerInterval'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getTriggerInterval();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTriggerInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTriggerInterval of class  GEventFrame */
#ifndef TOLUA_DISABLE_tolua_game_GEventFrame_setTriggerInterval00
static int tolua_game_GEventFrame_setTriggerInterval00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GEventFrame",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GEventFrame* self = (GEventFrame*)  tolua_tousertype(tolua_S,1,0);
  int value = ((int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTriggerInterval'", NULL);
#endif
  {
   self->setTriggerInterval(value);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTriggerInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurTriggerCount of class  GEventFrame */
#ifndef TOLUA_DISABLE_tolua_game_GEventFrame_getCurTriggerCount00
static int tolua_game_GEventFrame_getCurTriggerCount00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GEventFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GEventFrame* self = (GEventFrame*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurTriggerCount'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getCurTriggerCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurTriggerCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLastTriggerFrameIndex of class  GEventFrame */
#ifndef TOLUA_DISABLE_tolua_game_GEventFrame_getLastTriggerFrameIndex00
static int tolua_game_GEventFrame_getLastTriggerFrameIndex00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GEventFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GEventFrame* self = (GEventFrame*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLastTriggerFrameIndex'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getLastTriggerFrameIndex();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLastTriggerFrameIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: canTrigger of class  GEventFrame */
#ifndef TOLUA_DISABLE_tolua_game_GEventFrame_canTrigger00
static int tolua_game_GEventFrame_canTrigger00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GEventFrame",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GEventFrame* self = (GEventFrame*)  tolua_tousertype(tolua_S,1,0);
  int currentFrameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'canTrigger'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->canTrigger(currentFrameIndex);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'canTrigger'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getArgStr of class  GScriptFrame */
#ifndef TOLUA_DISABLE_tolua_game_GScriptFrame_getArgStr00
static int tolua_game_GScriptFrame_getArgStr00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GScriptFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GScriptFrame* self = (GScriptFrame*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getArgStr'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getArgStr();
   tolua_pushcppstring(tolua_S,tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getArgStr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getElapsed of class  GAction */
#ifndef TOLUA_DISABLE_tolua_game_GAction_getElapsed00
static int tolua_game_GAction_getElapsed00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GAction",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GAction* self = (GAction*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getElapsed'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->getElapsed();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getElapsed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFrameLength of class  GAction */
#ifndef TOLUA_DISABLE_tolua_game_GAction_getFrameLength00
static int tolua_game_GAction_getFrameLength00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GAction",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GAction* self = (GAction*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFrameLength'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->getFrameLength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFrameLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: interrupt of class  GAction */
#ifndef TOLUA_DISABLE_tolua_game_GAction_interrupt00
static int tolua_game_GAction_interrupt00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GAction",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GAction* self = (GAction*)  tolua_tousertype(tolua_S,1,0);
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'interrupt'", NULL);
#endif
  {
   self->interrupt((GInterruptType)type);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'interrupt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurLoopCount of class  GAction */
#ifndef TOLUA_DISABLE_tolua_game_GAction_getCurLoopCount00
static int tolua_game_GAction_getCurLoopCount00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GAction",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GAction* self = (GAction*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurLoopCount'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->getCurLoopCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurLoopCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  GAction */
#ifndef TOLUA_DISABLE_tolua_game_GAction_getName00
static int tolua_game_GAction_getName00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GAction",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GAction* self = (GAction*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getName();
   tolua_pushcppstring(tolua_S,tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurFrame of class  GAction */
#ifndef TOLUA_DISABLE_tolua_game_GAction_getCurFrame00
static int tolua_game_GAction_getCurFrame00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GAction",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GAction* self = (GAction*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurFrame'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->getCurFrame();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isInRect of class  GTools */
#ifndef TOLUA_DISABLE_tolua_game_GTools_isInRect00
static int tolua_game_GTools_isInRect00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GTools",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"cc.Node",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* InNode = ((Node*)  tolua_tousertype(tolua_S,2,0));
  float InX = ((float)  tolua_tonumber(tolua_S,3,0));
  float InY = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   bool tolua_ret = (bool)  GTools::isInRect(InNode,InX,InY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isInRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: copyFile of class  GTools */
#ifndef TOLUA_DISABLE_tolua_game_GTools_copyFile00
static int tolua_game_GTools_copyFile00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GTools",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string filepath = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  std::string newFilepath = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  GTools::copyFile(filepath,newFilepath);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'copyFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: U32_OR of class  GTools */
#ifndef TOLUA_DISABLE_tolua_game_GTools_U32_OR00
static int tolua_game_GTools_U32_OR00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GTools",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int src = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int dst = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  {
   unsigned int tolua_ret = (unsigned int)  GTools::U32_OR(src,dst);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'U32_OR'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: U32_AND of class  GTools */
#ifndef TOLUA_DISABLE_tolua_game_GTools_U32_AND00
static int tolua_game_GTools_U32_AND00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GTools",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int src = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int dst = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  {
   unsigned int tolua_ret = (unsigned int)  GTools::U32_AND(src,dst);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'U32_AND'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: U32_BIT_SET of class  GTools */
#ifndef TOLUA_DISABLE_tolua_game_GTools_U32_BIT_SET00
static int tolua_game_GTools_U32_BIT_SET00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GTools",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int b = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int flag = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  {
   unsigned int tolua_ret = (unsigned int)  GTools::U32_BIT_SET(b,flag);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'U32_BIT_SET'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: U32_BIT_GET of class  GTools */
#ifndef TOLUA_DISABLE_tolua_game_GTools_U32_BIT_GET00
static int tolua_game_GTools_U32_BIT_GET00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GTools",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int b = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int flag = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  {
   unsigned int tolua_ret = (unsigned int)  GTools::U32_BIT_GET(b,flag);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'U32_BIT_GET'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: U32_BIT_REMOVE of class  GTools */
#ifndef TOLUA_DISABLE_tolua_game_GTools_U32_BIT_REMOVE00
static int tolua_game_GTools_U32_BIT_REMOVE00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GTools",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int b = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int flag = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  {
   unsigned int tolua_ret = (unsigned int)  GTools::U32_BIT_REMOVE(b,flag);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'U32_BIT_REMOVE'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: U32_BIT_EQUAL of class  GTools */
#ifndef TOLUA_DISABLE_tolua_game_GTools_U32_BIT_EQUAL00
static int tolua_game_GTools_U32_BIT_EQUAL00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GTools",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int b = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int flag = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  GTools::U32_BIT_EQUAL(b,flag);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'U32_BIT_EQUAL'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: U32_BIT_NO_EQUAL of class  GTools */
#ifndef TOLUA_DISABLE_tolua_game_GTools_U32_BIT_NO_EQUAL00
static int tolua_game_GTools_U32_BIT_NO_EQUAL00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GTools",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int b = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int flag = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  GTools::U32_BIT_NO_EQUAL(b,flag);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'U32_BIT_NO_EQUAL'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: U32_L_SHIFT of class  GTools */
#ifndef TOLUA_DISABLE_tolua_game_GTools_U32_L_SHIFT00
static int tolua_game_GTools_U32_L_SHIFT00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GTools",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int src = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int move = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  {
   unsigned int tolua_ret = (unsigned int)  GTools::U32_L_SHIFT(src,move);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'U32_L_SHIFT'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_game_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"net_uv",0);
  tolua_beginmodule(tolua_S,"net_uv");
   tolua_cclass(tolua_S,"Session","net_uv::Session","",NULL);
   tolua_beginmodule(tolua_S,"Session");
    tolua_function(tolua_S,"send",tolua_game_net_uv_Session_send00);
    tolua_function(tolua_S,"disconnect",tolua_game_net_uv_Session_disconnect00);
    tolua_function(tolua_S,"getSessionID",tolua_game_net_uv_Session_getSessionID00);
    tolua_function(tolua_S,"getPort",tolua_game_net_uv_Session_getPort00);
    tolua_function(tolua_S,"getIp",tolua_game_net_uv_Session_getIp00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"NetClient","CCNetClient","cc.Ref",NULL);
  tolua_beginmodule(tolua_S,"NetClient");
   tolua_function(tolua_S,"create",tolua_game_NetClient_create00);
   tolua_function(tolua_S,"connect",tolua_game_NetClient_connect00);
   tolua_function(tolua_S,"removeSession",tolua_game_NetClient_removeSession00);
   tolua_function(tolua_S,"disconnect",tolua_game_NetClient_disconnect00);
   tolua_function(tolua_S,"sendMsg",tolua_game_NetClient_sendMsg00);
   tolua_function(tolua_S,"setHeartBeatTime",tolua_game_NetClient_setHeartBeatTime00);
   tolua_function(tolua_S,"setHeartBeatLoseMaxCount",tolua_game_NetClient_setHeartBeatLoseMaxCount00);
   tolua_function(tolua_S,"closeClient",tolua_game_NetClient_closeClient00);
   tolua_function(tolua_S,"registerLuaHandle",tolua_game_NetClient_registerLuaHandle00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GVirtualCamera","GVirtualCamera","",NULL);
  tolua_beginmodule(tolua_S,"GVirtualCamera");
   tolua_function(tolua_S,"setPosition",tolua_game_GVirtualCamera_setPosition00);
   tolua_function(tolua_S,"setZoom",tolua_game_GVirtualCamera_setZoom00);
   tolua_function(tolua_S,"setAnchorPoint",tolua_game_GVirtualCamera_setAnchorPoint00);
   tolua_function(tolua_S,"validPosition",tolua_game_GVirtualCamera_validPosition00);
   tolua_function(tolua_S,"setCameraBoundingBox",tolua_game_GVirtualCamera_setCameraBoundingBox00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GMapLayer","GMapLayer","cc.Node",NULL);
  tolua_beginmodule(tolua_S,"GMapLayer");
   tolua_function(tolua_S,"getActorNode",tolua_game_GMapLayer_getActorNode00);
   tolua_function(tolua_S,"getRootNode",tolua_game_GMapLayer_getRootNode00);
   tolua_function(tolua_S,"getVirtualCamera",tolua_game_GMapLayer_getVirtualCamera00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"GGameWorld","GGameWorld","",tolua_collect_GGameWorld);
  #else
  tolua_cclass(tolua_S,"GGameWorld","GGameWorld","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"GGameWorld");
   tolua_function(tolua_S,"delete",tolua_game_GGameWorld_delete00);
   tolua_function(tolua_S,"getInstance",tolua_game_GGameWorld_getInstance00);
   tolua_function(tolua_S,"create",tolua_game_GGameWorld_create00);
   tolua_function(tolua_S,"step",tolua_game_GGameWorld_step00);
   tolua_function(tolua_S,"render",tolua_game_GGameWorld_render00);
   tolua_function(tolua_S,"input",tolua_game_GGameWorld_input00);
   tolua_function(tolua_S,"spwanActor",tolua_game_GGameWorld_spwanActor00);
   tolua_function(tolua_S,"enableDebugDraw",tolua_game_GGameWorld_enableDebugDraw00);
   tolua_function(tolua_S,"setScheduler",tolua_game_GGameWorld_setScheduler00);
   tolua_function(tolua_S,"getLocalPlayer",tolua_game_GGameWorld_getLocalPlayer00);
   tolua_function(tolua_S,"setLocalPlayer",tolua_game_GGameWorld_setLocalPlayer00);
   tolua_function(tolua_S,"registerLuaHandle",tolua_game_GGameWorld_registerLuaHandle00);
   tolua_function(tolua_S,"getMapLayer",tolua_game_GGameWorld_getMapLayer00);
   tolua_function(tolua_S,"getGameLogicFrame",tolua_game_GGameWorld_getGameLogicFrame00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"slot",1);
  tolua_beginmodule(tolua_S,"slot");
   tolua_variable(tolua_S,"G_KEY_NONE",tolua_get_slot_unsigned_G_KEY_NONE,NULL);
   tolua_variable(tolua_S,"G_KEY_MOVE_LEFT",tolua_get_slot_unsigned_G_KEY_MOVE_LEFT,NULL);
   tolua_variable(tolua_S,"G_KEY_MOVE_RIGHT",tolua_get_slot_unsigned_G_KEY_MOVE_RIGHT,NULL);
   tolua_variable(tolua_S,"G_KEY_MOVE_UP",tolua_get_slot_unsigned_G_KEY_MOVE_UP,NULL);
   tolua_variable(tolua_S,"G_KEY_MOVE_DOWN",tolua_get_slot_unsigned_G_KEY_MOVE_DOWN,NULL);
   tolua_variable(tolua_S,"G_KEY_JUMP",tolua_get_slot_unsigned_G_KEY_JUMP,NULL);
   tolua_variable(tolua_S,"G_KEY_SKILL_1",tolua_get_slot_unsigned_G_KEY_SKILL_1,NULL);
   tolua_variable(tolua_S,"G_KEY_SKILL_2",tolua_get_slot_unsigned_G_KEY_SKILL_2,NULL);
   tolua_variable(tolua_S,"G_KEY_SKILL_3",tolua_get_slot_unsigned_G_KEY_SKILL_3,NULL);
   tolua_variable(tolua_S,"G_KEY_SKILL_4",tolua_get_slot_unsigned_G_KEY_SKILL_4,NULL);
   tolua_variable(tolua_S,"G_KEY_SKILL_5",tolua_get_slot_unsigned_G_KEY_SKILL_5,NULL);
   tolua_variable(tolua_S,"G_KEY_SKILL_6",tolua_get_slot_unsigned_G_KEY_SKILL_6,NULL);
   tolua_variable(tolua_S,"G_KEY_SKILL_7",tolua_get_slot_unsigned_G_KEY_SKILL_7,NULL);
   tolua_variable(tolua_S,"G_KEY_MAX_COUNT",tolua_get_slot_unsigned_G_KEY_MAX_COUNT,NULL);
   tolua_variable(tolua_S,"G_KEY_MOVE_MUSTER",tolua_get_slot_unsigned_G_KEY_MOVE_MUSTER,NULL);
   tolua_variable(tolua_S,"G_KEY_MOVE_X",tolua_get_slot_unsigned_G_KEY_MOVE_X,NULL);
   tolua_variable(tolua_S,"G_KEY_MOVE_Y",tolua_get_slot_unsigned_G_KEY_MOVE_Y,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GComponent","GComponent","",NULL);
  tolua_beginmodule(tolua_S,"GComponent");
   tolua_function(tolua_S,"addComponent",tolua_game_GComponent_addComponent00);
   tolua_function(tolua_S,"removeComponent",tolua_game_GComponent_removeComponent00);
   tolua_function(tolua_S,"getComponent",tolua_game_GComponent_getComponent00);
   tolua_function(tolua_S,"getEntity",tolua_game_GComponent_getEntity00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GEntity","GEntity","",NULL);
  tolua_beginmodule(tolua_S,"GEntity");
   tolua_function(tolua_S,"addComponent",tolua_game_GEntity_addComponent00);
   tolua_function(tolua_S,"removeComponent",tolua_game_GEntity_removeComponent00);
   tolua_function(tolua_S,"getComponent",tolua_game_GEntity_getComponent00);
   tolua_function(tolua_S,"getId",tolua_game_GEntity_getId00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"GAvatarComponent","GAvatarComponent","GComponent",tolua_collect_GAvatarComponent);
  #else
  tolua_cclass(tolua_S,"GAvatarComponent","GAvatarComponent","GComponent",NULL);
  #endif
  tolua_beginmodule(tolua_S,"GAvatarComponent");
   tolua_function(tolua_S,"new",tolua_game_GAvatarComponent_new00);
   tolua_function(tolua_S,"new_local",tolua_game_GAvatarComponent_new00_local);
   tolua_function(tolua_S,".call",tolua_game_GAvatarComponent_new00_local);
   tolua_function(tolua_S,"getRootNode",tolua_game_GAvatarComponent_getRootNode00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GActorComponent","GActorComponent","GComponent",NULL);
  tolua_beginmodule(tolua_S,"GActorComponent");
   tolua_function(tolua_S,"getSkill",tolua_game_GActorComponent_getSkill00);
   tolua_function(tolua_S,"getCurSkill",tolua_game_GActorComponent_getCurSkill00);
   tolua_function(tolua_S,"doSkill",tolua_game_GActorComponent_doSkill00);
   tolua_function(tolua_S,"isKeepPress",tolua_game_GActorComponent_isKeepPress00);
   tolua_function(tolua_S,"isKeyDown",tolua_game_GActorComponent_isKeyDown00);
   tolua_function(tolua_S,"isKeyUp",tolua_game_GActorComponent_isKeyUp00);
   tolua_function(tolua_S,"setPosition",tolua_game_GActorComponent_setPosition00);
   tolua_function(tolua_S,"isInAir",tolua_game_GActorComponent_isInAir00);
   tolua_function(tolua_S,"isLeft",tolua_game_GActorComponent_isLeft00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GDataComponent","GDataComponent","GComponent",NULL);
  tolua_beginmodule(tolua_S,"GDataComponent");
   tolua_variable(tolua_S,"moveSpeed",tolua_get_GDataComponent_moveSpeed,tolua_set_GDataComponent_moveSpeed);
   tolua_variable(tolua_S,"force",tolua_get_GDataComponent_force,tolua_set_GDataComponent_force);
   tolua_variable(tolua_S,"impulse",tolua_get_GDataComponent_impulse,tolua_set_GDataComponent_impulse);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GRigidBodyComponent","GRigidBodyComponent","GComponent",NULL);
  tolua_beginmodule(tolua_S,"GRigidBodyComponent");
   tolua_variable(tolua_S,"linearVelocity",tolua_get_GRigidBodyComponent_linearVelocity,tolua_set_GRigidBodyComponent_linearVelocity);
   tolua_variable(tolua_S,"force",tolua_get_GRigidBodyComponent_force,tolua_set_GRigidBodyComponent_force);
   tolua_function(tolua_S,"setMass",tolua_game_GRigidBodyComponent_setMass00);
   tolua_function(tolua_S,"appendOffsetOneSecond",tolua_game_GRigidBodyComponent_appendOffsetOneSecond00);
   tolua_function(tolua_S,"applyForce",tolua_game_GRigidBodyComponent_applyForce00);
   tolua_function(tolua_S,"applyImpulse",tolua_game_GRigidBodyComponent_applyImpulse00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"CheckType",0);
  tolua_beginmodule(tolua_S,"CheckType");
   tolua_constant(tolua_S,"Continuous",CheckType::Continuous);
   tolua_constant(tolua_S,"Once",CheckType::Once);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GChannel","GChannel","",NULL);
  tolua_beginmodule(tolua_S,"GChannel");
   tolua_function(tolua_S,"getSkill",tolua_game_GChannel_getSkill00);
   tolua_function(tolua_S,"getNextSkillId",tolua_game_GChannel_getNextSkillId00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GCondition","GCondition","",NULL);
  tolua_beginmodule(tolua_S,"GCondition");
   tolua_function(tolua_S,"getBeginFrame",tolua_game_GCondition_getBeginFrame00);
   tolua_function(tolua_S,"getFrameLen",tolua_game_GCondition_getFrameLen00);
   tolua_function(tolua_S,"getChannel",tolua_game_GCondition_getChannel00);
   tolua_function(tolua_S,"getType",tolua_game_GCondition_getType00);
   tolua_function(tolua_S,"getEntity",tolua_game_GCondition_getEntity00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GScriptCondition","GScriptCondition","GCondition",NULL);
  tolua_beginmodule(tolua_S,"GScriptCondition");
   tolua_function(tolua_S,"getArgStr",tolua_game_GScriptCondition_getArgStr00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GSkill","GSkill","",NULL);
  tolua_beginmodule(tolua_S,"GSkill");
   tolua_function(tolua_S,"getTrack",tolua_game_GSkill_getTrack00);
   tolua_function(tolua_S,"getName",tolua_game_GSkill_getName00);
   tolua_function(tolua_S,"getId",tolua_game_GSkill_getId00);
   tolua_function(tolua_S,"getTotalFrame",tolua_game_GSkill_getTotalFrame00);
   tolua_function(tolua_S,"getCurFrame",tolua_game_GSkill_getCurFrame00);
   tolua_function(tolua_S,"getTotalLoopCount",tolua_game_GSkill_getTotalLoopCount00);
   tolua_function(tolua_S,"getCurLoopCount",tolua_game_GSkill_getCurLoopCount00);
   tolua_function(tolua_S,"getCurAction",tolua_game_GSkill_getCurAction00);
   tolua_function(tolua_S,"getCurActionIdx",tolua_game_GSkill_getCurActionIdx00);
   tolua_function(tolua_S,"getActions",tolua_game_GSkill_getActions00);
   tolua_function(tolua_S,"getChannel",tolua_game_GSkill_getChannel00);
   tolua_function(tolua_S,"getActorComponent",tolua_game_GSkill_getActorComponent00);
   tolua_function(tolua_S,"getEntity",tolua_game_GSkill_getEntity00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GTimeline","GTimeline","",NULL);
  tolua_beginmodule(tolua_S,"GTimeline");
   tolua_function(tolua_S,"getSkill",tolua_game_GTimeline_getSkill00);
   tolua_function(tolua_S,"getTrack",tolua_game_GTimeline_getTrack00);
   tolua_function(tolua_S,"getFrame",tolua_game_GTimeline_getFrame00);
   tolua_function(tolua_S,"getCurFrame",tolua_game_GTimeline_getCurFrame00);
   tolua_function(tolua_S,"getFrames",tolua_game_GTimeline_getFrames00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GTrack","GTrack","",NULL);
  tolua_beginmodule(tolua_S,"GTrack");
   tolua_function(tolua_S,"getSkill",tolua_game_GTrack_getSkill00);
   tolua_function(tolua_S,"getTimelines",tolua_game_GTrack_getTimelines00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GFrame","GFrame","",NULL);
  tolua_beginmodule(tolua_S,"GFrame");
   tolua_function(tolua_S,"getStartFrame",tolua_game_GFrame_getStartFrame00);
   tolua_function(tolua_S,"getFrameLen",tolua_game_GFrame_getFrameLen00);
   tolua_function(tolua_S,"getTimeline",tolua_game_GFrame_getTimeline00);
   tolua_function(tolua_S,"getEntity",tolua_game_GFrame_getEntity00);
   tolua_function(tolua_S,"getComponent",tolua_game_GFrame_getComponent00);
   tolua_function(tolua_S,"getSkill",tolua_game_GFrame_getSkill00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GEventFrame","GEventFrame","GFrame",NULL);
  tolua_beginmodule(tolua_S,"GEventFrame");
   tolua_function(tolua_S,"getTriggerMaxCount",tolua_game_GEventFrame_getTriggerMaxCount00);
   tolua_function(tolua_S,"setTriggerMaxCount",tolua_game_GEventFrame_setTriggerMaxCount00);
   tolua_function(tolua_S,"getTriggerInterval",tolua_game_GEventFrame_getTriggerInterval00);
   tolua_function(tolua_S,"setTriggerInterval",tolua_game_GEventFrame_setTriggerInterval00);
   tolua_function(tolua_S,"getCurTriggerCount",tolua_game_GEventFrame_getCurTriggerCount00);
   tolua_function(tolua_S,"getLastTriggerFrameIndex",tolua_game_GEventFrame_getLastTriggerFrameIndex00);
   tolua_function(tolua_S,"canTrigger",tolua_game_GEventFrame_canTrigger00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GScriptFrame","GScriptFrame","GEventFrame",NULL);
  tolua_beginmodule(tolua_S,"GScriptFrame");
   tolua_function(tolua_S,"getArgStr",tolua_game_GScriptFrame_getArgStr00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GInterruptType",0);
  tolua_beginmodule(tolua_S,"GInterruptType");
   tolua_constant(tolua_S,"DELAY",GInterruptType::DELAY);
   tolua_constant(tolua_S,"PROMPTLY",GInterruptType::PROMPTLY);
   tolua_constant(tolua_S,"NONE_INTERRUPT",GInterruptType::NONE_INTERRUPT);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GAction","GAction","",NULL);
  tolua_beginmodule(tolua_S,"GAction");
   tolua_function(tolua_S,"getElapsed",tolua_game_GAction_getElapsed00);
   tolua_function(tolua_S,"getFrameLength",tolua_game_GAction_getFrameLength00);
   tolua_function(tolua_S,"interrupt",tolua_game_GAction_interrupt00);
   tolua_function(tolua_S,"getCurLoopCount",tolua_game_GAction_getCurLoopCount00);
   tolua_function(tolua_S,"getName",tolua_game_GAction_getName00);
   tolua_function(tolua_S,"getCurFrame",tolua_game_GAction_getCurFrame00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GTools","GTools","",NULL);
  tolua_beginmodule(tolua_S,"GTools");
   tolua_function(tolua_S,"isInRect",tolua_game_GTools_isInRect00);
   tolua_function(tolua_S,"copyFile",tolua_game_GTools_copyFile00);
   tolua_function(tolua_S,"U32_OR",tolua_game_GTools_U32_OR00);
   tolua_function(tolua_S,"U32_AND",tolua_game_GTools_U32_AND00);
   tolua_function(tolua_S,"U32_BIT_SET",tolua_game_GTools_U32_BIT_SET00);
   tolua_function(tolua_S,"U32_BIT_GET",tolua_game_GTools_U32_BIT_GET00);
   tolua_function(tolua_S,"U32_BIT_REMOVE",tolua_game_GTools_U32_BIT_REMOVE00);
   tolua_function(tolua_S,"U32_BIT_EQUAL",tolua_game_GTools_U32_BIT_EQUAL00);
   tolua_function(tolua_S,"U32_BIT_NO_EQUAL",tolua_game_GTools_U32_BIT_NO_EQUAL00);
   tolua_function(tolua_S,"U32_L_SHIFT",tolua_game_GTools_U32_L_SHIFT00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_game (lua_State* tolua_S) {
 return tolua_game_open(tolua_S);
};
#endif

