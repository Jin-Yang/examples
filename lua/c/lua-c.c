#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

// C函数，简单获取实部、虚部，并返回
int calcComplex(lua_State *L)
{
    //从栈中读入实部，虚部
    double r = luaL_checknumber(L, 1);
    double i = luaL_checknumber(L, 2);

    lua_pushnumber(L, r); // 再将两个数据返回
    lua_pushnumber(L, i);
    return 2; //两个结果
}

int main(void)
{
    char *szLua_code =
        "v,a = CalcComplex(3, 4)\n"
        "print(v,a)";

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // 放入C函数
    lua_pushcfunction(L, calcComplex);
    lua_setglobal(L, "CalcComplex");

    // 执行
    if (luaL_loadstring(L, szLua_code) || lua_pcall(L, 0, 0, 0)) {
        fprintf(stderr, "ERROR: %s\n", lua_tostring(L, -1)); // 如果错误，显示相关信息
        lua_pop(L, 1);
    }

    lua_close(L);
    return 0;
}
