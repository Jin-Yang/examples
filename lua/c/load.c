#include <string.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

int main(void)
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    if ((luaL_loadfile(L, "loiad.lua") || lua_pcall(L, 0, 0, 0)) != 0) {
        luaL_error(L, "loadfile error!: %s", lua_tostring(L, -1));
    }

    // 准备取得foobar.name，也即foobar["name"]
    lua_getglobal(L, "foobar");     // Lua执行后取得全局变量的值
    if(!lua_istable(L, -1)) {       // 再次判断x是否为table
        luaL_error(L, "'foobar' is not a table! %s\n", lua_tostring(L, -1));
    }

    lua_pushstring(L, "name");      // 设置key
    lua_gettable(L, -2);            // 由于这次压栈，x处于栈顶第二位置
                                    // lua_gettable()会弹出上面压入的key，然后把对应的value压入
    fprintf(stdout, "foobar.name = %s\n", lua_tostring(L, -1));
    lua_pop(L, 1);

    lua_pop(L, 1); // 弹出栈顶的x

    lua_close(L);
    return 0;
}
