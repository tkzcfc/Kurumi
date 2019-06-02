/*
** Lua binding: ecs
** Generated automatically by tolua++-1.0.92 on 06/02/19 20:53:08.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_ecs_open (lua_State* tolua_S);

#include "lua_function/tolua_ext.h"
#include "ecs/AnaxHelper.h"
#include "anax/anax.hpp"
#include "ecs/system/ArmatureCollisionSystem.h"
#include "ecs/system/Box2DSystem.h"
#include "ecs/system/MapFollowSystem.h"
#include "ecs/system/UpdateSystem.h"
#include "ecs/system/FilterSystem.h"
#include "ecs/components/ArmatureComponent.h"
#include "ecs/components/Box2DComponent.h"
#include "ecs/components/MapFollowComponent.h"
#include "ecs/components/OrientationComponent.h"
#include "ecs/components/UpdateComponent.h"
#include "ecs/components/FilterComponent.h"
#include "foundation/Actor.h"
using namespace cocos2d;
using namespace cocostudio;

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_ArmatureCollisionSystem (lua_State* tolua_S)
{
 ArmatureCollisionSystem* self = (ArmatureCollisionSystem*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_FilterSystem (lua_State* tolua_S)
{
 FilterSystem* self = (FilterSystem*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_MapFollowSystem (lua_State* tolua_S)
{
 MapFollowSystem* self = (MapFollowSystem*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_FilterComponent (lua_State* tolua_S)
{
 FilterComponent* self = (FilterComponent*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UpdateComponent (lua_State* tolua_S)
{
 UpdateComponent* self = (UpdateComponent*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_std__vector_Actor__ (lua_State* tolua_S)
{
 std::vector<Actor*>* self = (std::vector<Actor*>*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UpdateSystem (lua_State* tolua_S)
{
 UpdateSystem* self = (UpdateSystem*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_Box2DSystem (lua_State* tolua_S)
{
 Box2DSystem* self = (Box2DSystem*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"ArmatureCollisionSystem");
 tolua_usertype(tolua_S,"Box2DSystem");
 tolua_usertype(tolua_S,"Vec2");
 tolua_usertype(tolua_S,"Box2DComponent");
 tolua_usertype(tolua_S,"ccs.Armature");
 tolua_usertype(tolua_S,"DrawNode");
 tolua_usertype(tolua_S,"FilterSystem");
 tolua_usertype(tolua_S,"std::vector<Actor*>");
 tolua_usertype(tolua_S,"FilterComponent");
 tolua_usertype(tolua_S,"ArmatureComponent");
 tolua_usertype(tolua_S,"UpdateComponent");
 tolua_usertype(tolua_S,"anax::Component");
 tolua_usertype(tolua_S,"Size");
 tolua_usertype(tolua_S,"ArmatureCollisionComponent");
 tolua_usertype(tolua_S,"Actor");
 tolua_usertype(tolua_S,"MapFollowComponent");
 tolua_usertype(tolua_S,"LuaFunction");
 tolua_usertype(tolua_S,"anax::System");
 tolua_usertype(tolua_S,"CollisionFilterComponent");
 tolua_usertype(tolua_S,"anax::World");
 tolua_usertype(tolua_S,"OrientationComponent");
 tolua_usertype(tolua_S,"cc.Node");
 tolua_usertype(tolua_S,"MapFollowSystem");
 tolua_usertype(tolua_S,"UpdateSystem");
 tolua_usertype(tolua_S,"anax::Entity");
 tolua_usertype(tolua_S,"GameMap");
 tolua_usertype(tolua_S,"b2Body");
 tolua_usertype(tolua_S,"AnaxHelper");
 tolua_usertype(tolua_S,"b2World");
}

/* method: addComponent of class  AnaxHelper */
#ifndef TOLUA_DISABLE_tolua_ecs_AnaxHelper_addComponent00
static int tolua_ecs_AnaxHelper_addComponent00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnaxHelper",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"anax::Entity",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anax::Entity* entity = ((anax::Entity*)  tolua_tousertype(tolua_S,2,0));
  const std::string component = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  {
   anax::Component* tolua_ret = (anax::Component*)  AnaxHelper::addComponent(entity,component);
    tolua_ext_object_to_luaval<anax::Component>(tolua_S,(void*)tolua_ret,"anax::Component");
   tolua_pushcppstring(tolua_S,(const char*)component);
  }
 }
 return 2;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getComponent of class  AnaxHelper */
#ifndef TOLUA_DISABLE_tolua_ecs_AnaxHelper_getComponent00
static int tolua_ecs_AnaxHelper_getComponent00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnaxHelper",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"anax::Entity",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anax::Entity* entity = ((anax::Entity*)  tolua_tousertype(tolua_S,2,0));
  const std::string component = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  {
   anax::Component* tolua_ret = (anax::Component*)  AnaxHelper::getComponent(entity,component);
    tolua_ext_object_to_luaval<anax::Component>(tolua_S,(void*)tolua_ret,"anax::Component");
   tolua_pushcppstring(tolua_S,(const char*)component);
  }
 }
 return 2;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeComponent of class  AnaxHelper */
#ifndef TOLUA_DISABLE_tolua_ecs_AnaxHelper_removeComponent00
static int tolua_ecs_AnaxHelper_removeComponent00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnaxHelper",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"anax::Entity",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anax::Entity* entity = ((anax::Entity*)  tolua_tousertype(tolua_S,2,0));
  const std::string component = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  {
   AnaxHelper::removeComponent(entity,component);
   tolua_pushcppstring(tolua_S,(const char*)component);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hasComponent of class  AnaxHelper */
#ifndef TOLUA_DISABLE_tolua_ecs_AnaxHelper_hasComponent00
static int tolua_ecs_AnaxHelper_hasComponent00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnaxHelper",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"anax::Entity",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anax::Entity* entity = ((anax::Entity*)  tolua_tousertype(tolua_S,2,0));
  const std::string component = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  AnaxHelper::hasComponent(entity,component);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)component);
  }
 }
 return 2;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hasComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getComponentTypeID of class  AnaxHelper */
#ifndef TOLUA_DISABLE_tolua_ecs_AnaxHelper_getComponentTypeID00
static int tolua_ecs_AnaxHelper_getComponentTypeID00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnaxHelper",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string component = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   unsigned int tolua_ret = (unsigned int)  AnaxHelper::getComponentTypeID(component);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)component);
  }
 }
 return 2;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getComponentTypeID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addSystem of class  AnaxHelper */
