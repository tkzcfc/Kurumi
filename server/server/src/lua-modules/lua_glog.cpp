/*
** Lua binding: glog
** Generated automatically by tolua++-1.0.92 on 06/03/18 22:47:54.
*/

#include "tolua_fix.h"
#include "tolua++.h"
#include <string>


#define GLOG_NO_ABBREVIATED_SEVERITIES 
#include "glog/logging.h"



enum GLOGTYPE
{
	GINFO = 0,
	GWARNING,
	GERROR,
	GFATAL
};
void GLOG(GLOGTYPE type, const std::string& log)
{
	switch (type)
	{
	case GINFO:
		LOG(INFO) << log;
		break;
	case GWARNING:
		LOG(WARNING) << log;
		break;
	case GERROR:
		LOG(ERROR) << log;
		break;
	case GFATAL:
		LOG(FATAL) << log;
		break;
	default:
		break;
	}
}



/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* function: GLOG */
#ifndef TOLUA_DISABLE_tolua_glog_GLOG00
static int tolua_glog_GLOG00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GLOGTYPE type = ((GLOGTYPE) (int)  tolua_tonumber(tolua_S,1,0));
  const std::string log = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   GLOG(type,log);
   tolua_pushcppstring(tolua_S,(const char*)log);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GLOG'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_glog_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"GINFO",GINFO);
  tolua_constant(tolua_S,"GWARNING",GWARNING);
  tolua_constant(tolua_S,"GERROR",GERROR);
  tolua_constant(tolua_S,"GFATAL",GFATAL);
  tolua_function(tolua_S,"GLOG",tolua_glog_GLOG00);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_glog (lua_State* tolua_S) {
 return tolua_glog_open(tolua_S);
};
#endif

