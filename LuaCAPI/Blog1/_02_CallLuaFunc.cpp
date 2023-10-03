#include "Common.h"

#if _02_CallLuaFunc

#define QUOTE(...) #__VA_ARGS__
static const char* lua_code = QUOTE(
    function identity(...)
    // error("test")
    return table.unpack({...})
    end
);

int main(int argc, char* argv[])
{
    int status = 0;

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    status = luaL_loadstring(L, lua_code) || lua_pcall(L, 0, 0, 0);
    if (status)
    {
        fprintf(stderr, "%s", lua_tostring(L, -1));
        lua_pop(L, 1);
        lua_close(L);
        return status;
    }

    lua_getglobal(L, "identity"); // identity
    lua_pushinteger(L, 1); // identity, 1
    // 参数: L, 参数个数, 返回值个数
    lua_call(L, 1, 2);
    // r1, r2 = identity(1)
    // stack: 1, nil
    printf(
        "r1, r2 = %d, %s\n",
        (int)lua_tointeger(L, -2),
        lua_isnil(L, -1) ? "nil" : "not nil"
    );
    lua_pop(L, 2);

    lua_getglobal(L, "identity"); // identity
    lua_pushinteger(L, 1); // identity, 1
    lua_pushinteger(L, 2); // identity, 1, 2
    // 参数: L, 参数个数, 返回值个数, 指定处理错误的函数的栈位置,这里是0,表示没有处理错误的函数
    status = lua_pcall(L, 2, 1, 0);
    if (status)
    {
        fprintf(stderr, "%s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    else
    {
        printf("r1 = %d\n", (int)lua_tointeger(L, -1));
        lua_pop(L, 1);
    }

    lua_close(L);
    return status;
}


#endif
