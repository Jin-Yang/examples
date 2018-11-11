/*
** Lua binding: HelloWorld
** Generated automatically by tolua++-1.0.92 on Mon Jan  8 23:56:36 2018.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_HelloWorld_open (lua_State* tolua_S);

#include "HelloWorld.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* get function: g_Arr */
#ifndef TOLUA_DISABLE_tolua_get_HelloWorld_Arr
static int tolua_get_HelloWorld_Arr(lua_State* tolua_S)
{
 int tolua_index;
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=10)
  tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)g_Arr[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: g_Arr */
#ifndef TOLUA_DISABLE_tolua_set_HelloWorld_Arr
static int tolua_set_HelloWorld_Arr(lua_State* tolua_S)
{
 int tolua_index;
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=10)
  tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  g_Arr[tolua_index] = ((int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* function: print_sth */
#ifndef TOLUA_DISABLE_tolua_HelloWorld_print_sth00
static int tolua_HelloWorld_print_sth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  {
   print_sth(L);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'print_sth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_HelloWorld_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,1);
 tolua_beginmodule(tolua_S,NULL);
  tolua_array(tolua_S,"Arr",tolua_get_HelloWorld_Arr,tolua_set_HelloWorld_Arr);
  tolua_function(tolua_S,"print_sth",tolua_HelloWorld_print_sth00);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_HelloWorld (lua_State* tolua_S) {
 return tolua_HelloWorld_open(tolua_S);
};
#endif

