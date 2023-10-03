#include "Common.h"

#if _00_Main

int main()
{
    lua_State* l = luaL_newstate();
    luaL_openlibs(l);
    luaL_dofile(l, "Main.lua");
    lua_close(l);
}

#endif
