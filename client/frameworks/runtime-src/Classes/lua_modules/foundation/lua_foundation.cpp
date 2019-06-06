/*
** Lua binding: foundation
** Generated automatically by tolua++-1.0.92 on 06/06/19 22:57:33.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_foundation_open (lua_State* tolua_S);

#include "lua_function/tolua_ext.h"
#include "foundation/FSM.h"
#include "foundation/GameMap.h"
#include "Box2D/Box2D.h"
#include "foundation/ParticleSystemHelper.h"
#include "foundation/Actor.h"
#include "foundation/Character.h"
#include "foundation/GameWorld.h"
#include "foundation/GameMacro.h"
using namespace cocostudio;

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_b2Vec2 (lua_State* tolua_S)
{
 b2Vec2* self = (b2Vec2*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_QFSMState (lua_State* tolua_S)
{
 QFSMState* self = (QFSMState*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_b2BodyType (lua_State* tolua_S)
{
 b2BodyType* self = (b2BodyType*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_QFSM (lua_State* tolua_S)
{
 QFSM* self = (QFSM*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_b2Filter (lua_State* tolua_S)
{
 b2Filter* self = (b2Filter*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_b2MassData (lua_State* tolua_S)
{
 b2MassData* self = (b2MassData*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"QFSMState");
 tolua_usertype(tolua_S,"b2BodyType");
 tolua_usertype(tolua_S,"b2Shape");
 tolua_usertype(tolua_S,"ccs.Armature");
 tolua_usertype(tolua_S,"b2Fixture");
 tolua_usertype(tolua_S,"b2Filter");
 tolua_usertype(tolua_S,"GameWorld");
 tolua_usertype(tolua_S,"QFSM");
 tolua_usertype(tolua_S,"anax::Component");
 tolua_usertype(tolua_S,"Size");
 tolua_usertype(tolua_S,"Actor");
 tolua_usertype(tolua_S,"LuaFunction");
 tolua_usertype(tolua_S,"anax::World");
 tolua_usertype(tolua_S,"b2MassData");
 tolua_usertype(tolua_S,"Vec2");
 tolua_usertype(tolua_S,"Character");
 tolua_usertype(tolua_S,"anax::Entity");
 tolua_usertype(tolua_S,"GameMap");
 tolua_usertype(tolua_S,"b2Body");
 tolua_usertype(tolua_S,"cc.Node");
 tolua_usertype(tolua_S,"b2Vec2");
}

/* method: new of class  QFSMState */
#ifndef TOLUA_DISABLE_tolua_foundation_QFSMState_new00
static int tolua_foundation_QFSMState_new00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"QFSMState",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_ext_check_isfunction(tolua_S,3,"LuaFunction",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_ext_check_isfunction(tolua_S,4,"LuaFunction",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string stateName = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  LuaFunction enterFunc = (  LuaFunction(tolua_S,3,0));
  LuaFunction leaveFunc = (  LuaFunction(tolua_S,4,0));
  {
   QFSMState* tolua_ret = (QFSMState*)  Mtolua_new((QFSMState)(stateName,enterFunc,leaveFunc));
    tolua_ext_object_to_luaval<QFSMState>(tolua_S,(void*)tolua_ret,"QFSMState");
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

/* method: new_local of class  QFSMState */
#ifndef TOLUA_DISABLE_tolua_foundation_QFSMState_new00_local
static int tolua_foundation_QFSMState_new00_local(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"QFSMState",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_ext_check_isfunction(tolua_S,3,"LuaFunction",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_ext_check_isfunction(tolua_S,4,"LuaFunction",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string stateName = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  LuaFunction enterFunc = (  LuaFunction(tolua_S,3,0));
  LuaFunction leaveFunc = (  LuaFunction(tolua_S,4,0));
  {
   QFSMState* tolua_ret = (QFSMState*)  Mtolua_new((QFSMState)(stateName,enterFunc,leaveFunc));
    tolua_ext_object_to_luaval<QFSMState>(tolua_S,(void*)tolua_ret,"QFSMState");
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

/* method: delete of class  QFSMState */
#ifndef TOLUA_DISABLE_tolua_foundation_QFSMState_delete00
static int tolua_foundation_QFSMState_delete00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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

/* method: getStateName of class  QFSMState */
#ifndef TOLUA_DISABLE_tolua_foundation_QFSMState_getStateName00
static int tolua_foundation_QFSMState_getStateName00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStateName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getStateName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStateName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFSM of class  QFSMState */
#ifndef TOLUA_DISABLE_tolua_foundation_QFSMState_getFSM00
static int tolua_foundation_QFSMState_getFSM00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFSM'", NULL);
#endif
  {
   QFSM* tolua_ret = (QFSM*)  self->getFSM();
    tolua_ext_object_to_luaval<QFSM>(tolua_S,(void*)tolua_ret,"QFSM");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFSM'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_foundation_QFSM_new00
static int tolua_foundation_QFSM_new00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
    tolua_ext_object_to_luaval<QFSM>(tolua_S,(void*)tolua_ret,"QFSM");
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

/* method: new_local of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_foundation_QFSM_new00_local
static int tolua_foundation_QFSM_new00_local(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
    tolua_ext_object_to_luaval<QFSM>(tolua_S,(void*)tolua_ret,"QFSM");
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

/* method: delete of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_foundation_QFSM_delete00
static int tolua_foundation_QFSM_delete00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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

/* method: addState of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_foundation_QFSM_addState00
static int tolua_foundation_QFSM_addState00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QFSM",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_ext_check_isfunction(tolua_S,3,"LuaFunction",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_ext_check_isfunction(tolua_S,4,"LuaFunction",0,&tolua_err)) ||
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addState'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->addState(stateName,enterFunc,leaveFunc);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addTranslation of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_foundation_QFSM_addTranslation00
static int tolua_foundation_QFSM_addTranslation00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addTranslation'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->addTranslation(fromStateName,eventName,toStateName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addTranslation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeTranslation of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_foundation_QFSM_removeTranslation00
static int tolua_foundation_QFSM_removeTranslation00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeTranslation'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->removeTranslation(fromStateName,eventName,toStateName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeTranslation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: start of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_foundation_QFSM_start00
static int tolua_foundation_QFSM_start00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'start'", NULL);
#endif
  {
   self->start(startStateName);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'start'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: handle of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_foundation_QFSM_handle00
static int tolua_foundation_QFSM_handle00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'handle'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->handle(eventName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'handle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_foundation_QFSM_clear00
static int tolua_foundation_QFSM_clear00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: forceSwitch of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_foundation_QFSM_forceSwitch00
static int tolua_foundation_QFSM_forceSwitch00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'forceSwitch'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->forceSwitch(startStateName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'forceSwitch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPreState of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_foundation_QFSM_getPreState00
static int tolua_foundation_QFSM_getPreState00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPreState'", NULL);
#endif
  {
   QFSMState* tolua_ret = (QFSMState*)  self->getPreState();
    tolua_ext_object_to_luaval<QFSMState>(tolua_S,(void*)tolua_ret,"QFSMState");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPreState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPreStateName of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_foundation_QFSM_getPreStateName00
static int tolua_foundation_QFSM_getPreStateName00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPreStateName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getPreStateName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPreStateName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNextState of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_foundation_QFSM_getNextState00
static int tolua_foundation_QFSM_getNextState00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNextState'", NULL);
#endif
  {
   QFSMState* tolua_ret = (QFSMState*)  self->getNextState();
    tolua_ext_object_to_luaval<QFSMState>(tolua_S,(void*)tolua_ret,"QFSMState");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNextState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurState of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_foundation_QFSM_getCurState00
static int tolua_foundation_QFSM_getCurState00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurState'", NULL);
#endif
  {
   QFSMState* tolua_ret = (QFSMState*)  self->getCurState();
    tolua_ext_object_to_luaval<QFSMState>(tolua_S,(void*)tolua_ret,"QFSMState");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurStateName of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_foundation_QFSM_getCurStateName00
static int tolua_foundation_QFSM_getCurStateName00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurStateName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getCurStateName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurStateName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurEventName of class  QFSM */
#ifndef TOLUA_DISABLE_tolua_foundation_QFSM_getCurEventName00
static int tolua_foundation_QFSM_getCurEventName00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurEventName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getCurEventName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurEventName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  GameMap */
#ifndef TOLUA_DISABLE_tolua_foundation_GameMap_create00
static int tolua_foundation_GameMap_create00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameMap",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameMap* tolua_ret = (GameMap*)  GameMap::create();
    tolua_ext_object_to_luaval<GameMap>(tolua_S,(void*)tolua_ret,"GameMap");
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

/* method: loadMapFile of class  GameMap */
#ifndef TOLUA_DISABLE_tolua_foundation_GameMap_loadMapFile00
static int tolua_foundation_GameMap_loadMapFile00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameMap",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameMap* self = (GameMap*)  tolua_tousertype(tolua_S,1,0);
  const std::string filepath = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string actorNodeName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string fixNodeName = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  float minPosY = ((float)  tolua_tonumber(tolua_S,5,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadMapFile'", NULL);
#endif
  {
   self->loadMapFile(filepath,actorNodeName,fixNodeName,minPosY);
   tolua_pushcppstring(tolua_S,(const char*)filepath);
   tolua_pushcppstring(tolua_S,(const char*)actorNodeName);
   tolua_pushcppstring(tolua_S,(const char*)fixNodeName);
  }
 }
 return 3;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadMapFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setViewPos of class  GameMap */
#ifndef TOLUA_DISABLE_tolua_foundation_GameMap_setViewPos00
static int tolua_foundation_GameMap_setViewPos00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameMap",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameMap* self = (GameMap*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setViewPos'", NULL);
#endif
  {
   self->setViewPos(x,y);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setViewPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setViewSize of class  GameMap */
#ifndef TOLUA_DISABLE_tolua_foundation_GameMap_setViewSize00
static int tolua_foundation_GameMap_setViewSize00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameMap",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameMap* self = (GameMap*)  tolua_tousertype(tolua_S,1,0);
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setViewSize'", NULL);
#endif
  {
   self->setViewSize(width,height);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setViewSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getActorNode of class  GameMap */
#ifndef TOLUA_DISABLE_tolua_foundation_GameMap_getActorNode00
static int tolua_foundation_GameMap_getActorNode00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameMap",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameMap* self = (GameMap*)  tolua_tousertype(tolua_S,1,0);
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

/* method: lockMapY of class  GameMap */
#ifndef TOLUA_DISABLE_tolua_foundation_GameMap_lockMapY00
static int tolua_foundation_GameMap_lockMapY00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameMap",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameMap* self = (GameMap*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'lockMapY'", NULL);
#endif
  {
   self->lockMapY();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'lockMapY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unlockMapY of class  GameMap */
#ifndef TOLUA_DISABLE_tolua_foundation_GameMap_unlockMapY00
static int tolua_foundation_GameMap_unlockMapY00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameMap",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameMap* self = (GameMap*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unlockMapY'", NULL);
#endif
  {
   self->unlockMapY();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unlockMapY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMapWidth of class  GameMap */
#ifndef TOLUA_DISABLE_tolua_foundation_GameMap_getMapWidth00
static int tolua_foundation_GameMap_getMapWidth00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameMap",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameMap* self = (GameMap*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMapWidth'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getMapWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMapWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMapHeight of class  GameMap */
#ifndef TOLUA_DISABLE_tolua_foundation_GameMap_getMapHeight00
static int tolua_foundation_GameMap_getMapHeight00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameMap",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameMap* self = (GameMap*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMapHeight'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getMapHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMapHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRootNode of class  GameMap */
#ifndef TOLUA_DISABLE_tolua_foundation_GameMap_getRootNode00
static int tolua_foundation_GameMap_getRootNode00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameMap",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameMap* self = (GameMap*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getMinPosY of class  GameMap */
#ifndef TOLUA_DISABLE_tolua_foundation_GameMap_getMinPosY00
static int tolua_foundation_GameMap_getMinPosY00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameMap",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameMap* self = (GameMap*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMinPosY'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getMinPosY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMinPosY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  b2MassData */
#ifndef TOLUA_DISABLE_tolua_foundation_b2MassData_new00
static int tolua_foundation_b2MassData_new00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"b2MassData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   b2MassData* tolua_ret = (b2MassData*)  Mtolua_new((b2MassData)());
    tolua_ext_object_to_luaval<b2MassData>(tolua_S,(void*)tolua_ret,"b2MassData");
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

/* method: new_local of class  b2MassData */
#ifndef TOLUA_DISABLE_tolua_foundation_b2MassData_new00_local
static int tolua_foundation_b2MassData_new00_local(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"b2MassData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   b2MassData* tolua_ret = (b2MassData*)  Mtolua_new((b2MassData)());
    tolua_ext_object_to_luaval<b2MassData>(tolua_S,(void*)tolua_ret,"b2MassData");
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

/* method: delete of class  b2MassData */
#ifndef TOLUA_DISABLE_tolua_foundation_b2MassData_delete00
static int tolua_foundation_b2MassData_delete00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2MassData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2MassData* self = (b2MassData*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: mass of class  b2MassData */
#ifndef TOLUA_DISABLE_tolua_get_b2MassData_mass
static int tolua_get_b2MassData_mass(lua_State* tolua_S)
{
  b2MassData* self = (b2MassData*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mass'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->mass);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mass of class  b2MassData */
#ifndef TOLUA_DISABLE_tolua_set_b2MassData_mass
static int tolua_set_b2MassData_mass(lua_State* tolua_S)
{
  b2MassData* self = (b2MassData*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mass'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mass = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: center of class  b2MassData */
#ifndef TOLUA_DISABLE_tolua_get_b2MassData_center
static int tolua_get_b2MassData_center(lua_State* tolua_S)
{
  b2MassData* self = (b2MassData*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'center'",NULL);
#endif
   tolua_ext_b2vec2_to_luaval(tolua_S,self->center,"b2Vec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: center of class  b2MassData */
#ifndef TOLUA_DISABLE_tolua_set_b2MassData_center
static int tolua_set_b2MassData_center(lua_State* tolua_S)
{
  b2MassData* self = (b2MassData*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'center'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"b2Vec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->center = (  tolua_ext_luaval_to_b2vec2(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: I of class  b2MassData */
#ifndef TOLUA_DISABLE_tolua_get_b2MassData_I
static int tolua_get_b2MassData_I(lua_State* tolua_S)
{
  b2MassData* self = (b2MassData*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'I'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->I);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: I of class  b2MassData */
#ifndef TOLUA_DISABLE_tolua_set_b2MassData_I
static int tolua_set_b2MassData_I(lua_State* tolua_S)
{
  b2MassData* self = (b2MassData*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'I'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->I = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTransform of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_SetTransform00
static int tolua_foundation_b2Body_SetTransform00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"b2Vec2",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  b2Vec2 position = (  tolua_ext_luaval_to_b2vec2(tolua_S,2,0));
  float angle = ((float)  tolua_tonumber(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTransform'", NULL);
#endif
  {
   self->SetTransform(position,angle);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPosition of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_GetPosition00
static int tolua_foundation_b2Body_GetPosition00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPosition'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->GetPosition();
   {
   tolua_ext_b2vec2_to_luaval(tolua_S, tolua_ret, "b2Vec2");
   }
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAngle of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_GetAngle00
static int tolua_foundation_b2Body_GetAngle00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAngle'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAngle();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAngle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWorldCenter of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_GetWorldCenter00
static int tolua_foundation_b2Body_GetWorldCenter00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWorldCenter'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->GetWorldCenter();
   {
   tolua_ext_b2vec2_to_luaval(tolua_S, tolua_ret, "b2Vec2");
   }
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWorldCenter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLocalCenter of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_GetLocalCenter00
static int tolua_foundation_b2Body_GetLocalCenter00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLocalCenter'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->GetLocalCenter();
   {
   tolua_ext_b2vec2_to_luaval(tolua_S, tolua_ret, "b2Vec2");
   }
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLocalCenter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLinearVelocity of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_SetLinearVelocity00
static int tolua_foundation_b2Body_SetLinearVelocity00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  b2Vec2 v = (  tolua_ext_luaval_to_b2vec2(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLinearVelocity'", NULL);
#endif
  {
   self->SetLinearVelocity(v);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLinearVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLinearVelocity of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_GetLinearVelocity00
static int tolua_foundation_b2Body_GetLinearVelocity00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLinearVelocity'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->GetLinearVelocity();
   {
   tolua_ext_b2vec2_to_luaval(tolua_S, tolua_ret, "b2Vec2");
   }
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLinearVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAngularVelocity of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_SetAngularVelocity00
static int tolua_foundation_b2Body_SetAngularVelocity00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  float omega = ((float)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAngularVelocity'", NULL);
#endif
  {
   self->SetAngularVelocity(omega);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAngularVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAngularVelocity of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_GetAngularVelocity00
static int tolua_foundation_b2Body_GetAngularVelocity00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAngularVelocity'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAngularVelocity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAngularVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ApplyForce of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_ApplyForce00
static int tolua_foundation_b2Body_ApplyForce00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"b2Vec2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_ext_check_is_table(tolua_S,3,"b2Vec2",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  b2Vec2 force = (  tolua_ext_luaval_to_b2vec2(tolua_S,2,0));
  b2Vec2 point = (  tolua_ext_luaval_to_b2vec2(tolua_S,3,0));
  bool wake = ((bool)  tolua_toboolean(tolua_S,4,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ApplyForce'", NULL);
#endif
  {
   self->ApplyForce(force,point,wake);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ApplyForce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ApplyForceToCenter of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_ApplyForceToCenter00
static int tolua_foundation_b2Body_ApplyForceToCenter00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"b2Vec2",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  b2Vec2 force = (  tolua_ext_luaval_to_b2vec2(tolua_S,2,0));
  bool wake = ((bool)  tolua_toboolean(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ApplyForceToCenter'", NULL);
#endif
  {
   self->ApplyForceToCenter(force,wake);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ApplyForceToCenter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ApplyTorque of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_ApplyTorque00
static int tolua_foundation_b2Body_ApplyTorque00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  float torque = ((float)  tolua_tonumber(tolua_S,2,0));
  bool wake = ((bool)  tolua_toboolean(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ApplyTorque'", NULL);
#endif
  {
   self->ApplyTorque(torque,wake);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ApplyTorque'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ApplyLinearImpulse of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_ApplyLinearImpulse00
static int tolua_foundation_b2Body_ApplyLinearImpulse00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"b2Vec2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_ext_check_is_table(tolua_S,3,"b2Vec2",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  b2Vec2 impulse = (  tolua_ext_luaval_to_b2vec2(tolua_S,2,0));
  b2Vec2 point = (  tolua_ext_luaval_to_b2vec2(tolua_S,3,0));
  bool wake = ((bool)  tolua_toboolean(tolua_S,4,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ApplyLinearImpulse'", NULL);
#endif
  {
   self->ApplyLinearImpulse(impulse,point,wake);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ApplyLinearImpulse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ApplyAngularImpulse of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_ApplyAngularImpulse00
static int tolua_foundation_b2Body_ApplyAngularImpulse00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  float impulse = ((float)  tolua_tonumber(tolua_S,2,0));
  bool wake = ((bool)  tolua_toboolean(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ApplyAngularImpulse'", NULL);
#endif
  {
   self->ApplyAngularImpulse(impulse,wake);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ApplyAngularImpulse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMass of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_GetMass00
static int tolua_foundation_b2Body_GetMass00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMass'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetMass();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInertia of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_GetInertia00
static int tolua_foundation_b2Body_GetInertia00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInertia'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetInertia();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInertia'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMassData of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_GetMassData00
static int tolua_foundation_b2Body_GetMassData00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"b2MassData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  b2MassData* data = ((b2MassData*)  tolua_tousertype(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMassData'", NULL);
#endif
  {
   self->GetMassData(data);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMassData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMassData of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_SetMassData00
static int tolua_foundation_b2Body_SetMassData00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"b2MassData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  b2MassData* data = ((b2MassData*)  tolua_tousertype(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMassData'", NULL);
#endif
  {
   self->SetMassData(data);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMassData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResetMassData of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_ResetMassData00
static int tolua_foundation_b2Body_ResetMassData00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResetMassData'", NULL);
#endif
  {
   self->ResetMassData();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ResetMassData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWorldPoint of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_GetWorldPoint00
static int tolua_foundation_b2Body_GetWorldPoint00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  b2Vec2 localPoint = (  tolua_ext_luaval_to_b2vec2(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWorldPoint'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->GetWorldPoint(localPoint);
   {
   tolua_ext_b2vec2_to_luaval(tolua_S, tolua_ret, "b2Vec2");
   }
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWorldPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWorldVector of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_GetWorldVector00
static int tolua_foundation_b2Body_GetWorldVector00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  b2Vec2 localVector = (  tolua_ext_luaval_to_b2vec2(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWorldVector'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->GetWorldVector(localVector);
   {
   tolua_ext_b2vec2_to_luaval(tolua_S, tolua_ret, "b2Vec2");
   }
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWorldVector'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLocalPoint of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_GetLocalPoint00
static int tolua_foundation_b2Body_GetLocalPoint00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  b2Vec2 worldPoint = (  tolua_ext_luaval_to_b2vec2(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLocalPoint'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->GetLocalPoint(worldPoint);
   {
   tolua_ext_b2vec2_to_luaval(tolua_S, tolua_ret, "b2Vec2");
   }
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLocalPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLocalVector of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_GetLocalVector00
static int tolua_foundation_b2Body_GetLocalVector00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  b2Vec2 worldVector = (  tolua_ext_luaval_to_b2vec2(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLocalVector'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->GetLocalVector(worldVector);
   {
   tolua_ext_b2vec2_to_luaval(tolua_S, tolua_ret, "b2Vec2");
   }
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLocalVector'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLinearVelocityFromWorldPoint of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_GetLinearVelocityFromWorldPoint00
static int tolua_foundation_b2Body_GetLinearVelocityFromWorldPoint00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  b2Vec2 worldPoint = (  tolua_ext_luaval_to_b2vec2(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLinearVelocityFromWorldPoint'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->GetLinearVelocityFromWorldPoint(worldPoint);
   {
   tolua_ext_b2vec2_to_luaval(tolua_S, tolua_ret, "b2Vec2");
   }
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLinearVelocityFromWorldPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLinearVelocityFromLocalPoint of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_GetLinearVelocityFromLocalPoint00
static int tolua_foundation_b2Body_GetLinearVelocityFromLocalPoint00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  b2Vec2 localPoint = (  tolua_ext_luaval_to_b2vec2(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLinearVelocityFromLocalPoint'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->GetLinearVelocityFromLocalPoint(localPoint);
   {
   tolua_ext_b2vec2_to_luaval(tolua_S, tolua_ret, "b2Vec2");
   }
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLinearVelocityFromLocalPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLinearDamping of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_GetLinearDamping00
static int tolua_foundation_b2Body_GetLinearDamping00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLinearDamping'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetLinearDamping();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLinearDamping'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLinearDamping of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_SetLinearDamping00
static int tolua_foundation_b2Body_SetLinearDamping00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  float linearDamping = ((float)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLinearDamping'", NULL);
#endif
  {
   self->SetLinearDamping(linearDamping);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLinearDamping'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAngularDamping of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_GetAngularDamping00
static int tolua_foundation_b2Body_GetAngularDamping00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAngularDamping'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAngularDamping();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAngularDamping'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAngularDamping of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_SetAngularDamping00
static int tolua_foundation_b2Body_SetAngularDamping00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  float angularDamping = ((float)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAngularDamping'", NULL);
#endif
  {
   self->SetAngularDamping(angularDamping);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAngularDamping'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGravityScale of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_GetGravityScale00
static int tolua_foundation_b2Body_GetGravityScale00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGravityScale'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetGravityScale();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGravityScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetGravityScale of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_SetGravityScale00
static int tolua_foundation_b2Body_SetGravityScale00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  float scale = ((float)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetGravityScale'", NULL);
#endif
  {
   self->SetGravityScale(scale);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetGravityScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetType of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_SetType00
static int tolua_foundation_b2Body_SetType00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2BodyType",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  b2BodyType type = *((b2BodyType*)  tolua_tousertype(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetType'", NULL);
#endif
  {
   self->SetType(type);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetType of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_GetType00
static int tolua_foundation_b2Body_GetType00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetType'", NULL);
#endif
  {
   b2BodyType tolua_ret = (b2BodyType)  self->GetType();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2BodyType)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2BodyType");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,&tolua_ret,sizeof(b2BodyType));
     tolua_pushusertype(tolua_S,tolua_obj,"b2BodyType");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBullet of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_SetBullet00
static int tolua_foundation_b2Body_SetBullet00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  bool flag = ((bool)  tolua_toboolean(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBullet'", NULL);
#endif
  {
   self->SetBullet(flag);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBullet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsBullet of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_IsBullet00
static int tolua_foundation_b2Body_IsBullet00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsBullet'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsBullet();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsBullet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSleepingAllowed of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_SetSleepingAllowed00
static int tolua_foundation_b2Body_SetSleepingAllowed00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  bool flag = ((bool)  tolua_toboolean(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSleepingAllowed'", NULL);
#endif
  {
   self->SetSleepingAllowed(flag);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSleepingAllowed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsSleepingAllowed of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_IsSleepingAllowed00
static int tolua_foundation_b2Body_IsSleepingAllowed00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsSleepingAllowed'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsSleepingAllowed();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsSleepingAllowed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAwake of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_SetAwake00
static int tolua_foundation_b2Body_SetAwake00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  bool flag = ((bool)  tolua_toboolean(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAwake'", NULL);
#endif
  {
   self->SetAwake(flag);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAwake'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsAwake of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_IsAwake00
static int tolua_foundation_b2Body_IsAwake00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsAwake'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsAwake();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAwake'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetActive of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_SetActive00
static int tolua_foundation_b2Body_SetActive00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  bool flag = ((bool)  tolua_toboolean(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetActive'", NULL);
#endif
  {
   self->SetActive(flag);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetActive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsActive of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_IsActive00
static int tolua_foundation_b2Body_IsActive00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsActive'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsActive();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsActive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFixedRotation of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_SetFixedRotation00
static int tolua_foundation_b2Body_SetFixedRotation00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  bool flag = ((bool)  tolua_toboolean(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFixedRotation'", NULL);
#endif
  {
   self->SetFixedRotation(flag);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFixedRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsFixedRotation of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_IsFixedRotation00
static int tolua_foundation_b2Body_IsFixedRotation00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsFixedRotation'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsFixedRotation();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsFixedRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFixtureList of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_GetFixtureList00
static int tolua_foundation_b2Body_GetFixtureList00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFixtureList'", NULL);
#endif
  {
   b2Fixture* tolua_ret = (b2Fixture*)  self->GetFixtureList();
    tolua_ext_object_to_luaval<b2Fixture>(tolua_S,(void*)tolua_ret,"b2Fixture");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFixtureList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNext of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Body_GetNext00
static int tolua_foundation_b2Body_GetNext00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNext'", NULL);
#endif
  {
   b2Body* tolua_ret = (b2Body*)  self->GetNext();
    tolua_ext_object_to_luaval<b2Body>(tolua_S,(void*)tolua_ret,"b2Body");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNext'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  b2Filter */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Filter_new00
static int tolua_foundation_b2Filter_new00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"b2Filter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   b2Filter* tolua_ret = (b2Filter*)  Mtolua_new((b2Filter)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"b2Filter");
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

/* method: new_local of class  b2Filter */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Filter_new00_local
static int tolua_foundation_b2Filter_new00_local(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"b2Filter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   b2Filter* tolua_ret = (b2Filter*)  Mtolua_new((b2Filter)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"b2Filter");
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

/* get function: categoryBits of class  b2Filter */
#ifndef TOLUA_DISABLE_tolua_get_b2Filter_categoryBits
static int tolua_get_b2Filter_categoryBits(lua_State* tolua_S)
{
  b2Filter* self = (b2Filter*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'categoryBits'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->categoryBits);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: categoryBits of class  b2Filter */
#ifndef TOLUA_DISABLE_tolua_set_b2Filter_categoryBits
static int tolua_set_b2Filter_categoryBits(lua_State* tolua_S)
{
  b2Filter* self = (b2Filter*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'categoryBits'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->categoryBits = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maskBits of class  b2Filter */
#ifndef TOLUA_DISABLE_tolua_get_b2Filter_maskBits
static int tolua_get_b2Filter_maskBits(lua_State* tolua_S)
{
  b2Filter* self = (b2Filter*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maskBits'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maskBits);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maskBits of class  b2Filter */
#ifndef TOLUA_DISABLE_tolua_set_b2Filter_maskBits
static int tolua_set_b2Filter_maskBits(lua_State* tolua_S)
{
  b2Filter* self = (b2Filter*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maskBits'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maskBits = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: groupIndex of class  b2Filter */
#ifndef TOLUA_DISABLE_tolua_get_b2Filter_groupIndex
static int tolua_get_b2Filter_groupIndex(lua_State* tolua_S)
{
  b2Filter* self = (b2Filter*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'groupIndex'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->groupIndex);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: groupIndex of class  b2Filter */
#ifndef TOLUA_DISABLE_tolua_set_b2Filter_groupIndex
static int tolua_set_b2Filter_groupIndex(lua_State* tolua_S)
{
  b2Filter* self = (b2Filter*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'groupIndex'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->groupIndex = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShape of class  b2Fixture */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Fixture_GetShape00
static int tolua_foundation_b2Fixture_GetShape00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Fixture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Fixture* self = (b2Fixture*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShape'", NULL);
#endif
  {
   b2Shape* tolua_ret = (b2Shape*)  self->GetShape();
    tolua_ext_object_to_luaval<b2Shape>(tolua_S,(void*)tolua_ret,"b2Shape");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShape'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSensor of class  b2Fixture */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Fixture_SetSensor00
static int tolua_foundation_b2Fixture_SetSensor00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Fixture",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Fixture* self = (b2Fixture*)  tolua_tousertype(tolua_S,1,0);
  bool sensor = ((bool)  tolua_toboolean(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSensor'", NULL);
#endif
  {
   self->SetSensor(sensor);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSensor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsSensor of class  b2Fixture */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Fixture_IsSensor00
static int tolua_foundation_b2Fixture_IsSensor00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2Fixture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Fixture* self = (const b2Fixture*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsSensor'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsSensor();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsSensor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFilterData of class  b2Fixture */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Fixture_SetFilterData00
static int tolua_foundation_b2Fixture_SetFilterData00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Fixture",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Filter",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Fixture* self = (b2Fixture*)  tolua_tousertype(tolua_S,1,0);
  b2Filter filter = *((b2Filter*)  tolua_tousertype(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFilterData'", NULL);
#endif
  {
   self->SetFilterData(filter);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFilterData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFilterData of class  b2Fixture */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Fixture_GetFilterData00
static int tolua_foundation_b2Fixture_GetFilterData00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2Fixture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Fixture* self = (const b2Fixture*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFilterData'", NULL);
#endif
  {
   b2Filter tolua_ret = (b2Filter)  self->GetFilterData();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Filter)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Filter");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,&tolua_ret,sizeof(b2Filter));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Filter");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFilterData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Refilter of class  b2Fixture */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Fixture_Refilter00
static int tolua_foundation_b2Fixture_Refilter00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Fixture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Fixture* self = (b2Fixture*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Refilter'", NULL);
#endif
  {
   self->Refilter();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Refilter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBody of class  b2Fixture */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Fixture_GetBody00
static int tolua_foundation_b2Fixture_GetBody00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Fixture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Fixture* self = (b2Fixture*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBody'", NULL);
#endif
  {
   b2Body* tolua_ret = (b2Body*)  self->GetBody();
    tolua_ext_object_to_luaval<b2Body>(tolua_S,(void*)tolua_ret,"b2Body");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNext of class  b2Fixture */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Fixture_GetNext00
static int tolua_foundation_b2Fixture_GetNext00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Fixture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Fixture* self = (b2Fixture*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNext'", NULL);
#endif
  {
   b2Fixture* tolua_ret = (b2Fixture*)  self->GetNext();
    tolua_ext_object_to_luaval<b2Fixture>(tolua_S,(void*)tolua_ret,"b2Fixture");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNext'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TestPoint of class  b2Fixture */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Fixture_TestPoint00
static int tolua_foundation_b2Fixture_TestPoint00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2Fixture",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Fixture* self = (const b2Fixture*)  tolua_tousertype(tolua_S,1,0);
  b2Vec2 p = (  tolua_ext_luaval_to_b2vec2(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TestPoint'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->TestPoint(p);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TestPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMassData of class  b2Fixture */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Fixture_GetMassData00
static int tolua_foundation_b2Fixture_GetMassData00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2Fixture",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"b2MassData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Fixture* self = (const b2Fixture*)  tolua_tousertype(tolua_S,1,0);
  b2MassData* massData = ((b2MassData*)  tolua_tousertype(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMassData'", NULL);
#endif
  {
   self->GetMassData(massData);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMassData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDensity of class  b2Fixture */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Fixture_SetDensity00
static int tolua_foundation_b2Fixture_SetDensity00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Fixture",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Fixture* self = (b2Fixture*)  tolua_tousertype(tolua_S,1,0);
  float density = ((float)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDensity'", NULL);
#endif
  {
   self->SetDensity(density);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDensity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDensity of class  b2Fixture */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Fixture_GetDensity00
static int tolua_foundation_b2Fixture_GetDensity00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2Fixture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Fixture* self = (const b2Fixture*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDensity'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetDensity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDensity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFriction of class  b2Fixture */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Fixture_GetFriction00
static int tolua_foundation_b2Fixture_GetFriction00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2Fixture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Fixture* self = (const b2Fixture*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFriction'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetFriction();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFriction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFriction of class  b2Fixture */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Fixture_SetFriction00
static int tolua_foundation_b2Fixture_SetFriction00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Fixture",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Fixture* self = (b2Fixture*)  tolua_tousertype(tolua_S,1,0);
  float friction = ((float)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFriction'", NULL);
#endif
  {
   self->SetFriction(friction);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFriction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRestitution of class  b2Fixture */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Fixture_GetRestitution00
static int tolua_foundation_b2Fixture_GetRestitution00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2Fixture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Fixture* self = (const b2Fixture*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRestitution'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetRestitution();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRestitution'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRestitution of class  b2Fixture */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Fixture_SetRestitution00
static int tolua_foundation_b2Fixture_SetRestitution00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Fixture",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Fixture* self = (b2Fixture*)  tolua_tousertype(tolua_S,1,0);
  float restitution = ((float)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRestitution'", NULL);
#endif
  {
   self->SetRestitution(restitution);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRestitution'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Dump of class  b2Fixture */
#ifndef TOLUA_DISABLE_tolua_foundation_b2Fixture_Dump00
static int tolua_foundation_b2Fixture_Dump00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Fixture",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Fixture* self = (b2Fixture*)  tolua_tousertype(tolua_S,1,0);
  int bodyIndex = ((int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Dump'", NULL);
#endif
  {
   self->Dump(bodyIndex);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Dump'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: changeParticleSystemPositionType */
#ifndef TOLUA_DISABLE_tolua_foundation_changeParticleSystemPositionType00
static int tolua_foundation_changeParticleSystemPositionType00(lua_State* tolua_S)
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

/* method: create of class  Actor */
#ifndef TOLUA_DISABLE_tolua_foundation_Actor_create00
static int tolua_foundation_Actor_create00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Actor",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWorld* world = ((GameWorld*)  tolua_tousertype(tolua_S,2,0));
  {
   Actor* tolua_ret = (Actor*)  Actor::create(world);
    tolua_ext_object_to_luaval<Actor>(tolua_S,(void*)tolua_ret,"Actor");
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

/* method: destroy of class  Actor */
#ifndef TOLUA_DISABLE_tolua_foundation_Actor_destroy00
static int tolua_foundation_Actor_destroy00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Actor* self = (Actor*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'destroy'", NULL);
#endif
  {
   self->destroy();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFilterData of class  Actor */
#ifndef TOLUA_DISABLE_tolua_foundation_Actor_setFilterData00
static int tolua_foundation_Actor_setFilterData00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Actor* self = (Actor*)  tolua_tousertype(tolua_S,1,0);
  int inValue = ((int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFilterData'", NULL);
#endif
  {
   self->setFilterData(inValue);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFilterData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFilterData of class  Actor */
#ifndef TOLUA_DISABLE_tolua_foundation_Actor_getFilterData00
static int tolua_foundation_Actor_getFilterData00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Actor* self = (Actor*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFilterData'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getFilterData();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFilterData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getGameWorld of class  Actor */
#ifndef TOLUA_DISABLE_tolua_foundation_Actor_getGameWorld00
static int tolua_foundation_Actor_getGameWorld00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Actor* self = (Actor*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getGameWorld'", NULL);
#endif
  {
   GameWorld* tolua_ret = (GameWorld*)  self->getGameWorld();
    tolua_ext_object_to_luaval<GameWorld>(tolua_S,(void*)tolua_ret,"GameWorld");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getGameWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEntity of class  Actor */
#ifndef TOLUA_DISABLE_tolua_foundation_Actor_getEntity00
static int tolua_foundation_Actor_getEntity00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Actor* self = (Actor*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEntity'", NULL);
#endif
  {
   anax::Entity* tolua_ret = (anax::Entity*)  self->getEntity();
    tolua_ext_object_to_luaval<anax::Entity>(tolua_S,(void*)tolua_ret,"anax::Entity");
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

/* method: addAnaxComponent of class  Actor */
#ifndef TOLUA_DISABLE_tolua_foundation_Actor_addAnaxComponent00
static int tolua_foundation_Actor_addAnaxComponent00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Actor* self = (Actor*)  tolua_tousertype(tolua_S,1,0);
  const std::string component = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addAnaxComponent'", NULL);
#endif
  {
   anax::Component* tolua_ret = (anax::Component*)  self->addAnaxComponent(component);
    tolua_ext_object_to_luaval<anax::Component>(tolua_S,(void*)tolua_ret,"anax::Component");
   tolua_pushcppstring(tolua_S,(const char*)component);
  }
 }
 return 2;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addAnaxComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnaxComponent of class  Actor */
#ifndef TOLUA_DISABLE_tolua_foundation_Actor_getAnaxComponent00
static int tolua_foundation_Actor_getAnaxComponent00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Actor* self = (Actor*)  tolua_tousertype(tolua_S,1,0);
  const std::string component = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnaxComponent'", NULL);
#endif
  {
   anax::Component* tolua_ret = (anax::Component*)  self->getAnaxComponent(component);
    tolua_ext_object_to_luaval<anax::Component>(tolua_S,(void*)tolua_ret,"anax::Component");
   tolua_pushcppstring(tolua_S,(const char*)component);
  }
 }
 return 2;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnaxComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAnaxComponent of class  Actor */
#ifndef TOLUA_DISABLE_tolua_foundation_Actor_removeAnaxComponent00
static int tolua_foundation_Actor_removeAnaxComponent00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Actor* self = (Actor*)  tolua_tousertype(tolua_S,1,0);
  const std::string component = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAnaxComponent'", NULL);
#endif
  {
   self->removeAnaxComponent(component);
   tolua_pushcppstring(tolua_S,(const char*)component);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAnaxComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hasAnaxComponent of class  Actor */
#ifndef TOLUA_DISABLE_tolua_foundation_Actor_hasAnaxComponent00
static int tolua_foundation_Actor_hasAnaxComponent00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Actor* self = (Actor*)  tolua_tousertype(tolua_S,1,0);
  const std::string component = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hasAnaxComponent'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->hasAnaxComponent(component);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)component);
  }
 }
 return 2;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hasAnaxComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerLuaHandle of class  Actor */
#ifndef TOLUA_DISABLE_tolua_foundation_Actor_registerLuaHandle00
static int tolua_foundation_Actor_registerLuaHandle00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_ext_check_isfunction(tolua_S,3,"LuaFunction",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Actor* self = (Actor*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  LuaFunction handle = (  LuaFunction(tolua_S,3,0));
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

/* method: unregisterLuaHandle of class  Actor */
#ifndef TOLUA_DISABLE_tolua_foundation_Actor_unregisterLuaHandle00
static int tolua_foundation_Actor_unregisterLuaHandle00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Actor* self = (Actor*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterLuaHandle'", NULL);
#endif
  {
   self->unregisterLuaHandle(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterLuaHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearLuaHandle of class  Actor */
#ifndef TOLUA_DISABLE_tolua_foundation_Actor_clearLuaHandle00
static int tolua_foundation_Actor_clearLuaHandle00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Actor* self = (Actor*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearLuaHandle'", NULL);
#endif
  {
   self->clearLuaHandle();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearLuaHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  Character */
#ifndef TOLUA_DISABLE_tolua_foundation_Character_create00
static int tolua_foundation_Character_create00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Character",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWorld* world = ((GameWorld*)  tolua_tousertype(tolua_S,2,0));
  {
   Character* tolua_ret = (Character*)  Character::create(world);
    tolua_ext_object_to_luaval<Character>(tolua_S,(void*)tolua_ret,"Character");
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

/* method: loadArmature of class  Character */
#ifndef TOLUA_DISABLE_tolua_foundation_Character_loadArmature00
static int tolua_foundation_Character_loadArmature00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Character",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Character* self = (Character*)  tolua_tousertype(tolua_S,1,0);
  std::string filepath = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadArmature'", NULL);
#endif
  {
   self->loadArmature(filepath);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadArmature'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: enableBox2DComponent of class  Character */
#ifndef TOLUA_DISABLE_tolua_foundation_Character_enableBox2DComponent00
static int tolua_foundation_Character_enableBox2DComponent00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Character",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"Vec2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_ext_check_is_table(tolua_S,3,"Size",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Character* self = (Character*)  tolua_tousertype(tolua_S,1,0);
  Vec2 bodyPos = (  tolua_ext_luaval_to_vec2_value(tolua_S,2,0));
  Size characterSize = (  tolua_ext_luaval_to_size_value(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'enableBox2DComponent'", NULL);
#endif
  {
   self->enableBox2DComponent(bodyPos,characterSize);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'enableBox2DComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPositionAndSyncPhysicsTransform of class  Character */
#ifndef TOLUA_DISABLE_tolua_foundation_Character_setPositionAndSyncPhysicsTransform00
static int tolua_foundation_Character_setPositionAndSyncPhysicsTransform00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Character",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Character* self = (Character*)  tolua_tousertype(tolua_S,1,0);
  Vec2 inPos = (  tolua_ext_luaval_to_vec2_value(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPositionAndSyncPhysicsTransform'", NULL);
#endif
  {
   self->setPositionAndSyncPhysicsTransform(inPos);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPositionAndSyncPhysicsTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFSM of class  Character */
#ifndef TOLUA_DISABLE_tolua_foundation_Character_getFSM00
static int tolua_foundation_Character_getFSM00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Character",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Character* self = (Character*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFSM'", NULL);
#endif
  {
   QFSM* tolua_ret = (QFSM*)  self->getFSM();
    tolua_ext_object_to_luaval<QFSM>(tolua_S,(void*)tolua_ret,"QFSM");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFSM'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getArmature of class  Character */
#ifndef TOLUA_DISABLE_tolua_foundation_Character_getArmature00
static int tolua_foundation_Character_getArmature00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Character",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Character* self = (Character*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getArmature'", NULL);
#endif
  {
   Armature* tolua_ret = (Armature*)  self->getArmature();
    tolua_ext_object_to_luaval<Armature>(tolua_S,(void*)tolua_ret,"ccs.Armature");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getArmature'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCharacterWidth of class  Character */
#ifndef TOLUA_DISABLE_tolua_foundation_Character_getCharacterWidth00
static int tolua_foundation_Character_getCharacterWidth00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Character",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Character* self = (Character*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCharacterWidth'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getCharacterWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCharacterWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCharacterHeight of class  Character */
#ifndef TOLUA_DISABLE_tolua_foundation_Character_getCharacterHeight00
static int tolua_foundation_Character_getCharacterHeight00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Character",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Character* self = (Character*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCharacterHeight'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getCharacterHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCharacterHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  GameWorld */
#ifndef TOLUA_DISABLE_tolua_foundation_GameWorld_create00
static int tolua_foundation_GameWorld_create00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameWorld* tolua_ret = (GameWorld*)  GameWorld::create();
    tolua_ext_object_to_luaval<GameWorld>(tolua_S,(void*)tolua_ret,"GameWorld");
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

/* method: initWorld of class  GameWorld */
#ifndef TOLUA_DISABLE_tolua_foundation_GameWorld_initWorld00
static int tolua_foundation_GameWorld_initWorld00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameMap",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWorld* self = (GameWorld*)  tolua_tousertype(tolua_S,1,0);
  GameMap* gameMap = ((GameMap*)  tolua_tousertype(tolua_S,2,0));
  float left_offset = ((float)  tolua_tonumber(tolua_S,3,0));
  float right_offset = ((float)  tolua_tonumber(tolua_S,4,0));
  float top_offset = ((float)  tolua_tonumber(tolua_S,5,0));
  float bottom_offset = ((float)  tolua_tonumber(tolua_S,6,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWorld'", NULL);
#endif
  {
   self->initWorld(gameMap,left_offset,right_offset,top_offset,bottom_offset);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destroy of class  GameWorld */
#ifndef TOLUA_DISABLE_tolua_foundation_GameWorld_destroy00
static int tolua_foundation_GameWorld_destroy00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Actor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWorld* self = (GameWorld*)  tolua_tousertype(tolua_S,1,0);
  Actor* actor = ((Actor*)  tolua_tousertype(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'destroy'", NULL);
#endif
  {
   self->destroy(actor);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDebugEnable of class  GameWorld */
#ifndef TOLUA_DISABLE_tolua_foundation_GameWorld_setDebugEnable00
static int tolua_foundation_GameWorld_setDebugEnable00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWorld",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWorld* self = (GameWorld*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDebugEnable'", NULL);
#endif
  {
   self->setDebugEnable(enable);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDebugEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isEnableDebug of class  GameWorld */
#ifndef TOLUA_DISABLE_tolua_foundation_GameWorld_isEnableDebug00
static int tolua_foundation_GameWorld_isEnableDebug00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWorld* self = (GameWorld*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isEnableDebug'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isEnableDebug();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEnableDebug'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setGameMap of class  GameWorld */
#ifndef TOLUA_DISABLE_tolua_foundation_GameWorld_setGameMap00
static int tolua_foundation_GameWorld_setGameMap00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameMap",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWorld* self = (GameWorld*)  tolua_tousertype(tolua_S,1,0);
  GameMap* gameMap = ((GameMap*)  tolua_tousertype(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setGameMap'", NULL);
#endif
  {
   self->setGameMap(gameMap);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setGameMap'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getValidWorldX of class  GameWorld */
#ifndef TOLUA_DISABLE_tolua_foundation_GameWorld_getValidWorldX00
static int tolua_foundation_GameWorld_getValidWorldX00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWorld* self = (GameWorld*)  tolua_tousertype(tolua_S,1,0);
  int inValue = ((int)  tolua_tonumber(tolua_S,2,0));
  int actorRadius = ((int)  tolua_tonumber(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getValidWorldX'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getValidWorldX(inValue,actorRadius);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getValidWorldX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getValidWorldY of class  GameWorld */
#ifndef TOLUA_DISABLE_tolua_foundation_GameWorld_getValidWorldY00
static int tolua_foundation_GameWorld_getValidWorldY00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWorld* self = (GameWorld*)  tolua_tousertype(tolua_S,1,0);
  int inValue = ((int)  tolua_tonumber(tolua_S,2,0));
  int actorRadius = ((int)  tolua_tonumber(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getValidWorldY'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getValidWorldY(inValue,actorRadius);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getValidWorldY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getGameMap of class  GameWorld */
#ifndef TOLUA_DISABLE_tolua_foundation_GameWorld_getGameMap00
static int tolua_foundation_GameWorld_getGameMap00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWorld* self = (GameWorld*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getGameMap'", NULL);
#endif
  {
   GameMap* tolua_ret = (GameMap*)  self->getGameMap();
    tolua_ext_object_to_luaval<GameMap>(tolua_S,(void*)tolua_ret,"GameMap");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getGameMap'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWorld of class  GameWorld */
#ifndef TOLUA_DISABLE_tolua_foundation_GameWorld_getWorld00
static int tolua_foundation_GameWorld_getWorld00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWorld* self = (GameWorld*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWorld'", NULL);
#endif
  {
   anax::World* tolua_ret = (anax::World*)  self->getWorld();
    tolua_ext_object_to_luaval<anax::World>(tolua_S,(void*)tolua_ret,"anax::World");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAdmin of class  GameWorld */
#ifndef TOLUA_DISABLE_tolua_foundation_GameWorld_getAdmin00
static int tolua_foundation_GameWorld_getAdmin00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWorld* self = (GameWorld*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAdmin'", NULL);
#endif
  {
   anax::Entity* tolua_ret = (anax::Entity*)  self->getAdmin();
    tolua_ext_object_to_luaval<anax::Entity>(tolua_S,(void*)tolua_ret,"anax::Entity");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAdmin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNode of class  GameWorld */
#ifndef TOLUA_DISABLE_tolua_foundation_GameWorld_getNode00
static int tolua_foundation_GameWorld_getNode00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWorld* self = (GameWorld*)  tolua_tousertype(tolua_S,1,0);
  int nodeTag = ((int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNode'", NULL);
#endif
  {
   Node* tolua_ret = (Node*)  self->getNode(nodeTag);
    tolua_ext_object_to_luaval<Node>(tolua_S,(void*)tolua_ret,"cc.Node");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerLuaHandle of class  GameWorld */
#ifndef TOLUA_DISABLE_tolua_foundation_GameWorld_registerLuaHandle00
static int tolua_foundation_GameWorld_registerLuaHandle00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWorld",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_ext_check_isfunction(tolua_S,3,"LuaFunction",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWorld* self = (GameWorld*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  LuaFunction handle = (  LuaFunction(tolua_S,3,0));
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

/* method: unregisterLuaHandle of class  GameWorld */
#ifndef TOLUA_DISABLE_tolua_foundation_GameWorld_unregisterLuaHandle00
static int tolua_foundation_GameWorld_unregisterLuaHandle00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWorld",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWorld* self = (GameWorld*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterLuaHandle'", NULL);
#endif
  {
   self->unregisterLuaHandle(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterLuaHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearLuaHandle of class  GameWorld */
#ifndef TOLUA_DISABLE_tolua_foundation_GameWorld_clearLuaHandle00
static int tolua_foundation_GameWorld_clearLuaHandle00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameWorld* self = (GameWorld*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearLuaHandle'", NULL);
#endif
  {
   self->clearLuaHandle();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearLuaHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_foundation_open (lua_State* tolua_S)
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
   tolua_function(tolua_S,"new",tolua_foundation_QFSMState_new00);
   tolua_function(tolua_S,"new_local",tolua_foundation_QFSMState_new00_local);
   tolua_function(tolua_S,".call",tolua_foundation_QFSMState_new00_local);
   tolua_function(tolua_S,"delete",tolua_foundation_QFSMState_delete00);
   tolua_function(tolua_S,"getStateName",tolua_foundation_QFSMState_getStateName00);
   tolua_function(tolua_S,"getFSM",tolua_foundation_QFSMState_getFSM00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"QFSM","QFSM","",tolua_collect_QFSM);
  #else
  tolua_cclass(tolua_S,"QFSM","QFSM","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"QFSM");
   tolua_function(tolua_S,"new",tolua_foundation_QFSM_new00);
   tolua_function(tolua_S,"new_local",tolua_foundation_QFSM_new00_local);
   tolua_function(tolua_S,".call",tolua_foundation_QFSM_new00_local);
   tolua_function(tolua_S,"delete",tolua_foundation_QFSM_delete00);
   tolua_function(tolua_S,"addState",tolua_foundation_QFSM_addState00);
   tolua_function(tolua_S,"addTranslation",tolua_foundation_QFSM_addTranslation00);
   tolua_function(tolua_S,"removeTranslation",tolua_foundation_QFSM_removeTranslation00);
   tolua_function(tolua_S,"start",tolua_foundation_QFSM_start00);
   tolua_function(tolua_S,"handle",tolua_foundation_QFSM_handle00);
   tolua_function(tolua_S,"clear",tolua_foundation_QFSM_clear00);
   tolua_function(tolua_S,"forceSwitch",tolua_foundation_QFSM_forceSwitch00);
   tolua_function(tolua_S,"getPreState",tolua_foundation_QFSM_getPreState00);
   tolua_function(tolua_S,"getPreStateName",tolua_foundation_QFSM_getPreStateName00);
   tolua_function(tolua_S,"getNextState",tolua_foundation_QFSM_getNextState00);
   tolua_function(tolua_S,"getCurState",tolua_foundation_QFSM_getCurState00);
   tolua_function(tolua_S,"getCurStateName",tolua_foundation_QFSM_getCurStateName00);
   tolua_function(tolua_S,"getCurEventName",tolua_foundation_QFSM_getCurEventName00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GameMap","GameMap","cc.Node",NULL);
  tolua_beginmodule(tolua_S,"GameMap");
   tolua_function(tolua_S,"create",tolua_foundation_GameMap_create00);
   tolua_function(tolua_S,"loadMapFile",tolua_foundation_GameMap_loadMapFile00);
   tolua_function(tolua_S,"setViewPos",tolua_foundation_GameMap_setViewPos00);
   tolua_function(tolua_S,"setViewSize",tolua_foundation_GameMap_setViewSize00);
   tolua_function(tolua_S,"getActorNode",tolua_foundation_GameMap_getActorNode00);
   tolua_function(tolua_S,"lockMapY",tolua_foundation_GameMap_lockMapY00);
   tolua_function(tolua_S,"unlockMapY",tolua_foundation_GameMap_unlockMapY00);
   tolua_function(tolua_S,"getMapWidth",tolua_foundation_GameMap_getMapWidth00);
   tolua_function(tolua_S,"getMapHeight",tolua_foundation_GameMap_getMapHeight00);
   tolua_function(tolua_S,"getRootNode",tolua_foundation_GameMap_getRootNode00);
   tolua_function(tolua_S,"getMinPosY",tolua_foundation_GameMap_getMinPosY00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"b2MassData","b2MassData","",tolua_collect_b2MassData);
  #else
  tolua_cclass(tolua_S,"b2MassData","b2MassData","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"b2MassData");
   tolua_function(tolua_S,"new",tolua_foundation_b2MassData_new00);
   tolua_function(tolua_S,"new_local",tolua_foundation_b2MassData_new00_local);
   tolua_function(tolua_S,".call",tolua_foundation_b2MassData_new00_local);
   tolua_function(tolua_S,"delete",tolua_foundation_b2MassData_delete00);
   tolua_variable(tolua_S,"mass",tolua_get_b2MassData_mass,tolua_set_b2MassData_mass);
   tolua_variable(tolua_S,"center",tolua_get_b2MassData_center,tolua_set_b2MassData_center);
   tolua_variable(tolua_S,"I",tolua_get_b2MassData_I,tolua_set_b2MassData_I);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"b2Body","b2Body","",NULL);
  tolua_beginmodule(tolua_S,"b2Body");
   tolua_function(tolua_S,"SetTransform",tolua_foundation_b2Body_SetTransform00);
   tolua_function(tolua_S,"GetPosition",tolua_foundation_b2Body_GetPosition00);
   tolua_function(tolua_S,"GetAngle",tolua_foundation_b2Body_GetAngle00);
   tolua_function(tolua_S,"GetWorldCenter",tolua_foundation_b2Body_GetWorldCenter00);
   tolua_function(tolua_S,"GetLocalCenter",tolua_foundation_b2Body_GetLocalCenter00);
   tolua_function(tolua_S,"SetLinearVelocity",tolua_foundation_b2Body_SetLinearVelocity00);
   tolua_function(tolua_S,"GetLinearVelocity",tolua_foundation_b2Body_GetLinearVelocity00);
   tolua_function(tolua_S,"SetAngularVelocity",tolua_foundation_b2Body_SetAngularVelocity00);
   tolua_function(tolua_S,"GetAngularVelocity",tolua_foundation_b2Body_GetAngularVelocity00);
   tolua_function(tolua_S,"ApplyForce",tolua_foundation_b2Body_ApplyForce00);
   tolua_function(tolua_S,"ApplyForceToCenter",tolua_foundation_b2Body_ApplyForceToCenter00);
   tolua_function(tolua_S,"ApplyTorque",tolua_foundation_b2Body_ApplyTorque00);
   tolua_function(tolua_S,"ApplyLinearImpulse",tolua_foundation_b2Body_ApplyLinearImpulse00);
   tolua_function(tolua_S,"ApplyAngularImpulse",tolua_foundation_b2Body_ApplyAngularImpulse00);
   tolua_function(tolua_S,"GetMass",tolua_foundation_b2Body_GetMass00);
   tolua_function(tolua_S,"GetInertia",tolua_foundation_b2Body_GetInertia00);
   tolua_function(tolua_S,"GetMassData",tolua_foundation_b2Body_GetMassData00);
   tolua_function(tolua_S,"SetMassData",tolua_foundation_b2Body_SetMassData00);
   tolua_function(tolua_S,"ResetMassData",tolua_foundation_b2Body_ResetMassData00);
   tolua_function(tolua_S,"GetWorldPoint",tolua_foundation_b2Body_GetWorldPoint00);
   tolua_function(tolua_S,"GetWorldVector",tolua_foundation_b2Body_GetWorldVector00);
   tolua_function(tolua_S,"GetLocalPoint",tolua_foundation_b2Body_GetLocalPoint00);
   tolua_function(tolua_S,"GetLocalVector",tolua_foundation_b2Body_GetLocalVector00);
   tolua_function(tolua_S,"GetLinearVelocityFromWorldPoint",tolua_foundation_b2Body_GetLinearVelocityFromWorldPoint00);
   tolua_function(tolua_S,"GetLinearVelocityFromLocalPoint",tolua_foundation_b2Body_GetLinearVelocityFromLocalPoint00);
   tolua_function(tolua_S,"GetLinearDamping",tolua_foundation_b2Body_GetLinearDamping00);
   tolua_function(tolua_S,"SetLinearDamping",tolua_foundation_b2Body_SetLinearDamping00);
   tolua_function(tolua_S,"GetAngularDamping",tolua_foundation_b2Body_GetAngularDamping00);
   tolua_function(tolua_S,"SetAngularDamping",tolua_foundation_b2Body_SetAngularDamping00);
   tolua_function(tolua_S,"GetGravityScale",tolua_foundation_b2Body_GetGravityScale00);
   tolua_function(tolua_S,"SetGravityScale",tolua_foundation_b2Body_SetGravityScale00);
   tolua_function(tolua_S,"SetType",tolua_foundation_b2Body_SetType00);
   tolua_function(tolua_S,"GetType",tolua_foundation_b2Body_GetType00);
   tolua_function(tolua_S,"SetBullet",tolua_foundation_b2Body_SetBullet00);
   tolua_function(tolua_S,"IsBullet",tolua_foundation_b2Body_IsBullet00);
   tolua_function(tolua_S,"SetSleepingAllowed",tolua_foundation_b2Body_SetSleepingAllowed00);
   tolua_function(tolua_S,"IsSleepingAllowed",tolua_foundation_b2Body_IsSleepingAllowed00);
   tolua_function(tolua_S,"SetAwake",tolua_foundation_b2Body_SetAwake00);
   tolua_function(tolua_S,"IsAwake",tolua_foundation_b2Body_IsAwake00);
   tolua_function(tolua_S,"SetActive",tolua_foundation_b2Body_SetActive00);
   tolua_function(tolua_S,"IsActive",tolua_foundation_b2Body_IsActive00);
   tolua_function(tolua_S,"SetFixedRotation",tolua_foundation_b2Body_SetFixedRotation00);
   tolua_function(tolua_S,"IsFixedRotation",tolua_foundation_b2Body_IsFixedRotation00);
   tolua_function(tolua_S,"GetFixtureList",tolua_foundation_b2Body_GetFixtureList00);
   tolua_function(tolua_S,"GetNext",tolua_foundation_b2Body_GetNext00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"b2Filter","b2Filter","",tolua_collect_b2Filter);
  #else
  tolua_cclass(tolua_S,"b2Filter","b2Filter","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"b2Filter");
   tolua_function(tolua_S,"new",tolua_foundation_b2Filter_new00);
   tolua_function(tolua_S,"new_local",tolua_foundation_b2Filter_new00_local);
   tolua_function(tolua_S,".call",tolua_foundation_b2Filter_new00_local);
   tolua_variable(tolua_S,"categoryBits",tolua_get_b2Filter_categoryBits,tolua_set_b2Filter_categoryBits);
   tolua_variable(tolua_S,"maskBits",tolua_get_b2Filter_maskBits,tolua_set_b2Filter_maskBits);
   tolua_variable(tolua_S,"groupIndex",tolua_get_b2Filter_groupIndex,tolua_set_b2Filter_groupIndex);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"b2Fixture","b2Fixture","",NULL);
  tolua_beginmodule(tolua_S,"b2Fixture");
   tolua_function(tolua_S,"GetShape",tolua_foundation_b2Fixture_GetShape00);
   tolua_function(tolua_S,"SetSensor",tolua_foundation_b2Fixture_SetSensor00);
   tolua_function(tolua_S,"IsSensor",tolua_foundation_b2Fixture_IsSensor00);
   tolua_function(tolua_S,"SetFilterData",tolua_foundation_b2Fixture_SetFilterData00);
   tolua_function(tolua_S,"GetFilterData",tolua_foundation_b2Fixture_GetFilterData00);
   tolua_function(tolua_S,"Refilter",tolua_foundation_b2Fixture_Refilter00);
   tolua_function(tolua_S,"GetBody",tolua_foundation_b2Fixture_GetBody00);
   tolua_function(tolua_S,"GetNext",tolua_foundation_b2Fixture_GetNext00);
   tolua_function(tolua_S,"TestPoint",tolua_foundation_b2Fixture_TestPoint00);
   tolua_function(tolua_S,"GetMassData",tolua_foundation_b2Fixture_GetMassData00);
   tolua_function(tolua_S,"SetDensity",tolua_foundation_b2Fixture_SetDensity00);
   tolua_function(tolua_S,"GetDensity",tolua_foundation_b2Fixture_GetDensity00);
   tolua_function(tolua_S,"GetFriction",tolua_foundation_b2Fixture_GetFriction00);
   tolua_function(tolua_S,"SetFriction",tolua_foundation_b2Fixture_SetFriction00);
   tolua_function(tolua_S,"GetRestitution",tolua_foundation_b2Fixture_GetRestitution00);
   tolua_function(tolua_S,"SetRestitution",tolua_foundation_b2Fixture_SetRestitution00);
   tolua_function(tolua_S,"Dump",tolua_foundation_b2Fixture_Dump00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"changeParticleSystemPositionType",tolua_foundation_changeParticleSystemPositionType00);
  tolua_cclass(tolua_S,"Actor","Actor","cc.Node",NULL);
  tolua_beginmodule(tolua_S,"Actor");
   tolua_function(tolua_S,"create",tolua_foundation_Actor_create00);
   tolua_function(tolua_S,"destroy",tolua_foundation_Actor_destroy00);
   tolua_function(tolua_S,"setFilterData",tolua_foundation_Actor_setFilterData00);
   tolua_function(tolua_S,"getFilterData",tolua_foundation_Actor_getFilterData00);
   tolua_function(tolua_S,"getGameWorld",tolua_foundation_Actor_getGameWorld00);
   tolua_function(tolua_S,"getEntity",tolua_foundation_Actor_getEntity00);
   tolua_function(tolua_S,"addAnaxComponent",tolua_foundation_Actor_addAnaxComponent00);
   tolua_function(tolua_S,"getAnaxComponent",tolua_foundation_Actor_getAnaxComponent00);
   tolua_function(tolua_S,"removeAnaxComponent",tolua_foundation_Actor_removeAnaxComponent00);
   tolua_function(tolua_S,"hasAnaxComponent",tolua_foundation_Actor_hasAnaxComponent00);
   tolua_function(tolua_S,"registerLuaHandle",tolua_foundation_Actor_registerLuaHandle00);
   tolua_function(tolua_S,"unregisterLuaHandle",tolua_foundation_Actor_unregisterLuaHandle00);
   tolua_function(tolua_S,"clearLuaHandle",tolua_foundation_Actor_clearLuaHandle00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Character","Character","Actor",NULL);
  tolua_beginmodule(tolua_S,"Character");
   tolua_function(tolua_S,"create",tolua_foundation_Character_create00);
   tolua_function(tolua_S,"loadArmature",tolua_foundation_Character_loadArmature00);
   tolua_function(tolua_S,"enableBox2DComponent",tolua_foundation_Character_enableBox2DComponent00);
   tolua_function(tolua_S,"setPositionAndSyncPhysicsTransform",tolua_foundation_Character_setPositionAndSyncPhysicsTransform00);
   tolua_function(tolua_S,"getFSM",tolua_foundation_Character_getFSM00);
   tolua_function(tolua_S,"getArmature",tolua_foundation_Character_getArmature00);
   tolua_function(tolua_S,"getCharacterWidth",tolua_foundation_Character_getCharacterWidth00);
   tolua_function(tolua_S,"getCharacterHeight",tolua_foundation_Character_getCharacterHeight00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GameWorld","GameWorld","cc.Node",NULL);
  tolua_beginmodule(tolua_S,"GameWorld");
   tolua_function(tolua_S,"create",tolua_foundation_GameWorld_create00);
   tolua_function(tolua_S,"initWorld",tolua_foundation_GameWorld_initWorld00);
   tolua_function(tolua_S,"destroy",tolua_foundation_GameWorld_destroy00);
   tolua_function(tolua_S,"setDebugEnable",tolua_foundation_GameWorld_setDebugEnable00);
   tolua_function(tolua_S,"isEnableDebug",tolua_foundation_GameWorld_isEnableDebug00);
   tolua_function(tolua_S,"setGameMap",tolua_foundation_GameWorld_setGameMap00);
   tolua_function(tolua_S,"getValidWorldX",tolua_foundation_GameWorld_getValidWorldX00);
   tolua_function(tolua_S,"getValidWorldY",tolua_foundation_GameWorld_getValidWorldY00);
   tolua_function(tolua_S,"getGameMap",tolua_foundation_GameWorld_getGameMap00);
   tolua_function(tolua_S,"getWorld",tolua_foundation_GameWorld_getWorld00);
   tolua_function(tolua_S,"getAdmin",tolua_foundation_GameWorld_getAdmin00);
   tolua_function(tolua_S,"getNode",tolua_foundation_GameWorld_getNode00);
   tolua_function(tolua_S,"registerLuaHandle",tolua_foundation_GameWorld_registerLuaHandle00);
   tolua_function(tolua_S,"unregisterLuaHandle",tolua_foundation_GameWorld_unregisterLuaHandle00);
   tolua_function(tolua_S,"clearLuaHandle",tolua_foundation_GameWorld_clearLuaHandle00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"BOX2D_PIXEL_TO_METER",BOX2D_PIXEL_TO_METER);
  tolua_module(tolua_S,"BOX2D_FILTER_MASK",0);
  tolua_beginmodule(tolua_S,"BOX2D_FILTER_MASK");
   tolua_constant(tolua_S,"B2DM_GROUND",B2DM_GROUND);
   tolua_constant(tolua_S,"B2DM_SIDE_WALL",B2DM_SIDE_WALL);
   tolua_constant(tolua_S,"B2DM_PLAYER",B2DM_PLAYER);
   tolua_constant(tolua_S,"B2DM_MONSTER",B2DM_MONSTER);
   tolua_constant(tolua_S,"B2DM_SKILL",B2DM_SKILL);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"GAMEWORLD_NODE_MAP",GAMEWORLD_NODE_MAP);
  tolua_constant(tolua_S,"GAMEWORLD_NODE_UI",GAMEWORLD_NODE_UI);
  tolua_constant(tolua_S,"GAMEWORLD_NODE_MAX",GAMEWORLD_NODE_MAX);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_foundation (lua_State* tolua_S) {
 return tolua_foundation_open(tolua_S);
};
#endif

