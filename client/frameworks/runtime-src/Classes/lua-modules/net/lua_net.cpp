/*
** Lua binding: net
** Generated automatically by tolua++-1.0.92 on 10/13/18 21:47:22.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"
#include "tolua++.h"
#include "lua_function/tolua_ext.h"
#include "tolua_fix.h"
//#include "LuaBasicConversions.h"


/* Exported function */
TOLUA_API int  tolua_net_open (lua_State* tolua_S);

#include "base/Session.h"
#include "base/Client.h"
#include "base/Client.h"
#include "tcp/TCPSession.h"
#include "tcp/TCPClient.h"
#include "tcp/TCPServer.h"
#include "kcp/KCPSession.h"
#include "kcp/KCPClient.h"
#include "kcp/KCPServer.h"
#include "TCPLuaClient.h"
#include "TCPLuaServer.h"
#include "KCPLuaClient.h"
#include "KCPLuaServer.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_net_uv__TCPClient (lua_State* tolua_S)
{
 net_uv::TCPClient* self = (net_uv::TCPClient*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_net_uv__KCPClient (lua_State* tolua_S)
{
 net_uv::KCPClient* self = (net_uv::KCPClient*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_net_uv__KCPServer (lua_State* tolua_S)
{
 net_uv::KCPServer* self = (net_uv::KCPServer*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_net_uv__TCPServer (lua_State* tolua_S)
{
 net_uv::TCPServer* self = (net_uv::TCPServer*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_TCPLuaServer (lua_State* tolua_S)
{
 TCPLuaServer* self = (TCPLuaServer*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_KCPLuaServer (lua_State* tolua_S)
{
 KCPLuaServer* self = (KCPLuaServer*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"net_uv::TCPServer");
 tolua_usertype(tolua_S,"net_uv::TCPSession");
 tolua_usertype(tolua_S,"net_uv::KCPClient");
 tolua_usertype(tolua_S,"KCPLuaServer");
 tolua_usertype(tolua_S,"TCPLuaServer");
 tolua_usertype(tolua_S,"net_uv::Server");
 tolua_usertype(tolua_S,"net_uv::Client");
 
 tolua_usertype(tolua_S,"TCPLuaClient");
 tolua_usertype(tolua_S,"net_uv::KCPServer");
 tolua_usertype(tolua_S,"net_uv::TCPClient");
 tolua_usertype(tolua_S,"net_uv::KCPSession");
 tolua_usertype(tolua_S,"KCPLuaClient");
 tolua_usertype(tolua_S,"net_uv::Session");
}

/* method: send of class  net_uv::Session */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_Session_send00
static int tolua_net_net_uv_Session_send00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
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
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send'", NULL);
#endif
  {
   self->send(data,len);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'send'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disconnect of class  net_uv::Session */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_Session_disconnect00
static int tolua_net_net_uv_Session_disconnect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
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
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disconnect'", NULL);
#endif
  {
   self->disconnect();
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSessionID of class  net_uv::Session */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_Session_getSessionID00
static int tolua_net_net_uv_Session_getSessionID00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
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
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSessionID'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getSessionID();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSessionID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPort of class  net_uv::Session */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_Session_getPort00
static int tolua_net_net_uv_Session_getPort00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
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
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPort'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getPort();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPort'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIp of class  net_uv::Session */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_Session_getIp00
static int tolua_net_net_uv_Session_getIp00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
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
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIp'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getIp();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: connect of class  net_uv::Client */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_Client_connect00
static int tolua_net_net_uv_Client_connect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::Client",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::Client* self = (net_uv::Client*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int port = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned int sessionId = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'connect'", NULL);
#endif
  {
   self->connect(ip,port,sessionId);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'connect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disconnect of class  net_uv::Client */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_Client_disconnect00
static int tolua_net_net_uv_Client_disconnect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::Client",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::Client* self = (net_uv::Client*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disconnect'", NULL);
#endif
  {
   self->disconnect(sessionId);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: closeClient of class  net_uv::Client */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_Client_closeClient00
static int tolua_net_net_uv_Client_closeClient00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::Client",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::Client* self = (net_uv::Client*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'closeClient'", NULL);
#endif
  {
   self->closeClient();
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'closeClient'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateFrame of class  net_uv::Client */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_Client_updateFrame00
static int tolua_net_net_uv_Client_updateFrame00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::Client",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::Client* self = (net_uv::Client*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateFrame'", NULL);
#endif
  {
   self->updateFrame();
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: send of class  net_uv::Client */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_Client_send00
static int tolua_net_net_uv_Client_send00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::Client",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::Client* self = (net_uv::Client*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  char* data = ((char*)  tolua_tostring(tolua_S,3,0));
  unsigned int len = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send'", NULL);
#endif
  {
   self->send(sessionId,data,len);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'send'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeSession of class  net_uv::Client */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_Client_removeSession00
static int tolua_net_net_uv_Client_removeSession00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::Client",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::Client* self = (net_uv::Client*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeSession'", NULL);
#endif
  {
   self->removeSession(sessionId);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeSession'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: startServer of class  net_uv::Server */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_Server_startServer00
static int tolua_net_net_uv_Server_startServer00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::Server",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::Server* self = (net_uv::Server*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int port = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  bool isIPV6 = ((bool)  tolua_toboolean(tolua_S,4,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'startServer'", NULL);
#endif
  {
   self->startServer(ip,port,isIPV6);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'startServer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopServer of class  net_uv::Server */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_Server_stopServer00
static int tolua_net_net_uv_Server_stopServer00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::Server",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::Server* self = (net_uv::Server*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopServer'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->stopServer();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopServer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  net_uv::TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_TCPClient_new00
static int tolua_net_net_uv_TCPClient_new00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"net_uv::TCPClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   net_uv::TCPClient* tolua_ret = (net_uv::TCPClient*)  Mtolua_new((net_uv::TCPClient)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"net_uv::TCPClient");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  net_uv::TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_TCPClient_new00_local
static int tolua_net_net_uv_TCPClient_new00_local(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"net_uv::TCPClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   net_uv::TCPClient* tolua_ret = (net_uv::TCPClient*)  Mtolua_new((net_uv::TCPClient)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"net_uv::TCPClient");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  net_uv::TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_TCPClient_delete00
static int tolua_net_net_uv_TCPClient_delete00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::TCPClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::TCPClient* self = (net_uv::TCPClient*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: send of class  net_uv::TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_TCPClient_send00
static int tolua_net_net_uv_TCPClient_send00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::TCPClient",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"net_uv::Session",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::TCPClient* self = (net_uv::TCPClient*)  tolua_tousertype(tolua_S,1,0);
  net_uv::Session* session = ((net_uv::Session*)  tolua_tousertype(tolua_S,2,0));
  char* data = ((char*)  tolua_tostring(tolua_S,3,0));
  unsigned int len = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send'", NULL);
#endif
  {
   self->send(session,data,len);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'send'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disconnect of class  net_uv::TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_TCPClient_disconnect00
static int tolua_net_net_uv_TCPClient_disconnect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::TCPClient",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"net_uv::Session",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::TCPClient* self = (net_uv::TCPClient*)  tolua_tousertype(tolua_S,1,0);
  net_uv::Session* session = ((net_uv::Session*)  tolua_tousertype(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disconnect'", NULL);
#endif
  {
   self->disconnect(session);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCloseFinish of class  net_uv::TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_TCPClient_isCloseFinish00
static int tolua_net_net_uv_TCPClient_isCloseFinish00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::TCPClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::TCPClient* self = (net_uv::TCPClient*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCloseFinish'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCloseFinish();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCloseFinish'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSocketNoDelay of class  net_uv::TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_TCPClient_setSocketNoDelay00
static int tolua_net_net_uv_TCPClient_setSocketNoDelay00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::TCPClient",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::TCPClient* self = (net_uv::TCPClient*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSocketNoDelay'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->setSocketNoDelay(enable);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSocketNoDelay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSocketKeepAlive of class  net_uv::TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_TCPClient_setSocketKeepAlive00
static int tolua_net_net_uv_TCPClient_setSocketKeepAlive00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::TCPClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::TCPClient* self = (net_uv::TCPClient*)  tolua_tousertype(tolua_S,1,0);
  int enable = ((int)  tolua_tonumber(tolua_S,2,0));
  unsigned int delay = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSocketKeepAlive'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->setSocketKeepAlive(enable,delay);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSocketKeepAlive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoReconnect of class  net_uv::TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_TCPClient_setAutoReconnect00
static int tolua_net_net_uv_TCPClient_setAutoReconnect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::TCPClient",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::TCPClient* self = (net_uv::TCPClient*)  tolua_tousertype(tolua_S,1,0);
  bool isAuto = ((bool)  tolua_toboolean(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoReconnect'", NULL);
#endif
  {
   self->setAutoReconnect(isAuto);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoReconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoReconnectTime of class  net_uv::TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_TCPClient_setAutoReconnectTime00
static int tolua_net_net_uv_TCPClient_setAutoReconnectTime00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::TCPClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::TCPClient* self = (net_uv::TCPClient*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoReconnectTime'", NULL);
#endif
  {
   self->setAutoReconnectTime(time);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoReconnectTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoReconnectBySessionID of class  net_uv::TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_TCPClient_setAutoReconnectBySessionID00
static int tolua_net_net_uv_TCPClient_setAutoReconnectBySessionID00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::TCPClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::TCPClient* self = (net_uv::TCPClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionID = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  bool isAuto = ((bool)  tolua_toboolean(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoReconnectBySessionID'", NULL);
#endif
  {
   self->setAutoReconnectBySessionID(sessionID,isAuto);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoReconnectBySessionID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoReconnectTimeBySessionID of class  net_uv::TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_TCPClient_setAutoReconnectTimeBySessionID00
static int tolua_net_net_uv_TCPClient_setAutoReconnectTimeBySessionID00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::TCPClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::TCPClient* self = (net_uv::TCPClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionID = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  float time = ((float)  tolua_tonumber(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoReconnectTimeBySessionID'", NULL);
#endif
  {
   self->setAutoReconnectTimeBySessionID(sessionID,time);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoReconnectTimeBySessionID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  net_uv::TCPServer */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_TCPServer_new00
static int tolua_net_net_uv_TCPServer_new00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"net_uv::TCPServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   net_uv::TCPServer* tolua_ret = (net_uv::TCPServer*)  Mtolua_new((net_uv::TCPServer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"net_uv::TCPServer");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  net_uv::TCPServer */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_TCPServer_new00_local
static int tolua_net_net_uv_TCPServer_new00_local(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"net_uv::TCPServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   net_uv::TCPServer* tolua_ret = (net_uv::TCPServer*)  Mtolua_new((net_uv::TCPServer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"net_uv::TCPServer");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  net_uv::TCPServer */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_TCPServer_delete00
static int tolua_net_net_uv_TCPServer_delete00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::TCPServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::TCPServer* self = (net_uv::TCPServer*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: send of class  net_uv::TCPServer */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_TCPServer_send00
static int tolua_net_net_uv_TCPServer_send00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::TCPServer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"net_uv::Session",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::TCPServer* self = (net_uv::TCPServer*)  tolua_tousertype(tolua_S,1,0);
  net_uv::Session* session = ((net_uv::Session*)  tolua_tousertype(tolua_S,2,0));
  char* data = ((char*)  tolua_tostring(tolua_S,3,0));
  unsigned int len = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send'", NULL);
#endif
  {
   self->send(session,data,len);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'send'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disconnect of class  net_uv::TCPServer */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_TCPServer_disconnect00
static int tolua_net_net_uv_TCPServer_disconnect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::TCPServer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"net_uv::Session",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::TCPServer* self = (net_uv::TCPServer*)  tolua_tousertype(tolua_S,1,0);
  net_uv::Session* session = ((net_uv::Session*)  tolua_tousertype(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disconnect'", NULL);
#endif
  {
   self->disconnect(session);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCloseFinish of class  net_uv::TCPServer */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_TCPServer_isCloseFinish00
static int tolua_net_net_uv_TCPServer_isCloseFinish00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::TCPServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::TCPServer* self = (net_uv::TCPServer*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCloseFinish'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCloseFinish();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCloseFinish'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  net_uv::KCPClient */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_KCPClient_new00
static int tolua_net_net_uv_KCPClient_new00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"net_uv::KCPClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   net_uv::KCPClient* tolua_ret = (net_uv::KCPClient*)  Mtolua_new((net_uv::KCPClient)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"net_uv::KCPClient");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  net_uv::KCPClient */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_KCPClient_new00_local
static int tolua_net_net_uv_KCPClient_new00_local(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"net_uv::KCPClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   net_uv::KCPClient* tolua_ret = (net_uv::KCPClient*)  Mtolua_new((net_uv::KCPClient)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"net_uv::KCPClient");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  net_uv::KCPClient */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_KCPClient_delete00
static int tolua_net_net_uv_KCPClient_delete00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::KCPClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::KCPClient* self = (net_uv::KCPClient*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: send of class  net_uv::KCPClient */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_KCPClient_send00
static int tolua_net_net_uv_KCPClient_send00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::KCPClient",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"net_uv::Session",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::KCPClient* self = (net_uv::KCPClient*)  tolua_tousertype(tolua_S,1,0);
  net_uv::Session* session = ((net_uv::Session*)  tolua_tousertype(tolua_S,2,0));
  char* data = ((char*)  tolua_tostring(tolua_S,3,0));
  unsigned int len = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send'", NULL);
#endif
  {
   self->send(session,data,len);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'send'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disconnect of class  net_uv::KCPClient */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_KCPClient_disconnect00
static int tolua_net_net_uv_KCPClient_disconnect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::KCPClient",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"net_uv::Session",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::KCPClient* self = (net_uv::KCPClient*)  tolua_tousertype(tolua_S,1,0);
  net_uv::Session* session = ((net_uv::Session*)  tolua_tousertype(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disconnect'", NULL);
#endif
  {
   self->disconnect(session);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCloseFinish of class  net_uv::KCPClient */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_KCPClient_isCloseFinish00
static int tolua_net_net_uv_KCPClient_isCloseFinish00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::KCPClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::KCPClient* self = (net_uv::KCPClient*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCloseFinish'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCloseFinish();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCloseFinish'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoReconnect of class  net_uv::KCPClient */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_KCPClient_setAutoReconnect00
static int tolua_net_net_uv_KCPClient_setAutoReconnect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::KCPClient",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::KCPClient* self = (net_uv::KCPClient*)  tolua_tousertype(tolua_S,1,0);
  bool isAuto = ((bool)  tolua_toboolean(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoReconnect'", NULL);
#endif
  {
   self->setAutoReconnect(isAuto);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoReconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoReconnectTime of class  net_uv::KCPClient */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_KCPClient_setAutoReconnectTime00
static int tolua_net_net_uv_KCPClient_setAutoReconnectTime00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::KCPClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::KCPClient* self = (net_uv::KCPClient*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoReconnectTime'", NULL);
#endif
  {
   self->setAutoReconnectTime(time);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoReconnectTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoReconnectBySessionID of class  net_uv::KCPClient */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_KCPClient_setAutoReconnectBySessionID00
static int tolua_net_net_uv_KCPClient_setAutoReconnectBySessionID00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::KCPClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::KCPClient* self = (net_uv::KCPClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionID = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  bool isAuto = ((bool)  tolua_toboolean(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoReconnectBySessionID'", NULL);
#endif
  {
   self->setAutoReconnectBySessionID(sessionID,isAuto);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoReconnectBySessionID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoReconnectTimeBySessionID of class  net_uv::KCPClient */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_KCPClient_setAutoReconnectTimeBySessionID00
static int tolua_net_net_uv_KCPClient_setAutoReconnectTimeBySessionID00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::KCPClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::KCPClient* self = (net_uv::KCPClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionID = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  float time = ((float)  tolua_tonumber(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoReconnectTimeBySessionID'", NULL);
#endif
  {
   self->setAutoReconnectTimeBySessionID(sessionID,time);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoReconnectTimeBySessionID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  net_uv::KCPServer */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_KCPServer_new00
static int tolua_net_net_uv_KCPServer_new00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"net_uv::KCPServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   net_uv::KCPServer* tolua_ret = (net_uv::KCPServer*)  Mtolua_new((net_uv::KCPServer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"net_uv::KCPServer");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  net_uv::KCPServer */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_KCPServer_new00_local
static int tolua_net_net_uv_KCPServer_new00_local(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"net_uv::KCPServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   net_uv::KCPServer* tolua_ret = (net_uv::KCPServer*)  Mtolua_new((net_uv::KCPServer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"net_uv::KCPServer");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  net_uv::KCPServer */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_KCPServer_delete00
static int tolua_net_net_uv_KCPServer_delete00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::KCPServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::KCPServer* self = (net_uv::KCPServer*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: send of class  net_uv::KCPServer */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_KCPServer_send00
static int tolua_net_net_uv_KCPServer_send00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::KCPServer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"net_uv::Session",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::KCPServer* self = (net_uv::KCPServer*)  tolua_tousertype(tolua_S,1,0);
  net_uv::Session* session = ((net_uv::Session*)  tolua_tousertype(tolua_S,2,0));
  char* data = ((char*)  tolua_tostring(tolua_S,3,0));
  unsigned int len = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send'", NULL);
#endif
  {
   self->send(session,data,len);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'send'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disconnect of class  net_uv::KCPServer */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_KCPServer_disconnect00
static int tolua_net_net_uv_KCPServer_disconnect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::KCPServer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"net_uv::Session",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::KCPServer* self = (net_uv::KCPServer*)  tolua_tousertype(tolua_S,1,0);
  net_uv::Session* session = ((net_uv::Session*)  tolua_tousertype(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disconnect'", NULL);
#endif
  {
   self->disconnect(session);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCloseFinish of class  net_uv::KCPServer */
#ifndef TOLUA_DISABLE_tolua_net_net_uv_KCPServer_isCloseFinish00
static int tolua_net_net_uv_KCPServer_isCloseFinish00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"net_uv::KCPServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  net_uv::KCPServer* self = (net_uv::KCPServer*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCloseFinish'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCloseFinish();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCloseFinish'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  TCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaClient_getInstance00
static int tolua_net_TCPLuaClient_getInstance00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TCPLuaClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TCPLuaClient* tolua_ret = (TCPLuaClient*)  TCPLuaClient::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TCPLuaClient");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destroy of class  TCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaClient_destroy00
static int tolua_net_TCPLuaClient_destroy00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TCPLuaClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TCPLuaClient::destroy();
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: connect of class  TCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaClient_connect00
static int tolua_net_TCPLuaClient_connect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaClient* self = (TCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int port = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned int sessionId = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'connect'", NULL);
#endif
  {
   self->connect(ip,port,sessionId);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'connect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disconnect of class  TCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaClient_disconnect00
static int tolua_net_TCPLuaClient_disconnect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaClient* self = (TCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disconnect'", NULL);
#endif
  {
   self->disconnect(sessionId);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: closeClient of class  TCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaClient_closeClient00
static int tolua_net_TCPLuaClient_closeClient00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaClient* self = (TCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'closeClient'", NULL);
#endif
  {
   self->closeClient();
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'closeClient'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: send of class  TCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaClient_send00
static int tolua_net_TCPLuaClient_send00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaClient* self = (TCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  char* data = ((char*)  tolua_tostring(tolua_S,3,0));
  unsigned int len = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send'", NULL);
#endif
  {
   self->send(sessionId,data,len);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'send'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeSession of class  TCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaClient_removeSession00
static int tolua_net_TCPLuaClient_removeSession00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaClient* self = (TCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeSession'", NULL);
#endif
  {
   self->removeSession(sessionId);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeSession'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: send of class  TCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaClient_send01
static int tolua_net_TCPLuaClient_send01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaClient",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"net_uv::Session",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  TCPLuaClient* self = (TCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  net_uv::Session* session = ((net_uv::Session*)  tolua_tousertype(tolua_S,2,0));
  char* data = ((char*)  tolua_tostring(tolua_S,3,0));
  unsigned int len = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send'", NULL);
#endif
  {
   self->send(session,data,len);
  }
 }
 return 0;
tolua_lerror:
 return tolua_net_TCPLuaClient_send00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: disconnect of class  TCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaClient_disconnect01
static int tolua_net_TCPLuaClient_disconnect01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaClient",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"net_uv::Session",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  TCPLuaClient* self = (TCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  net_uv::Session* session = ((net_uv::Session*)  tolua_tousertype(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disconnect'", NULL);
#endif
  {
   self->disconnect(session);
  }
 }
 return 0;
tolua_lerror:
 return tolua_net_TCPLuaClient_disconnect00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCloseFinish of class  TCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaClient_isCloseFinish00
static int tolua_net_TCPLuaClient_isCloseFinish00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaClient* self = (TCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCloseFinish'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCloseFinish();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCloseFinish'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSocketNoDelay of class  TCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaClient_setSocketNoDelay00
static int tolua_net_TCPLuaClient_setSocketNoDelay00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaClient",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaClient* self = (TCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSocketNoDelay'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->setSocketNoDelay(enable);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSocketNoDelay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSocketKeepAlive of class  TCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaClient_setSocketKeepAlive00
static int tolua_net_TCPLuaClient_setSocketKeepAlive00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaClient* self = (TCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  int enable = ((int)  tolua_tonumber(tolua_S,2,0));
  unsigned int delay = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSocketKeepAlive'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->setSocketKeepAlive(enable,delay);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSocketKeepAlive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoReconnect of class  TCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaClient_setAutoReconnect00
static int tolua_net_TCPLuaClient_setAutoReconnect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaClient",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaClient* self = (TCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  bool isAuto = ((bool)  tolua_toboolean(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoReconnect'", NULL);
#endif
  {
   self->setAutoReconnect(isAuto);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoReconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoReconnectTime of class  TCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaClient_setAutoReconnectTime00
static int tolua_net_TCPLuaClient_setAutoReconnectTime00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaClient* self = (TCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoReconnectTime'", NULL);
#endif
  {
   self->setAutoReconnectTime(time);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoReconnectTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoReconnectBySessionID of class  TCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaClient_setAutoReconnectBySessionID00
static int tolua_net_TCPLuaClient_setAutoReconnectBySessionID00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaClient* self = (TCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionID = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  bool isAuto = ((bool)  tolua_toboolean(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoReconnectBySessionID'", NULL);
#endif
  {
   self->setAutoReconnectBySessionID(sessionID,isAuto);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoReconnectBySessionID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoReconnectTimeBySessionID of class  TCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaClient_setAutoReconnectTimeBySessionID00
static int tolua_net_TCPLuaClient_setAutoReconnectTimeBySessionID00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaClient* self = (TCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionID = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  float time = ((float)  tolua_tonumber(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoReconnectTimeBySessionID'", NULL);
#endif
  {
   self->setAutoReconnectTimeBySessionID(sessionID,time);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoReconnectTimeBySessionID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTCPClient of class  TCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaClient_getTCPClient00
static int tolua_net_TCPLuaClient_getTCPClient00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaClient* self = (TCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTCPClient'", NULL);
#endif
  {
   net_uv::TCPClient* tolua_ret = (net_uv::TCPClient*)  self->getTCPClient();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"net_uv::TCPClient");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTCPClient'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerLuaHandle of class  TCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaClient_registerLuaHandle00
static int tolua_net_TCPLuaClient_registerLuaHandle00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaClient",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_isfunction(tolua_S,3,"LuaFunction",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaClient* self = (TCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  LuaFunction handle = (  LuaFunction(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerLuaHandle'", NULL);
#endif
  {
   self->registerLuaHandle(name,handle);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerLuaHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterLuaHandle of class  TCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaClient_unregisterLuaHandle00
static int tolua_net_TCPLuaClient_unregisterLuaHandle00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaClient",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaClient* self = (TCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterLuaHandle'", NULL);
#endif
  {
   self->unregisterLuaHandle(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterLuaHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearLuaHandle of class  TCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaClient_clearLuaHandle00
static int tolua_net_TCPLuaClient_clearLuaHandle00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaClient* self = (TCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearLuaHandle'", NULL);
#endif
  {
   self->clearLuaHandle();
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearLuaHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  TCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaServer_new00
static int tolua_net_TCPLuaServer_new00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TCPLuaServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TCPLuaServer* tolua_ret = (TCPLuaServer*)  Mtolua_new((TCPLuaServer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TCPLuaServer");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  TCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaServer_new00_local
static int tolua_net_TCPLuaServer_new00_local(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TCPLuaServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TCPLuaServer* tolua_ret = (TCPLuaServer*)  Mtolua_new((TCPLuaServer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TCPLuaServer");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  TCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaServer_delete00
static int tolua_net_TCPLuaServer_delete00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaServer* self = (TCPLuaServer*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: startServer of class  TCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaServer_startServer00
static int tolua_net_TCPLuaServer_startServer00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaServer",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaServer* self = (TCPLuaServer*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int port = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  bool isIPV6 = ((bool)  tolua_toboolean(tolua_S,4,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'startServer'", NULL);
#endif
  {
   self->startServer(ip,port,isIPV6);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'startServer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopServer of class  TCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaServer_stopServer00
static int tolua_net_TCPLuaServer_stopServer00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaServer* self = (TCPLuaServer*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopServer'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->stopServer();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopServer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: send of class  TCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaServer_send00
static int tolua_net_TCPLuaServer_send00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaServer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"net_uv::Session",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaServer* self = (TCPLuaServer*)  tolua_tousertype(tolua_S,1,0);
  net_uv::Session* session = ((net_uv::Session*)  tolua_tousertype(tolua_S,2,0));
  char* data = ((char*)  tolua_tostring(tolua_S,3,0));
  unsigned int len = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send'", NULL);
#endif
  {
   self->send(session,data,len);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'send'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disconnect of class  TCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaServer_disconnect00
static int tolua_net_TCPLuaServer_disconnect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaServer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"net_uv::Session",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaServer* self = (TCPLuaServer*)  tolua_tousertype(tolua_S,1,0);
  net_uv::Session* session = ((net_uv::Session*)  tolua_tousertype(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disconnect'", NULL);
#endif
  {
   self->disconnect(session);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCloseFinish of class  TCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaServer_isCloseFinish00
static int tolua_net_TCPLuaServer_isCloseFinish00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaServer* self = (TCPLuaServer*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCloseFinish'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCloseFinish();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCloseFinish'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTCPServer of class  TCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaServer_getTCPServer00
static int tolua_net_TCPLuaServer_getTCPServer00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaServer* self = (TCPLuaServer*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTCPServer'", NULL);
#endif
  {
   net_uv::TCPServer* tolua_ret = (net_uv::TCPServer*)  self->getTCPServer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"net_uv::TCPServer");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTCPServer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerLuaHandle of class  TCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaServer_registerLuaHandle00
static int tolua_net_TCPLuaServer_registerLuaHandle00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaServer",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_isfunction(tolua_S,3,"LuaFunction",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaServer* self = (TCPLuaServer*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  LuaFunction handle = (  LuaFunction(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerLuaHandle'", NULL);
#endif
  {
   self->registerLuaHandle(name,handle);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerLuaHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterLuaHandle of class  TCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaServer_unregisterLuaHandle00
static int tolua_net_TCPLuaServer_unregisterLuaHandle00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaServer",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaServer* self = (TCPLuaServer*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterLuaHandle'", NULL);
#endif
  {
   self->unregisterLuaHandle(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterLuaHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearLuaHandle of class  TCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_TCPLuaServer_clearLuaHandle00
static int tolua_net_TCPLuaServer_clearLuaHandle00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPLuaServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPLuaServer* self = (TCPLuaServer*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearLuaHandle'", NULL);
#endif
  {
   self->clearLuaHandle();
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearLuaHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  KCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaClient_getInstance00
static int tolua_net_KCPLuaClient_getInstance00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"KCPLuaClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   KCPLuaClient* tolua_ret = (KCPLuaClient*)  KCPLuaClient::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"KCPLuaClient");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destroy of class  KCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaClient_destroy00
static int tolua_net_KCPLuaClient_destroy00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"KCPLuaClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   KCPLuaClient::destroy();
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: connect of class  KCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaClient_connect00
static int tolua_net_KCPLuaClient_connect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaClient* self = (KCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int port = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned int sessionId = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'connect'", NULL);
#endif
  {
   self->connect(ip,port,sessionId);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'connect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disconnect of class  KCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaClient_disconnect00
static int tolua_net_KCPLuaClient_disconnect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaClient* self = (KCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disconnect'", NULL);
#endif
  {
   self->disconnect(sessionId);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: closeClient of class  KCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaClient_closeClient00
static int tolua_net_KCPLuaClient_closeClient00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaClient* self = (KCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'closeClient'", NULL);
#endif
  {
   self->closeClient();
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'closeClient'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: send of class  KCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaClient_send00
static int tolua_net_KCPLuaClient_send00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaClient* self = (KCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  char* data = ((char*)  tolua_tostring(tolua_S,3,0));
  unsigned int len = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send'", NULL);
#endif
  {
   self->send(sessionId,data,len);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'send'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeSession of class  KCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaClient_removeSession00
static int tolua_net_KCPLuaClient_removeSession00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaClient* self = (KCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeSession'", NULL);
#endif
  {
   self->removeSession(sessionId);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeSession'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: send of class  KCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaClient_send01
static int tolua_net_KCPLuaClient_send01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaClient",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"net_uv::Session",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  KCPLuaClient* self = (KCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  net_uv::Session* session = ((net_uv::Session*)  tolua_tousertype(tolua_S,2,0));
  char* data = ((char*)  tolua_tostring(tolua_S,3,0));
  unsigned int len = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send'", NULL);
#endif
  {
   self->send(session,data,len);
  }
 }
 return 0;
tolua_lerror:
 return tolua_net_KCPLuaClient_send00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: disconnect of class  KCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaClient_disconnect01
static int tolua_net_KCPLuaClient_disconnect01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaClient",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"net_uv::Session",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  KCPLuaClient* self = (KCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  net_uv::Session* session = ((net_uv::Session*)  tolua_tousertype(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disconnect'", NULL);
#endif
  {
   self->disconnect(session);
  }
 }
 return 0;
tolua_lerror:
 return tolua_net_KCPLuaClient_disconnect00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCloseFinish of class  KCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaClient_isCloseFinish00
static int tolua_net_KCPLuaClient_isCloseFinish00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaClient* self = (KCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCloseFinish'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCloseFinish();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCloseFinish'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoReconnect of class  KCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaClient_setAutoReconnect00
static int tolua_net_KCPLuaClient_setAutoReconnect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaClient",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaClient* self = (KCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  bool isAuto = ((bool)  tolua_toboolean(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoReconnect'", NULL);
#endif
  {
   self->setAutoReconnect(isAuto);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoReconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoReconnectTime of class  KCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaClient_setAutoReconnectTime00
static int tolua_net_KCPLuaClient_setAutoReconnectTime00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaClient* self = (KCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoReconnectTime'", NULL);
#endif
  {
   self->setAutoReconnectTime(time);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoReconnectTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoReconnectBySessionID of class  KCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaClient_setAutoReconnectBySessionID00
static int tolua_net_KCPLuaClient_setAutoReconnectBySessionID00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaClient* self = (KCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionID = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  bool isAuto = ((bool)  tolua_toboolean(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoReconnectBySessionID'", NULL);
#endif
  {
   self->setAutoReconnectBySessionID(sessionID,isAuto);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoReconnectBySessionID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoReconnectTimeBySessionID of class  KCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaClient_setAutoReconnectTimeBySessionID00
static int tolua_net_KCPLuaClient_setAutoReconnectTimeBySessionID00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaClient* self = (KCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int sessionID = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  float time = ((float)  tolua_tonumber(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoReconnectTimeBySessionID'", NULL);
#endif
  {
   self->setAutoReconnectTimeBySessionID(sessionID,time);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoReconnectTimeBySessionID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getKCPClient of class  KCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaClient_getKCPClient00
static int tolua_net_KCPLuaClient_getKCPClient00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaClient* self = (KCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getKCPClient'", NULL);
#endif
  {
   net_uv::KCPClient* tolua_ret = (net_uv::KCPClient*)  self->getKCPClient();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"net_uv::KCPClient");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getKCPClient'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerLuaHandle of class  KCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaClient_registerLuaHandle00
static int tolua_net_KCPLuaClient_registerLuaHandle00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaClient",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_isfunction(tolua_S,3,"LuaFunction",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaClient* self = (KCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  LuaFunction handle = (  LuaFunction(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerLuaHandle'", NULL);
#endif
  {
   self->registerLuaHandle(name,handle);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerLuaHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterLuaHandle of class  KCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaClient_unregisterLuaHandle00
static int tolua_net_KCPLuaClient_unregisterLuaHandle00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaClient",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaClient* self = (KCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterLuaHandle'", NULL);
#endif
  {
   self->unregisterLuaHandle(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterLuaHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearLuaHandle of class  KCPLuaClient */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaClient_clearLuaHandle00
static int tolua_net_KCPLuaClient_clearLuaHandle00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaClient* self = (KCPLuaClient*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearLuaHandle'", NULL);
#endif
  {
   self->clearLuaHandle();
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearLuaHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  KCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaServer_new00
static int tolua_net_KCPLuaServer_new00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"KCPLuaServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   KCPLuaServer* tolua_ret = (KCPLuaServer*)  Mtolua_new((KCPLuaServer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"KCPLuaServer");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  KCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaServer_new00_local
static int tolua_net_KCPLuaServer_new00_local(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"KCPLuaServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   KCPLuaServer* tolua_ret = (KCPLuaServer*)  Mtolua_new((KCPLuaServer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"KCPLuaServer");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  KCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaServer_delete00
static int tolua_net_KCPLuaServer_delete00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaServer* self = (KCPLuaServer*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: startServer of class  KCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaServer_startServer00
static int tolua_net_KCPLuaServer_startServer00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaServer",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaServer* self = (KCPLuaServer*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int port = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  bool isIPV6 = ((bool)  tolua_toboolean(tolua_S,4,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'startServer'", NULL);
#endif
  {
   self->startServer(ip,port,isIPV6);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'startServer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopServer of class  KCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaServer_stopServer00
static int tolua_net_KCPLuaServer_stopServer00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaServer* self = (KCPLuaServer*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopServer'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->stopServer();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopServer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: send of class  KCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaServer_send00
static int tolua_net_KCPLuaServer_send00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaServer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"net_uv::Session",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaServer* self = (KCPLuaServer*)  tolua_tousertype(tolua_S,1,0);
  net_uv::Session* session = ((net_uv::Session*)  tolua_tousertype(tolua_S,2,0));
  char* data = ((char*)  tolua_tostring(tolua_S,3,0));
  unsigned int len = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send'", NULL);
#endif
  {
   self->send(session,data,len);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'send'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disconnect of class  KCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaServer_disconnect00
static int tolua_net_KCPLuaServer_disconnect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaServer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"net_uv::Session",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaServer* self = (KCPLuaServer*)  tolua_tousertype(tolua_S,1,0);
  net_uv::Session* session = ((net_uv::Session*)  tolua_tousertype(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disconnect'", NULL);
#endif
  {
   self->disconnect(session);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCloseFinish of class  KCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaServer_isCloseFinish00
static int tolua_net_KCPLuaServer_isCloseFinish00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaServer* self = (KCPLuaServer*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCloseFinish'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCloseFinish();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCloseFinish'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getKCPServer of class  KCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaServer_getKCPServer00
static int tolua_net_KCPLuaServer_getKCPServer00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaServer* self = (KCPLuaServer*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getKCPServer'", NULL);
#endif
  {
   net_uv::KCPServer* tolua_ret = (net_uv::KCPServer*)  self->getKCPServer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"net_uv::KCPServer");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getKCPServer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerLuaHandle of class  KCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaServer_registerLuaHandle00
static int tolua_net_KCPLuaServer_registerLuaHandle00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaServer",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_isfunction(tolua_S,3,"LuaFunction",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaServer* self = (KCPLuaServer*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  LuaFunction handle = (  LuaFunction(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerLuaHandle'", NULL);
#endif
  {
   self->registerLuaHandle(name,handle);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerLuaHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterLuaHandle of class  KCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaServer_unregisterLuaHandle00
static int tolua_net_KCPLuaServer_unregisterLuaHandle00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaServer",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaServer* self = (KCPLuaServer*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterLuaHandle'", NULL);
#endif
  {
   self->unregisterLuaHandle(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterLuaHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearLuaHandle of class  KCPLuaServer */
#ifndef TOLUA_DISABLE_tolua_net_KCPLuaServer_clearLuaHandle00
static int tolua_net_KCPLuaServer_clearLuaHandle00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KCPLuaServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KCPLuaServer* self = (KCPLuaServer*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearLuaHandle'", NULL);
#endif
  {
   self->clearLuaHandle();
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearLuaHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_net_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"net_uv",0);
  tolua_beginmodule(tolua_S,"net_uv");
   tolua_cclass(tolua_S,"Session","net_uv::Session","",NULL);
   tolua_beginmodule(tolua_S,"Session");
    tolua_function(tolua_S,"send",tolua_net_net_uv_Session_send00);
    tolua_function(tolua_S,"disconnect",tolua_net_net_uv_Session_disconnect00);
    tolua_function(tolua_S,"getSessionID",tolua_net_net_uv_Session_getSessionID00);
    tolua_function(tolua_S,"getPort",tolua_net_net_uv_Session_getPort00);
    tolua_function(tolua_S,"getIp",tolua_net_net_uv_Session_getIp00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"net_uv",0);
  tolua_beginmodule(tolua_S,"net_uv");
   tolua_cclass(tolua_S,"Client","net_uv::Client","",NULL);
   tolua_beginmodule(tolua_S,"Client");
    tolua_function(tolua_S,"connect",tolua_net_net_uv_Client_connect00);
    tolua_function(tolua_S,"disconnect",tolua_net_net_uv_Client_disconnect00);
    tolua_function(tolua_S,"closeClient",tolua_net_net_uv_Client_closeClient00);
    tolua_function(tolua_S,"updateFrame",tolua_net_net_uv_Client_updateFrame00);
    tolua_function(tolua_S,"send",tolua_net_net_uv_Client_send00);
    tolua_function(tolua_S,"removeSession",tolua_net_net_uv_Client_removeSession00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"net_uv",0);
  tolua_beginmodule(tolua_S,"net_uv");
   tolua_cclass(tolua_S,"Server","net_uv::Server","",NULL);
   tolua_beginmodule(tolua_S,"Server");
    tolua_function(tolua_S,"startServer",tolua_net_net_uv_Server_startServer00);
    tolua_function(tolua_S,"stopServer",tolua_net_net_uv_Server_stopServer00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"net_uv",0);
  tolua_beginmodule(tolua_S,"net_uv");
   tolua_cclass(tolua_S,"TCPSession","net_uv::TCPSession","net_uv::Session",NULL);
   tolua_beginmodule(tolua_S,"TCPSession");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"net_uv",0);
  tolua_beginmodule(tolua_S,"net_uv");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"TCPClient","net_uv::TCPClient","net_uv::Client",tolua_collect_net_uv__TCPClient);
   #else
   tolua_cclass(tolua_S,"TCPClient","net_uv::TCPClient","net_uv::Client",NULL);
   #endif
   tolua_beginmodule(tolua_S,"TCPClient");
    tolua_function(tolua_S,"new",tolua_net_net_uv_TCPClient_new00);
    tolua_function(tolua_S,"new_local",tolua_net_net_uv_TCPClient_new00_local);
    tolua_function(tolua_S,".call",tolua_net_net_uv_TCPClient_new00_local);
    tolua_function(tolua_S,"delete",tolua_net_net_uv_TCPClient_delete00);
    tolua_function(tolua_S,"send",tolua_net_net_uv_TCPClient_send00);
    tolua_function(tolua_S,"disconnect",tolua_net_net_uv_TCPClient_disconnect00);
    tolua_function(tolua_S,"isCloseFinish",tolua_net_net_uv_TCPClient_isCloseFinish00);
    tolua_function(tolua_S,"setSocketNoDelay",tolua_net_net_uv_TCPClient_setSocketNoDelay00);
    tolua_function(tolua_S,"setSocketKeepAlive",tolua_net_net_uv_TCPClient_setSocketKeepAlive00);
    tolua_function(tolua_S,"setAutoReconnect",tolua_net_net_uv_TCPClient_setAutoReconnect00);
    tolua_function(tolua_S,"setAutoReconnectTime",tolua_net_net_uv_TCPClient_setAutoReconnectTime00);
    tolua_function(tolua_S,"setAutoReconnectBySessionID",tolua_net_net_uv_TCPClient_setAutoReconnectBySessionID00);
    tolua_function(tolua_S,"setAutoReconnectTimeBySessionID",tolua_net_net_uv_TCPClient_setAutoReconnectTimeBySessionID00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"net_uv",0);
  tolua_beginmodule(tolua_S,"net_uv");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"TCPServer","net_uv::TCPServer","net_uv::Server",tolua_collect_net_uv__TCPServer);
   #else
   tolua_cclass(tolua_S,"TCPServer","net_uv::TCPServer","net_uv::Server",NULL);
   #endif
   tolua_beginmodule(tolua_S,"TCPServer");
    tolua_function(tolua_S,"new",tolua_net_net_uv_TCPServer_new00);
    tolua_function(tolua_S,"new_local",tolua_net_net_uv_TCPServer_new00_local);
    tolua_function(tolua_S,".call",tolua_net_net_uv_TCPServer_new00_local);
    tolua_function(tolua_S,"delete",tolua_net_net_uv_TCPServer_delete00);
    tolua_function(tolua_S,"send",tolua_net_net_uv_TCPServer_send00);
    tolua_function(tolua_S,"disconnect",tolua_net_net_uv_TCPServer_disconnect00);
    tolua_function(tolua_S,"isCloseFinish",tolua_net_net_uv_TCPServer_isCloseFinish00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"net_uv",0);
  tolua_beginmodule(tolua_S,"net_uv");
   tolua_cclass(tolua_S,"KCPSession","net_uv::KCPSession","net_uv::Session",NULL);
   tolua_beginmodule(tolua_S,"KCPSession");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"net_uv",0);
  tolua_beginmodule(tolua_S,"net_uv");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"KCPClient","net_uv::KCPClient","net_uv::Client",tolua_collect_net_uv__KCPClient);
   #else
   tolua_cclass(tolua_S,"KCPClient","net_uv::KCPClient","net_uv::Client",NULL);
   #endif
   tolua_beginmodule(tolua_S,"KCPClient");
    tolua_function(tolua_S,"new",tolua_net_net_uv_KCPClient_new00);
    tolua_function(tolua_S,"new_local",tolua_net_net_uv_KCPClient_new00_local);
    tolua_function(tolua_S,".call",tolua_net_net_uv_KCPClient_new00_local);
    tolua_function(tolua_S,"delete",tolua_net_net_uv_KCPClient_delete00);
    tolua_function(tolua_S,"send",tolua_net_net_uv_KCPClient_send00);
    tolua_function(tolua_S,"disconnect",tolua_net_net_uv_KCPClient_disconnect00);
    tolua_function(tolua_S,"isCloseFinish",tolua_net_net_uv_KCPClient_isCloseFinish00);
    tolua_function(tolua_S,"setAutoReconnect",tolua_net_net_uv_KCPClient_setAutoReconnect00);
    tolua_function(tolua_S,"setAutoReconnectTime",tolua_net_net_uv_KCPClient_setAutoReconnectTime00);
    tolua_function(tolua_S,"setAutoReconnectBySessionID",tolua_net_net_uv_KCPClient_setAutoReconnectBySessionID00);
    tolua_function(tolua_S,"setAutoReconnectTimeBySessionID",tolua_net_net_uv_KCPClient_setAutoReconnectTimeBySessionID00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"net_uv",0);
  tolua_beginmodule(tolua_S,"net_uv");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"KCPServer","net_uv::KCPServer","net_uv::Server",tolua_collect_net_uv__KCPServer);
   #else
   tolua_cclass(tolua_S,"KCPServer","net_uv::KCPServer","net_uv::Server",NULL);
   #endif
   tolua_beginmodule(tolua_S,"KCPServer");
    tolua_function(tolua_S,"new",tolua_net_net_uv_KCPServer_new00);
    tolua_function(tolua_S,"new_local",tolua_net_net_uv_KCPServer_new00_local);
    tolua_function(tolua_S,".call",tolua_net_net_uv_KCPServer_new00_local);
    tolua_function(tolua_S,"delete",tolua_net_net_uv_KCPServer_delete00);
    tolua_function(tolua_S,"send",tolua_net_net_uv_KCPServer_send00);
    tolua_function(tolua_S,"disconnect",tolua_net_net_uv_KCPServer_disconnect00);
    tolua_function(tolua_S,"isCloseFinish",tolua_net_net_uv_KCPServer_isCloseFinish00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"TCPLuaClient","TCPLuaClient","",NULL);
  tolua_beginmodule(tolua_S,"TCPLuaClient");
   tolua_function(tolua_S,"getInstance",tolua_net_TCPLuaClient_getInstance00);
   tolua_function(tolua_S,"destroy",tolua_net_TCPLuaClient_destroy00);
   tolua_function(tolua_S,"connect",tolua_net_TCPLuaClient_connect00);
   tolua_function(tolua_S,"disconnect",tolua_net_TCPLuaClient_disconnect00);
   tolua_function(tolua_S,"closeClient",tolua_net_TCPLuaClient_closeClient00);
   tolua_function(tolua_S,"send",tolua_net_TCPLuaClient_send00);
   tolua_function(tolua_S,"removeSession",tolua_net_TCPLuaClient_removeSession00);
   tolua_function(tolua_S,"send",tolua_net_TCPLuaClient_send01);
   tolua_function(tolua_S,"disconnect",tolua_net_TCPLuaClient_disconnect01);
   tolua_function(tolua_S,"isCloseFinish",tolua_net_TCPLuaClient_isCloseFinish00);
   tolua_function(tolua_S,"setSocketNoDelay",tolua_net_TCPLuaClient_setSocketNoDelay00);
   tolua_function(tolua_S,"setSocketKeepAlive",tolua_net_TCPLuaClient_setSocketKeepAlive00);
   tolua_function(tolua_S,"setAutoReconnect",tolua_net_TCPLuaClient_setAutoReconnect00);
   tolua_function(tolua_S,"setAutoReconnectTime",tolua_net_TCPLuaClient_setAutoReconnectTime00);
   tolua_function(tolua_S,"setAutoReconnectBySessionID",tolua_net_TCPLuaClient_setAutoReconnectBySessionID00);
   tolua_function(tolua_S,"setAutoReconnectTimeBySessionID",tolua_net_TCPLuaClient_setAutoReconnectTimeBySessionID00);
   tolua_function(tolua_S,"getTCPClient",tolua_net_TCPLuaClient_getTCPClient00);
   tolua_function(tolua_S,"registerLuaHandle",tolua_net_TCPLuaClient_registerLuaHandle00);
   tolua_function(tolua_S,"unregisterLuaHandle",tolua_net_TCPLuaClient_unregisterLuaHandle00);
   tolua_function(tolua_S,"clearLuaHandle",tolua_net_TCPLuaClient_clearLuaHandle00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"TCPLuaServer","TCPLuaServer","",tolua_collect_TCPLuaServer);
  #else
  tolua_cclass(tolua_S,"TCPLuaServer","TCPLuaServer","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"TCPLuaServer");
   tolua_function(tolua_S,"new",tolua_net_TCPLuaServer_new00);
   tolua_function(tolua_S,"new_local",tolua_net_TCPLuaServer_new00_local);
   tolua_function(tolua_S,".call",tolua_net_TCPLuaServer_new00_local);
   tolua_function(tolua_S,"delete",tolua_net_TCPLuaServer_delete00);
   tolua_function(tolua_S,"startServer",tolua_net_TCPLuaServer_startServer00);
   tolua_function(tolua_S,"stopServer",tolua_net_TCPLuaServer_stopServer00);
   tolua_function(tolua_S,"send",tolua_net_TCPLuaServer_send00);
   tolua_function(tolua_S,"disconnect",tolua_net_TCPLuaServer_disconnect00);
   tolua_function(tolua_S,"isCloseFinish",tolua_net_TCPLuaServer_isCloseFinish00);
   tolua_function(tolua_S,"getTCPServer",tolua_net_TCPLuaServer_getTCPServer00);
   tolua_function(tolua_S,"registerLuaHandle",tolua_net_TCPLuaServer_registerLuaHandle00);
   tolua_function(tolua_S,"unregisterLuaHandle",tolua_net_TCPLuaServer_unregisterLuaHandle00);
   tolua_function(tolua_S,"clearLuaHandle",tolua_net_TCPLuaServer_clearLuaHandle00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"KCPLuaClient","KCPLuaClient","",NULL);
  tolua_beginmodule(tolua_S,"KCPLuaClient");
   tolua_function(tolua_S,"getInstance",tolua_net_KCPLuaClient_getInstance00);
   tolua_function(tolua_S,"destroy",tolua_net_KCPLuaClient_destroy00);
   tolua_function(tolua_S,"connect",tolua_net_KCPLuaClient_connect00);
   tolua_function(tolua_S,"disconnect",tolua_net_KCPLuaClient_disconnect00);
   tolua_function(tolua_S,"closeClient",tolua_net_KCPLuaClient_closeClient00);
   tolua_function(tolua_S,"send",tolua_net_KCPLuaClient_send00);
   tolua_function(tolua_S,"removeSession",tolua_net_KCPLuaClient_removeSession00);
   tolua_function(tolua_S,"send",tolua_net_KCPLuaClient_send01);
   tolua_function(tolua_S,"disconnect",tolua_net_KCPLuaClient_disconnect01);
   tolua_function(tolua_S,"isCloseFinish",tolua_net_KCPLuaClient_isCloseFinish00);
   tolua_function(tolua_S,"setAutoReconnect",tolua_net_KCPLuaClient_setAutoReconnect00);
   tolua_function(tolua_S,"setAutoReconnectTime",tolua_net_KCPLuaClient_setAutoReconnectTime00);
   tolua_function(tolua_S,"setAutoReconnectBySessionID",tolua_net_KCPLuaClient_setAutoReconnectBySessionID00);
   tolua_function(tolua_S,"setAutoReconnectTimeBySessionID",tolua_net_KCPLuaClient_setAutoReconnectTimeBySessionID00);
   tolua_function(tolua_S,"getKCPClient",tolua_net_KCPLuaClient_getKCPClient00);
   tolua_function(tolua_S,"registerLuaHandle",tolua_net_KCPLuaClient_registerLuaHandle00);
   tolua_function(tolua_S,"unregisterLuaHandle",tolua_net_KCPLuaClient_unregisterLuaHandle00);
   tolua_function(tolua_S,"clearLuaHandle",tolua_net_KCPLuaClient_clearLuaHandle00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"KCPLuaServer","KCPLuaServer","",tolua_collect_KCPLuaServer);
  #else
  tolua_cclass(tolua_S,"KCPLuaServer","KCPLuaServer","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"KCPLuaServer");
   tolua_function(tolua_S,"new",tolua_net_KCPLuaServer_new00);
   tolua_function(tolua_S,"new_local",tolua_net_KCPLuaServer_new00_local);
   tolua_function(tolua_S,".call",tolua_net_KCPLuaServer_new00_local);
   tolua_function(tolua_S,"delete",tolua_net_KCPLuaServer_delete00);
   tolua_function(tolua_S,"startServer",tolua_net_KCPLuaServer_startServer00);
   tolua_function(tolua_S,"stopServer",tolua_net_KCPLuaServer_stopServer00);
   tolua_function(tolua_S,"send",tolua_net_KCPLuaServer_send00);
   tolua_function(tolua_S,"disconnect",tolua_net_KCPLuaServer_disconnect00);
   tolua_function(tolua_S,"isCloseFinish",tolua_net_KCPLuaServer_isCloseFinish00);
   tolua_function(tolua_S,"getKCPServer",tolua_net_KCPLuaServer_getKCPServer00);
   tolua_function(tolua_S,"registerLuaHandle",tolua_net_KCPLuaServer_registerLuaHandle00);
   tolua_function(tolua_S,"unregisterLuaHandle",tolua_net_KCPLuaServer_unregisterLuaHandle00);
   tolua_function(tolua_S,"clearLuaHandle",tolua_net_KCPLuaServer_clearLuaHandle00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_net (lua_State* tolua_S) {
 return tolua_net_open(tolua_S);
};
#endif

