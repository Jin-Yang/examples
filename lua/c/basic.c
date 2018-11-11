#include <string.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

int main()
{
    char buff[256] = {0};

    lua_State *L = lua_open();    // 初始化，5.0之后建议采用luaL_newstate()
    luaL_openlibs(L);             // 载入所有lua标准库，包括base、package、coroutine等

    while (fgets(buff, sizeof(buff), stdin) != NULL) { // 从stdin中读入一行到buff
        // 载入buff的lua代码后执行
        if (luaL_loadbuffer(L, buff, strlen(buff), "line") || lua_pcall(L, 0, 0, 0)) {
            fprintf(stderr, "ERROR: %s\n", lua_tostring(L, -1)); // 如果错误，显示相关信息
            //luaL_error(L, "loadfile error! %s", lua_tostring(L, -1));   // 直接退出，打印错误
            lua_pop(L, 1); // 弹出错误信息所在的最上层栈
        }
    }
    lua_close(L);                 // 关闭
    return 0;
}
