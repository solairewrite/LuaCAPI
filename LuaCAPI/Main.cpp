// _04_MetaTable3很有参考价值
#include "Common.h"

#if _00_Main

int main()
{
    lua_State* l = luaL_newstate();
    luaL_openlibs(l);
    luaL_dofile(l, "./Lua/Main.lua");
    lua_close(l);
}

#endif
