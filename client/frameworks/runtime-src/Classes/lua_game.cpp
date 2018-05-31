/*
** Lua binding: game
** Generated automatically by tolua++-1.0.92 on 05/31/18 22:32:53.
*/

#include "tolua_fix.h"
#include "tolua++.h"
#include <string>




#include "gamecore/FSM.h"
#include "gamecore/GameActor.h"
#include "gamecore/GameAttribute.h"
#include "gamecore/GameWord.h"
#include "net/Client.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_GameAttribute (lua_State* tolua_S)
{
 GameAttribute* self = (GameAttribute*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_GameActor (lua_State* tolua_S)
{
 GameActor* self = (GameActor*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_GameWord (lua_State* tolua_S)
{
 GameWord* self = (GameWord*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_QFSM (lua_State* tolua_S)
{
 QFSM* self = (QFSM*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_QFSMState (lua_State* tolua_S)
{
 QFSMState* self = (QFSMState*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_Size (lua_State* tolua_S)
{
 Size* self = (Size*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"GameAttribute");
 tolua_usertype(tolua_S,"QFSMState");
 
 tolua_usertype(tolua_S,"Vec2");
 tolua_usertype(tolua_S,"ccs.Armature");
 tolua_usertype(tolua_S,"TCPClient");
 tolua_usertype(tolua_S,"GameActor");
 tolua_usertype(tolua_S,"SK");
 tolua_usertype(tolua_S,"GameWord");
 tolua_usertype(tolua_S,"QFSM");
 tolua_usertype(tolua_S,"Client");
 tolua_usertype(tolua_S,"cc.Node");
 tolua_usertype(tolua_S,"Size");
}

/* method: new of class  QFSMState */
#ifndef TOLUA_DISABLE_tolua_game_QFSMState_new00
static int tolua_game_QFSMState_new00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"QFSMState",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SK",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_isfunction(tolua_S,3,"LuaFunction",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !toluafix_isfunction(tolua_S,4,"LuaFunction",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SK stateName = *((SK*)  tolua_tousertype(tolua_S,2,0));
  LuaFunction enterFunc = (  LuaFunction(tolua_S,3,0));
  LuaFunction leaveFunc = (  LuaFunction(tolua_S,4,0));
  {
   QFSMState* tolua_ret = (QFSMState*)  Mtolua_new((QFSMState)(stateName,enterFunc,leaveFunc));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"QFSMState");
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

/* method: new_local of class  QFSMState */
#ifndef TOLUA_DISABLE_tolua_game_QFSMState_new00_local
static int tolua_game_QFSMState_new00_local(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"QFSMState",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SK",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_isfunction(tolua_S,3,"LuaFunction",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !toluafix_isfunction(tolua_S,4,"LuaFunction",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SK stateName = *((SK*)  tolua_tousertype(tolua_S,2,0));
  LuaFunction enterFunc = (  LuaFunction(tolua_S,3,0));
  LuaFunction leaveFunc = (  LuaFunction(tolua_S,4,0));
  {
   QFSMState* tolua_ret = (QFSMState*)  Mtolua_new((QFSMState)(stateName,enterFunc,leaveFunc));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"QFSMState");
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

/* method: delete of class  QFSMState */
#ifndef TOLUA_DISABLE_tolua_game_QFSMState_delete00
static int tolua_game_QFSMState_delete00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QFSMState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  QFSMState* self = (QFSMState*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getStateName of class  QFSMState */
#ifndef TOLUA_DISABLE_tolua_game_QFSMState_getStateName00
static int tolua_game_QFSMState_getStateName00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QFSMState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  QFSMState* self = (QFSMState*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStateName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getStateName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStateName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFSM of class  QFSMState */
#ifndef TOLUA_DISABLE_tolua_game_QFSMState_getFSM00
static int tolua_game_QFSMState_getFSM00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QFSMState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  QFSMState* self = (QFSMState*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFSM'", NULL);
#endif
  {
   QFSM* tolua_ret = (QFSM*)  self->getFSM();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"QFSM");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFSM'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_game_QFSM_new00
static int tolua_game_QFSM_new00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"QFSM",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   QFSM* tolua_ret = (QFSM*)  Mtolua_new((QFSM)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"QFSM");
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

/* method: new_local of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_game_QFSM_new00_local
static int tolua_game_QFSM_new00_local(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"QFSM",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   QFSM* tolua_ret = (QFSM*)  Mtolua_new((QFSM)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"QFSM");
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

/* method: delete of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_game_QFSM_delete00
static int tolua_game_QFSM_delete00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QFSM",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  QFSM* self = (QFSM*)  tolua_tousertype(tolua_S,1,0);
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

/* method: addState of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_game_QFSM_addState00
static int tolua_game_QFSM_addState00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QFSM",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_isfunction(tolua_S,3,"LuaFunction",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !toluafix_isfunction(tolua_S,4,"LuaFunction",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  QFSM* self = (QFSM*)  tolua_tousertype(tolua_S,1,0);
  std::string stateName = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  LuaFunction enterFunc = (  LuaFunction(tolua_S,3,0));
  LuaFunction leaveFunc = (  LuaFunction(tolua_S,4,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addState'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->addState(stateName,enterFunc,leaveFunc);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addTranslation of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_game_QFSM_addTranslation00
static int tolua_game_QFSM_addTranslation00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QFSM",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  QFSM* self = (QFSM*)  tolua_tousertype(tolua_S,1,0);
  std::string fromStateName = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  std::string eventName = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  std::string toStateName = ((std::string)  tolua_tocppstring(tolua_S,4,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addTranslation'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->addTranslation(fromStateName,eventName,toStateName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addTranslation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeTranslation of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_game_QFSM_removeTranslation00
static int tolua_game_QFSM_removeTranslation00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QFSM",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  QFSM* self = (QFSM*)  tolua_tousertype(tolua_S,1,0);
  std::string fromStateName = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  std::string eventName = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  std::string toStateName = ((std::string)  tolua_tocppstring(tolua_S,4,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeTranslation'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->removeTranslation(fromStateName,eventName,toStateName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeTranslation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: start of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_game_QFSM_start00
static int tolua_game_QFSM_start00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QFSM",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  QFSM* self = (QFSM*)  tolua_tousertype(tolua_S,1,0);
  std::string startStateName = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'start'", NULL);
#endif
  {
   self->start(startStateName);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'start'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: handle of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_game_QFSM_handle00
static int tolua_game_QFSM_handle00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QFSM",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  QFSM* self = (QFSM*)  tolua_tousertype(tolua_S,1,0);
  std::string eventName = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'handle'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->handle(eventName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'handle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_game_QFSM_clear00
static int tolua_game_QFSM_clear00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QFSM",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  QFSM* self = (QFSM*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPreState of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_game_QFSM_getPreState00
static int tolua_game_QFSM_getPreState00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QFSM",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  QFSM* self = (QFSM*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPreState'", NULL);
#endif
  {
   QFSMState* tolua_ret = (QFSMState*)  self->getPreState();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"QFSMState");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPreState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNextState of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_game_QFSM_getNextState00
static int tolua_game_QFSM_getNextState00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QFSM",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  QFSM* self = (QFSM*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNextState'", NULL);
#endif
  {
   QFSMState* tolua_ret = (QFSMState*)  self->getNextState();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"QFSMState");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNextState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurState of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_game_QFSM_getCurState00
static int tolua_game_QFSM_getCurState00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QFSM",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  QFSM* self = (QFSM*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurState'", NULL);
#endif
  {
   QFSMState* tolua_ret = (QFSMState*)  self->getCurState();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"QFSMState");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurEventName of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_game_QFSM_getCurEventName00
static int tolua_game_QFSM_getCurEventName00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QFSM",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  QFSM* self = (QFSM*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurEventName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getCurEventName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurEventName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_create00
static int tolua_game_GameActor_create00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameActor* tolua_ret = (GameActor*)  GameActor::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameActor");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_new00
static int tolua_game_GameActor_new00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameActor* tolua_ret = (GameActor*)  Mtolua_new((GameActor)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameActor");
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

/* method: new_local of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_new00_local
static int tolua_game_GameActor_new00_local(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameActor* tolua_ret = (GameActor*)  Mtolua_new((GameActor)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameActor");
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

/* method: delete of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_delete00
static int tolua_game_GameActor_delete00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getGameAttribute of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_getGameAttribute00
static int tolua_game_GameActor_getGameAttribute00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getGameAttribute'", NULL);
#endif
  {
   GameAttribute* tolua_ret = (GameAttribute*)  self->getGameAttribute();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameAttribute");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getGameAttribute'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFSM of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_getFSM00
static int tolua_game_GameActor_getFSM00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFSM'", NULL);
#endif
  {
   QFSM* tolua_ret = (QFSM*)  self->getFSM();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"QFSM");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFSM'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getArmature of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_getArmature00
static int tolua_game_GameActor_getArmature00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getArmature'", NULL);
#endif
  {
   Armature* tolua_ret = (Armature*)  self->getArmature();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ccs.Armature");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getArmature'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getGameWord of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_getGameWord00
static int tolua_game_GameActor_getGameWord00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getGameWord'", NULL);
#endif
  {
   GameWord* tolua_ret = (GameWord*)  self->getGameWord();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameWord");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getGameWord'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_init00
static int tolua_game_GameActor_init00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resetMoveSpeed of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_resetMoveSpeed00
static int tolua_game_GameActor_resetMoveSpeed00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resetMoveSpeed'", NULL);
#endif
  {
   self->resetMoveSpeed(x,y);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resetMoveSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: appendMoveSpeed of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_appendMoveSpeed00
static int tolua_game_GameActor_appendMoveSpeed00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'appendMoveSpeed'", NULL);
#endif
  {
   self->appendMoveSpeed(x,y);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'appendMoveSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: logicUpdate of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_logicUpdate00
static int tolua_game_GameActor_logicUpdate00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
  float d = ((float)  tolua_tonumber(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'logicUpdate'", NULL);
#endif
  {
   self->logicUpdate(d);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'logicUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCanMove of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_isCanMove00
static int tolua_game_GameActor_isCanMove00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCanMove'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCanMove();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCanMove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOrientation of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_setOrientation00
static int tolua_game_GameActor_setOrientation00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
  short ori = ((short)  tolua_tonumber(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOrientation'", NULL);
#endif
  {
   self->setOrientation(ori);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOrientation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadArmature of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_loadArmature00
static int tolua_game_GameActor_loadArmature00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
  const std::string filepath = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadArmature'", NULL);
#endif
  {
   self->loadArmature(filepath);
   tolua_pushcppstring(tolua_S,(const char*)filepath);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadArmature'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getActorType of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_getActorType00
static int tolua_game_GameActor_getActorType00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getActorType'", NULL);
#endif
  {
   GameActorType tolua_ret = (GameActorType)  self->getActorType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getActorType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setActorType of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_setActorType00
static int tolua_game_GameActor_setActorType00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
  GameActorType type = ((GameActorType) (int)  tolua_tonumber(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setActorType'", NULL);
#endif
  {
   self->setActorType(type);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setActorType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getActorPosition of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_getActorPosition00
static int tolua_game_GameActor_getActorPosition00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getActorPosition'", NULL);
#endif
  {
   const Vec2& tolua_ret = (const Vec2&)  self->getActorPosition();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vec2");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getActorPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getActorPositionX of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_getActorPositionX00
static int tolua_game_GameActor_getActorPositionX00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getActorPositionX'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getActorPositionX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getActorPositionX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getActorPositionY of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_getActorPositionY00
static int tolua_game_GameActor_getActorPositionY00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getActorPositionY'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getActorPositionY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getActorPositionY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setActorPosition of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_setActorPosition00
static int tolua_game_GameActor_setActorPosition00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setActorPosition'", NULL);
#endif
  {
   self->setActorPosition(x,y);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setActorPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isRunAABB of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_isRunAABB00
static int tolua_game_GameActor_isRunAABB00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameActor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
  GameActor* other = ((GameActor*)  tolua_tousertype(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isRunAABB'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isRunAABB(other);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isRunAABB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: attLevelTest of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_attLevelTest00
static int tolua_game_GameActor_attLevelTest00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameActor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
  GameActor* other = ((GameActor*)  tolua_tousertype(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attLevelTest'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->attLevelTest(other);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attLevelTest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AABBCallback of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_AABBCallback00
static int tolua_game_GameActor_AABBCallback00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameActor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
  GameActor* other = ((GameActor*)  tolua_tousertype(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AABBCallback'", NULL);
#endif
  {
   self->AABBCallback(other);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AABBCallback'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: attOtherActorCallback of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_attOtherActorCallback00
static int tolua_game_GameActor_attOtherActorCallback00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameActor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
  GameActor* other = ((GameActor*)  tolua_tousertype(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attOtherActorCallback'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->attOtherActorCallback(other);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attOtherActorCallback'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerLuaHandle of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_registerLuaHandle00
static int tolua_game_GameActor_registerLuaHandle00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_isfunction(tolua_S,3,"LuaFunction",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
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

/* method: unregisterLuaHandle of class  GameActor */
#ifndef TOLUA_DISABLE_tolua_game_GameActor_unregisterLuaHandle00
static int tolua_game_GameActor_unregisterLuaHandle00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameActor",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameActor* self = (GameActor*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_new00
static int tolua_game_GameAttribute_new00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameAttribute* tolua_ret = (GameAttribute*)  Mtolua_new((GameAttribute)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameAttribute");
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

/* method: new_local of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_new00_local
static int tolua_game_GameAttribute_new00_local(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameAttribute* tolua_ret = (GameAttribute*)  Mtolua_new((GameAttribute)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameAttribute");
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

/* method: setHP of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_setHP00
static int tolua_game_GameAttribute_setHP00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAttribute* self = (GameAttribute*)  tolua_tousertype(tolua_S,1,0);
  int value = ((int)  tolua_tonumber(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setHP'", NULL);
#endif
  {
   self->setHP(value);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setHP'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHP of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_getHP00
static int tolua_game_GameAttribute_getHP00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAttribute* self = (GameAttribute*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHP'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getHP();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHP'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAtt of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_setAtt00
static int tolua_game_GameAttribute_setAtt00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAttribute* self = (GameAttribute*)  tolua_tousertype(tolua_S,1,0);
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAtt'", NULL);
#endif
  {
   self->setAtt(value);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAtt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAtt of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_getAtt00
static int tolua_game_GameAttribute_getAtt00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAttribute* self = (GameAttribute*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAtt'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getAtt();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAtt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDef of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_setDef00
static int tolua_game_GameAttribute_setDef00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAttribute* self = (GameAttribute*)  tolua_tousertype(tolua_S,1,0);
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDef'", NULL);
#endif
  {
   self->setDef(value);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDef'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDef of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_getDef00
static int tolua_game_GameAttribute_getDef00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAttribute* self = (GameAttribute*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDef'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getDef();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDef'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSpeed of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_setSpeed00
static int tolua_game_GameAttribute_setSpeed00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAttribute* self = (GameAttribute*)  tolua_tousertype(tolua_S,1,0);
  float value1 = ((float)  tolua_tonumber(tolua_S,2,0));
  float value2 = ((float)  tolua_tonumber(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSpeed'", NULL);
#endif
  {
   self->setSpeed(value1,value2);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSpeedX of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_getSpeedX00
static int tolua_game_GameAttribute_getSpeedX00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAttribute* self = (GameAttribute*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSpeedX'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getSpeedX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSpeedX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSpeedY of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_getSpeedY00
static int tolua_game_GameAttribute_getSpeedY00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAttribute* self = (GameAttribute*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSpeedY'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getSpeedY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSpeedY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCurSpeed of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_setCurSpeed00
static int tolua_game_GameAttribute_setCurSpeed00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAttribute* self = (GameAttribute*)  tolua_tousertype(tolua_S,1,0);
  float value1 = ((float)  tolua_tonumber(tolua_S,2,0));
  float value2 = ((float)  tolua_tonumber(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCurSpeed'", NULL);
#endif
  {
   self->setCurSpeed(value1,value2);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCurSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurSpeedX of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_getCurSpeedX00
static int tolua_game_GameAttribute_getCurSpeedX00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAttribute* self = (GameAttribute*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurSpeedX'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getCurSpeedX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurSpeedX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurSpeedY of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_getCurSpeedY00
static int tolua_game_GameAttribute_getCurSpeedY00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAttribute* self = (GameAttribute*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurSpeedY'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getCurSpeedY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurSpeedY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMoveDirection of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_setMoveDirection00
static int tolua_game_GameAttribute_setMoveDirection00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAttribute* self = (GameAttribute*)  tolua_tousertype(tolua_S,1,0);
  float value1 = ((float)  tolua_tonumber(tolua_S,2,0));
  float value2 = ((float)  tolua_tonumber(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMoveDirection'", NULL);
#endif
  {
   self->setMoveDirection(value1,value2);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMoveDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMoveDirectionX of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_getMoveDirectionX00
static int tolua_game_GameAttribute_getMoveDirectionX00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAttribute* self = (GameAttribute*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMoveDirectionX'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getMoveDirectionX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMoveDirectionX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMoveDirectionY of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_getMoveDirectionY00
static int tolua_game_GameAttribute_getMoveDirectionY00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAttribute* self = (GameAttribute*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMoveDirectionY'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getMoveDirectionY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMoveDirectionY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCurOrientation of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_setCurOrientation00
static int tolua_game_GameAttribute_setCurOrientation00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAttribute* self = (GameAttribute*)  tolua_tousertype(tolua_S,1,0);
  short value = ((short)  tolua_tonumber(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCurOrientation'", NULL);
#endif
  {
   self->setCurOrientation(value);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCurOrientation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurOrientation of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_getCurOrientation00
static int tolua_game_GameAttribute_getCurOrientation00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAttribute* self = (GameAttribute*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurOrientation'", NULL);
#endif
  {
   short tolua_ret = (short)  self->getCurOrientation();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurOrientation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIsJumpState of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_setIsJumpState00
static int tolua_game_GameAttribute_setIsJumpState00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAttribute* self = (GameAttribute*)  tolua_tousertype(tolua_S,1,0);
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIsJumpState'", NULL);
#endif
  {
   self->setIsJumpState(value);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIsJumpState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIsJumpState of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_getIsJumpState00
static int tolua_game_GameAttribute_getIsJumpState00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAttribute* self = (GameAttribute*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIsJumpState'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getIsJumpState();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIsJumpState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIsBackState of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_setIsBackState00
static int tolua_game_GameAttribute_setIsBackState00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAttribute* self = (GameAttribute*)  tolua_tousertype(tolua_S,1,0);
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIsBackState'", NULL);
#endif
  {
   self->setIsBackState(value);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIsBackState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIsBackState of class  GameAttribute */
#ifndef TOLUA_DISABLE_tolua_game_GameAttribute_getIsBackState00
static int tolua_game_GameAttribute_getIsBackState00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAttribute* self = (GameAttribute*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIsBackState'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getIsBackState();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIsBackState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GameWord */
#ifndef TOLUA_DISABLE_tolua_game_GameWord_new00
static int tolua_game_GameWord_new00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameWord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameWord* tolua_ret = (GameWord*)  Mtolua_new((GameWord)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameWord");
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

/* method: new_local of class  GameWord */
#ifndef TOLUA_DISABLE_tolua_game_GameWord_new00_local
static int tolua_game_GameWord_new00_local(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameWord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameWord* tolua_ret = (GameWord*)  Mtolua_new((GameWord)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameWord");
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

/* method: delete of class  GameWord */
#ifndef TOLUA_DISABLE_tolua_game_GameWord_delete00
static int tolua_game_GameWord_delete00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWord* self = (GameWord*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  GameWord */
#ifndef TOLUA_DISABLE_tolua_game_GameWord_create00
static int tolua_game_GameWord_create00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameWord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameWord* tolua_ret = (GameWord*)  GameWord::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameWord");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  GameWord */
#ifndef TOLUA_DISABLE_tolua_game_GameWord_init00
static int tolua_game_GameWord_init00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWord* self = (GameWord*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addBackgroundMap of class  GameWord */
#ifndef TOLUA_DISABLE_tolua_game_GameWord_addBackgroundMap00
static int tolua_game_GameWord_addBackgroundMap00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWord",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"cc.Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWord* self = (GameWord*)  tolua_tousertype(tolua_S,1,0);
  Node* map = ((Node*)  tolua_tousertype(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addBackgroundMap'", NULL);
#endif
  {
   self->addBackgroundMap(map);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addBackgroundMap'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addForegroundMap of class  GameWord */
#ifndef TOLUA_DISABLE_tolua_game_GameWord_addForegroundMap00
static int tolua_game_GameWord_addForegroundMap00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWord",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"cc.Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWord* self = (GameWord*)  tolua_tousertype(tolua_S,1,0);
  Node* map = ((Node*)  tolua_tousertype(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addForegroundMap'", NULL);
#endif
  {
   self->addForegroundMap(map);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addForegroundMap'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addActor of class  GameWord */
#ifndef TOLUA_DISABLE_tolua_game_GameWord_addActor00
static int tolua_game_GameWord_addActor00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWord",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameActor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWord* self = (GameWord*)  tolua_tousertype(tolua_S,1,0);
  GameActor* actor = ((GameActor*)  tolua_tousertype(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addActor'", NULL);
#endif
  {
   self->addActor(actor);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addActor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeActor of class  GameWord */
#ifndef TOLUA_DISABLE_tolua_game_GameWord_removeActor00
static int tolua_game_GameWord_removeActor00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWord",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameActor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWord* self = (GameWord*)  tolua_tousertype(tolua_S,1,0);
  GameActor* actor = ((GameActor*)  tolua_tousertype(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeActor'", NULL);
#endif
  {
   self->removeActor(actor);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeActor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPlayer of class  GameWord */
#ifndef TOLUA_DISABLE_tolua_game_GameWord_setPlayer00
static int tolua_game_GameWord_setPlayer00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWord",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameActor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWord* self = (GameWord*)  tolua_tousertype(tolua_S,1,0);
  GameActor* player = ((GameActor*)  tolua_tousertype(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPlayer'", NULL);
#endif
  {
   self->setPlayer(player);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPlayer of class  GameWord */
#ifndef TOLUA_DISABLE_tolua_game_GameWord_getPlayer00
static int tolua_game_GameWord_getPlayer00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWord* self = (GameWord*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPlayer'", NULL);
#endif
  {
   GameActor* tolua_ret = (GameActor*)  self->getPlayer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameActor");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeActorByName of class  GameWord */
#ifndef TOLUA_DISABLE_tolua_game_GameWord_removeActorByName00
static int tolua_game_GameWord_removeActorByName00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWord",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWord* self = (GameWord*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeActorByName'", NULL);
#endif
  {
   self->removeActorByName(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeActorByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: logicUpdate of class  GameWord */
#ifndef TOLUA_DISABLE_tolua_game_GameWord_logicUpdate00
static int tolua_game_GameWord_logicUpdate00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWord",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWord* self = (GameWord*)  tolua_tousertype(tolua_S,1,0);
  float d = ((float)  tolua_tonumber(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'logicUpdate'", NULL);
#endif
  {
   self->logicUpdate(d);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'logicUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: openDebugDraw of class  GameWord */
#ifndef TOLUA_DISABLE_tolua_game_GameWord_openDebugDraw00
static int tolua_game_GameWord_openDebugDraw00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWord",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWord* self = (GameWord*)  tolua_tousertype(tolua_S,1,0);
  bool open = ((bool)  tolua_toboolean(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'openDebugDraw'", NULL);
#endif
  {
   self->openDebugDraw(open);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'openDebugDraw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isOpenDebugDraw of class  GameWord */
#ifndef TOLUA_DISABLE_tolua_game_GameWord_isOpenDebugDraw00
static int tolua_game_GameWord_isOpenDebugDraw00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWord* self = (GameWord*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isOpenDebugDraw'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isOpenDebugDraw();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isOpenDebugDraw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRootNode of class  GameWord */
#ifndef TOLUA_DISABLE_tolua_game_GameWord_getRootNode00
static int tolua_game_GameWord_getRootNode00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWord* self = (GameWord*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRootNode'", NULL);
#endif
  {
   Node* tolua_ret = (Node*)  self->getRootNode();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"cc.Node");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRootNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBackgroundMap of class  GameWord */
#ifndef TOLUA_DISABLE_tolua_game_GameWord_getBackgroundMap00
static int tolua_game_GameWord_getBackgroundMap00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWord* self = (GameWord*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBackgroundMap'", NULL);
#endif
  {
   Node* tolua_ret = (Node*)  self->getBackgroundMap();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"cc.Node");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBackgroundMap'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getForegroundMap of class  GameWord */
#ifndef TOLUA_DISABLE_tolua_game_GameWord_getForegroundMap00
static int tolua_game_GameWord_getForegroundMap00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWord* self = (GameWord*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getForegroundMap'", NULL);
#endif
  {
   Node* tolua_ret = (Node*)  self->getForegroundMap();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"cc.Node");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getForegroundMap'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getActorNode of class  GameWord */
#ifndef TOLUA_DISABLE_tolua_game_GameWord_getActorNode00
static int tolua_game_GameWord_getActorNode00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWord* self = (GameWord*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getActorNode'", NULL);
#endif
  {
   Node* tolua_ret = (Node*)  self->getActorNode();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"cc.Node");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getActorNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChildNode of class  GameWord */
#ifndef TOLUA_DISABLE_tolua_game_GameWord_getChildNode00
static int tolua_game_GameWord_getChildNode00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWord",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWord* self = (GameWord*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildNode'", NULL);
#endif
  {
   Node* tolua_ret = (Node*)  self->getChildNode(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"cc.Node");
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChildNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMapSize of class  GameWord */
#ifndef TOLUA_DISABLE_tolua_game_GameWord_getMapSize00
static int tolua_game_GameWord_getMapSize00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWord* self = (GameWord*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMapSize'", NULL);
#endif
  {
   Size tolua_ret = (Size)  self->getMapSize();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Size)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Size");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Size));
     tolua_pushusertype(tolua_S,tolua_obj,"Size");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMapSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  Client */
#ifndef TOLUA_DISABLE_tolua_game_Client_getInstance00
static int tolua_game_Client_getInstance00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Client",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Client* tolua_ret = (Client*)  Client::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Client");
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

/* method: destroy of class  Client */
#ifndef TOLUA_DISABLE_tolua_game_Client_destroy00
static int tolua_game_Client_destroy00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Client",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Client::destroy();
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

/* method: setCallFunc of class  Client */
#ifndef TOLUA_DISABLE_tolua_game_Client_setCallFunc00
static int tolua_game_Client_setCallFunc00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Client",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LuaFunction",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Client* self = (Client*)  tolua_tousertype(tolua_S,1,0);
  LuaFunction handle = (  LuaFunction(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCallFunc'", NULL);
#endif
  {
   self->setCallFunc(handle);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCallFunc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: connect of class  Client */
#ifndef TOLUA_DISABLE_tolua_game_Client_connect00
static int tolua_game_Client_connect00(lua_State* tolua_S)
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
  int port = ((int)  tolua_tonumber(tolua_S,3,0));
  unsigned int key = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'connect'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->connect(ip,port,key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'connect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disconnect of class  Client */
#ifndef TOLUA_DISABLE_tolua_game_Client_disconnect00
static int tolua_game_Client_disconnect00(lua_State* tolua_S)
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
  unsigned int key = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disconnect'", NULL);
#endif
  {
   self->disconnect(key);
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
#ifndef TOLUA_DISABLE_tolua_game_Client_closeClient00
static int tolua_game_Client_closeClient00(lua_State* tolua_S)
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

/* method: isCloseFinish of class  Client */
#ifndef TOLUA_DISABLE_tolua_game_Client_isCloseFinish00
static int tolua_game_Client_isCloseFinish00(lua_State* tolua_S)
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

/* method: send of class  Client */
#ifndef TOLUA_DISABLE_tolua_game_Client_send00
static int tolua_game_Client_send00(lua_State* tolua_S)
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
  unsigned int key = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  char* data = ((char*)  tolua_tostring(tolua_S,3,0));
  unsigned int len = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->send(key,data,len);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'send'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: send of class  Client */
#ifndef TOLUA_DISABLE_tolua_game_Client_send01
static int tolua_game_Client_send01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Client",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Client* self = (Client*)  tolua_tousertype(tolua_S,1,0);
  unsigned int key = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  char* data = ((char*)  tolua_tostring(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->send(key,data);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_game_Client_send00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNoDelay of class  Client */
#ifndef TOLUA_DISABLE_tolua_game_Client_setNoDelay00
static int tolua_game_Client_setNoDelay00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Client",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Client* self = (Client*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNoDelay'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->setNoDelay(enable);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNoDelay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setKeepAlive of class  Client */
#ifndef TOLUA_DISABLE_tolua_game_Client_setKeepAlive00
static int tolua_game_Client_setKeepAlive00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Client",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Client* self = (Client*)  tolua_tousertype(tolua_S,1,0);
  int enable = ((int)  tolua_tonumber(tolua_S,2,0));
  unsigned int delay = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setKeepAlive'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->setKeepAlive(enable,delay);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setKeepAlive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkState of class  Client */
#ifndef TOLUA_DISABLE_tolua_game_Client_checkState00
static int tolua_game_Client_checkState00(lua_State* tolua_S)
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
  unsigned int key = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkState'", NULL);
#endif
  {
   TCPClient::CONNECTSTATE tolua_ret = (TCPClient::CONNECTSTATE)  self->checkState(key);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkState of class  Client */
#ifndef TOLUA_DISABLE_tolua_game_Client_checkState01
static int tolua_game_Client_checkState01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Client",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Client* self = (Client*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int port = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkState'", NULL);
#endif
  {
   TCPClient::CONNECTSTATE tolua_ret = (TCPClient::CONNECTSTATE)  self->checkState(ip,port);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_game_Client_checkState00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoReconnect of class  Client */
#ifndef TOLUA_DISABLE_tolua_game_Client_setAutoReconnect00
static int tolua_game_Client_setAutoReconnect00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Client",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Client* self = (Client*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setAutoReconnectTime of class  Client */
#ifndef TOLUA_DISABLE_tolua_game_Client_setAutoReconnectTime00
static int tolua_game_Client_setAutoReconnectTime00(lua_State* tolua_S)
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

/* method: setAutoReconnectByKey of class  Client */
#ifndef TOLUA_DISABLE_tolua_game_Client_setAutoReconnectByKey00
static int tolua_game_Client_setAutoReconnectByKey00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Client",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Client* self = (Client*)  tolua_tousertype(tolua_S,1,0);
  unsigned int key = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  bool isAuto = ((bool)  tolua_toboolean(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoReconnectByKey'", NULL);
#endif
  {
   self->setAutoReconnectByKey(key,isAuto);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoReconnectByKey'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoReconnectTimeByKey of class  Client */
#ifndef TOLUA_DISABLE_tolua_game_Client_setAutoReconnectTimeByKey00
static int tolua_game_Client_setAutoReconnectTimeByKey00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Client",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Client* self = (Client*)  tolua_tousertype(tolua_S,1,0);
  unsigned int key = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  float time = ((float)  tolua_tonumber(tolua_S,3,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoReconnectTimeByKey'", NULL);
#endif
  {
   self->setAutoReconnectTimeByKey(key,time);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoReconnectTimeByKey'.",&tolua_err);
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
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"QFSMState","QFSMState","",tolua_collect_QFSMState);
  #else
  tolua_cclass(tolua_S,"QFSMState","QFSMState","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"QFSMState");
   tolua_function(tolua_S,"new",tolua_game_QFSMState_new00);
   tolua_function(tolua_S,"new_local",tolua_game_QFSMState_new00_local);
   tolua_function(tolua_S,".call",tolua_game_QFSMState_new00_local);
   tolua_function(tolua_S,"delete",tolua_game_QFSMState_delete00);
   tolua_function(tolua_S,"getStateName",tolua_game_QFSMState_getStateName00);
   tolua_function(tolua_S,"getFSM",tolua_game_QFSMState_getFSM00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"QFSM","QFSM","",tolua_collect_QFSM);
  #else
  tolua_cclass(tolua_S,"QFSM","QFSM","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"QFSM");
   tolua_function(tolua_S,"new",tolua_game_QFSM_new00);
   tolua_function(tolua_S,"new_local",tolua_game_QFSM_new00_local);
   tolua_function(tolua_S,".call",tolua_game_QFSM_new00_local);
   tolua_function(tolua_S,"delete",tolua_game_QFSM_delete00);
   tolua_function(tolua_S,"addState",tolua_game_QFSM_addState00);
   tolua_function(tolua_S,"addTranslation",tolua_game_QFSM_addTranslation00);
   tolua_function(tolua_S,"removeTranslation",tolua_game_QFSM_removeTranslation00);
   tolua_function(tolua_S,"start",tolua_game_QFSM_start00);
   tolua_function(tolua_S,"handle",tolua_game_QFSM_handle00);
   tolua_function(tolua_S,"clear",tolua_game_QFSM_clear00);
   tolua_function(tolua_S,"getPreState",tolua_game_QFSM_getPreState00);
   tolua_function(tolua_S,"getNextState",tolua_game_QFSM_getNextState00);
   tolua_function(tolua_S,"getCurState",tolua_game_QFSM_getCurState00);
   tolua_function(tolua_S,"getCurEventName",tolua_game_QFSM_getCurEventName00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"AT_MONSTER",AT_MONSTER);
  tolua_constant(tolua_S,"AT_NPC",AT_NPC);
  tolua_constant(tolua_S,"AT_PLAYER",AT_PLAYER);
  tolua_constant(tolua_S,"AT_NONE",AT_NONE);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"GameActor","GameActor","cc.Node",tolua_collect_GameActor);
  #else
  tolua_cclass(tolua_S,"GameActor","GameActor","cc.Node",NULL);
  #endif
  tolua_beginmodule(tolua_S,"GameActor");
   tolua_function(tolua_S,"create",tolua_game_GameActor_create00);
   tolua_function(tolua_S,"new",tolua_game_GameActor_new00);
   tolua_function(tolua_S,"new_local",tolua_game_GameActor_new00_local);
   tolua_function(tolua_S,".call",tolua_game_GameActor_new00_local);
   tolua_function(tolua_S,"delete",tolua_game_GameActor_delete00);
   tolua_function(tolua_S,"getGameAttribute",tolua_game_GameActor_getGameAttribute00);
   tolua_function(tolua_S,"getFSM",tolua_game_GameActor_getFSM00);
   tolua_function(tolua_S,"getArmature",tolua_game_GameActor_getArmature00);
   tolua_function(tolua_S,"getGameWord",tolua_game_GameActor_getGameWord00);
   tolua_function(tolua_S,"init",tolua_game_GameActor_init00);
   tolua_function(tolua_S,"resetMoveSpeed",tolua_game_GameActor_resetMoveSpeed00);
   tolua_function(tolua_S,"appendMoveSpeed",tolua_game_GameActor_appendMoveSpeed00);
   tolua_function(tolua_S,"logicUpdate",tolua_game_GameActor_logicUpdate00);
   tolua_function(tolua_S,"isCanMove",tolua_game_GameActor_isCanMove00);
   tolua_function(tolua_S,"setOrientation",tolua_game_GameActor_setOrientation00);
   tolua_function(tolua_S,"loadArmature",tolua_game_GameActor_loadArmature00);
   tolua_function(tolua_S,"getActorType",tolua_game_GameActor_getActorType00);
   tolua_function(tolua_S,"setActorType",tolua_game_GameActor_setActorType00);
   tolua_function(tolua_S,"getActorPosition",tolua_game_GameActor_getActorPosition00);
   tolua_function(tolua_S,"getActorPositionX",tolua_game_GameActor_getActorPositionX00);
   tolua_function(tolua_S,"getActorPositionY",tolua_game_GameActor_getActorPositionY00);
   tolua_function(tolua_S,"setActorPosition",tolua_game_GameActor_setActorPosition00);
   tolua_function(tolua_S,"isRunAABB",tolua_game_GameActor_isRunAABB00);
   tolua_function(tolua_S,"attLevelTest",tolua_game_GameActor_attLevelTest00);
   tolua_function(tolua_S,"AABBCallback",tolua_game_GameActor_AABBCallback00);
   tolua_function(tolua_S,"attOtherActorCallback",tolua_game_GameActor_attOtherActorCallback00);
   tolua_function(tolua_S,"registerLuaHandle",tolua_game_GameActor_registerLuaHandle00);
   tolua_function(tolua_S,"unregisterLuaHandle",tolua_game_GameActor_unregisterLuaHandle00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"GAME_ORI_LEFT",GAME_ORI_LEFT);
  tolua_constant(tolua_S,"GAME_ORI_RIGHT",GAME_ORI_RIGHT);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"GameAttribute","GameAttribute","",tolua_collect_GameAttribute);
  #else
  tolua_cclass(tolua_S,"GameAttribute","GameAttribute","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"GameAttribute");
   tolua_function(tolua_S,"new",tolua_game_GameAttribute_new00);
   tolua_function(tolua_S,"new_local",tolua_game_GameAttribute_new00_local);
   tolua_function(tolua_S,".call",tolua_game_GameAttribute_new00_local);
   tolua_function(tolua_S,"setHP",tolua_game_GameAttribute_setHP00);
   tolua_function(tolua_S,"getHP",tolua_game_GameAttribute_getHP00);
   tolua_function(tolua_S,"setAtt",tolua_game_GameAttribute_setAtt00);
   tolua_function(tolua_S,"getAtt",tolua_game_GameAttribute_getAtt00);
   tolua_function(tolua_S,"setDef",tolua_game_GameAttribute_setDef00);
   tolua_function(tolua_S,"getDef",tolua_game_GameAttribute_getDef00);
   tolua_function(tolua_S,"setSpeed",tolua_game_GameAttribute_setSpeed00);
   tolua_function(tolua_S,"getSpeedX",tolua_game_GameAttribute_getSpeedX00);
   tolua_function(tolua_S,"getSpeedY",tolua_game_GameAttribute_getSpeedY00);
   tolua_function(tolua_S,"setCurSpeed",tolua_game_GameAttribute_setCurSpeed00);
   tolua_function(tolua_S,"getCurSpeedX",tolua_game_GameAttribute_getCurSpeedX00);
   tolua_function(tolua_S,"getCurSpeedY",tolua_game_GameAttribute_getCurSpeedY00);
   tolua_function(tolua_S,"setMoveDirection",tolua_game_GameAttribute_setMoveDirection00);
   tolua_function(tolua_S,"getMoveDirectionX",tolua_game_GameAttribute_getMoveDirectionX00);
   tolua_function(tolua_S,"getMoveDirectionY",tolua_game_GameAttribute_getMoveDirectionY00);
   tolua_function(tolua_S,"setCurOrientation",tolua_game_GameAttribute_setCurOrientation00);
   tolua_function(tolua_S,"getCurOrientation",tolua_game_GameAttribute_getCurOrientation00);
   tolua_function(tolua_S,"setIsJumpState",tolua_game_GameAttribute_setIsJumpState00);
   tolua_function(tolua_S,"getIsJumpState",tolua_game_GameAttribute_getIsJumpState00);
   tolua_function(tolua_S,"setIsBackState",tolua_game_GameAttribute_setIsBackState00);
   tolua_function(tolua_S,"getIsBackState",tolua_game_GameAttribute_getIsBackState00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"GameWord","GameWord","cc.Node",tolua_collect_GameWord);
  #else
  tolua_cclass(tolua_S,"GameWord","GameWord","cc.Node",NULL);
  #endif
  tolua_beginmodule(tolua_S,"GameWord");
   tolua_function(tolua_S,"new",tolua_game_GameWord_new00);
   tolua_function(tolua_S,"new_local",tolua_game_GameWord_new00_local);
   tolua_function(tolua_S,".call",tolua_game_GameWord_new00_local);
   tolua_function(tolua_S,"delete",tolua_game_GameWord_delete00);
   tolua_function(tolua_S,"create",tolua_game_GameWord_create00);
   tolua_function(tolua_S,"init",tolua_game_GameWord_init00);
   tolua_function(tolua_S,"addBackgroundMap",tolua_game_GameWord_addBackgroundMap00);
   tolua_function(tolua_S,"addForegroundMap",tolua_game_GameWord_addForegroundMap00);
   tolua_function(tolua_S,"addActor",tolua_game_GameWord_addActor00);
   tolua_function(tolua_S,"removeActor",tolua_game_GameWord_removeActor00);
   tolua_function(tolua_S,"setPlayer",tolua_game_GameWord_setPlayer00);
   tolua_function(tolua_S,"getPlayer",tolua_game_GameWord_getPlayer00);
   tolua_function(tolua_S,"removeActorByName",tolua_game_GameWord_removeActorByName00);
   tolua_function(tolua_S,"logicUpdate",tolua_game_GameWord_logicUpdate00);
   tolua_function(tolua_S,"openDebugDraw",tolua_game_GameWord_openDebugDraw00);
   tolua_function(tolua_S,"isOpenDebugDraw",tolua_game_GameWord_isOpenDebugDraw00);
   tolua_function(tolua_S,"getRootNode",tolua_game_GameWord_getRootNode00);
   tolua_function(tolua_S,"getBackgroundMap",tolua_game_GameWord_getBackgroundMap00);
   tolua_function(tolua_S,"getForegroundMap",tolua_game_GameWord_getForegroundMap00);
   tolua_function(tolua_S,"getActorNode",tolua_game_GameWord_getActorNode00);
   tolua_function(tolua_S,"getChildNode",tolua_game_GameWord_getChildNode00);
   tolua_function(tolua_S,"getMapSize",tolua_game_GameWord_getMapSize00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"TCPClient","TCPClient","",NULL);
  tolua_beginmodule(tolua_S,"TCPClient");
   tolua_constant(tolua_S,"CONNECT",TCPClient::CONNECT);
   tolua_constant(tolua_S,"CONNECTING",TCPClient::CONNECTING);
   tolua_constant(tolua_S,"DISCONNECTING",TCPClient::DISCONNECTING);
   tolua_constant(tolua_S,"DISCONNECT",TCPClient::DISCONNECT);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Client","Client","",NULL);
  tolua_beginmodule(tolua_S,"Client");
   tolua_function(tolua_S,"getInstance",tolua_game_Client_getInstance00);
   tolua_function(tolua_S,"destroy",tolua_game_Client_destroy00);
   tolua_function(tolua_S,"setCallFunc",tolua_game_Client_setCallFunc00);
   tolua_function(tolua_S,"connect",tolua_game_Client_connect00);
   tolua_function(tolua_S,"disconnect",tolua_game_Client_disconnect00);
   tolua_function(tolua_S,"closeClient",tolua_game_Client_closeClient00);
   tolua_function(tolua_S,"isCloseFinish",tolua_game_Client_isCloseFinish00);
   tolua_function(tolua_S,"send",tolua_game_Client_send00);
   tolua_function(tolua_S,"send",tolua_game_Client_send01);
   tolua_function(tolua_S,"setNoDelay",tolua_game_Client_setNoDelay00);
   tolua_function(tolua_S,"setKeepAlive",tolua_game_Client_setKeepAlive00);
   tolua_function(tolua_S,"checkState",tolua_game_Client_checkState00);
   tolua_function(tolua_S,"checkState",tolua_game_Client_checkState01);
   tolua_function(tolua_S,"setAutoReconnect",tolua_game_Client_setAutoReconnect00);
   tolua_function(tolua_S,"setAutoReconnectTime",tolua_game_Client_setAutoReconnectTime00);
   tolua_function(tolua_S,"setAutoReconnectByKey",tolua_game_Client_setAutoReconnectByKey00);
   tolua_function(tolua_S,"setAutoReconnectTimeByKey",tolua_game_Client_setAutoReconnectTimeByKey00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_game (lua_State* tolua_S) {
 return tolua_game_open(tolua_S);
};
#endif

