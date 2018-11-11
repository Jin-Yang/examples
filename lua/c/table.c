#include <string.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

int main()
{
    char *szLua_code =                            // Lua示例代码，使用table
        "for k, v in pairs(c) do print(k, v) end\n"
        "x = {} --用于存放结果的table\n"
        "x[1],x[2] = string.gsub(c.Str, c.Mode, c.Tag) --x[1]里是结果，x[2]里是替换次数\n"
        "print(x[1],x[2])\n"
        "x.u = string.upper(x[1])\n";

    char *szMode = "(%w+)%s*=%s*(%w+)";           // Lua的字符串模式
    char *szStr = "key1 = value1 key2 = value2";  // 要处理的字符串
    char *szTag = "<%1>%2</%1>";                  // 目标字符串模式

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // 新建一个table，并传递给lua
    lua_newtable(L);                   // 新建一个table并压入栈顶
    lua_pushstring(L, "Mode");         // 设置key
    lua_pushstring(L, szMode);         // 以及value，等价于newtable[Mode]=szMode
    lua_settable(L, -3);               // 由于上面两次压栈，现在table元素排在栈顶往下数第三的位置
                                       // lua_settable()会自己弹出上面压入的key和value

    lua_pushstring(L, "Tag");          // key
    lua_pushstring(L, szTag);          // value
    lua_settable(L, -3);               // 设置newtable[Tag]=szTag

    lua_pushstring(L, "Str");          // key
    lua_pushstring(L, szStr);          // value
    lua_settable(L, -3);               // 设置newtable[Str]=szStr

    lua_setglobal(L, "c");             // 将栈顶元素(newtable)置为Lua中的全局变量c

    // 执行
    int err = luaL_loadbuffer(L, szLua_code, strlen(szLua_code), "demo") ||
               lua_pcall(L, 0, 0, 0);
    if(err) {
        fprintf(stderr, "%s\n", lua_tostring(L, -1)); // 如果错误，显示相关信息
        lua_pop(L, 1); // 弹出错误信息所在的最上层栈
    } else {
        lua_getglobal(L, "x");         // Lua执行后取得全局变量的值
        if(lua_istable(L, -1)) {       // 再次判断x是否为table
            // 准备取得x.u，也即x["u"]
            lua_pushstring(L, "u");    // 设置key
            lua_gettable(L, -2);       // 由于这次压栈，x处于栈顶第二位置
                                       // lua_gettable()会弹出上面压入的key，然后把对应的value压入
            fprintf(stdout, "x.u = %s\n", lua_tostring(L, -1));
            lua_pop(L, 1);

            // 取得x[1]和x[2]
            for(int i=1; i<=2; i++) {
                lua_pushnumber(L, i);  // 除了key是数字外，与上面的没什么区别
                lua_gettable(L, -2);
                fprintf(stdout, "x[%d]=%s\n", i, lua_tostring(L, -1));
                lua_pop(L, 1);
            }
        }

        lua_pop(L, 1); // 弹出栈顶的x
    }
    lua_close(L);
    return 0;
}
