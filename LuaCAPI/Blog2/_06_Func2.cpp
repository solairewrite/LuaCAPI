#include "Common.h"

#if _06_Func2

int Func1(lua_State* L)
{
    const int arg1 = lua_tointeger(L, 1);
    const int arg2 = lua_tointeger(L, 2);

    lua_pushinteger(L, arg1 + arg2);

    return 1;
}

int Func2(lua_State* L)
{
    const lua_Integer arg1 = lua_tointeger(L, 1);
    const lua_Integer arg2 = lua_tointeger(L, 2);

    lua_pushinteger(L, arg1 * arg2);

    return 1;
}

// 模块打开函数
int ModuleOpen(lua_State* L)
{
    // 创建表作为模块的命名空间
    lua_newtable(L);

    // 在模块的命名空间表中注册函数

    // lua_pushstring(L, "func1");
    lua_pushcfunction(L, Func1);

    lua_setfield(L, -2, "func1");
    // lua_setfield(), lua_settable()两种写法等同
    // lua_settable(L, -3);

    // 返回模块的命名空间表
    return 1;
}

void Require()
{
    lua_State* L = luaL_newstate();

    luaL_openlibs(L);

    luaL_requiref(L, "myModule", ModuleOpen, 1);

    const char* LuaCode = Lua_Code(
        print("megumin")
        print(myModule)
        print(myModule.func1)
        result = myModule.func1(3, 4)
        print(result)
        print("akuya")
    );

    luaL_dostring(L, LuaCode);

    lua_close(L);
}

// 模块的打开函数
int luaopen_AkuyaModule(lua_State* L)
{
    lua_newtable(L);
    lua_pushcfunction(L, Func2);
    lua_setfield(L, -2, "func2");
    return 1;
}

void Open()
{
    lua_State* L = luaL_newstate();

    luaL_openlibs(L);

    luaL_requiref(L, "IQ", luaopen_AkuyaModule, 1);

    const char* LuaCode = Lua_Code(
        print("darkness")
        print(IQ)
        print(IQ.func2)
        result = IQ.func2(3, 4)
        print(result)
        print("akuya")
    );

    luaL_dostring(L, LuaCode);

    lua_close(L);
}

int main()
{
    Require();
    cout << endl;
    Open();
}

#endif
