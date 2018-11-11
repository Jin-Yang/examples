#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

int main()
{
    char foobar[] = "print('hello world')";
    lua_State *L = lua_open();    // 初始化，5.0之后建议采用luaL_newstate()
    luaL_openlibs(L);             // 载入所有lua标准库，包括base、package、coroutine等

    luaL_loadbuffer(L,            // 载入lua代码后执行
            foobar,
            sizeof(foobar)-1,     // 去除'\0'，或者使用strlen(foobar)
            "line");
    lua_pcall(L, 0, 0, 0);        // 调用执行

    lua_close(L);//关闭
    return 0;
}
