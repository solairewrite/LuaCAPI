extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

int main()
{
	lua_State* l = luaL_newstate();
	luaL_openlibs(l);
	luaL_dofile(l, "Main.lua");
	lua_close(l);
}