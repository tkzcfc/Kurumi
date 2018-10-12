/*
** Lua binding: net
** Generated automatically by tolua++-1.0.92 on 10/11/18 22:51:43.
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

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_TCPClient (lua_State* tolua_S)
{
 TCPClient* self = (TCPClient*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_TCPServer (lua_State* tolua_S)
{
 TCPServer* self = (TCPServer*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"TCPClient");
 tolua_usertype(tolua_S,"TCPServer");
 tolua_usertype(tolua_S,"TCPSession");
 tolua_usertype(tolua_S,"Client");
 tolua_usertype(tolua_S,"Session");
 tolua_usertype(tolua_S,"Server");
}

/* method: send of class  Session */
#ifndef TOLUA_DISABLE_tolua_net_Session_send00
static int tolua_net_Session_send00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Session",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Session* self = (Session*)  tolua_tousertype(tolua_S,1,0);
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

/* method: disconnect of class  Session */
#ifndef TOLUA_DISABLE_tolua_net_Session_disconnect00
static int tolua_net_Session_disconnect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Session",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Session* self = (Session*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getSessionID of class  Session */
#ifndef TOLUA_DISABLE_tolua_net_Session_getSessionID00
static int tolua_net_Session_getSessionID00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Session",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Session* self = (Session*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getPort of class  Session */
#ifndef TOLUA_DISABLE_tolua_net_Session_getPort00
static int tolua_net_Session_getPort00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Session",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Session* self = (Session*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getIp of class  Session */
#ifndef TOLUA_DISABLE_tolua_net_Session_getIp00
static int tolua_net_Session_getIp00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Session",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Session* self = (Session*)  tolua_tousertype(tolua_S,1,0);
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

/* method: connect of class  Client */
#ifndef TOLUA_DISABLE_tolua_net_Client_connect00
static int tolua_net_Client_connect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Client",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Client* self = (Client*)  tolua_tousertype(tolua_S,1,0);
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

/* method: disconnect of class  Client */
#ifndef TOLUA_DISABLE_tolua_net_Client_disconnect00
static int tolua_net_Client_disconnect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Client",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Client* self = (Client*)  tolua_tousertype(tolua_S,1,0);
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

/* method: closeClient of class  Client */
#ifndef TOLUA_DISABLE_tolua_net_Client_closeClient00
static int tolua_net_Client_closeClient00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Client",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Client* self = (Client*)  tolua_tousertype(tolua_S,1,0);
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

/* method: updateFrame of class  Client */
#ifndef TOLUA_DISABLE_tolua_net_Client_updateFrame00
static int tolua_net_Client_updateFrame00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Client",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Client* self = (Client*)  tolua_tousertype(tolua_S,1,0);
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

/* method: send of class  Client */
#ifndef TOLUA_DISABLE_tolua_net_Client_send00
static int tolua_net_Client_send00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Client",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Client* self = (Client*)  tolua_tousertype(tolua_S,1,0);
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

/* method: removeSession of class  Client */
#ifndef TOLUA_DISABLE_tolua_net_Client_removeSession00
static int tolua_net_Client_removeSession00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Client",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Client* self = (Client*)  tolua_tousertype(tolua_S,1,0);
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

/* method: startServer of class  Server */
#ifndef TOLUA_DISABLE_tolua_net_Server_startServer00
static int tolua_net_Server_startServer00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Server",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Server* self = (Server*)  tolua_tousertype(tolua_S,1,0);
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

