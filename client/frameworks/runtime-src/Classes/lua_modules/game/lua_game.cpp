/*
** Lua binding: game
** Generated automatically by tolua++-1.0.92 on 05/30/21 22:09:06.
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
#include "net_uv_cc/CCClient.h"
#include "net_uv/net_uv.h"
#include "net_uv_cc/CCNetClient.h"
#include "ecs/utils/CommonUtils.h"
#include "game/GGameWorld.h"
#include "foundation/CTools.h"
#include "ext/MyButton.h"
#include "foundation/ParticleSystemHelper.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_GGameWorld (lua_State* tolua_S)
{
 GGameWorld* self = (GGameWorld*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"TCPClient");
 tolua_usertype(tolua_S,"GGameWorld");
 tolua_usertype(tolua_S,"CTools");
 tolua_usertype(tolua_S,"CCNetClient");
 tolua_usertype(tolua_S,"cc.Ref");
 tolua_usertype(tolua_S,"KCPClient");
 tolua_usertype(tolua_S,"MyButton");
 tolua_usertype(tolua_S,"LUA_FUNCTION");
 tolua_usertype(tolua_S,"ccui.Button");
 tolua_usertype(tolua_S,"cc.Node");
 tolua_usertype(tolua_S,"net_uv::Session");
}

/* method: create of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_game_TCPClient_create00
static int tolua_game_TCPClient_create00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TCPClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TCPClient* tolua_ret = (TCPClient*)  TCPClient::create();
    tolua_ext_object_to_luaval<TCPClient>(tolua_S,(void*)tolua_ret,"TCPClient");
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

/* method: connect of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_game_TCPClient_connect00
static int tolua_game_TCPClient_connect00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPClient* self = (TCPClient*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int port = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned int sessionId = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
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

/* method: closeClient of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_game_TCPClient_closeClient00
static int tolua_game_TCPClient_closeClient00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPClient* self = (TCPClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: removeSession of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_game_TCPClient_removeSession00
static int tolua_game_TCPClient_removeSession00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPClient* self = (TCPClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
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

/* method: disconnect of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_game_TCPClient_disconnect00
static int tolua_game_TCPClient_disconnect00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPClient* self = (TCPClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
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

/* method: send of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_game_TCPClient_send00
static int tolua_game_TCPClient_send00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPClient* self = (TCPClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  char* data = ((char*)  tolua_tostring(tolua_S,3,0));
  unsigned int len = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send'", NULL);
#endif
  {
   self->send(sessionId,data,len);
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

/* method: registerLuaHandle of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_game_TCPClient_registerLuaHandle00
static int tolua_game_TCPClient_registerLuaHandle00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPClient",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPClient* self = (TCPClient*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  LUA_FUNCTION handle = (  toluafix_ref_function(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerLuaHandle'", NULL);
#endif
  {
   self->registerLuaHandle(name,handle);
   tolua_pushcppstring(tolua_S,(const char*)name);
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

/* method: create of class  KCPClient */
#ifndef TOLUA_DISABLE_tolua_game_KCPClient_create00
static int tolua_game_KCPClient_create00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"KCPClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   KCPClient* tolua_ret = (KCPClient*)  KCPClient::create();
    tolua_ext_object_to_luaval<KCPClient>(tolua_S,(void*)tolua_ret,"KCPClient");
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

