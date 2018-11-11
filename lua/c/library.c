#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

    #include <iostream>
    #include <string>
    #include <windows.h>
    using namespace std;

    //函数库示例，Windows下查找文件功能
    //输入:string路径名
    //输出:userdata存放Handle(如果没找到，则是nil), string文件名
    int findfirst( lua_State *L )
    {
        WIN32_FIND_DATAA FindFileData;
        HANDLE hFind = ::FindFirstFileA(luaL_checkstring(L,1), &FindFileData);

        if(INVALID_HANDLE_VALUE == hFind)
            lua_pushnil(L);
        else
            lua_pushlightuserdata(L, hFind);

        lua_pushstring(L, FindFileData.cFileName);

        return 2;
    }

    //输入:userdata:findfirst返回的Handle
    //输出:string：文件名，如果没找到，则返回nil
    int findnext( lua_State *L )
    {
        WIN32_FIND_DATAA FindFileData;
        if(::FindNextFileA(lua_touserdata(L,1),&FindFileData))
            lua_pushstring(L, FindFileData.cFileName);
        else
            lua_pushnil(L);
        return 1;
    }

    //输入:userdata:findfirst返回的Handle
    //没有输出
    int findclose( lua_State *L )
    {
        ::FindClose(lua_touserdata(L,1));
        return 0;
    }

//注册函数库
static const struct luaL_reg lrFiles [] = {
    {"FindFirst", findfirst},
    {"FindNext", findnext},
    {"FindClose", findclose},
    {NULL, NULL}    /* sentinel */
};

int luaopen_Files (lua_State *L) {
    luaL_register(L, "Files", lrFiles);
    return 1;
}

int main(void)
{
        char* szLua_code=
            "hFind,sFile = Files.FindFirst('c:////*.*'); "
            "if hFind then "
            "    repeat "
            "        print(sFile) "
            "        sFile = Files.FindNext(hFind) "
            "    until sFile==nil; "
            "    Files.FindClose(hFind) "
            "end";

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_Files(L);

    if (luaL_loadstring(L, szLua_code) || lua_pcall(L, 0, 0, 0)) {
        fprintf(stderr, "ERROR: %s\n", lua_tostring(L, -1)); // 如果错误，显示相关信息
        lua_pop(L, 1);
    }
    lua_close(L);
    return 0;
}
