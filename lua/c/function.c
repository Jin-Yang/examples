#include <string.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

int main(void)
{
    char *szLua_code =                        // Lua示例代码，使用函数
        "function gsub(Str, Mode, Tag)\n"
        "    a,b = string.gsub(Str, Mode, Tag)\n"
        "    c = string.upper(a)\n"
        "    return a,b,c --多个返回值\n"
        "end";
    char *szMode = "(%w+)%s*=%s*(%w+)";            // Lua的字符串模式
    char *szStr = "key1 = value1 key2 = value2";   // 要处理的字符串
    char *szTag = "<%1>%2</%1>";                   // 目标字符串模式

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // 执行
    if (luaL_loadbuffer(L, szLua_code, strlen(szLua_code), "demo") || lua_pcall(L, 0, 0, 0)) {
        fprintf(stderr, "ERROR: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
    } else {
        // Lua执行后取得全局变量的值
        lua_getglobal(L, "gsub");
        if(lua_isfunction(L, -1)) {  // 确认一下是个函数
            // 依次放入三个参数
            lua_pushstring(L, szStr);
            lua_pushstring(L, szMode);
            lua_pushstring(L, szTag);

            // 虽然gsub()返回了3个，不过在此只要2个
            if(0 != lua_pcall(L, 3, 2, 0)) {
                fprintf(stderr, "ERROR: %s\n", lua_tostring(L, -1)); // 如果错误，显示
                lua_pop(L, 1);
            } else {
                // 正确，得到两个结果，注意在栈里的顺序
                fprintf(stdout, "a = %s\n", lua_tostring(L, -2));
                fprintf(stdout, "b = %s\n", lua_tostring(L, -1));
                lua_pop(L, 2); // 弹出这两个结果
            }
        } else {
            lua_pop(L,1);
        }
    }
    lua_close(L);
    return 0;
}