#ifndef TOLUA_DISABLE_tolua_ecs_AnaxHelper_addSystem00
static int tolua_ecs_AnaxHelper_addSystem00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnaxHelper",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"anax::World",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anax::World* world = ((anax::World*)  tolua_tousertype(tolua_S,2,0));
  const std::string systemName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  void* sys = ((void*)  tolua_touserdata(tolua_S,4,0));
  {
   AnaxHelper::addSystem(world,systemName,sys);
   tolua_pushcppstring(tolua_S,(const char*)systemName);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addSystem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeSystem of class  AnaxHelper */
#ifndef TOLUA_DISABLE_tolua_ecs_AnaxHelper_removeSystem00
static int tolua_ecs_AnaxHelper_removeSystem00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnaxHelper",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"anax::World",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anax::World* world = ((anax::World*)  tolua_tousertype(tolua_S,2,0));
  const std::string systemName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  {
   AnaxHelper::removeSystem(world,systemName);
   tolua_pushcppstring(tolua_S,(const char*)systemName);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeSystem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: doesSystemExist of class  AnaxHelper */
#ifndef TOLUA_DISABLE_tolua_ecs_AnaxHelper_doesSystemExist00
static int tolua_ecs_AnaxHelper_doesSystemExist00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnaxHelper",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"anax::World",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anax::World* world = ((anax::World*)  tolua_tousertype(tolua_S,2,0));
  const std::string systemName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  AnaxHelper::doesSystemExist(world,systemName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)systemName);
  }
 }
 return 2;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'doesSystemExist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSystemWorld of class  AnaxHelper */
#ifndef TOLUA_DISABLE_tolua_ecs_AnaxHelper_getSystemWorld00
static int tolua_ecs_AnaxHelper_getSystemWorld00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnaxHelper",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string systemName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  void* sys = ((void*)  tolua_touserdata(tolua_S,3,0));
  {
   anax::World* tolua_ret = (anax::World*)  AnaxHelper::getSystemWorld(systemName,sys);
    tolua_ext_object_to_luaval<anax::World>(tolua_S,(void*)tolua_ret,"anax::World");
   tolua_pushcppstring(tolua_S,(const char*)systemName);
  }
 }
 return 2;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSystemWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSystemTypeID of class  AnaxHelper */
#ifndef TOLUA_DISABLE_tolua_ecs_AnaxHelper_getSystemTypeID00
static int tolua_ecs_AnaxHelper_getSystemTypeID00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnaxHelper",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string systemName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   unsigned int tolua_ret = (unsigned int)  AnaxHelper::getSystemTypeID(systemName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)systemName);
  }
 }
 return 2;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSystemTypeID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllSystems of class  anax::World */
