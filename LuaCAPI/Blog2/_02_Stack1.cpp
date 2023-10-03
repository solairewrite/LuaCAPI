#include "Common.h"

#if _02_Stack1

static int Func1(lua_State* L)
{
    cout << "Func1" << endl;
    return 0;
}

int main()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushnumber(L, 23); // 1
    lua_pushstring(L, "akuya"); // 2
    lua_pushboolean(L, 1); // 3
    lua_pushnil(L); // 4
    lua_pushcfunction(L, Func1); // 5

    lua_Number num = lua_tonumber(L, 1); // 1是栈底
    const char* str = lua_tostring(L, 2);
    const int b = lua_toboolean(L, 3);
    const bool bNil = lua_isnil(L, -2);
    const lua_CFunction func = lua_tocfunction(L, -1); // -1是栈顶

    cout << num << endl;
    cout << str << endl;
    cout << b << endl;
    cout << bNil << endl;
    cout << func << endl;

    lua_close(L);
}

#endif