/* method: connect of class  KCPClient */
#ifndef TOLUA_DISABLE_tolua_game_KCPClient_connect00
static int tolua_game_KCPClient_connect00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPClient* self = (KCPClient*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int port = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned int sessionId = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
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

/* method: closeClient of class  KCPClient */
#ifndef TOLUA_DISABLE_tolua_game_KCPClient_closeClient00
static int tolua_game_KCPClient_closeClient00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPClient* self = (KCPClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: removeSession of class  KCPClient */
#ifndef TOLUA_DISABLE_tolua_game_KCPClient_removeSession00
static int tolua_game_KCPClient_removeSession00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPClient* self = (KCPClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
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

/* method: disconnect of class  KCPClient */
#ifndef TOLUA_DISABLE_tolua_game_KCPClient_disconnect00
static int tolua_game_KCPClient_disconnect00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPClient* self = (KCPClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
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

/* method: send of class  KCPClient */
#ifndef TOLUA_DISABLE_tolua_game_KCPClient_send00
static int tolua_game_KCPClient_send00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPClient* self = (KCPClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  char* data = ((char*)  tolua_tostring(tolua_S,3,0));
  unsigned int len = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send'", NULL);
#endif
  {
   self->send(sessionId,data,len);
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

/* method: registerLuaHandle of class  KCPClient */
#ifndef TOLUA_DISABLE_tolua_game_KCPClient_registerLuaHandle00
static int tolua_game_KCPClient_registerLuaHandle00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPClient",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPClient* self = (KCPClient*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  LUA_FUNCTION handle = (  toluafix_ref_function(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerLuaHandle'", NULL);
#endif
  {
   self->registerLuaHandle(name,handle);
   tolua_pushcppstring(tolua_S,(const char*)name);
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
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
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
   tolua_pushcppstring(tolua_S,(const char*)name);
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

/* function: CommonUtils::U32_OR */
#ifndef TOLUA_DISABLE_tolua_game_CommonUtils_U32_OR00
static int tolua_game_CommonUtils_U32_OR00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int src = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  unsigned int dst = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   unsigned int tolua_ret = (unsigned int)  CommonUtils::U32_OR(src,dst);
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

/* function: CommonUtils::U32_AND */
#ifndef TOLUA_DISABLE_tolua_game_CommonUtils_U32_AND00
static int tolua_game_CommonUtils_U32_AND00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int src = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  unsigned int dst = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   unsigned int tolua_ret = (unsigned int)  CommonUtils::U32_AND(src,dst);
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

/* function: CommonUtils::U32_BIT_SET */
#ifndef TOLUA_DISABLE_tolua_game_CommonUtils_U32_BIT_SET00
static int tolua_game_CommonUtils_U32_BIT_SET00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int b = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  unsigned int flag = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   unsigned int tolua_ret = (unsigned int)  CommonUtils::U32_BIT_SET(b,flag);
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

/* function: CommonUtils::U32_BIT_GET */
#ifndef TOLUA_DISABLE_tolua_game_CommonUtils_U32_BIT_GET00
static int tolua_game_CommonUtils_U32_BIT_GET00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int b = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  unsigned int flag = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   unsigned int tolua_ret = (unsigned int)  CommonUtils::U32_BIT_GET(b,flag);
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

/* function: CommonUtils::U32_BIT_REMOVE */
#ifndef TOLUA_DISABLE_tolua_game_CommonUtils_U32_BIT_REMOVE00
static int tolua_game_CommonUtils_U32_BIT_REMOVE00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int b = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  unsigned int flag = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   unsigned int tolua_ret = (unsigned int)  CommonUtils::U32_BIT_REMOVE(b,flag);
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

/* function: CommonUtils::U32_BIT_EQUAL */
#ifndef TOLUA_DISABLE_tolua_game_CommonUtils_U32_BIT_EQUAL00
static int tolua_game_CommonUtils_U32_BIT_EQUAL00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int b = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  unsigned int flag = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  CommonUtils::U32_BIT_EQUAL(b,flag);
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

/* function: CommonUtils::U32_BIT_NO_EQUAL */
#ifndef TOLUA_DISABLE_tolua_game_CommonUtils_U32_BIT_NO_EQUAL00
static int tolua_game_CommonUtils_U32_BIT_NO_EQUAL00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int b = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  unsigned int flag = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  CommonUtils::U32_BIT_NO_EQUAL(b,flag);
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

/* function: CommonUtils::U32_L_SHIFT */
#ifndef TOLUA_DISABLE_tolua_game_CommonUtils_U32_L_SHIFT00
static int tolua_game_CommonUtils_U32_L_SHIFT00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int src = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  unsigned int move = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   unsigned int tolua_ret = (unsigned int)  CommonUtils::U32_L_SHIFT(src,move);
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

/* method: new of class  GGameWorld */
#ifndef TOLUA_DISABLE_tolua_game_GGameWorld_new00
static int tolua_game_GGameWorld_new00(lua_State* tolua_S)
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
   GGameWorld* tolua_ret = (GGameWorld*)  Mtolua_new((GGameWorld)());
    tolua_ext_object_to_luaval<GGameWorld>(tolua_S,(void*)tolua_ret,"GGameWorld");
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

/* method: new_local of class  GGameWorld */
#ifndef TOLUA_DISABLE_tolua_game_GGameWorld_new00_local
static int tolua_game_GGameWorld_new00_local(lua_State* tolua_S)
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
   GGameWorld* tolua_ret = (GGameWorld*)  Mtolua_new((GGameWorld)());
    tolua_ext_object_to_luaval<GGameWorld>(tolua_S,(void*)tolua_ret,"GGameWorld");
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

/* method: init of class  GGameWorld */
#ifndef TOLUA_DISABLE_tolua_game_GGameWorld_init00
static int tolua_game_GGameWorld_init00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GGameWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"cc.Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GGameWorld* self = (GGameWorld*)  tolua_tousertype(tolua_S,1,0);
   int mapId = ((  int)  tolua_tonumber(tolua_S,2,0));
  unsigned int randomSeed = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned int uuidSeed = (( unsigned int)  tolua_tonumber(tolua_S,4,0));
  Node* rootNode = ((Node*)  tolua_tousertype(tolua_S,5,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(mapId,randomSeed,uuidSeed,rootNode);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  GGameWorld */
#ifndef TOLUA_DISABLE_tolua_game_GGameWorld_update00
static int tolua_game_GGameWorld_update00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update(dt);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
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
  int uuid = ((int)  tolua_tonumber(tolua_S,2,0));
  unsigned int frame = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned int keydown = (( unsigned int)  tolua_tonumber(tolua_S,4,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'input'", NULL);
#endif
  {
   self->input(uuid,frame,keydown);
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

/* method: render of class  GGameWorld */
#ifndef TOLUA_DISABLE_tolua_game_GGameWorld_render00
static int tolua_game_GGameWorld_render00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'render'", NULL);
#endif
  {
   self->render();
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

/* method: getGameLogicFrame of class  GGameWorld */
#ifndef TOLUA_DISABLE_tolua_game_GGameWorld_getGameLogicFrame00
static int tolua_game_GGameWorld_getGameLogicFrame00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GGameWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GGameWorld* self = (const GGameWorld*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isInRect of class  CTools */
#ifndef TOLUA_DISABLE_tolua_game_CTools_isInRect00
static int tolua_game_CTools_isInRect00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTools",0,&tolua_err) ||
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
   bool tolua_ret = (bool)  CTools::isInRect(InNode,InX,InY);
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

/* method: create of class  MyButton */
#ifndef TOLUA_DISABLE_tolua_game_MyButton_create00
static int tolua_game_MyButton_create00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MyButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MyButton* tolua_ret = (MyButton*)  MyButton::create();
    tolua_ext_object_to_luaval<MyButton>(tolua_S,(void*)tolua_ret,"MyButton");
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

/* method: registerStateChangedCall of class  MyButton */
#ifndef TOLUA_DISABLE_tolua_game_MyButton_registerStateChangedCall00
static int tolua_game_MyButton_registerStateChangedCall00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MyButton",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MyButton* self = (MyButton*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION call = (  toluafix_ref_function(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerStateChangedCall'", NULL);
#endif
  {
   self->registerStateChangedCall(call);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerStateChangedCall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: enableTouchScaleEffect of class  MyButton */
#ifndef TOLUA_DISABLE_tolua_game_MyButton_enableTouchScaleEffect00
static int tolua_game_MyButton_enableTouchScaleEffect00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MyButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MyButton* self = (MyButton*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'enableTouchScaleEffect'", NULL);
#endif
  {
   self->enableTouchScaleEffect();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'enableTouchScaleEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disenableTouchScaleEffect of class  MyButton */
#ifndef TOLUA_DISABLE_tolua_game_MyButton_disenableTouchScaleEffect00
static int tolua_game_MyButton_disenableTouchScaleEffect00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MyButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MyButton* self = (MyButton*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disenableTouchScaleEffect'", NULL);
#endif
  {
   self->disenableTouchScaleEffect();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disenableTouchScaleEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScaleOnPressed of class  MyButton */
#ifndef TOLUA_DISABLE_tolua_game_MyButton_setScaleOnPressed00
static int tolua_game_MyButton_setScaleOnPressed00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MyButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MyButton* self = (MyButton*)  tolua_tousertype(tolua_S,1,0);
  float scale = ((float)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScaleOnPressed'", NULL);
#endif
  {
   self->setScaleOnPressed(scale);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScaleOnPressed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getScaleOnPressed of class  MyButton */
#ifndef TOLUA_DISABLE_tolua_game_MyButton_getScaleOnPressed00
static int tolua_game_MyButton_getScaleOnPressed00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MyButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MyButton* self = (MyButton*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScaleOnPressed'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getScaleOnPressed();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getScaleOnPressed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: changeParticleSystemPositionType */
#ifndef TOLUA_DISABLE_tolua_game_changeParticleSystemPositionType00
static int tolua_game_changeParticleSystemPositionType00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* root = ((Node*)  tolua_tousertype(tolua_S,1,0));
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   changeParticleSystemPositionType(root,type);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeParticleSystemPositionType'.",&tolua_err);
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
  tolua_cclass(tolua_S,"TCPClient","TCPClient","cc.Ref",NULL);
  tolua_beginmodule(tolua_S,"TCPClient");
   tolua_function(tolua_S,"create",tolua_game_TCPClient_create00);
   tolua_function(tolua_S,"connect",tolua_game_TCPClient_connect00);
   tolua_function(tolua_S,"closeClient",tolua_game_TCPClient_closeClient00);
   tolua_function(tolua_S,"removeSession",tolua_game_TCPClient_removeSession00);
   tolua_function(tolua_S,"disconnect",tolua_game_TCPClient_disconnect00);
   tolua_function(tolua_S,"send",tolua_game_TCPClient_send00);
   tolua_function(tolua_S,"registerLuaHandle",tolua_game_TCPClient_registerLuaHandle00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"KCPClient","KCPClient","cc.Ref",NULL);
  tolua_beginmodule(tolua_S,"KCPClient");
   tolua_function(tolua_S,"create",tolua_game_KCPClient_create00);
   tolua_function(tolua_S,"connect",tolua_game_KCPClient_connect00);
   tolua_function(tolua_S,"closeClient",tolua_game_KCPClient_closeClient00);
   tolua_function(tolua_S,"removeSession",tolua_game_KCPClient_removeSession00);
   tolua_function(tolua_S,"disconnect",tolua_game_KCPClient_disconnect00);
   tolua_function(tolua_S,"send",tolua_game_KCPClient_send00);
   tolua_function(tolua_S,"registerLuaHandle",tolua_game_KCPClient_registerLuaHandle00);
  tolua_endmodule(tolua_S);
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
  tolua_module(tolua_S,"CommonUtils",0);
  tolua_beginmodule(tolua_S,"CommonUtils");
   tolua_function(tolua_S,"U32_OR",tolua_game_CommonUtils_U32_OR00);
   tolua_function(tolua_S,"U32_AND",tolua_game_CommonUtils_U32_AND00);
   tolua_function(tolua_S,"U32_BIT_SET",tolua_game_CommonUtils_U32_BIT_SET00);
   tolua_function(tolua_S,"U32_BIT_GET",tolua_game_CommonUtils_U32_BIT_GET00);
   tolua_function(tolua_S,"U32_BIT_REMOVE",tolua_game_CommonUtils_U32_BIT_REMOVE00);
   tolua_function(tolua_S,"U32_BIT_EQUAL",tolua_game_CommonUtils_U32_BIT_EQUAL00);
   tolua_function(tolua_S,"U32_BIT_NO_EQUAL",tolua_game_CommonUtils_U32_BIT_NO_EQUAL00);
   tolua_function(tolua_S,"U32_L_SHIFT",tolua_game_CommonUtils_U32_L_SHIFT00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"GGameWorld","GGameWorld","",tolua_collect_GGameWorld);
  #else
  tolua_cclass(tolua_S,"GGameWorld","GGameWorld","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"GGameWorld");
   tolua_function(tolua_S,"new",tolua_game_GGameWorld_new00);
   tolua_function(tolua_S,"new_local",tolua_game_GGameWorld_new00_local);
   tolua_function(tolua_S,".call",tolua_game_GGameWorld_new00_local);
   tolua_function(tolua_S,"delete",tolua_game_GGameWorld_delete00);
   tolua_function(tolua_S,"init",tolua_game_GGameWorld_init00);
   tolua_function(tolua_S,"update",tolua_game_GGameWorld_update00);
   tolua_function(tolua_S,"input",tolua_game_GGameWorld_input00);
   tolua_function(tolua_S,"render",tolua_game_GGameWorld_render00);
   tolua_function(tolua_S,"getGameLogicFrame",tolua_game_GGameWorld_getGameLogicFrame00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CTools","CTools","",NULL);
  tolua_beginmodule(tolua_S,"CTools");
   tolua_function(tolua_S,"isInRect",tolua_game_CTools_isInRect00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"MyButton","MyButton","ccui.Button",NULL);
  tolua_beginmodule(tolua_S,"MyButton");
   tolua_function(tolua_S,"create",tolua_game_MyButton_create00);
   tolua_function(tolua_S,"registerStateChangedCall",tolua_game_MyButton_registerStateChangedCall00);
   tolua_function(tolua_S,"enableTouchScaleEffect",tolua_game_MyButton_enableTouchScaleEffect00);
   tolua_function(tolua_S,"disenableTouchScaleEffect",tolua_game_MyButton_disenableTouchScaleEffect00);
   tolua_function(tolua_S,"setScaleOnPressed",tolua_game_MyButton_setScaleOnPressed00);
   tolua_function(tolua_S,"getScaleOnPressed",tolua_game_MyButton_getScaleOnPressed00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"changeParticleSystemPositionType",tolua_game_changeParticleSystemPositionType00);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_game (lua_State* tolua_S) {
 return tolua_game_open(tolua_S);
};
#endif

