// 失败
#include "Common.h"

#if _09_GetMetaTable

void GetMetaTable()
{
    lua_State* L = luaL_newstate(); // 创建 Lua 状态

    luaL_dostring(L, "my_table = {}"); // 在 Lua 脚本中创建一个表

    lua_getglobal(L, "my_table"); // 获取全局变量 "my_table" 的值

    int hasMetatable = lua_getmetatable(L, -1); // 获取值的元表

    if (hasMetatable)
    {
        printf("Value has a metatable.\n");
    }
    else
    {
        printf("Value does not have a metatable.\n");
    }

    lua_close(L); // 关闭并销毁 Lua 状态
}

static int my_index_function(lua_State* L)
{
    // TData* data = (TData*)lua_touserdata(L, 1);
    // std::string attribute = luaL_checkstring(L, 2);
    // int result = 0;
    // if (attribute == "x")
    // {
    //     result = data->x;
    // }
    // else if (attribute == "y")
    // {
    //     result = data->y;
    // }
    // else
    // {
    //     result = data->z;
    // }
    // lua_pushnumber(L, result);
    lua_pushnumber(L, 33);
    return 1;
}

void SetMetaTable()
{
    lua_State* L = luaL_newstate(); // 创建 Lua 状态
    luaL_openlibs(L);

    luaL_newmetatable(L, "MyMetatable"); // 创建一个新的元表
    lua_pushstring(L, "__index");
    lua_pushcfunction(L, my_index_function); // 设置元表中的 "__index" 元方法
    lua_settable(L, -3);

    luaL_dostring(L, "my_table = {}"); // 在 Lua 脚本中创建一个表
    lua_getglobal(L, "my_table"); // 获取全局变量 "my_table" 的值

    lua_getmetatable(L, -1); // 获取值的元表
    lua_setmetatable(L, -2); // 为值设置元表

    luaL_dostring(L, "print(\"akuya\"); print(my_table); print(my_table.foo)");

    lua_close(L); // 关闭并销毁 Lua 状态
}

int main()
{
    // 失败
    // GetMetaTable();
    SetMetaTable();
}

#endif