/* method: stopServer of class  Server */
#ifndef TOLUA_DISABLE_tolua_net_Server_stopServer00
static int tolua_net_Server_stopServer00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Server",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Server* self = (Server*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPClient_new00
static int tolua_net_TCPClient_new00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
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
   TCPClient* tolua_ret = (TCPClient*)  Mtolua_new((TCPClient)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TCPClient");
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

/* method: new_local of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPClient_new00_local
static int tolua_net_TCPClient_new00_local(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
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
   TCPClient* tolua_ret = (TCPClient*)  Mtolua_new((TCPClient)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TCPClient");
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

/* method: delete of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPClient_delete00
static int tolua_net_TCPClient_delete00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
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

/* method: send of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPClient_send00
static int tolua_net_TCPClient_send00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPClient",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Session",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPClient* self = (TCPClient*)  tolua_tousertype(tolua_S,1,0);
  Session* session = ((Session*)  tolua_tousertype(tolua_S,2,0));
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

/* method: disconnect of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPClient_disconnect00
static int tolua_net_TCPClient_disconnect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPClient",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Session",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPClient* self = (TCPClient*)  tolua_tousertype(tolua_S,1,0);
  Session* session = ((Session*)  tolua_tousertype(tolua_S,2,0));
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

/* method: isCloseFinish of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPClient_isCloseFinish00
static int tolua_net_TCPClient_isCloseFinish00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
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

/* method: setSocketNoDelay of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPClient_setSocketNoDelay00
static int tolua_net_TCPClient_setSocketNoDelay00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPClient",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPClient* self = (TCPClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setSocketKeepAlive of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPClient_setSocketKeepAlive00
static int tolua_net_TCPClient_setSocketKeepAlive00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPClient* self = (TCPClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setAutoReconnect of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPClient_setAutoReconnect00
static int tolua_net_TCPClient_setAutoReconnect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPClient",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPClient* self = (TCPClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setAutoReconnectTime of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPClient_setAutoReconnectTime00
static int tolua_net_TCPClient_setAutoReconnectTime00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
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

/* method: setAutoReconnectBySessionID of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPClient_setAutoReconnectBySessionID00
static int tolua_net_TCPClient_setAutoReconnectBySessionID00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPClient* self = (TCPClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setAutoReconnectTimeBySessionID of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_net_TCPClient_setAutoReconnectTimeBySessionID00
static int tolua_net_TCPClient_setAutoReconnectTimeBySessionID00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPClient",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPClient* self = (TCPClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  TCPServer */
#ifndef TOLUA_DISABLE_tolua_net_TCPServer_new00
static int tolua_net_TCPServer_new00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TCPServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TCPServer* tolua_ret = (TCPServer*)  Mtolua_new((TCPServer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TCPServer");
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

/* method: new_local of class  TCPServer */
#ifndef TOLUA_DISABLE_tolua_net_TCPServer_new00_local
static int tolua_net_TCPServer_new00_local(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TCPServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TCPServer* tolua_ret = (TCPServer*)  Mtolua_new((TCPServer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TCPServer");
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

/* method: delete of class  TCPServer */
#ifndef TOLUA_DISABLE_tolua_net_TCPServer_delete00
static int tolua_net_TCPServer_delete00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPServer* self = (TCPServer*)  tolua_tousertype(tolua_S,1,0);
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

/* method: send of class  TCPServer */
#ifndef TOLUA_DISABLE_tolua_net_TCPServer_send00
static int tolua_net_TCPServer_send00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPServer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Session",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPServer* self = (TCPServer*)  tolua_tousertype(tolua_S,1,0);
  Session* session = ((Session*)  tolua_tousertype(tolua_S,2,0));
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

/* method: disconnect of class  TCPServer */
#ifndef TOLUA_DISABLE_tolua_net_TCPServer_disconnect00
static int tolua_net_TCPServer_disconnect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPServer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Session",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPServer* self = (TCPServer*)  tolua_tousertype(tolua_S,1,0);
  Session* session = ((Session*)  tolua_tousertype(tolua_S,2,0));
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

/* method: isCloseFinish of class  TCPServer */
#ifndef TOLUA_DISABLE_tolua_net_TCPServer_isCloseFinish00
static int tolua_net_TCPServer_isCloseFinish00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPServer* self = (TCPServer*)  tolua_tousertype(tolua_S,1,0);
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

/* Open function */
TOLUA_API int tolua_net_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"Session","Session","",NULL);
  tolua_beginmodule(tolua_S,"Session");
   tolua_function(tolua_S,"send",tolua_net_Session_send00);
   tolua_function(tolua_S,"disconnect",tolua_net_Session_disconnect00);
   tolua_function(tolua_S,"getSessionID",tolua_net_Session_getSessionID00);
   tolua_function(tolua_S,"getPort",tolua_net_Session_getPort00);
   tolua_function(tolua_S,"getIp",tolua_net_Session_getIp00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Client","Client","",NULL);
  tolua_beginmodule(tolua_S,"Client");
   tolua_function(tolua_S,"connect",tolua_net_Client_connect00);
   tolua_function(tolua_S,"disconnect",tolua_net_Client_disconnect00);
   tolua_function(tolua_S,"closeClient",tolua_net_Client_closeClient00);
   tolua_function(tolua_S,"updateFrame",tolua_net_Client_updateFrame00);
   tolua_function(tolua_S,"send",tolua_net_Client_send00);
   tolua_function(tolua_S,"removeSession",tolua_net_Client_removeSession00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Server","Server","",NULL);
  tolua_beginmodule(tolua_S,"Server");
   tolua_function(tolua_S,"startServer",tolua_net_Server_startServer00);
   tolua_function(tolua_S,"stopServer",tolua_net_Server_stopServer00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"TCPSession","TCPSession","Session",NULL);
  tolua_beginmodule(tolua_S,"TCPSession");
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"TCPClient","TCPClient","Client",tolua_collect_TCPClient);
  #else
  tolua_cclass(tolua_S,"TCPClient","TCPClient","Client",NULL);
  #endif
  tolua_beginmodule(tolua_S,"TCPClient");
   tolua_function(tolua_S,"new",tolua_net_TCPClient_new00);
   tolua_function(tolua_S,"new_local",tolua_net_TCPClient_new00_local);
   tolua_function(tolua_S,".call",tolua_net_TCPClient_new00_local);
   tolua_function(tolua_S,"delete",tolua_net_TCPClient_delete00);
   tolua_function(tolua_S,"send",tolua_net_TCPClient_send00);
   tolua_function(tolua_S,"disconnect",tolua_net_TCPClient_disconnect00);
   tolua_function(tolua_S,"isCloseFinish",tolua_net_TCPClient_isCloseFinish00);
   tolua_function(tolua_S,"setSocketNoDelay",tolua_net_TCPClient_setSocketNoDelay00);
   tolua_function(tolua_S,"setSocketKeepAlive",tolua_net_TCPClient_setSocketKeepAlive00);
   tolua_function(tolua_S,"setAutoReconnect",tolua_net_TCPClient_setAutoReconnect00);
   tolua_function(tolua_S,"setAutoReconnectTime",tolua_net_TCPClient_setAutoReconnectTime00);
   tolua_function(tolua_S,"setAutoReconnectBySessionID",tolua_net_TCPClient_setAutoReconnectBySessionID00);
   tolua_function(tolua_S,"setAutoReconnectTimeBySessionID",tolua_net_TCPClient_setAutoReconnectTimeBySessionID00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"TCPServer","TCPServer","Server",tolua_collect_TCPServer);
  #else
  tolua_cclass(tolua_S,"TCPServer","TCPServer","Server",NULL);
  #endif
  tolua_beginmodule(tolua_S,"TCPServer");
   tolua_function(tolua_S,"new",tolua_net_TCPServer_new00);
   tolua_function(tolua_S,"new_local",tolua_net_TCPServer_new00_local);
   tolua_function(tolua_S,".call",tolua_net_TCPServer_new00_local);
   tolua_function(tolua_S,"delete",tolua_net_TCPServer_delete00);
   tolua_function(tolua_S,"send",tolua_net_TCPServer_send00);
   tolua_function(tolua_S,"disconnect",tolua_net_TCPServer_disconnect00);
   tolua_function(tolua_S,"isCloseFinish",tolua_net_TCPServer_isCloseFinish00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_net (lua_State* tolua_S) {
 return tolua_net_open(tolua_S);
};
#endif

