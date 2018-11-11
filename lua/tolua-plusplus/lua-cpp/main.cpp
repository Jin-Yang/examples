#include "lua.hpp"
#include "HelloWorld.h"

int tolua_HelloWorld_open (lua_State* tolua_S);
int g_Arr[10]={0};

int main(int argc, char** argv)
{
    lua_State * L = lua_open();
    int i=0;
    for(i=0; i<10; i++) g_Arr[i] = i;

    luaopen_base(L);
    tolua_HelloWorld_open(L);
    luaL_dofile(L, "test1.lua");

    printf("now in c++, re-show Arr:");
    for(i=0; i<10; i++) printf("%d ", g_Arr[i]);
    printf(" \n\n");

    luaL_dofile(L, "test2.lua");

    lua_close(L);
    return 0;
}
