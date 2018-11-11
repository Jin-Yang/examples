#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

// 计算函数
int count(lua_State *L)
{
    double m_ = lua_tonumber(L, lua_upvalueindex(1)); // 得到UpValue
    lua_pushnumber(L, ++m_); // 更改UpValue
    lua_replace(L, lua_upvalueindex(1));
    // 返回结果（直接复制一份UpValue作为结果）
    lua_pushvalue(L, lua_upvalueindex(1));
    return 1;
}
// 工厂函数，把一个数字和count函数关联打包后返回闭包。
int newCount(lua_State *L)
{
    lua_pushnumber(L, 0);          // 计数器初值（即UpValue）
    lua_pushcclosure(L, count, 1); // 放入计算函数，告诉它与这个函数相关联的数据个数
    return 1;// 一个结果，即函数体
}

int main()
{
    char *szLua_code =
        "c1 = NewCount()\n"
        "c2 = NewCount()\n"
        "for i=1,5 do print(c1()) end\n"
        "for i=1,5 do print(c2()) end";

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // 放入C函数
    lua_register(L, "NewCount", newCount);

    //执行
    if(luaL_loadstring(L, szLua_code) || lua_pcall(L, 0, 0, 0)) {
        fprintf(stderr, "ERROR: %s\n", lua_tostring(L, -1)); // 如果错误，显示相关信息
        lua_pop(L, 1);
    }

    lua_close(L);
    return 0;
}