#ifndef TOLUA_DISABLE_tolua_ecs_anax_World_removeAllSystems00
static int tolua_ecs_anax_World_removeAllSystems00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anax::World",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anax::World* self = (anax::World*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllSystems'", NULL);
#endif
  {
   self->removeAllSystems();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllSystems'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: refresh of class  anax::World */
#ifndef TOLUA_DISABLE_tolua_ecs_anax_World_refresh00
static int tolua_ecs_anax_World_refresh00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anax::World",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anax::World* self = (anax::World*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'refresh'", NULL);
#endif
  {
   self->refresh();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'refresh'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  anax::World */
#ifndef TOLUA_DISABLE_tolua_ecs_anax_World_clear00
static int tolua_ecs_anax_World_clear00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anax::World",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anax::World* self = (anax::World*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getEntityCount of class  anax::World */
#ifndef TOLUA_DISABLE_tolua_ecs_anax_World_getEntityCount00
static int tolua_ecs_anax_World_getEntityCount00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anax::World",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anax::World* self = (anax::World*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEntityCount'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getEntityCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEntityCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSystemByID of class  anax::World */
#ifndef TOLUA_DISABLE_tolua_ecs_anax_World_getSystemByID00
static int tolua_ecs_anax_World_getSystemByID00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anax::World",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anax::World* self = (anax::World*)  tolua_tousertype(tolua_S,1,0);
  unsigned int typeID = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSystemByID'", NULL);
#endif
  {
   void* tolua_ret = (void*)  self->getSystemByID(typeID);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSystemByID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isValid of class  anax::Entity */
#ifndef TOLUA_DISABLE_tolua_ecs_anax_Entity_isValid00
static int tolua_ecs_anax_Entity_isValid00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const anax::Entity",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const anax::Entity* self = (const anax::Entity*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isValid'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isValid();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isActivated of class  anax::Entity */
#ifndef TOLUA_DISABLE_tolua_ecs_anax_Entity_isActivated00
static int tolua_ecs_anax_Entity_isActivated00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const anax::Entity",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const anax::Entity* self = (const anax::Entity*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isActivated'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isActivated();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isActivated'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: activate of class  anax::Entity */
#ifndef TOLUA_DISABLE_tolua_ecs_anax_Entity_activate00
static int tolua_ecs_anax_Entity_activate00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anax::Entity",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anax::Entity* self = (anax::Entity*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'activate'", NULL);
#endif
  {
   self->activate();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'activate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: deactivate of class  anax::Entity */
#ifndef TOLUA_DISABLE_tolua_ecs_anax_Entity_deactivate00
static int tolua_ecs_anax_Entity_deactivate00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anax::Entity",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anax::Entity* self = (anax::Entity*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'deactivate'", NULL);
#endif
  {
   self->deactivate();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'deactivate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: kill of class  anax::Entity */
#ifndef TOLUA_DISABLE_tolua_ecs_anax_Entity_kill00
static int tolua_ecs_anax_Entity_kill00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anax::Entity",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anax::Entity* self = (anax::Entity*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'kill'", NULL);
#endif
  {
   self->kill();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'kill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: post of class  anax::Entity */
#ifndef TOLUA_DISABLE_tolua_ecs_anax_Entity_post00
static int tolua_ecs_anax_Entity_post00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anax::Entity",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anax::Entity* self = (anax::Entity*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'post'", NULL);
#endif
  {
   self->post();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'post'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllComponents of class  anax::Entity */
#ifndef TOLUA_DISABLE_tolua_ecs_anax_Entity_removeAllComponents00
static int tolua_ecs_anax_Entity_removeAllComponents00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"anax::Entity",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  anax::Entity* self = (anax::Entity*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllComponents'", NULL);
#endif
  {
   self->removeAllComponents();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllComponents'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ArmatureCollisionSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_ArmatureCollisionSystem_new00
static int tolua_ecs_ArmatureCollisionSystem_new00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ArmatureCollisionSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ArmatureCollisionSystem* tolua_ret = (ArmatureCollisionSystem*)  Mtolua_new((ArmatureCollisionSystem)());
    tolua_ext_object_to_luaval<ArmatureCollisionSystem>(tolua_S,(void*)tolua_ret,"ArmatureCollisionSystem");
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

/* method: new_local of class  ArmatureCollisionSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_ArmatureCollisionSystem_new00_local
static int tolua_ecs_ArmatureCollisionSystem_new00_local(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ArmatureCollisionSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ArmatureCollisionSystem* tolua_ret = (ArmatureCollisionSystem*)  Mtolua_new((ArmatureCollisionSystem)());
    tolua_ext_object_to_luaval<ArmatureCollisionSystem>(tolua_S,(void*)tolua_ret,"ArmatureCollisionSystem");
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

/* method: delete of class  ArmatureCollisionSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_ArmatureCollisionSystem_delete00
static int tolua_ecs_ArmatureCollisionSystem_delete00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArmatureCollisionSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArmatureCollisionSystem* self = (ArmatureCollisionSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setDebugDrawNode of class  ArmatureCollisionSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_ArmatureCollisionSystem_setDebugDrawNode00
static int tolua_ecs_ArmatureCollisionSystem_setDebugDrawNode00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArmatureCollisionSystem",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"DrawNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArmatureCollisionSystem* self = (ArmatureCollisionSystem*)  tolua_tousertype(tolua_S,1,0);
  DrawNode* debugDrawNode = ((DrawNode*)  tolua_tousertype(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDebugDrawNode'", NULL);
#endif
  {
   self->setDebugDrawNode(debugDrawNode);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDebugDrawNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: collisionTest of class  ArmatureCollisionSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_ArmatureCollisionSystem_collisionTest00
static int tolua_ecs_ArmatureCollisionSystem_collisionTest00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArmatureCollisionSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArmatureCollisionSystem* self = (ArmatureCollisionSystem*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'collisionTest'", NULL);
#endif
  {
   self->collisionTest();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'collisionTest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Box2DSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_Box2DSystem_new00
static int tolua_ecs_Box2DSystem_new00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Box2DSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Box2DSystem* tolua_ret = (Box2DSystem*)  Mtolua_new((Box2DSystem)());
    tolua_ext_object_to_luaval<Box2DSystem>(tolua_S,(void*)tolua_ret,"Box2DSystem");
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

/* method: new_local of class  Box2DSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_Box2DSystem_new00_local
static int tolua_ecs_Box2DSystem_new00_local(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Box2DSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Box2DSystem* tolua_ret = (Box2DSystem*)  Mtolua_new((Box2DSystem)());
    tolua_ext_object_to_luaval<Box2DSystem>(tolua_S,(void*)tolua_ret,"Box2DSystem");
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

/* method: delete of class  Box2DSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_Box2DSystem_delete00
static int tolua_ecs_Box2DSystem_delete00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Box2DSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Box2DSystem* self = (Box2DSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: initPhysics of class  Box2DSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_Box2DSystem_initPhysics00
static int tolua_ecs_Box2DSystem_initPhysics00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Box2DSystem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_is_table(tolua_S,2,"Vec2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_ext_check_is_table(tolua_S,3,"Size",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Box2DSystem* self = (Box2DSystem*)  tolua_tousertype(tolua_S,1,0);
  Vec2 gravity = (  tolua_ext_luaval_to_vec2_value(tolua_S,2,0));
  Size worldSize = (  tolua_ext_luaval_to_size_value(tolua_S,3,0));
  float left_offset = ((float)  tolua_tonumber(tolua_S,4,0));
  float right_offset = ((float)  tolua_tonumber(tolua_S,5,0));
  float top_offset = ((float)  tolua_tonumber(tolua_S,6,0));
  float bottom_offset = ((float)  tolua_tonumber(tolua_S,7,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initPhysics'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initPhysics(gravity,worldSize,left_offset,right_offset,top_offset,bottom_offset);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initPhysics'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateWorld of class  Box2DSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_Box2DSystem_updateWorld00
static int tolua_ecs_Box2DSystem_updateWorld00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Box2DSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Box2DSystem* self = (Box2DSystem*)  tolua_tousertype(tolua_S,1,0);
  float delta = ((float)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateWorld'", NULL);
#endif
  {
   self->updateWorld(delta);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addDiscardB2Body of class  Box2DSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_Box2DSystem_addDiscardB2Body00
static int tolua_ecs_Box2DSystem_addDiscardB2Body00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Box2DSystem",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Box2DSystem* self = (Box2DSystem*)  tolua_tousertype(tolua_S,1,0);
  b2Body* body = ((b2Body*)  tolua_tousertype(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addDiscardB2Body'", NULL);
#endif
  {
   self->addDiscardB2Body(body);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addDiscardB2Body'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBox2DWorld of class  Box2DSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_Box2DSystem_getBox2DWorld00
static int tolua_ecs_Box2DSystem_getBox2DWorld00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Box2DSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Box2DSystem* self = (Box2DSystem*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBox2DWorld'", NULL);
#endif
  {
   b2World* tolua_ret = (b2World*)  self->getBox2DWorld();
    tolua_ext_object_to_luaval<b2World>(tolua_S,(void*)tolua_ret,"b2World");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBox2DWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  MapFollowSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_MapFollowSystem_new00
static int tolua_ecs_MapFollowSystem_new00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MapFollowSystem",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameMap",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameMap* gameMap = ((GameMap*)  tolua_tousertype(tolua_S,2,0));
  {
   MapFollowSystem* tolua_ret = (MapFollowSystem*)  Mtolua_new((MapFollowSystem)(gameMap));
    tolua_ext_object_to_luaval<MapFollowSystem>(tolua_S,(void*)tolua_ret,"MapFollowSystem");
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

/* method: new_local of class  MapFollowSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_MapFollowSystem_new00_local
static int tolua_ecs_MapFollowSystem_new00_local(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MapFollowSystem",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameMap",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameMap* gameMap = ((GameMap*)  tolua_tousertype(tolua_S,2,0));
  {
   MapFollowSystem* tolua_ret = (MapFollowSystem*)  Mtolua_new((MapFollowSystem)(gameMap));
    tolua_ext_object_to_luaval<MapFollowSystem>(tolua_S,(void*)tolua_ret,"MapFollowSystem");
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

/* method: delete of class  MapFollowSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_MapFollowSystem_delete00
static int tolua_ecs_MapFollowSystem_delete00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MapFollowSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MapFollowSystem* self = (MapFollowSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: update of class  MapFollowSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_MapFollowSystem_update00
static int tolua_ecs_MapFollowSystem_update00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MapFollowSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MapFollowSystem* self = (MapFollowSystem*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update();
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

/* method: resetGameMap of class  MapFollowSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_MapFollowSystem_resetGameMap00
static int tolua_ecs_MapFollowSystem_resetGameMap00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MapFollowSystem",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameMap",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MapFollowSystem* self = (MapFollowSystem*)  tolua_tousertype(tolua_S,1,0);
  GameMap* gameMap = ((GameMap*)  tolua_tousertype(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resetGameMap'", NULL);
#endif
  {
   self->resetGameMap(gameMap);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resetGameMap'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UpdateSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_UpdateSystem_new00
static int tolua_ecs_UpdateSystem_new00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UpdateSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UpdateSystem* tolua_ret = (UpdateSystem*)  Mtolua_new((UpdateSystem)());
    tolua_ext_object_to_luaval<UpdateSystem>(tolua_S,(void*)tolua_ret,"UpdateSystem");
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

/* method: new_local of class  UpdateSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_UpdateSystem_new00_local
static int tolua_ecs_UpdateSystem_new00_local(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UpdateSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UpdateSystem* tolua_ret = (UpdateSystem*)  Mtolua_new((UpdateSystem)());
    tolua_ext_object_to_luaval<UpdateSystem>(tolua_S,(void*)tolua_ret,"UpdateSystem");
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

/* method: delete of class  UpdateSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_UpdateSystem_delete00
static int tolua_ecs_UpdateSystem_delete00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UpdateSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UpdateSystem* self = (UpdateSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: update of class  UpdateSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_UpdateSystem_update00
static int tolua_ecs_UpdateSystem_update00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UpdateSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UpdateSystem* self = (UpdateSystem*)  tolua_tousertype(tolua_S,1,0);
  float delta = ((float)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update(delta);
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

/* method: lastUpdate of class  UpdateSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_UpdateSystem_lastUpdate00
static int tolua_ecs_UpdateSystem_lastUpdate00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UpdateSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UpdateSystem* self = (UpdateSystem*)  tolua_tousertype(tolua_S,1,0);
  float delta = ((float)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'lastUpdate'", NULL);
#endif
  {
   self->lastUpdate(delta);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'lastUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  FilterSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_FilterSystem_new00
static int tolua_ecs_FilterSystem_new00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"FilterSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   FilterSystem* tolua_ret = (FilterSystem*)  Mtolua_new((FilterSystem)());
    tolua_ext_object_to_luaval<FilterSystem>(tolua_S,(void*)tolua_ret,"FilterSystem");
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

/* method: new_local of class  FilterSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_FilterSystem_new00_local
static int tolua_ecs_FilterSystem_new00_local(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"FilterSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   FilterSystem* tolua_ret = (FilterSystem*)  Mtolua_new((FilterSystem)());
    tolua_ext_object_to_luaval<FilterSystem>(tolua_S,(void*)tolua_ret,"FilterSystem");
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

/* method: delete of class  FilterSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_FilterSystem_delete00
static int tolua_ecs_FilterSystem_delete00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FilterSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FilterSystem* self = (FilterSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getAllActorByFilterData of class  FilterSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_FilterSystem_getAllActorByFilterData00
static int tolua_ecs_FilterSystem_getAllActorByFilterData00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FilterSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FilterSystem* self = (FilterSystem*)  tolua_tousertype(tolua_S,1,0);
  int filterData = ((int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAllActorByFilterData'", NULL);
#endif
  {
   std::vector<Actor*> tolua_ret = (std::vector<Actor*>)  self->getAllActorByFilterData(filterData);
   {
   tolua_ext_object_arr_to_luaval<Actor>(tolua_S, tolua_ret, "std::vector<Actor*>");
   }
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAllActorByFilterData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: randomGetActorByFilterData of class  FilterSystem */
#ifndef TOLUA_DISABLE_tolua_ecs_FilterSystem_randomGetActorByFilterData00
static int tolua_ecs_FilterSystem_randomGetActorByFilterData00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FilterSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FilterSystem* self = (FilterSystem*)  tolua_tousertype(tolua_S,1,0);
  int filterData = ((int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'randomGetActorByFilterData'", NULL);
#endif
  {
   Actor* tolua_ret = (Actor*)  self->randomGetActorByFilterData(filterData);
    tolua_ext_object_to_luaval<Actor>(tolua_S,(void*)tolua_ret,"Actor");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'randomGetActorByFilterData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_armature of class  ArmatureComponent */
#ifndef TOLUA_DISABLE_tolua_get_ArmatureComponent_m_armature_ptr
static int tolua_get_ArmatureComponent_m_armature_ptr(lua_State* tolua_S)
{
  ArmatureComponent* self = (ArmatureComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_armature'",NULL);
#endif
   tolua_ext_object_to_luaval<Armature>(tolua_S,(void*)self->m_armature,"ccs.Armature");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_armature of class  ArmatureComponent */
#ifndef TOLUA_DISABLE_tolua_set_ArmatureComponent_m_armature_ptr
static int tolua_set_ArmatureComponent_m_armature_ptr(lua_State* tolua_S)
{
  ArmatureComponent* self = (ArmatureComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_armature'",NULL);
  if (!tolua_isusertype(tolua_S,2,"ccs.Armature",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_armature = ((Armature*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_owner of class  ArmatureComponent */
#ifndef TOLUA_DISABLE_tolua_get_ArmatureComponent_m_owner_ptr
static int tolua_get_ArmatureComponent_m_owner_ptr(lua_State* tolua_S)
{
  ArmatureComponent* self = (ArmatureComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_owner'",NULL);
#endif
   tolua_ext_object_to_luaval<Node>(tolua_S,(void*)self->m_owner,"cc.Node");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_owner of class  ArmatureComponent */
#ifndef TOLUA_DISABLE_tolua_set_ArmatureComponent_m_owner_ptr
static int tolua_set_ArmatureComponent_m_owner_ptr(lua_State* tolua_S)
{
  ArmatureComponent* self = (ArmatureComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_owner'",NULL);
  if (!tolua_isusertype(tolua_S,2,"cc.Node",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_owner = ((Node*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_attCollisionCall of class  ArmatureCollisionComponent */
#ifndef TOLUA_DISABLE_tolua_get_ArmatureCollisionComponent_m_attCollisionCall
static int tolua_get_ArmatureCollisionComponent_m_attCollisionCall(lua_State* tolua_S)
{
  ArmatureCollisionComponent* self = (ArmatureCollisionComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_attCollisionCall'",NULL);
#endif
   tolua_ext_function_to_luaval(tolua_S,self->m_attCollisionCall,"LuaFunction");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_attCollisionCall of class  ArmatureCollisionComponent */
#ifndef TOLUA_DISABLE_tolua_set_ArmatureCollisionComponent_m_attCollisionCall
static int tolua_set_ArmatureCollisionComponent_m_attCollisionCall(lua_State* tolua_S)
{
  ArmatureCollisionComponent* self = (ArmatureCollisionComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_attCollisionCall'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_isfunction(tolua_S,2,"LuaFunction",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_attCollisionCall = (  LuaFunction(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_defCollisionCall of class  ArmatureCollisionComponent */
#ifndef TOLUA_DISABLE_tolua_get_ArmatureCollisionComponent_m_defCollisionCall
static int tolua_get_ArmatureCollisionComponent_m_defCollisionCall(lua_State* tolua_S)
{
  ArmatureCollisionComponent* self = (ArmatureCollisionComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_defCollisionCall'",NULL);
#endif
   tolua_ext_function_to_luaval(tolua_S,self->m_defCollisionCall,"LuaFunction");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_defCollisionCall of class  ArmatureCollisionComponent */
#ifndef TOLUA_DISABLE_tolua_set_ArmatureCollisionComponent_m_defCollisionCall
static int tolua_set_ArmatureCollisionComponent_m_defCollisionCall(lua_State* tolua_S)
{
  ArmatureCollisionComponent* self = (ArmatureCollisionComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_defCollisionCall'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_isfunction(tolua_S,2,"LuaFunction",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_defCollisionCall = (  LuaFunction(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_defCacheDirty of class  ArmatureCollisionComponent */
#ifndef TOLUA_DISABLE_tolua_get_ArmatureCollisionComponent_m_defCacheDirty
static int tolua_get_ArmatureCollisionComponent_m_defCacheDirty(lua_State* tolua_S)
{
  ArmatureCollisionComponent* self = (ArmatureCollisionComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_defCacheDirty'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_defCacheDirty);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_defCacheDirty of class  ArmatureCollisionComponent */
#ifndef TOLUA_DISABLE_tolua_set_ArmatureCollisionComponent_m_defCacheDirty
static int tolua_set_ArmatureCollisionComponent_m_defCacheDirty(lua_State* tolua_S)
{
  ArmatureCollisionComponent* self = (ArmatureCollisionComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_defCacheDirty'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_defCacheDirty = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_attCacheDirty of class  ArmatureCollisionComponent */
#ifndef TOLUA_DISABLE_tolua_get_ArmatureCollisionComponent_m_attCacheDirty
static int tolua_get_ArmatureCollisionComponent_m_attCacheDirty(lua_State* tolua_S)
{
  ArmatureCollisionComponent* self = (ArmatureCollisionComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_attCacheDirty'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_attCacheDirty);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_attCacheDirty of class  ArmatureCollisionComponent */
#ifndef TOLUA_DISABLE_tolua_set_ArmatureCollisionComponent_m_attCacheDirty
static int tolua_set_ArmatureCollisionComponent_m_attCacheDirty(lua_State* tolua_S)
{
  ArmatureCollisionComponent* self = (ArmatureCollisionComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_attCacheDirty'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_attCacheDirty = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_groupIndex of class  CollisionFilterComponent */
#ifndef TOLUA_DISABLE_tolua_get_CollisionFilterComponent_m_groupIndex
static int tolua_get_CollisionFilterComponent_m_groupIndex(lua_State* tolua_S)
{
  CollisionFilterComponent* self = (CollisionFilterComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_groupIndex'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_groupIndex);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_groupIndex of class  CollisionFilterComponent */
#ifndef TOLUA_DISABLE_tolua_set_CollisionFilterComponent_m_groupIndex
static int tolua_set_CollisionFilterComponent_m_groupIndex(lua_State* tolua_S)
{
  CollisionFilterComponent* self = (CollisionFilterComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_groupIndex'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_groupIndex = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_collisionEnable of class  CollisionFilterComponent */
#ifndef TOLUA_DISABLE_tolua_get_CollisionFilterComponent_m_collisionEnable
static int tolua_get_CollisionFilterComponent_m_collisionEnable(lua_State* tolua_S)
{
  CollisionFilterComponent* self = (CollisionFilterComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_collisionEnable'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_collisionEnable);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_collisionEnable of class  CollisionFilterComponent */
#ifndef TOLUA_DISABLE_tolua_set_CollisionFilterComponent_m_collisionEnable
static int tolua_set_CollisionFilterComponent_m_collisionEnable(lua_State* tolua_S)
{
  CollisionFilterComponent* self = (CollisionFilterComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_collisionEnable'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_collisionEnable = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_body of class  Box2DComponent */
#ifndef TOLUA_DISABLE_tolua_get_Box2DComponent_m_body_ptr
static int tolua_get_Box2DComponent_m_body_ptr(lua_State* tolua_S)
{
  Box2DComponent* self = (Box2DComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_body'",NULL);
#endif
   tolua_ext_object_to_luaval<b2Body>(tolua_S,(void*)self->m_body,"b2Body");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_body of class  Box2DComponent */
#ifndef TOLUA_DISABLE_tolua_set_Box2DComponent_m_body_ptr
static int tolua_set_Box2DComponent_m_body_ptr(lua_State* tolua_S)
{
  Box2DComponent* self = (Box2DComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_body'",NULL);
  if (!tolua_isusertype(tolua_S,2,"b2Body",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_body = ((b2Body*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_syncPhysicsTransformCall of class  Box2DComponent */
#ifndef TOLUA_DISABLE_tolua_get_Box2DComponent_m_syncPhysicsTransformCall
static int tolua_get_Box2DComponent_m_syncPhysicsTransformCall(lua_State* tolua_S)
{
  Box2DComponent* self = (Box2DComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_syncPhysicsTransformCall'",NULL);
#endif
   tolua_ext_function_to_luaval(tolua_S,self->m_syncPhysicsTransformCall,"LuaFunction");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_syncPhysicsTransformCall of class  Box2DComponent */
#ifndef TOLUA_DISABLE_tolua_set_Box2DComponent_m_syncPhysicsTransformCall
static int tolua_set_Box2DComponent_m_syncPhysicsTransformCall(lua_State* tolua_S)
{
  Box2DComponent* self = (Box2DComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_syncPhysicsTransformCall'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_isfunction(tolua_S,2,"LuaFunction",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_syncPhysicsTransformCall = (  LuaFunction(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_owner of class  MapFollowComponent */
#ifndef TOLUA_DISABLE_tolua_get_MapFollowComponent_m_owner_ptr
static int tolua_get_MapFollowComponent_m_owner_ptr(lua_State* tolua_S)
{
  MapFollowComponent* self = (MapFollowComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_owner'",NULL);
#endif
   tolua_ext_object_to_luaval<Node>(tolua_S,(void*)self->m_owner,"cc.Node");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_owner of class  MapFollowComponent */
#ifndef TOLUA_DISABLE_tolua_set_MapFollowComponent_m_owner_ptr
static int tolua_set_MapFollowComponent_m_owner_ptr(lua_State* tolua_S)
{
  MapFollowComponent* self = (MapFollowComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_owner'",NULL);
  if (!tolua_isusertype(tolua_S,2,"cc.Node",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_owner = ((Node*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOrientation of class  OrientationComponent */
#ifndef TOLUA_DISABLE_tolua_ecs_OrientationComponent_setOrientation00
static int tolua_ecs_OrientationComponent_setOrientation00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"OrientationComponent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  OrientationComponent* self = (OrientationComponent*)  tolua_tousertype(tolua_S,1,0);
  int orientation = ((int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOrientation'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->setOrientation(orientation);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOrientation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_orientation of class  OrientationComponent */
#ifndef TOLUA_DISABLE_tolua_get_OrientationComponent_m_orientation
static int tolua_get_OrientationComponent_m_orientation(lua_State* tolua_S)
{
  OrientationComponent* self = (OrientationComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_orientation'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_orientation);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_orientation of class  OrientationComponent */
#ifndef TOLUA_DISABLE_tolua_set_OrientationComponent_m_orientation
static int tolua_set_OrientationComponent_m_orientation(lua_State* tolua_S)
{
  OrientationComponent* self = (OrientationComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_orientation'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_orientation = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_lockOrientation of class  OrientationComponent */
#ifndef TOLUA_DISABLE_tolua_get_OrientationComponent_m_lockOrientation
static int tolua_get_OrientationComponent_m_lockOrientation(lua_State* tolua_S)
{
  OrientationComponent* self = (OrientationComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_lockOrientation'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_lockOrientation);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_lockOrientation of class  OrientationComponent */
#ifndef TOLUA_DISABLE_tolua_set_OrientationComponent_m_lockOrientation
static int tolua_set_OrientationComponent_m_lockOrientation(lua_State* tolua_S)
{
  OrientationComponent* self = (OrientationComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_lockOrientation'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_lockOrientation = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_orientationTurnCall of class  OrientationComponent */
#ifndef TOLUA_DISABLE_tolua_get_OrientationComponent_m_orientationTurnCall
static int tolua_get_OrientationComponent_m_orientationTurnCall(lua_State* tolua_S)
{
  OrientationComponent* self = (OrientationComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_orientationTurnCall'",NULL);
#endif
   tolua_ext_function_to_luaval(tolua_S,self->m_orientationTurnCall,"LuaFunction");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_orientationTurnCall of class  OrientationComponent */
#ifndef TOLUA_DISABLE_tolua_set_OrientationComponent_m_orientationTurnCall
static int tolua_set_OrientationComponent_m_orientationTurnCall(lua_State* tolua_S)
{
  OrientationComponent* self = (OrientationComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_orientationTurnCall'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_isfunction(tolua_S,2,"LuaFunction",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_orientationTurnCall = (  LuaFunction(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UpdateComponent */
#ifndef TOLUA_DISABLE_tolua_ecs_UpdateComponent_new00
static int tolua_ecs_UpdateComponent_new00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UpdateComponent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UpdateComponent* tolua_ret = (UpdateComponent*)  Mtolua_new((UpdateComponent)());
    tolua_ext_object_to_luaval<UpdateComponent>(tolua_S,(void*)tolua_ret,"UpdateComponent");
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

/* method: new_local of class  UpdateComponent */
#ifndef TOLUA_DISABLE_tolua_ecs_UpdateComponent_new00_local
static int tolua_ecs_UpdateComponent_new00_local(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UpdateComponent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UpdateComponent* tolua_ret = (UpdateComponent*)  Mtolua_new((UpdateComponent)());
    tolua_ext_object_to_luaval<UpdateComponent>(tolua_S,(void*)tolua_ret,"UpdateComponent");
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

/* method: delete of class  UpdateComponent */
#ifndef TOLUA_DISABLE_tolua_ecs_UpdateComponent_delete00
static int tolua_ecs_UpdateComponent_delete00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UpdateComponent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UpdateComponent* self = (UpdateComponent*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: m_updateCall of class  UpdateComponent */
#ifndef TOLUA_DISABLE_tolua_get_UpdateComponent_m_updateCall
static int tolua_get_UpdateComponent_m_updateCall(lua_State* tolua_S)
{
  UpdateComponent* self = (UpdateComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_updateCall'",NULL);
#endif
   tolua_ext_function_to_luaval(tolua_S,self->m_updateCall,"LuaFunction");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_updateCall of class  UpdateComponent */
#ifndef TOLUA_DISABLE_tolua_set_UpdateComponent_m_updateCall
static int tolua_set_UpdateComponent_m_updateCall(lua_State* tolua_S)
{
  UpdateComponent* self = (UpdateComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_updateCall'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_isfunction(tolua_S,2,"LuaFunction",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_updateCall = (  LuaFunction(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_lastUpdateCall of class  UpdateComponent */
#ifndef TOLUA_DISABLE_tolua_get_UpdateComponent_m_lastUpdateCall
static int tolua_get_UpdateComponent_m_lastUpdateCall(lua_State* tolua_S)
{
  UpdateComponent* self = (UpdateComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_lastUpdateCall'",NULL);
#endif
   tolua_ext_function_to_luaval(tolua_S,self->m_lastUpdateCall,"LuaFunction");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_lastUpdateCall of class  UpdateComponent */
#ifndef TOLUA_DISABLE_tolua_set_UpdateComponent_m_lastUpdateCall
static int tolua_set_UpdateComponent_m_lastUpdateCall(lua_State* tolua_S)
{
  UpdateComponent* self = (UpdateComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_lastUpdateCall'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_isfunction(tolua_S,2,"LuaFunction",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_lastUpdateCall = (  LuaFunction(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  FilterComponent */
#ifndef TOLUA_DISABLE_tolua_ecs_FilterComponent_new00
static int tolua_ecs_FilterComponent_new00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"FilterComponent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   FilterComponent* tolua_ret = (FilterComponent*)  Mtolua_new((FilterComponent)());
    tolua_ext_object_to_luaval<FilterComponent>(tolua_S,(void*)tolua_ret,"FilterComponent");
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

/* method: new_local of class  FilterComponent */
#ifndef TOLUA_DISABLE_tolua_ecs_FilterComponent_new00_local
static int tolua_ecs_FilterComponent_new00_local(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"FilterComponent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   FilterComponent* tolua_ret = (FilterComponent*)  Mtolua_new((FilterComponent)());
    tolua_ext_object_to_luaval<FilterComponent>(tolua_S,(void*)tolua_ret,"FilterComponent");
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

/* method: delete of class  FilterComponent */
#ifndef TOLUA_DISABLE_tolua_ecs_FilterComponent_delete00
static int tolua_ecs_FilterComponent_delete00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FilterComponent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FilterComponent* self = (FilterComponent*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: m_owner of class  FilterComponent */
#ifndef TOLUA_DISABLE_tolua_get_FilterComponent_m_owner_ptr
static int tolua_get_FilterComponent_m_owner_ptr(lua_State* tolua_S)
{
  FilterComponent* self = (FilterComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_owner'",NULL);
#endif
   tolua_ext_object_to_luaval<Actor>(tolua_S,(void*)self->m_owner,"Actor");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_owner of class  FilterComponent */
#ifndef TOLUA_DISABLE_tolua_set_FilterComponent_m_owner_ptr
static int tolua_set_FilterComponent_m_owner_ptr(lua_State* tolua_S)
{
  FilterComponent* self = (FilterComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_owner'",NULL);
  if (!tolua_isusertype(tolua_S,2,"Actor",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_owner = ((Actor*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_filterData of class  FilterComponent */
#ifndef TOLUA_DISABLE_tolua_get_FilterComponent_m_filterData
static int tolua_get_FilterComponent_m_filterData(lua_State* tolua_S)
{
  FilterComponent* self = (FilterComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_filterData'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_filterData);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_filterData of class  FilterComponent */
#ifndef TOLUA_DISABLE_tolua_set_FilterComponent_m_filterData
static int tolua_set_FilterComponent_m_filterData(lua_State* tolua_S)
{
  FilterComponent* self = (FilterComponent*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_filterData'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_filterData = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_ecs_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"AnaxHelper","AnaxHelper","",NULL);
  tolua_beginmodule(tolua_S,"AnaxHelper");
   tolua_function(tolua_S,"addComponent",tolua_ecs_AnaxHelper_addComponent00);
   tolua_function(tolua_S,"getComponent",tolua_ecs_AnaxHelper_getComponent00);
   tolua_function(tolua_S,"removeComponent",tolua_ecs_AnaxHelper_removeComponent00);
   tolua_function(tolua_S,"hasComponent",tolua_ecs_AnaxHelper_hasComponent00);
   tolua_function(tolua_S,"getComponentTypeID",tolua_ecs_AnaxHelper_getComponentTypeID00);
   tolua_function(tolua_S,"addSystem",tolua_ecs_AnaxHelper_addSystem00);
   tolua_function(tolua_S,"removeSystem",tolua_ecs_AnaxHelper_removeSystem00);
   tolua_function(tolua_S,"doesSystemExist",tolua_ecs_AnaxHelper_doesSystemExist00);
   tolua_function(tolua_S,"getSystemWorld",tolua_ecs_AnaxHelper_getSystemWorld00);
   tolua_function(tolua_S,"getSystemTypeID",tolua_ecs_AnaxHelper_getSystemTypeID00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"anax",0);
  tolua_beginmodule(tolua_S,"anax");
   tolua_cclass(tolua_S,"World","anax::World","",NULL);
   tolua_beginmodule(tolua_S,"World");
    tolua_function(tolua_S,"removeAllSystems",tolua_ecs_anax_World_removeAllSystems00);
    tolua_function(tolua_S,"refresh",tolua_ecs_anax_World_refresh00);
    tolua_function(tolua_S,"clear",tolua_ecs_anax_World_clear00);
    tolua_function(tolua_S,"getEntityCount",tolua_ecs_anax_World_getEntityCount00);
    tolua_function(tolua_S,"getSystemByID",tolua_ecs_anax_World_getSystemByID00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"anax",0);
  tolua_beginmodule(tolua_S,"anax");
   tolua_cclass(tolua_S,"System","anax::System","",NULL);
   tolua_beginmodule(tolua_S,"System");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"anax",0);
  tolua_beginmodule(tolua_S,"anax");
   tolua_cclass(tolua_S,"Entity","anax::Entity","",NULL);
   tolua_beginmodule(tolua_S,"Entity");
    tolua_function(tolua_S,"isValid",tolua_ecs_anax_Entity_isValid00);
    tolua_function(tolua_S,"isActivated",tolua_ecs_anax_Entity_isActivated00);
    tolua_function(tolua_S,"activate",tolua_ecs_anax_Entity_activate00);
    tolua_function(tolua_S,"deactivate",tolua_ecs_anax_Entity_deactivate00);
    tolua_function(tolua_S,"kill",tolua_ecs_anax_Entity_kill00);
    tolua_function(tolua_S,"post",tolua_ecs_anax_Entity_post00);
    tolua_function(tolua_S,"removeAllComponents",tolua_ecs_anax_Entity_removeAllComponents00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ArmatureCollisionSystem","ArmatureCollisionSystem","anax::System",tolua_collect_ArmatureCollisionSystem);
  #else
  tolua_cclass(tolua_S,"ArmatureCollisionSystem","ArmatureCollisionSystem","anax::System",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ArmatureCollisionSystem");
   tolua_function(tolua_S,"new",tolua_ecs_ArmatureCollisionSystem_new00);
   tolua_function(tolua_S,"new_local",tolua_ecs_ArmatureCollisionSystem_new00_local);
   tolua_function(tolua_S,".call",tolua_ecs_ArmatureCollisionSystem_new00_local);
   tolua_function(tolua_S,"delete",tolua_ecs_ArmatureCollisionSystem_delete00);
   tolua_function(tolua_S,"setDebugDrawNode",tolua_ecs_ArmatureCollisionSystem_setDebugDrawNode00);
   tolua_function(tolua_S,"collisionTest",tolua_ecs_ArmatureCollisionSystem_collisionTest00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"BOX2D_PIXEL_TO_METER",BOX2D_PIXEL_TO_METER);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Box2DSystem","Box2DSystem","anax::System",tolua_collect_Box2DSystem);
  #else
  tolua_cclass(tolua_S,"Box2DSystem","Box2DSystem","anax::System",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Box2DSystem");
   tolua_function(tolua_S,"new",tolua_ecs_Box2DSystem_new00);
   tolua_function(tolua_S,"new_local",tolua_ecs_Box2DSystem_new00_local);
   tolua_function(tolua_S,".call",tolua_ecs_Box2DSystem_new00_local);
   tolua_function(tolua_S,"delete",tolua_ecs_Box2DSystem_delete00);
   tolua_function(tolua_S,"initPhysics",tolua_ecs_Box2DSystem_initPhysics00);
   tolua_function(tolua_S,"updateWorld",tolua_ecs_Box2DSystem_updateWorld00);
   tolua_function(tolua_S,"addDiscardB2Body",tolua_ecs_Box2DSystem_addDiscardB2Body00);
   tolua_function(tolua_S,"getBox2DWorld",tolua_ecs_Box2DSystem_getBox2DWorld00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"MapFollowSystem","MapFollowSystem","anax::System",tolua_collect_MapFollowSystem);
  #else
  tolua_cclass(tolua_S,"MapFollowSystem","MapFollowSystem","anax::System",NULL);
  #endif
  tolua_beginmodule(tolua_S,"MapFollowSystem");
   tolua_function(tolua_S,"new",tolua_ecs_MapFollowSystem_new00);
   tolua_function(tolua_S,"new_local",tolua_ecs_MapFollowSystem_new00_local);
   tolua_function(tolua_S,".call",tolua_ecs_MapFollowSystem_new00_local);
   tolua_function(tolua_S,"delete",tolua_ecs_MapFollowSystem_delete00);
   tolua_function(tolua_S,"update",tolua_ecs_MapFollowSystem_update00);
   tolua_function(tolua_S,"resetGameMap",tolua_ecs_MapFollowSystem_resetGameMap00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UpdateSystem","UpdateSystem","anax::System",tolua_collect_UpdateSystem);
  #else
  tolua_cclass(tolua_S,"UpdateSystem","UpdateSystem","anax::System",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UpdateSystem");
   tolua_function(tolua_S,"new",tolua_ecs_UpdateSystem_new00);
   tolua_function(tolua_S,"new_local",tolua_ecs_UpdateSystem_new00_local);
   tolua_function(tolua_S,".call",tolua_ecs_UpdateSystem_new00_local);
   tolua_function(tolua_S,"delete",tolua_ecs_UpdateSystem_delete00);
   tolua_function(tolua_S,"update",tolua_ecs_UpdateSystem_update00);
   tolua_function(tolua_S,"lastUpdate",tolua_ecs_UpdateSystem_lastUpdate00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"FilterSystem","FilterSystem","anax::System",tolua_collect_FilterSystem);
  #else
  tolua_cclass(tolua_S,"FilterSystem","FilterSystem","anax::System",NULL);
  #endif
  tolua_beginmodule(tolua_S,"FilterSystem");
   tolua_function(tolua_S,"new",tolua_ecs_FilterSystem_new00);
   tolua_function(tolua_S,"new_local",tolua_ecs_FilterSystem_new00_local);
   tolua_function(tolua_S,".call",tolua_ecs_FilterSystem_new00_local);
   tolua_function(tolua_S,"delete",tolua_ecs_FilterSystem_delete00);
   tolua_function(tolua_S,"getAllActorByFilterData",tolua_ecs_FilterSystem_getAllActorByFilterData00);
   tolua_function(tolua_S,"randomGetActorByFilterData",tolua_ecs_FilterSystem_randomGetActorByFilterData00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ArmatureComponent","ArmatureComponent","anax::Component",NULL);
  tolua_beginmodule(tolua_S,"ArmatureComponent");
   tolua_variable(tolua_S,"m_armature",tolua_get_ArmatureComponent_m_armature_ptr,tolua_set_ArmatureComponent_m_armature_ptr);
   tolua_variable(tolua_S,"m_owner",tolua_get_ArmatureComponent_m_owner_ptr,tolua_set_ArmatureComponent_m_owner_ptr);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ArmatureCollisionComponent","ArmatureCollisionComponent","anax::Component",NULL);
  tolua_beginmodule(tolua_S,"ArmatureCollisionComponent");
   tolua_variable(tolua_S,"m_attCollisionCall",tolua_get_ArmatureCollisionComponent_m_attCollisionCall,tolua_set_ArmatureCollisionComponent_m_attCollisionCall);
   tolua_variable(tolua_S,"m_defCollisionCall",tolua_get_ArmatureCollisionComponent_m_defCollisionCall,tolua_set_ArmatureCollisionComponent_m_defCollisionCall);
   tolua_variable(tolua_S,"m_defCacheDirty",tolua_get_ArmatureCollisionComponent_m_defCacheDirty,tolua_set_ArmatureCollisionComponent_m_defCacheDirty);
   tolua_variable(tolua_S,"m_attCacheDirty",tolua_get_ArmatureCollisionComponent_m_attCacheDirty,tolua_set_ArmatureCollisionComponent_m_attCacheDirty);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CollisionFilterComponent","CollisionFilterComponent","anax::Component",NULL);
  tolua_beginmodule(tolua_S,"CollisionFilterComponent");
   tolua_variable(tolua_S,"m_groupIndex",tolua_get_CollisionFilterComponent_m_groupIndex,tolua_set_CollisionFilterComponent_m_groupIndex);
   tolua_variable(tolua_S,"m_collisionEnable",tolua_get_CollisionFilterComponent_m_collisionEnable,tolua_set_CollisionFilterComponent_m_collisionEnable);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Box2DComponent","Box2DComponent","anax::Component",NULL);
  tolua_beginmodule(tolua_S,"Box2DComponent");
   tolua_variable(tolua_S,"m_body",tolua_get_Box2DComponent_m_body_ptr,tolua_set_Box2DComponent_m_body_ptr);
   tolua_variable(tolua_S,"m_syncPhysicsTransformCall",tolua_get_Box2DComponent_m_syncPhysicsTransformCall,tolua_set_Box2DComponent_m_syncPhysicsTransformCall);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"MapFollowComponent","MapFollowComponent","anax::Component",NULL);
  tolua_beginmodule(tolua_S,"MapFollowComponent");
   tolua_variable(tolua_S,"m_owner",tolua_get_MapFollowComponent_m_owner_ptr,tolua_set_MapFollowComponent_m_owner_ptr);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"OrientationComponent","OrientationComponent","anax::Component",NULL);
  tolua_beginmodule(tolua_S,"OrientationComponent");
   tolua_function(tolua_S,"setOrientation",tolua_ecs_OrientationComponent_setOrientation00);
   tolua_variable(tolua_S,"m_orientation",tolua_get_OrientationComponent_m_orientation,tolua_set_OrientationComponent_m_orientation);
   tolua_variable(tolua_S,"m_lockOrientation",tolua_get_OrientationComponent_m_lockOrientation,tolua_set_OrientationComponent_m_lockOrientation);
   tolua_variable(tolua_S,"m_orientationTurnCall",tolua_get_OrientationComponent_m_orientationTurnCall,tolua_set_OrientationComponent_m_orientationTurnCall);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UpdateComponent","UpdateComponent","anax::Component",tolua_collect_UpdateComponent);
  #else
  tolua_cclass(tolua_S,"UpdateComponent","UpdateComponent","anax::Component",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UpdateComponent");
   tolua_function(tolua_S,"new",tolua_ecs_UpdateComponent_new00);
   tolua_function(tolua_S,"new_local",tolua_ecs_UpdateComponent_new00_local);
   tolua_function(tolua_S,".call",tolua_ecs_UpdateComponent_new00_local);
   tolua_function(tolua_S,"delete",tolua_ecs_UpdateComponent_delete00);
   tolua_variable(tolua_S,"m_updateCall",tolua_get_UpdateComponent_m_updateCall,tolua_set_UpdateComponent_m_updateCall);
   tolua_variable(tolua_S,"m_lastUpdateCall",tolua_get_UpdateComponent_m_lastUpdateCall,tolua_set_UpdateComponent_m_lastUpdateCall);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"FilterComponent","FilterComponent","anax::Component",tolua_collect_FilterComponent);
  #else
  tolua_cclass(tolua_S,"FilterComponent","FilterComponent","anax::Component",NULL);
  #endif
  tolua_beginmodule(tolua_S,"FilterComponent");
   tolua_function(tolua_S,"new",tolua_ecs_FilterComponent_new00);
   tolua_function(tolua_S,"new_local",tolua_ecs_FilterComponent_new00_local);
   tolua_function(tolua_S,".call",tolua_ecs_FilterComponent_new00_local);
   tolua_function(tolua_S,"delete",tolua_ecs_FilterComponent_delete00);
   tolua_variable(tolua_S,"m_owner",tolua_get_FilterComponent_m_owner_ptr,tolua_set_FilterComponent_m_owner_ptr);
   tolua_variable(tolua_S,"m_filterData",tolua_get_FilterComponent_m_filterData,tolua_set_FilterComponent_m_filterData);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_ecs (lua_State* tolua_S) {
 return tolua_ecs_open(tolua_S);
};
#endif

