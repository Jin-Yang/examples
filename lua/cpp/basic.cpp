extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <string>
#include <iostream>
using namespace std;

int main()
{
    string buff;
    bool err;
    lua_State *L = lua_open();    // 初始化lua，5.0之后建议采用luaL_newstate()
    luaL_openlibs(L);             // 载入所有lua标准库，包括base、package、coroutine等

    while(getline(cin, buff)) {   // 从cin中读入一行到buff
        // 载入buff的lua代码后执行
        err = luaL_loadbuffer(L, buff.c_str(), buff.length(), "line") ||
            lua_pcall(L, 0, 0, 0);
        if (err) {
            cerr << lua_tostring(L, -1); // 如果错误，显示相关信息
            lua_pop(L, 1); // 弹出错误信息所在的最上层栈
        }
    }

    lua_close(L);                 // 关闭
    return 0;
}
