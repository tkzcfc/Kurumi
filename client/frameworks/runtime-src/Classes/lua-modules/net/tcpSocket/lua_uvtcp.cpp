/*
** Lua binding: uvtcp
** Generated automatically by tolua++-1.0.92 on 05/12/18 15:30:17.
*/

#include "tolua_fix.h"
#include "tolua++.h"
#include <string>


/* Exported function */
TOLUA_API int  tolua_uvtcp_open (lua_State* tolua_S);

#include "TCPServer.h"
#include "TCPSocket.h"
#include "TCPClient.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_TCPClient (lua_State* tolua_S)
{
 TCPClient* self = (TCPClient*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_TCPSocket (lua_State* tolua_S)
{
 TCPSocket* self = (TCPSocket*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"TCPClient");
 tolua_usertype(tolua_S,"TCPSocket");
 tolua_usertype(tolua_S,"std::vector<ThreadMsg_C>");
}

/* method: delete of class  TCPSocket */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPSocket_delete00
static int tolua_uvtcp_TCPSocket_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPSocket",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPSocket* self = (TCPSocket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: listen of class  TCPSocket */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPSocket_listen00
static int tolua_uvtcp_TCPSocket_listen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPSocket",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPSocket* self = (TCPSocket*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int port = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'listen'", NULL);
#endif
  {
   self->listen(ip,port);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'listen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: connect of class  TCPSocket */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPSocket_connect00
static int tolua_uvtcp_TCPSocket_connect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPSocket",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPSocket* self = (TCPSocket*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int port = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned int timeout = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'connect'", NULL);
#endif
  {
   self->connect(ip,port,timeout);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'connect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reconnect of class  TCPSocket */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPSocket_reconnect00
static int tolua_uvtcp_TCPSocket_reconnect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPSocket",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPSocket* self = (TCPSocket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reconnect'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->reconnect();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isConnect of class  TCPSocket */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPSocket_isConnect00
static int tolua_uvtcp_TCPSocket_isConnect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPSocket",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPSocket* self = (TCPSocket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isConnect'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isConnect();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isConnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disconnect of class  TCPSocket */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPSocket_disconnect00
static int tolua_uvtcp_TCPSocket_disconnect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPSocket",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPSocket* self = (TCPSocket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disconnect'", NULL);
#endif
  {
   self->disconnect();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: send of class  TCPSocket */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPSocket_send00
static int tolua_uvtcp_TCPSocket_send00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPSocket",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPSocket* self = (TCPSocket*)  tolua_tousertype(tolua_S,1,0);
  const char* data = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int len = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->send(data,len);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'send'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIp of class  TCPSocket */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPSocket_getIp00
static int tolua_uvtcp_TCPSocket_getIp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPSocket",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPSocket* self = (TCPSocket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIp'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getIp();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPort of class  TCPSocket */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPSocket_getPort00
static int tolua_uvtcp_TCPSocket_getPort00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPSocket",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPSocket* self = (TCPSocket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPort'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getPort();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPort'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getState of class  TCPSocket */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPSocket_getState00
static int tolua_uvtcp_TCPSocket_getState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPSocket",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPSocket* self = (TCPSocket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getState'", NULL);
#endif
  {
   tcpSocketState tolua_ret = (tcpSocketState)  self->getState();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNoDelay of class  TCPSocket */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPSocket_setNoDelay00
static int tolua_uvtcp_TCPSocket_setNoDelay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPSocket",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPSocket* self = (TCPSocket*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNoDelay'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->setNoDelay(enable);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNoDelay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setKeepAlive of class  TCPSocket */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPSocket_setKeepAlive00
static int tolua_uvtcp_TCPSocket_setKeepAlive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPSocket",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPSocket* self = (TCPSocket*)  tolua_tousertype(tolua_S,1,0);
  int enable = ((int)  tolua_tonumber(tolua_S,2,0));
  unsigned int delay = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setKeepAlive'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->setKeepAlive(enable,delay);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setKeepAlive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPClient_new00
static int tolua_uvtcp_TCPClient_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
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
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPClient_new00_local
static int tolua_uvtcp_TCPClient_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
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
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPClient_delete00
static int tolua_uvtcp_TCPClient_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
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
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: connect of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPClient_connect00
static int tolua_uvtcp_TCPClient_connect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPClient* self = (TCPClient*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  int port = ((int)  tolua_tonumber(tolua_S,3,0));
  unsigned int key = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
  unsigned int timeout = ((unsigned int)  tolua_tonumber(tolua_S,5,3000U));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'connect'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->connect(ip,port,key,timeout);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'connect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disconnect of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPClient_disconnect00
static int tolua_uvtcp_TCPClient_disconnect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
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
  unsigned int key = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disconnect'", NULL);
#endif
  {
   self->disconnect(key);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: closeClient of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPClient_closeClient00
static int tolua_uvtcp_TCPClient_closeClient00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
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
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'closeClient'", NULL);
#endif
  {
   self->closeClient();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'closeClient'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCloseFinish of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPClient_isCloseFinish00
static int tolua_uvtcp_TCPClient_isCloseFinish00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
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
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCloseFinish'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCloseFinish();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCloseFinish'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: send of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPClient_send00
static int tolua_uvtcp_TCPClient_send00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
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
  unsigned int key = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  char* data = ((char*)  tolua_tostring(tolua_S,3,0));
  unsigned int len = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->send(key,data,len);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'send'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSocketNoDelay of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPClient_setSocketNoDelay00
static int tolua_uvtcp_TCPClient_setSocketNoDelay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
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
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSocketNoDelay'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->setSocketNoDelay(enable);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSocketNoDelay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSocketKeepAlive of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPClient_setSocketKeepAlive00
static int tolua_uvtcp_TCPClient_setSocketKeepAlive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
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
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSocketKeepAlive'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->setSocketKeepAlive(enable,delay);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSocketKeepAlive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAllThreadMsg of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPClient_getAllThreadMsg00
static int tolua_uvtcp_TCPClient_getAllThreadMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPClient",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"std::vector<ThreadMsg_C>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TCPClient* self = (TCPClient*)  tolua_tousertype(tolua_S,1,0);
  std::vector<ThreadMsg_C>* v = ((std::vector<ThreadMsg_C>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAllThreadMsg'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getAllThreadMsg(v);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAllThreadMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSocketByKey of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPClient_getSocketByKey00
static int tolua_uvtcp_TCPClient_getSocketByKey00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
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
  unsigned int key = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSocketByKey'", NULL);
#endif
  {
   TCPSocket* tolua_ret = (TCPSocket*)  self->getSocketByKey(key);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TCPSocket");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSocketByKey'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkState of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPClient_checkState00
static int tolua_uvtcp_TCPClient_checkState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
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
  unsigned int key = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkState'", NULL);
#endif
  {
   TCPClient::CONNECTSTATE tolua_ret = (TCPClient::CONNECTSTATE)  self->checkState(key);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkState of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPClient_checkState01
static int tolua_uvtcp_TCPClient_checkState01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TCPClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  TCPClient* self = (TCPClient*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int port = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkState'", NULL);
#endif
  {
   TCPClient::CONNECTSTATE tolua_ret = (TCPClient::CONNECTSTATE)  self->checkState(ip,port);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_uvtcp_TCPClient_checkState00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoReconnect of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPClient_setAutoReconnect00
static int tolua_uvtcp_TCPClient_setAutoReconnect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
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
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoReconnect'", NULL);
#endif
  {
   self->setAutoReconnect(isAuto);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoReconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoReconnectTime of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPClient_setAutoReconnectTime00
static int tolua_uvtcp_TCPClient_setAutoReconnectTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
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
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoReconnectTime'", NULL);
#endif
  {
   self->setAutoReconnectTime(time);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoReconnectTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoReconnectByKey of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPClient_setAutoReconnectByKey00
static int tolua_uvtcp_TCPClient_setAutoReconnectByKey00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
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
  unsigned int key = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  bool isAuto = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoReconnectByKey'", NULL);
#endif
  {
   self->setAutoReconnectByKey(key,isAuto);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoReconnectByKey'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoReconnectTimeByKey of class  TCPClient */
#ifndef TOLUA_DISABLE_tolua_uvtcp_TCPClient_setAutoReconnectTimeByKey00
static int tolua_uvtcp_TCPClient_setAutoReconnectTimeByKey00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
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
  unsigned int key = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  float time = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoReconnectTimeByKey'", NULL);
#endif
  {
   self->setAutoReconnectTimeByKey(key,time);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoReconnectTimeByKey'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_uvtcp_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"tcps_dis_connect",tcps_dis_connect);
  tolua_constant(tolua_S,"tcps_connecting",tcps_connecting);
  tolua_constant(tolua_S,"tcps_connect",tcps_connect);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"TCPSocket","TCPSocket","",tolua_collect_TCPSocket);
  #else
  tolua_cclass(tolua_S,"TCPSocket","TCPSocket","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"TCPSocket");
   tolua_function(tolua_S,"delete",tolua_uvtcp_TCPSocket_delete00);
   tolua_function(tolua_S,"listen",tolua_uvtcp_TCPSocket_listen00);
   tolua_function(tolua_S,"connect",tolua_uvtcp_TCPSocket_connect00);
   tolua_function(tolua_S,"reconnect",tolua_uvtcp_TCPSocket_reconnect00);
   tolua_function(tolua_S,"isConnect",tolua_uvtcp_TCPSocket_isConnect00);
   tolua_function(tolua_S,"disconnect",tolua_uvtcp_TCPSocket_disconnect00);
   tolua_function(tolua_S,"send",tolua_uvtcp_TCPSocket_send00);
   tolua_function(tolua_S,"getIp",tolua_uvtcp_TCPSocket_getIp00);
   tolua_function(tolua_S,"getPort",tolua_uvtcp_TCPSocket_getPort00);
   tolua_function(tolua_S,"getState",tolua_uvtcp_TCPSocket_getState00);
   tolua_function(tolua_S,"setNoDelay",tolua_uvtcp_TCPSocket_setNoDelay00);
   tolua_function(tolua_S,"setKeepAlive",tolua_uvtcp_TCPSocket_setKeepAlive00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"TCPClient","TCPClient","",tolua_collect_TCPClient);
  #else
  tolua_cclass(tolua_S,"TCPClient","TCPClient","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"TCPClient");
   tolua_constant(tolua_S,"CONNECT",TCPClient::CONNECT);
   tolua_constant(tolua_S,"CONNECTING",TCPClient::CONNECTING);
   tolua_constant(tolua_S,"DISCONNECTING",TCPClient::DISCONNECTING);
   tolua_constant(tolua_S,"DISCONNECT",TCPClient::DISCONNECT);
   tolua_function(tolua_S,"new",tolua_uvtcp_TCPClient_new00);
   tolua_function(tolua_S,"new_local",tolua_uvtcp_TCPClient_new00_local);
   tolua_function(tolua_S,".call",tolua_uvtcp_TCPClient_new00_local);
   tolua_function(tolua_S,"delete",tolua_uvtcp_TCPClient_delete00);
   tolua_function(tolua_S,"connect",tolua_uvtcp_TCPClient_connect00);
   tolua_function(tolua_S,"disconnect",tolua_uvtcp_TCPClient_disconnect00);
   tolua_function(tolua_S,"closeClient",tolua_uvtcp_TCPClient_closeClient00);
   tolua_function(tolua_S,"isCloseFinish",tolua_uvtcp_TCPClient_isCloseFinish00);
   tolua_function(tolua_S,"send",tolua_uvtcp_TCPClient_send00);
   tolua_function(tolua_S,"setSocketNoDelay",tolua_uvtcp_TCPClient_setSocketNoDelay00);
   tolua_function(tolua_S,"setSocketKeepAlive",tolua_uvtcp_TCPClient_setSocketKeepAlive00);
   tolua_function(tolua_S,"getAllThreadMsg",tolua_uvtcp_TCPClient_getAllThreadMsg00);
   tolua_function(tolua_S,"getSocketByKey",tolua_uvtcp_TCPClient_getSocketByKey00);
   tolua_function(tolua_S,"checkState",tolua_uvtcp_TCPClient_checkState00);
   tolua_function(tolua_S,"checkState",tolua_uvtcp_TCPClient_checkState01);
   tolua_function(tolua_S,"setAutoReconnect",tolua_uvtcp_TCPClient_setAutoReconnect00);
   tolua_function(tolua_S,"setAutoReconnectTime",tolua_uvtcp_TCPClient_setAutoReconnectTime00);
   tolua_function(tolua_S,"setAutoReconnectByKey",tolua_uvtcp_TCPClient_setAutoReconnectByKey00);
   tolua_function(tolua_S,"setAutoReconnectTimeByKey",tolua_uvtcp_TCPClient_setAutoReconnectTimeByKey00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_uvtcp (lua_State* tolua_S) {
 return tolua_uvtcp_open(tolua_S);
};
#endif

