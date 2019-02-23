/*
** Lua binding: game_assets
** Generated automatically by tolua++-1.0.92 on 02/17/19 14:02:30.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"
#include "tolua++.h"
#include "lua_function/tolua_ext.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"


/* Exported function */
TOLUA_API int  tolua_game_assets_open (lua_State* tolua_S);

#include "assets/GameAssetsManagerEvent.h"
#include "assets/GameAssetsManagerEventListener.h"
#include "assets/GameAssetsManager.h"
#include "assets/GameManifest.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"GameManifest");
 tolua_usertype(tolua_S,"GameManifestAsset");
 
 tolua_usertype(tolua_S,"cc.EventCustom");
 tolua_usertype(tolua_S,"GameAssetsManager");
 tolua_usertype(tolua_S,"cc.Ref");
 tolua_usertype(tolua_S,"GameManifest::AssetDiff");
 tolua_usertype(tolua_S,"GameAssetsManagerEvent");
 tolua_usertype(tolua_S,"cc.EventListenerCustom");
 tolua_usertype(tolua_S,"GameAssetsManagerEventListener");
}

/* method: getEventCode of class  GameAssetsManagerEvent */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManagerEvent_getEventCode00
static int tolua_game_assets_GameAssetsManagerEvent_getEventCode00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameAssetsManagerEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameAssetsManagerEvent* self = (const GameAssetsManagerEvent*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEventCode'", NULL);
#endif
  {
   GameAssetsManagerEvent::EventCode tolua_ret = (GameAssetsManagerEvent::EventCode)  self->getEventCode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEventCode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCURLECode of class  GameAssetsManagerEvent */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManagerEvent_getCURLECode00
static int tolua_game_assets_GameAssetsManagerEvent_getCURLECode00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameAssetsManagerEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameAssetsManagerEvent* self = (const GameAssetsManagerEvent*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCURLECode'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getCURLECode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCURLECode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCURLMCode of class  GameAssetsManagerEvent */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManagerEvent_getCURLMCode00
static int tolua_game_assets_GameAssetsManagerEvent_getCURLMCode00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameAssetsManagerEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameAssetsManagerEvent* self = (const GameAssetsManagerEvent*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCURLMCode'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getCURLMCode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCURLMCode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMessage of class  GameAssetsManagerEvent */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManagerEvent_getMessage00
static int tolua_game_assets_GameAssetsManagerEvent_getMessage00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameAssetsManagerEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameAssetsManagerEvent* self = (const GameAssetsManagerEvent*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMessage'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getMessage();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAssetId of class  GameAssetsManagerEvent */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManagerEvent_getAssetId00
static int tolua_game_assets_GameAssetsManagerEvent_getAssetId00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameAssetsManagerEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameAssetsManagerEvent* self = (const GameAssetsManagerEvent*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAssetId'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getAssetId();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAssetId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getGameAssetsManager of class  GameAssetsManagerEvent */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManagerEvent_getGameAssetsManager00
static int tolua_game_assets_GameAssetsManagerEvent_getGameAssetsManager00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameAssetsManagerEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameAssetsManagerEvent* self = (const GameAssetsManagerEvent*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getGameAssetsManager'", NULL);
#endif
  {
   GameAssetsManager* tolua_ret = (GameAssetsManager*)  self->getGameAssetsManager();
    int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
    tolua_ext_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"GameAssetsManager");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getGameAssetsManager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPercent of class  GameAssetsManagerEvent */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManagerEvent_getPercent00
static int tolua_game_assets_GameAssetsManagerEvent_getPercent00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameAssetsManagerEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameAssetsManagerEvent* self = (const GameAssetsManagerEvent*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPercent'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getPercent();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPercent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPercentByFile of class  GameAssetsManagerEvent */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManagerEvent_getPercentByFile00
static int tolua_game_assets_GameAssetsManagerEvent_getPercentByFile00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameAssetsManagerEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameAssetsManagerEvent* self = (const GameAssetsManagerEvent*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPercentByFile'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getPercentByFile();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPercentByFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  GameAssetsManagerEventListener */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManagerEventListener_create00
static int tolua_game_assets_GameAssetsManagerEventListener_create00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameAssetsManagerEventListener",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameAssetsManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_ext_check_isfunction(tolua_S,3,"LuaFunction",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAssetsManager* gameAssetsManager = ((GameAssetsManager*)  tolua_tousertype(tolua_S,2,0));
  LuaFunction handle = (  LuaFunction(tolua_S,3,0));
  {
   GameAssetsManagerEventListener* tolua_ret = (GameAssetsManagerEventListener*)  GameAssetsManagerEventListener::create(gameAssetsManager,handle);
    int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
    tolua_ext_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"GameAssetsManagerEventListener");
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

/* method: create of class  GameAssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManager_create00
static int tolua_game_assets_GameAssetsManager_create00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameAssetsManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string manifestUrl = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string storagePath = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string platformName = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  {
   GameAssetsManager* tolua_ret = (GameAssetsManager*)  GameAssetsManager::create(manifestUrl,storagePath,platformName);
    int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
    tolua_ext_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"GameAssetsManager");
   tolua_pushcppstring(tolua_S,(const char*)manifestUrl);
   tolua_pushcppstring(tolua_S,(const char*)storagePath);
   tolua_pushcppstring(tolua_S,(const char*)platformName);
  }
 }
 return 4;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkUpdate of class  GameAssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManager_checkUpdate00
static int tolua_game_assets_GameAssetsManager_checkUpdate00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAssetsManager* self = (GameAssetsManager*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkUpdate'", NULL);
#endif
  {
   self->checkUpdate();
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  GameAssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManager_update00
static int tolua_game_assets_GameAssetsManager_update00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAssetsManager* self = (GameAssetsManager*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update();
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: continueUpdate of class  GameAssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManager_continueUpdate00
static int tolua_game_assets_GameAssetsManager_continueUpdate00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAssetsManager* self = (GameAssetsManager*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'continueUpdate'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->continueUpdate();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'continueUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: downloadFailedAssets of class  GameAssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManager_downloadFailedAssets00
static int tolua_game_assets_GameAssetsManager_downloadFailedAssets00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAssetsManager* self = (GameAssetsManager*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'downloadFailedAssets'", NULL);
#endif
  {
   self->downloadFailedAssets();
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'downloadFailedAssets'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getState of class  GameAssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManager_getState00
static int tolua_game_assets_GameAssetsManager_getState00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAssetsManager* self = (GameAssetsManager*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getState'", NULL);
#endif
  {
   GameAssetsManager::State tolua_ret = (GameAssetsManager::State)  self->getState();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStoragePath of class  GameAssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManager_getStoragePath00
static int tolua_game_assets_GameAssetsManager_getStoragePath00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAssetsManager* self = (GameAssetsManager*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStoragePath'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getStoragePath();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStoragePath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLocalManifest of class  GameAssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManager_getLocalManifest00
static int tolua_game_assets_GameAssetsManager_getLocalManifest00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAssetsManager* self = (GameAssetsManager*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLocalManifest'", NULL);
#endif
  {
   GameManifest* tolua_ret = (GameManifest*)  self->getLocalManifest();
    int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
    tolua_ext_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"GameManifest");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLocalManifest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRemoteManifest of class  GameAssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManager_getRemoteManifest00
static int tolua_game_assets_GameAssetsManager_getRemoteManifest00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAssetsManager* self = (GameAssetsManager*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRemoteManifest'", NULL);
#endif
  {
   GameManifest* tolua_ret = (GameManifest*)  self->getRemoteManifest();
    int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
    tolua_ext_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"GameManifest");
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRemoteManifest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaxConcurrentTask of class  GameAssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManager_getMaxConcurrentTask00
static int tolua_game_assets_GameAssetsManager_getMaxConcurrentTask00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAssetsManager* self = (GameAssetsManager*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaxConcurrentTask'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getMaxConcurrentTask();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaxConcurrentTask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMaxConcurrentTask of class  GameAssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManager_setMaxConcurrentTask00
static int tolua_game_assets_GameAssetsManager_setMaxConcurrentTask00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAssetsManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAssetsManager* self = (GameAssetsManager*)  tolua_tousertype(tolua_S,1,0);
  int max = ((int)  tolua_tonumber(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMaxConcurrentTask'", NULL);
#endif
  {
   self->setMaxConcurrentTask(max);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMaxConcurrentTask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVersionCompareLuaHandle of class  GameAssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManager_setVersionCompareLuaHandle00
static int tolua_game_assets_GameAssetsManager_setVersionCompareLuaHandle00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAssetsManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_isfunction(tolua_S,2,"LuaFunction",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAssetsManager* self = (GameAssetsManager*)  tolua_tousertype(tolua_S,1,0);
  LuaFunction handle = (  LuaFunction(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVersionCompareLuaHandle'", NULL);
#endif
  {
   self->setVersionCompareLuaHandle(handle);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVersionCompareLuaHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVerifyLuaCallback of class  GameAssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManager_setVerifyLuaCallback00
static int tolua_game_assets_GameAssetsManager_setVerifyLuaCallback00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAssetsManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_isfunction(tolua_S,2,"LuaFunction",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAssetsManager* self = (GameAssetsManager*)  tolua_tousertype(tolua_S,1,0);
  LuaFunction handle = (  LuaFunction(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVerifyLuaCallback'", NULL);
#endif
  {
   self->setVerifyLuaCallback(handle);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVerifyLuaCallback'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUpdateDownloadFilePercentLuaCallback of class  GameAssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameAssetsManager_setUpdateDownloadFilePercentLuaCallback00
static int tolua_game_assets_GameAssetsManager_setUpdateDownloadFilePercentLuaCallback00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAssetsManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_ext_check_isfunction(tolua_S,2,"LuaFunction",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAssetsManager* self = (GameAssetsManager*)  tolua_tousertype(tolua_S,1,0);
  LuaFunction handle = (  LuaFunction(tolua_S,2,0));
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUpdateDownloadFilePercentLuaCallback'", NULL);
#endif
  {
   self->setUpdateDownloadFilePercentLuaCallback(handle);
  }
 }
 return 0;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setUpdateDownloadFilePercentLuaCallback'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: md5 of class  GameManifestAsset */
#ifndef TOLUA_DISABLE_tolua_get_GameManifestAsset_md5
static int tolua_get_GameManifestAsset_md5(lua_State* tolua_S)
{
  GameManifestAsset* self = (GameManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'md5'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->md5);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: md5 of class  GameManifestAsset */
#ifndef TOLUA_DISABLE_tolua_set_GameManifestAsset_md5
static int tolua_set_GameManifestAsset_md5(lua_State* tolua_S)
{
  GameManifestAsset* self = (GameManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'md5'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->md5 = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: path of class  GameManifestAsset */
#ifndef TOLUA_DISABLE_tolua_get_GameManifestAsset_path
static int tolua_get_GameManifestAsset_path(lua_State* tolua_S)
{
  GameManifestAsset* self = (GameManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'path'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->path);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: path of class  GameManifestAsset */
#ifndef TOLUA_DISABLE_tolua_set_GameManifestAsset_path
static int tolua_set_GameManifestAsset_path(lua_State* tolua_S)
{
  GameManifestAsset* self = (GameManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'path'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->path = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: compressed of class  GameManifestAsset */
#ifndef TOLUA_DISABLE_tolua_get_GameManifestAsset_compressed
static int tolua_get_GameManifestAsset_compressed(lua_State* tolua_S)
{
  GameManifestAsset* self = (GameManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'compressed'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->compressed);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: compressed of class  GameManifestAsset */
#ifndef TOLUA_DISABLE_tolua_set_GameManifestAsset_compressed
static int tolua_set_GameManifestAsset_compressed(lua_State* tolua_S)
{
  GameManifestAsset* self = (GameManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'compressed'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->compressed = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: size of class  GameManifestAsset */
#ifndef TOLUA_DISABLE_tolua_get_GameManifestAsset_size
static int tolua_get_GameManifestAsset_size(lua_State* tolua_S)
{
  GameManifestAsset* self = (GameManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'size'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->size);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: size of class  GameManifestAsset */
#ifndef TOLUA_DISABLE_tolua_set_GameManifestAsset_size
static int tolua_set_GameManifestAsset_size(lua_State* tolua_S)
{
  GameManifestAsset* self = (GameManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'size'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->size = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: downloadState of class  GameManifestAsset */
#ifndef TOLUA_DISABLE_tolua_get_GameManifestAsset_downloadState
static int tolua_get_GameManifestAsset_downloadState(lua_State* tolua_S)
{
  GameManifestAsset* self = (GameManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'downloadState'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->downloadState);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: downloadState of class  GameManifestAsset */
#ifndef TOLUA_DISABLE_tolua_set_GameManifestAsset_downloadState
static int tolua_set_GameManifestAsset_downloadState(lua_State* tolua_S)
{
  GameManifestAsset* self = (GameManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'downloadState'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->downloadState = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fileSize of class  GameManifestAsset */
#ifndef TOLUA_DISABLE_tolua_get_GameManifestAsset_unsigned_fileSize
static int tolua_get_GameManifestAsset_unsigned_fileSize(lua_State* tolua_S)
{
  GameManifestAsset* self = (GameManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fileSize'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->fileSize);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fileSize of class  GameManifestAsset */
#ifndef TOLUA_DISABLE_tolua_set_GameManifestAsset_unsigned_fileSize
static int tolua_set_GameManifestAsset_unsigned_fileSize(lua_State* tolua_S)
{
  GameManifestAsset* self = (GameManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fileSize'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->fileSize = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: asset of class  AssetDiff */
#ifndef TOLUA_DISABLE_tolua_get_GameManifest__AssetDiff_asset
static int tolua_get_GameManifest__AssetDiff_asset(lua_State* tolua_S)
{
  GameManifest::AssetDiff* self = (GameManifest::AssetDiff*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'asset'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->asset,"GameManifestAsset");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: asset of class  AssetDiff */
#ifndef TOLUA_DISABLE_tolua_set_GameManifest__AssetDiff_asset
static int tolua_set_GameManifest__AssetDiff_asset(lua_State* tolua_S)
{
  GameManifest::AssetDiff* self = (GameManifest::AssetDiff*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'asset'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GameManifestAsset",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->asset = *((  GameManifestAsset*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  AssetDiff */
#ifndef TOLUA_DISABLE_tolua_get_GameManifest__AssetDiff_type
static int tolua_get_GameManifest__AssetDiff_type(lua_State* tolua_S)
{
  GameManifest::AssetDiff* self = (GameManifest::AssetDiff*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->type);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  AssetDiff */
#ifndef TOLUA_DISABLE_tolua_set_GameManifest__AssetDiff_type
static int tolua_set_GameManifest__AssetDiff_type(lua_State* tolua_S)
{
  GameManifest::AssetDiff* self = (GameManifest::AssetDiff*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->type = ((GameManifest::DiffType) (int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: isVersionLoaded of class  GameManifest */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameManifest_isVersionLoaded00
static int tolua_game_assets_GameManifest_isVersionLoaded00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameManifest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameManifest* self = (GameManifest*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isVersionLoaded'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isVersionLoaded();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isVersionLoaded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isLoaded of class  GameManifest */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameManifest_isLoaded00
static int tolua_game_assets_GameManifest_isLoaded00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameManifest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameManifest* self = (GameManifest*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isLoaded'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isLoaded();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isLoaded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStrongUpdateURL of class  GameManifest */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameManifest_getStrongUpdateURL00
static int tolua_game_assets_GameManifest_getStrongUpdateURL00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameManifest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameManifest* self = (GameManifest*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStrongUpdateURL'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->getStrongUpdateURL();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStrongUpdateURL'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getUpdateDescription of class  GameManifest */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameManifest_getUpdateDescription00
static int tolua_game_assets_GameManifest_getUpdateDescription00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameManifest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameManifest* self = (GameManifest*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUpdateDescription'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->getUpdateDescription();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUpdateDescription'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStrongUpdateDescription of class  GameManifest */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameManifest_getStrongUpdateDescription00
static int tolua_game_assets_GameManifest_getStrongUpdateDescription00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameManifest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameManifest* self = (GameManifest*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStrongUpdateDescription'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->getStrongUpdateDescription();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStrongUpdateDescription'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRestartLevel of class  GameManifest */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameManifest_getRestartLevel00
static int tolua_game_assets_GameManifest_getRestartLevel00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameManifest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameManifest* self = (GameManifest*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRestartLevel'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getRestartLevel();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRestartLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPackageUrl of class  GameManifest */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameManifest_getPackageUrl00
static int tolua_game_assets_GameManifest_getPackageUrl00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameManifest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameManifest* self = (GameManifest*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPackageUrl'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->getPackageUrl();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPackageUrl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getManifestFileUrl of class  GameManifest */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameManifest_getManifestFileUrl00
static int tolua_game_assets_GameManifest_getManifestFileUrl00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameManifest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameManifest* self = (GameManifest*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getManifestFileUrl'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->getManifestFileUrl();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getManifestFileUrl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVersionFileUrl of class  GameManifest */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameManifest_getVersionFileUrl00
static int tolua_game_assets_GameManifest_getVersionFileUrl00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameManifest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameManifest* self = (GameManifest*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVersionFileUrl'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->getVersionFileUrl();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVersionFileUrl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVersion of class  GameManifest */
#ifndef TOLUA_DISABLE_tolua_game_assets_GameManifest_getVersion00
static int tolua_game_assets_GameManifest_getVersion00(lua_State* tolua_S)
{
#if (COCOS2D_DEBUG == 1)
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameManifest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameManifest* self = (GameManifest*)  tolua_tousertype(tolua_S,1,0);
#if (COCOS2D_DEBUG == 1)
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVersion'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->getVersion();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if (COCOS2D_DEBUG == 1)
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVersion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_game_assets_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"GameAssetsManagerEvent","GameAssetsManagerEvent","cc.EventCustom",NULL);
  tolua_beginmodule(tolua_S,"GameAssetsManagerEvent");
   tolua_constant(tolua_S,"ERROR_NO_LOCAL_MANIFEST",GameAssetsManagerEvent::ERROR_NO_LOCAL_MANIFEST);
   tolua_constant(tolua_S,"ERROR_DOWNLOAD_MANIFEST",GameAssetsManagerEvent::ERROR_DOWNLOAD_MANIFEST);
   tolua_constant(tolua_S,"ERROR_PARSE_MANIFEST",GameAssetsManagerEvent::ERROR_PARSE_MANIFEST);
   tolua_constant(tolua_S,"NEW_VERSION_FOUND",GameAssetsManagerEvent::NEW_VERSION_FOUND);
   tolua_constant(tolua_S,"ALREADY_UP_TO_DATE",GameAssetsManagerEvent::ALREADY_UP_TO_DATE);
   tolua_constant(tolua_S,"UPDATE_PROGRESSION",GameAssetsManagerEvent::UPDATE_PROGRESSION);
   tolua_constant(tolua_S,"ASSET_UPDATED",GameAssetsManagerEvent::ASSET_UPDATED);
   tolua_constant(tolua_S,"ERROR_UPDATING",GameAssetsManagerEvent::ERROR_UPDATING);
   tolua_constant(tolua_S,"UPDATE_FINISHED",GameAssetsManagerEvent::UPDATE_FINISHED);
   tolua_constant(tolua_S,"UPDATE_FAILED",GameAssetsManagerEvent::UPDATE_FAILED);
   tolua_constant(tolua_S,"ERROR_DECOMPRESS",GameAssetsManagerEvent::ERROR_DECOMPRESS);
   tolua_constant(tolua_S,"NEED_STRONG_UPDATE",GameAssetsManagerEvent::NEED_STRONG_UPDATE);
   tolua_constant(tolua_S,"UPDATE_FILE_SIZE",GameAssetsManagerEvent::UPDATE_FILE_SIZE);
   tolua_function(tolua_S,"getEventCode",tolua_game_assets_GameAssetsManagerEvent_getEventCode00);
   tolua_function(tolua_S,"getCURLECode",tolua_game_assets_GameAssetsManagerEvent_getCURLECode00);
   tolua_function(tolua_S,"getCURLMCode",tolua_game_assets_GameAssetsManagerEvent_getCURLMCode00);
   tolua_function(tolua_S,"getMessage",tolua_game_assets_GameAssetsManagerEvent_getMessage00);
   tolua_function(tolua_S,"getAssetId",tolua_game_assets_GameAssetsManagerEvent_getAssetId00);
   tolua_function(tolua_S,"getGameAssetsManager",tolua_game_assets_GameAssetsManagerEvent_getGameAssetsManager00);
   tolua_function(tolua_S,"getPercent",tolua_game_assets_GameAssetsManagerEvent_getPercent00);
   tolua_function(tolua_S,"getPercentByFile",tolua_game_assets_GameAssetsManagerEvent_getPercentByFile00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GameAssetsManagerEventListener","GameAssetsManagerEventListener","cc.EventListenerCustom",NULL);
  tolua_beginmodule(tolua_S,"GameAssetsManagerEventListener");
   tolua_function(tolua_S,"create",tolua_game_assets_GameAssetsManagerEventListener_create00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GameAssetsManager","GameAssetsManager","cc.Ref",NULL);
  tolua_beginmodule(tolua_S,"GameAssetsManager");
   tolua_constant(tolua_S,"UNCHECKED",GameAssetsManager::UNCHECKED);
   tolua_constant(tolua_S,"PREDOWNLOAD_VERSION",GameAssetsManager::PREDOWNLOAD_VERSION);
   tolua_constant(tolua_S,"DOWNLOADING_VERSION",GameAssetsManager::DOWNLOADING_VERSION);
   tolua_constant(tolua_S,"VERSION_LOADED",GameAssetsManager::VERSION_LOADED);
   tolua_constant(tolua_S,"PREDOWNLOAD_MANIFEST",GameAssetsManager::PREDOWNLOAD_MANIFEST);
   tolua_constant(tolua_S,"DOWNLOADING_MANIFEST",GameAssetsManager::DOWNLOADING_MANIFEST);
   tolua_constant(tolua_S,"MANIFEST_LOADED",GameAssetsManager::MANIFEST_LOADED);
   tolua_constant(tolua_S,"NEED_UPDATE",GameAssetsManager::NEED_UPDATE);
   tolua_constant(tolua_S,"UPDATING",GameAssetsManager::UPDATING);
   tolua_constant(tolua_S,"UNZIPPING",GameAssetsManager::UNZIPPING);
   tolua_constant(tolua_S,"UP_TO_DATE",GameAssetsManager::UP_TO_DATE);
   tolua_constant(tolua_S,"FAIL_TO_UPDATE",GameAssetsManager::FAIL_TO_UPDATE);
   tolua_function(tolua_S,"create",tolua_game_assets_GameAssetsManager_create00);
   tolua_function(tolua_S,"checkUpdate",tolua_game_assets_GameAssetsManager_checkUpdate00);
   tolua_function(tolua_S,"update",tolua_game_assets_GameAssetsManager_update00);
   tolua_function(tolua_S,"continueUpdate",tolua_game_assets_GameAssetsManager_continueUpdate00);
   tolua_function(tolua_S,"downloadFailedAssets",tolua_game_assets_GameAssetsManager_downloadFailedAssets00);
   tolua_function(tolua_S,"getState",tolua_game_assets_GameAssetsManager_getState00);
   tolua_function(tolua_S,"getStoragePath",tolua_game_assets_GameAssetsManager_getStoragePath00);
   tolua_function(tolua_S,"getLocalManifest",tolua_game_assets_GameAssetsManager_getLocalManifest00);
   tolua_function(tolua_S,"getRemoteManifest",tolua_game_assets_GameAssetsManager_getRemoteManifest00);
   tolua_function(tolua_S,"getMaxConcurrentTask",tolua_game_assets_GameAssetsManager_getMaxConcurrentTask00);
   tolua_function(tolua_S,"setMaxConcurrentTask",tolua_game_assets_GameAssetsManager_setMaxConcurrentTask00);
   tolua_function(tolua_S,"setVersionCompareLuaHandle",tolua_game_assets_GameAssetsManager_setVersionCompareLuaHandle00);
   tolua_function(tolua_S,"setVerifyLuaCallback",tolua_game_assets_GameAssetsManager_setVerifyLuaCallback00);
   tolua_function(tolua_S,"setUpdateDownloadFilePercentLuaCallback",tolua_game_assets_GameAssetsManager_setUpdateDownloadFilePercentLuaCallback00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GameManifestAsset","GameManifestAsset","",NULL);
  tolua_beginmodule(tolua_S,"GameManifestAsset");
   tolua_variable(tolua_S,"md5",tolua_get_GameManifestAsset_md5,tolua_set_GameManifestAsset_md5);
   tolua_variable(tolua_S,"path",tolua_get_GameManifestAsset_path,tolua_set_GameManifestAsset_path);
   tolua_variable(tolua_S,"compressed",tolua_get_GameManifestAsset_compressed,tolua_set_GameManifestAsset_compressed);
   tolua_variable(tolua_S,"size",tolua_get_GameManifestAsset_size,tolua_set_GameManifestAsset_size);
   tolua_variable(tolua_S,"downloadState",tolua_get_GameManifestAsset_downloadState,tolua_set_GameManifestAsset_downloadState);
   tolua_variable(tolua_S,"fileSize",tolua_get_GameManifestAsset_unsigned_fileSize,tolua_set_GameManifestAsset_unsigned_fileSize);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GameManifest","GameManifest","cc.Ref",NULL);
  tolua_beginmodule(tolua_S,"GameManifest");
   tolua_constant(tolua_S,"ADDED",GameManifest::ADDED);
   tolua_constant(tolua_S,"DELETED",GameManifest::DELETED);
   tolua_constant(tolua_S,"MODIFIED",GameManifest::MODIFIED);
   tolua_constant(tolua_S,"UNSTARTED",GameManifest::UNSTARTED);
   tolua_constant(tolua_S,"DOWNLOADING",GameManifest::DOWNLOADING);
   tolua_constant(tolua_S,"SUCCESSED",GameManifest::SUCCESSED);
   tolua_constant(tolua_S,"UNMARKED",GameManifest::UNMARKED);
   tolua_cclass(tolua_S,"AssetDiff","GameManifest::AssetDiff","",NULL);
   tolua_beginmodule(tolua_S,"AssetDiff");
    tolua_variable(tolua_S,"asset",tolua_get_GameManifest__AssetDiff_asset,tolua_set_GameManifest__AssetDiff_asset);
    tolua_variable(tolua_S,"type",tolua_get_GameManifest__AssetDiff_type,tolua_set_GameManifest__AssetDiff_type);
   tolua_endmodule(tolua_S);
   tolua_function(tolua_S,"isVersionLoaded",tolua_game_assets_GameManifest_isVersionLoaded00);
   tolua_function(tolua_S,"isLoaded",tolua_game_assets_GameManifest_isLoaded00);
   tolua_function(tolua_S,"getStrongUpdateURL",tolua_game_assets_GameManifest_getStrongUpdateURL00);
   tolua_function(tolua_S,"getUpdateDescription",tolua_game_assets_GameManifest_getUpdateDescription00);
   tolua_function(tolua_S,"getStrongUpdateDescription",tolua_game_assets_GameManifest_getStrongUpdateDescription00);
   tolua_function(tolua_S,"getRestartLevel",tolua_game_assets_GameManifest_getRestartLevel00);
   tolua_function(tolua_S,"getPackageUrl",tolua_game_assets_GameManifest_getPackageUrl00);
   tolua_function(tolua_S,"getManifestFileUrl",tolua_game_assets_GameManifest_getManifestFileUrl00);
   tolua_function(tolua_S,"getVersionFileUrl",tolua_game_assets_GameManifest_getVersionFileUrl00);
   tolua_function(tolua_S,"getVersion",tolua_game_assets_GameManifest_getVersion00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_game_assets (lua_State* tolua_S) {
 return tolua_game_assets_open(tolua_S);
};
#endif

