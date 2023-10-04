#include "Common.h"

#if _01_LightUserData

typedef struct
{
    int x;
    int y;
    int z;
} TData;

static int getAttribute(lua_State* L)
{
    TData* data = (TData*)lua_touserdata(L, 1);
    std::string attribute = luaL_checkstring(L, 2);
    int result = 0;
    if (attribute == "x")
    {
        result = data->x;
    }
    else if (attribute == "y")
    {
        result = data->y;
    }
    else
    {
        result = data->z;
    }
    lua_pushnumber(L, result);
    return 1;
}

static luaL_Reg dataLib[] = {
    {"__index", getAttribute},
    {NULL, NULL}
};

void getMetaTable(lua_State* L, luaL_Reg* methods)
{
    lua_pushlightuserdata(L, methods);
    lua_gettable(L, LUA_REGISTRYINDEX);
    if (lua_isnil(L, -1))
    {
        /* not found */
        lua_pop(L, 1);

        lua_newtable(L);
        luaL_setfuncs(L, methods, 0);

        lua_pushlightuserdata(L, methods);
        lua_pushvalue(L, -2);
        lua_settable(L, LUA_REGISTRYINDEX);
    }
}

int main()
{
    lua_State* lua = luaL_newstate();
    luaL_openlibs(lua);

    TData input = {123, 456, 789};
    lua_pushlightuserdata(lua, &input);

    getMetaTable(lua, dataLib);
    lua_setmetatable(lua, -2);
    lua_setglobal(lua, "input");

    luaL_dostring(lua, "data = input.x; print(data)");

    lua_getglobal(lua, "data");

    const int output = lua_tointeger(lua, -1);
    cout << output << endl;
}

#endif
