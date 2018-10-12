/*
** Lua binding: dubase
** Generated automatically by tolua++-1.0.92 on 10/11/18 23:02:17.
*/

#include "tolua_fix.h"
#include "tolua++.h"
#include <string>


/* Exported function */
TOLUA_API int  tolua_dubase_open (lua_State* tolua_S);

#include "DUObject.h"
#include "DUScheduler.h"
#include "net/DUServer.h"
#include "DUGame.h"
#include "TestOBJ.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_DUObject (lua_State* tolua_S)
{
 DUObject* self = (DUObject*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_TestOBJ (lua_State* tolua_S)
{
 TestOBJ* self = (TestOBJ*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_DUServer (lua_State* tolua_S)
{
 DUServer* self = (DUServer*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"DUScheduler");
 tolua_usertype(tolua_S,"TestOBJ");
 
 tolua_usertype(tolua_S,"DUGame");
 tolua_usertype(tolua_S,"DUObject");
 tolua_usertype(tolua_S,"Session");
 tolua_usertype(tolua_S,"DUServer");
}

/* method: new of class  DUObject */
#ifndef TOLUA_DISABLE_tolua_dubase_DUObject_new00
static int tolua_dubase_DUObject_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DUObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DUObject* tolua_ret = (DUObject*)  Mtolua_new((DUObject)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DUObject");
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

/* method: new_local of class  DUObject */
#ifndef TOLUA_DISABLE_tolua_dubase_DUObject_new00_local
static int tolua_dubase_DUObject_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DUObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DUObject* tolua_ret = (DUObject*)  Mtolua_new((DUObject)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DUObject");
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

/* method: delete of class  DUObject */
#ifndef TOLUA_DISABLE_tolua_dubase_DUObject_delete00
static int tolua_dubase_DUObject_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUObject* self = (DUObject*)  tolua_tousertype(tolua_S,1,0);
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

/* method: retain of class  DUObject */
#ifndef TOLUA_DISABLE_tolua_dubase_DUObject_retain00
static int tolua_dubase_DUObject_retain00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUObject* self = (DUObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'retain'", NULL);
#endif
  {
   DUObject* tolua_ret = (DUObject*)  self->retain();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DUObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'retain'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: release of class  DUObject */
#ifndef TOLUA_DISABLE_tolua_dubase_DUObject_release00
static int tolua_dubase_DUObject_release00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUObject* self = (DUObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'release'", NULL);
#endif
  {
   self->release();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'release'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: printCount of class  DUObject */
#ifndef TOLUA_DISABLE_tolua_dubase_DUObject_printCount00
static int tolua_dubase_DUObject_printCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUObject* self = (DUObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'printCount'", NULL);
#endif
  {
   self->printCount();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'printCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  DUScheduler */
#ifndef TOLUA_DISABLE_tolua_dubase_DUScheduler_getInstance00
static int tolua_dubase_DUScheduler_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DUScheduler",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DUScheduler* tolua_ret = (DUScheduler*)  DUScheduler::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DUScheduler");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pauseSchedule of class  DUScheduler */
#ifndef TOLUA_DISABLE_tolua_dubase_DUScheduler_pauseSchedule00
static int tolua_dubase_DUScheduler_pauseSchedule00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUScheduler",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"DUObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUScheduler* self = (DUScheduler*)  tolua_tousertype(tolua_S,1,0);
  DUObject* pTarget = ((DUObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pauseSchedule'", NULL);
#endif
  {
   self->pauseSchedule(pTarget);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pauseSchedule'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pauseSchedule of class  DUScheduler */
#ifndef TOLUA_DISABLE_tolua_dubase_DUScheduler_pauseSchedule01
static int tolua_dubase_DUScheduler_pauseSchedule01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUScheduler",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  DUScheduler* self = (DUScheduler*)  tolua_tousertype(tolua_S,1,0);
  void* pTarget = ((void*)  tolua_touserdata(tolua_S,2,0));
  const std::string key = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pauseSchedule'", NULL);
#endif
  {
   self->pauseSchedule(pTarget,key);
   tolua_pushcppstring(tolua_S,(const char*)key);
  }
 }
 return 1;
tolua_lerror:
 return tolua_dubase_DUScheduler_pauseSchedule00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: pauseSchedule of class  DUScheduler */
#ifndef TOLUA_DISABLE_tolua_dubase_DUScheduler_pauseSchedule02
static int tolua_dubase_DUScheduler_pauseSchedule02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUScheduler",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  DUScheduler* self = (DUScheduler*)  tolua_tousertype(tolua_S,1,0);
  const std::string key = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pauseSchedule'", NULL);
#endif
  {
   self->pauseSchedule(key);
   tolua_pushcppstring(tolua_S,(const char*)key);
  }
 }
 return 1;
tolua_lerror:
 return tolua_dubase_DUScheduler_pauseSchedule01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: resumeSchedule of class  DUScheduler */
#ifndef TOLUA_DISABLE_tolua_dubase_DUScheduler_resumeSchedule00
static int tolua_dubase_DUScheduler_resumeSchedule00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUScheduler",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"DUObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUScheduler* self = (DUScheduler*)  tolua_tousertype(tolua_S,1,0);
  DUObject* pTarget = ((DUObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resumeSchedule'", NULL);
#endif
  {
   self->resumeSchedule(pTarget);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resumeSchedule'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resumeSchedule of class  DUScheduler */
#ifndef TOLUA_DISABLE_tolua_dubase_DUScheduler_resumeSchedule01
static int tolua_dubase_DUScheduler_resumeSchedule01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUScheduler",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  DUScheduler* self = (DUScheduler*)  tolua_tousertype(tolua_S,1,0);
  void* pTarget = ((void*)  tolua_touserdata(tolua_S,2,0));
  const std::string key = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resumeSchedule'", NULL);
#endif
  {
   self->resumeSchedule(pTarget,key);
   tolua_pushcppstring(tolua_S,(const char*)key);
  }
 }
 return 1;
tolua_lerror:
 return tolua_dubase_DUScheduler_resumeSchedule00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: resumeSchedule of class  DUScheduler */
#ifndef TOLUA_DISABLE_tolua_dubase_DUScheduler_resumeSchedule02
static int tolua_dubase_DUScheduler_resumeSchedule02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUScheduler",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  DUScheduler* self = (DUScheduler*)  tolua_tousertype(tolua_S,1,0);
  const std::string key = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resumeSchedule'", NULL);
#endif
  {
   self->resumeSchedule(key);
   tolua_pushcppstring(tolua_S,(const char*)key);
  }
 }
 return 1;
tolua_lerror:
 return tolua_dubase_DUScheduler_resumeSchedule01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: unScheduleByObject of class  DUScheduler */
#ifndef TOLUA_DISABLE_tolua_dubase_DUScheduler_unScheduleByObject00
static int tolua_dubase_DUScheduler_unScheduleByObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUScheduler",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"DUObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUScheduler* self = (DUScheduler*)  tolua_tousertype(tolua_S,1,0);
  DUObject* pTarget = ((DUObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unScheduleByObject'", NULL);
#endif
  {
   self->unScheduleByObject(pTarget);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unScheduleByObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unScheduleSeletorByKey of class  DUScheduler */
#ifndef TOLUA_DISABLE_tolua_dubase_DUScheduler_unScheduleSeletorByKey00
static int tolua_dubase_DUScheduler_unScheduleSeletorByKey00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUScheduler",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUScheduler* self = (DUScheduler*)  tolua_tousertype(tolua_S,1,0);
  void* pTarget = ((void*)  tolua_touserdata(tolua_S,2,0));
  const std::string key = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unScheduleSeletorByKey'", NULL);
#endif
  {
   self->unScheduleSeletorByKey(pTarget,key);
   tolua_pushcppstring(tolua_S,(const char*)key);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unScheduleSeletorByKey'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unScheduleSeletorByKey of class  DUScheduler */
#ifndef TOLUA_DISABLE_tolua_dubase_DUScheduler_unScheduleSeletorByKey01
static int tolua_dubase_DUScheduler_unScheduleSeletorByKey01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUScheduler",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  DUScheduler* self = (DUScheduler*)  tolua_tousertype(tolua_S,1,0);
  const std::string key = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unScheduleSeletorByKey'", NULL);
#endif
  {
   self->unScheduleSeletorByKey(key);
   tolua_pushcppstring(tolua_S,(const char*)key);
  }
 }
 return 1;
tolua_lerror:
 return tolua_dubase_DUScheduler_unScheduleSeletorByKey00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: unScheduleSeletorByObject of class  DUScheduler */
#ifndef TOLUA_DISABLE_tolua_dubase_DUScheduler_unScheduleSeletorByObject00
static int tolua_dubase_DUScheduler_unScheduleSeletorByObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUScheduler",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUScheduler* self = (DUScheduler*)  tolua_tousertype(tolua_S,1,0);
  void* pTarget = ((void*)  tolua_touserdata(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unScheduleSeletorByObject'", NULL);
#endif
  {
   self->unScheduleSeletorByObject(pTarget);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unScheduleSeletorByObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unScheduleAll of class  DUScheduler */
#ifndef TOLUA_DISABLE_tolua_dubase_DUScheduler_unScheduleAll00
static int tolua_dubase_DUScheduler_unScheduleAll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUScheduler",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUScheduler* self = (DUScheduler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unScheduleAll'", NULL);
#endif
  {
   self->unScheduleAll();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unScheduleAll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerScripSchedule of class  DUScheduler */
#ifndef TOLUA_DISABLE_tolua_dubase_DUScheduler_registerScripSchedule00
static int tolua_dubase_DUScheduler_registerScripSchedule00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUScheduler",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LuaFunction",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUScheduler* self = (DUScheduler*)  tolua_tousertype(tolua_S,1,0);
  LuaFunction func = (  LuaFunction(tolua_S,2,0));
  float interval = ((float)  tolua_tonumber(tolua_S,3,0));
  bool paused = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScripSchedule'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->registerScripSchedule(func,interval,paused);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerScripSchedule'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unRegisterScripSchedule of class  DUScheduler */
#ifndef TOLUA_DISABLE_tolua_dubase_DUScheduler_unRegisterScripSchedule00
static int tolua_dubase_DUScheduler_unRegisterScripSchedule00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUScheduler",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUScheduler* self = (DUScheduler*)  tolua_tousertype(tolua_S,1,0);
  const std::string key = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unRegisterScripSchedule'", NULL);
#endif
  {
   self->unRegisterScripSchedule(key);
   tolua_pushcppstring(tolua_S,(const char*)key);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unRegisterScripSchedule'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DUServer */
#ifndef TOLUA_DISABLE_tolua_dubase_DUServer_new00
static int tolua_dubase_DUServer_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DUServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DUServer* tolua_ret = (DUServer*)  Mtolua_new((DUServer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DUServer");
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

/* method: new_local of class  DUServer */
#ifndef TOLUA_DISABLE_tolua_dubase_DUServer_new00_local
static int tolua_dubase_DUServer_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DUServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DUServer* tolua_ret = (DUServer*)  Mtolua_new((DUServer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DUServer");
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

/* method: delete of class  DUServer */
#ifndef TOLUA_DISABLE_tolua_dubase_DUServer_delete00
static int tolua_dubase_DUServer_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUServer* self = (DUServer*)  tolua_tousertype(tolua_S,1,0);
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

/* method: startServer of class  DUServer */
#ifndef TOLUA_DISABLE_tolua_dubase_DUServer_startServer00
static int tolua_dubase_DUServer_startServer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUServer",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUServer* self = (DUServer*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int port = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  bool isIPV6 = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'startServer'", NULL);
#endif
  {
   self->startServer(ip,port,isIPV6);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'startServer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopServer of class  DUServer */
#ifndef TOLUA_DISABLE_tolua_dubase_DUServer_stopServer00
static int tolua_dubase_DUServer_stopServer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUServer* self = (DUServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopServer'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->stopServer();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopServer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: send of class  DUServer */
#ifndef TOLUA_DISABLE_tolua_dubase_DUServer_send00
static int tolua_dubase_DUServer_send00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUServer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Session",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUServer* self = (DUServer*)  tolua_tousertype(tolua_S,1,0);
  Session* session = ((Session*)  tolua_tousertype(tolua_S,2,0));
  char* data = ((char*)  tolua_tostring(tolua_S,3,0));
  unsigned int len = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send'", NULL);
#endif
  {
   self->send(session,data,len);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'send'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disconnect of class  DUServer */
#ifndef TOLUA_DISABLE_tolua_dubase_DUServer_disconnect00
static int tolua_dubase_DUServer_disconnect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUServer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Session",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUServer* self = (DUServer*)  tolua_tousertype(tolua_S,1,0);
  Session* session = ((Session*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disconnect'", NULL);
#endif
  {
   self->disconnect(session);
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

/* method: isCloseFinish of class  DUServer */
#ifndef TOLUA_DISABLE_tolua_dubase_DUServer_isCloseFinish00
static int tolua_dubase_DUServer_isCloseFinish00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUServer* self = (DUServer*)  tolua_tousertype(tolua_S,1,0);
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

/* method: registerLuaHandle of class  DUServer */
#ifndef TOLUA_DISABLE_tolua_dubase_DUServer_registerLuaHandle00
static int tolua_dubase_DUServer_registerLuaHandle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUServer",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_isfunction(tolua_S,3,"LuaFunction",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUServer* self = (DUServer*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  LuaFunction handle = (  LuaFunction(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerLuaHandle'", NULL);
#endif
  {
   self->registerLuaHandle(name,handle);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerLuaHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterLuaHandle of class  DUServer */
#ifndef TOLUA_DISABLE_tolua_dubase_DUServer_unregisterLuaHandle00
static int tolua_dubase_DUServer_unregisterLuaHandle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUServer",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUServer* self = (DUServer*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterLuaHandle'", NULL);
#endif
  {
   self->unregisterLuaHandle(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterLuaHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearLuaHandle of class  DUServer */
#ifndef TOLUA_DISABLE_tolua_dubase_DUServer_clearLuaHandle00
static int tolua_dubase_DUServer_clearLuaHandle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUServer* self = (DUServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearLuaHandle'", NULL);
#endif
  {
   self->clearLuaHandle();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearLuaHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  DUGame */
#ifndef TOLUA_DISABLE_tolua_dubase_DUGame_getInstance00
static int tolua_dubase_DUGame_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DUGame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DUGame* tolua_ret = (DUGame*)  DUGame::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DUGame");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destroy of class  DUGame */
#ifndef TOLUA_DISABLE_tolua_dubase_DUGame_destroy00
static int tolua_dubase_DUGame_destroy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DUGame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DUGame::destroy();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInterval of class  DUGame */
#ifndef TOLUA_DISABLE_tolua_dubase_DUGame_setInterval00
static int tolua_dubase_DUGame_setInterval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUGame",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUGame* self = (DUGame*)  tolua_tousertype(tolua_S,1,0);
  float interval = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInterval'", NULL);
#endif
  {
   self->setInterval(interval);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFileExist of class  DUGame */
#ifndef TOLUA_DISABLE_tolua_dubase_DUGame_isFileExist00
static int tolua_dubase_DUGame_isFileExist00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DUGame",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DUGame* self = (DUGame*)  tolua_tousertype(tolua_S,1,0);
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFileExist'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFileExist(filename);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFileExist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  TestOBJ */
#ifndef TOLUA_DISABLE_tolua_dubase_TestOBJ_new00
static int tolua_dubase_TestOBJ_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TestOBJ",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TestOBJ* tolua_ret = (TestOBJ*)  Mtolua_new((TestOBJ)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TestOBJ");
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

/* method: new_local of class  TestOBJ */
#ifndef TOLUA_DISABLE_tolua_dubase_TestOBJ_new00_local
static int tolua_dubase_TestOBJ_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TestOBJ",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TestOBJ* tolua_ret = (TestOBJ*)  Mtolua_new((TestOBJ)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TestOBJ");
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

/* method: delete of class  TestOBJ */
#ifndef TOLUA_DISABLE_tolua_dubase_TestOBJ_delete00
static int tolua_dubase_TestOBJ_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TestOBJ",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TestOBJ* self = (TestOBJ*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Test of class  TestOBJ */
#ifndef TOLUA_DISABLE_tolua_dubase_TestOBJ_Test00
static int tolua_dubase_TestOBJ_Test00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TestOBJ",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TestOBJ* self = (TestOBJ*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Test'", NULL);
#endif
  {
   self->Test();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Test'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_dubase_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"DUObject","DUObject","",tolua_collect_DUObject);
  #else
  tolua_cclass(tolua_S,"DUObject","DUObject","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"DUObject");
   tolua_function(tolua_S,"new",tolua_dubase_DUObject_new00);
   tolua_function(tolua_S,"new_local",tolua_dubase_DUObject_new00_local);
   tolua_function(tolua_S,".call",tolua_dubase_DUObject_new00_local);
   tolua_function(tolua_S,"delete",tolua_dubase_DUObject_delete00);
   tolua_function(tolua_S,"retain",tolua_dubase_DUObject_retain00);
   tolua_function(tolua_S,"release",tolua_dubase_DUObject_release00);
   tolua_function(tolua_S,"printCount",tolua_dubase_DUObject_printCount00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"DUScheduler","DUScheduler","DUObject",NULL);
  tolua_beginmodule(tolua_S,"DUScheduler");
   tolua_function(tolua_S,"getInstance",tolua_dubase_DUScheduler_getInstance00);
   tolua_function(tolua_S,"pauseSchedule",tolua_dubase_DUScheduler_pauseSchedule00);
   tolua_function(tolua_S,"pauseSchedule",tolua_dubase_DUScheduler_pauseSchedule01);
   tolua_function(tolua_S,"pauseSchedule",tolua_dubase_DUScheduler_pauseSchedule02);
   tolua_function(tolua_S,"resumeSchedule",tolua_dubase_DUScheduler_resumeSchedule00);
   tolua_function(tolua_S,"resumeSchedule",tolua_dubase_DUScheduler_resumeSchedule01);
   tolua_function(tolua_S,"resumeSchedule",tolua_dubase_DUScheduler_resumeSchedule02);
   tolua_function(tolua_S,"unScheduleByObject",tolua_dubase_DUScheduler_unScheduleByObject00);
   tolua_function(tolua_S,"unScheduleSeletorByKey",tolua_dubase_DUScheduler_unScheduleSeletorByKey00);
   tolua_function(tolua_S,"unScheduleSeletorByKey",tolua_dubase_DUScheduler_unScheduleSeletorByKey01);
   tolua_function(tolua_S,"unScheduleSeletorByObject",tolua_dubase_DUScheduler_unScheduleSeletorByObject00);
   tolua_function(tolua_S,"unScheduleAll",tolua_dubase_DUScheduler_unScheduleAll00);
   tolua_function(tolua_S,"registerScripSchedule",tolua_dubase_DUScheduler_registerScripSchedule00);
   tolua_function(tolua_S,"unRegisterScripSchedule",tolua_dubase_DUScheduler_unRegisterScripSchedule00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"DUServer","DUServer","DUObject",tolua_collect_DUServer);
  #else
  tolua_cclass(tolua_S,"DUServer","DUServer","DUObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"DUServer");
   tolua_function(tolua_S,"new",tolua_dubase_DUServer_new00);
   tolua_function(tolua_S,"new_local",tolua_dubase_DUServer_new00_local);
   tolua_function(tolua_S,".call",tolua_dubase_DUServer_new00_local);
   tolua_function(tolua_S,"delete",tolua_dubase_DUServer_delete00);
   tolua_function(tolua_S,"startServer",tolua_dubase_DUServer_startServer00);
   tolua_function(tolua_S,"stopServer",tolua_dubase_DUServer_stopServer00);
   tolua_function(tolua_S,"send",tolua_dubase_DUServer_send00);
   tolua_function(tolua_S,"disconnect",tolua_dubase_DUServer_disconnect00);
   tolua_function(tolua_S,"isCloseFinish",tolua_dubase_DUServer_isCloseFinish00);
   tolua_function(tolua_S,"registerLuaHandle",tolua_dubase_DUServer_registerLuaHandle00);
   tolua_function(tolua_S,"unregisterLuaHandle",tolua_dubase_DUServer_unregisterLuaHandle00);
   tolua_function(tolua_S,"clearLuaHandle",tolua_dubase_DUServer_clearLuaHandle00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"DUGame","DUGame","",NULL);
  tolua_beginmodule(tolua_S,"DUGame");
   tolua_function(tolua_S,"getInstance",tolua_dubase_DUGame_getInstance00);
   tolua_function(tolua_S,"destroy",tolua_dubase_DUGame_destroy00);
   tolua_function(tolua_S,"setInterval",tolua_dubase_DUGame_setInterval00);
   tolua_function(tolua_S,"isFileExist",tolua_dubase_DUGame_isFileExist00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"TestOBJ","TestOBJ","",tolua_collect_TestOBJ);
  #else
  tolua_cclass(tolua_S,"TestOBJ","TestOBJ","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"TestOBJ");
   tolua_function(tolua_S,"new",tolua_dubase_TestOBJ_new00);
   tolua_function(tolua_S,"new_local",tolua_dubase_TestOBJ_new00_local);
   tolua_function(tolua_S,".call",tolua_dubase_TestOBJ_new00_local);
   tolua_function(tolua_S,"delete",tolua_dubase_TestOBJ_delete00);
   tolua_function(tolua_S,"Test",tolua_dubase_TestOBJ_Test00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_dubase (lua_State* tolua_S) {
 return tolua_dubase_open(tolua_S);
};
#endif

