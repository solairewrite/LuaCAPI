#include "Common.h"

#if _02_MetaTable

static int average(lua_State* L)
{
    int a = lua_tonumber(L, -1);
    printf("average(%d)\n", a);
    return 0;
}

int main()
{
    lua_State* L = luaL_newstate();

    // 这两行代码都创建了表,不知道是什么,是不是_G?
    luaopen_base(L);
    luaopen_table(L);

    lua_newtable(L); // {}
    lua_newtable(L); // {}

    lua_pushstring(L, "__call"); // {}, __call
    lua_pushcfunction(L, average); // {}, __call, average
    // lua_rawset(L, -3); // {__call:average}, 不调用元函数,效率高
    lua_settable(L, -3); // {__call:average}

    lua_setmetatable(L, -2); // -2是不是全局表?

    lua_setglobal(L, "qq");

    lua_pop(L, 1); //After foo register the methods are still on the stack, remove them.

    luaL_dostring(L, "qq(8)");

    lua_close(L);
}

#endif
