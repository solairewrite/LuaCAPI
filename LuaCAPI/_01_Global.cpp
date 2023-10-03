#include "Common.h"

#if _01_Global

#define QUOTE(...) #__VA_ARGS__
static const char* lua_code = QUOTE(
    print("g_int: ", g_int)
    print("g_number: ", g_number)
    print("g_true: ", g_true)
    print("g_false: ", g_false)
    print("g_string: ", g_string)
    print("g_table.name: ", g_table.name)
);

int main(int argc, char* argv[])
{
    int status = 0;

    cout << lua_code << endl << endl;

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // g_int = 10
    lua_pushinteger(L, 10);
    lua_setglobal(L, "g_int");

    // g_number = 3.14
    lua_pushnumber(L, (lua_Number)3.14);
    lua_setglobal(L, "g_number");

    // g_true = true
    // g_false = false
    lua_pushboolean(L, 1);
    lua_setglobal(L, "g_true");
    lua_pushboolean(L, 0);
    lua_setglobal(L, "g_false");

    // g_string = "global set from C API"
    lua_pushstring(L, "global set from C API");
    lua_setglobal(L, "g_string");

    // g_table = { name = "table set from C API" }
    // {}(-1)
    lua_newtable(L);
    // {}(-2), "table set from C API"(-1)
    lua_pushstring(L, "table set from C API");
    // {name="table set from C API"}(-1)
    lua_setfield(L, -2, "name");
    // _G.g_table = {name="table set from C API"}
    lua_setglobal(L, "g_table");

    status = luaL_loadstring(L, lua_code) || lua_pcall(L, 0, 0, 0);
    if (status)
    {
        fprintf(stderr, "%s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    lua_close(L);
    return status;
}

#endif
