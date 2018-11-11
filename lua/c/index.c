#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

int main(void)
{
    char *szLua_code =
        "a=10\n"
        "b=\"hello\"\n"
        "c=true";



    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // 执行
    if (luaL_loadstring(L, szLua_code) || lua_pcall(L, 0, 0, 0)) {
        fprintf(stderr, "ERROR: %s\n", lua_tostring(L, -1)); // 如果错误，显示相关信息
        lua_pop(L, 1);
    } else {
        // 遍历LUA_GLOBALSINDEX所在的table得到
        lua_pushnil(L);

            while(0 != lua_next(L,LUA_GLOBALSINDEX))

            {

                // 'key' （在索引 -2 处） 和 'value' （在索引 -1 处）

                /*

                在遍历一张表的时候，不要直接对 key 调用 lua_tolstring ，

                除非你知道这个 key 一定是一个字符串。

                调用 lua_tolstring 有可能改变给定索引位置的值；

                这会对下一次调用 lua_next 造成影响。

                所以复制一个key到栈顶先

                */

                lua_pushvalue(L, -2);

                printf("%s - %s ",

                      lua_tostring(L, -1),    //key,刚才复制的

                      lua_typename(L, lua_type(L,-2))); //value，现在排在-2的位置了

                // 移除 'value' 和复制的key；保留源 'key' 做下一次叠代

                lua_pop(L, 2);

            }

        }

        lua_close(L);

        return 0;

    }



