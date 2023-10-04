#include "Common.h"

#if _05_LightUserData2

typedef struct
{
    int x;
    int y;
    int z;
} TData;

static int getAttribute(lua_State* L)
{
    TData* data = (TData*)lua_touserdata(L, 1);
    string attribute = luaL_checkstring(L, 2);
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

void getMetaTable(lua_State* L)
{
    luaL_Reg* methods = dataLib;
    lua_pushlightuserdata(L, methods); // address(input), address(methods)

    lua_gettable(L, LUA_REGISTRYINDEX); // address(input), registry[address(methods)]
    if (lua_isnil(L, -1)) // 没找到
    {
        lua_pop(L, 1); // address(input)

        lua_newtable(L); // address(input), {}

        // 向栈顶table注册函数 
        luaL_setfuncs(L, methods, 0); // address(input), {methods}

        lua_pushlightuserdata(L, methods); // address(input), {methods}, address(methods)
        // 复制[栈-2]到栈顶
        lua_pushvalue(L, -2); // address(input), {methods}, address(methods), {methods}
        // registry[address(methods)] = {methods}
        lua_settable(L, LUA_REGISTRYINDEX); //  address(input), {methods}
    }
}

void FuncA()
{
    lua_State* lua = luaL_newstate();
    luaL_openlibs(lua);

    TData input = {3, 6, 9};

    lua_pushlightuserdata(lua, &input); // address(input)
    getMetaTable(lua);
    // 将栈顶的table作为metatable设置给[栈-2]
    lua_setmetatable(lua, -2); // {address(input) = methods}

    lua_setglobal(lua, "input");

    luaL_dostring(lua, "data = input.x; print(data)");

    lua_getglobal(lua, "data");

    const int output = lua_tointeger(lua, -1);
    cout << output << endl;

    lua_close(lua);
}

void FuncB()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // LUA_REGISTRYINDEX: 假索引,理解成全局变量表的索引,不在栈中
    // Key值,可以使用字符串,或c函数的指针以lightuserdata作为键值

    // 唯一地址
    static char Key = 'k';

    // 地址入栈
    lua_pushlightuserdata(L, &Key); // address

    lua_pushnumber(L, 33); // address, 33

    // registry[address] = 33
    lua_settable(L, LUA_REGISTRYINDEX); // 空栈

    lua_pushlightuserdata(L, &Key); // address

    lua_gettable(L, LUA_REGISTRYINDEX); // registry[address]
    const int value = lua_tonumber(L, -1);
    printf("value: %d\n", value);

    lua_close(L);
}

int main()
{
    FuncA();
    FuncB();
}

#endif
