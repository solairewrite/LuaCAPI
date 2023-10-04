#include "Common.h"

#if _05_Func1

int Func1(lua_State* L)
{
    // 获取Lua传递的参数
    const int arg1 = lua_tointeger(L, 1); // 10, 20
    const int arg2 = lua_tointeger(L, 2);

    const int sum = arg1 + arg2;

    // 将返回值入栈
    lua_pushinteger(L, sum);

    // 返回结果个数
    return 1;
}

void PushFunc()
{
    lua_State* L = luaL_newstate();

    luaL_openlibs(L);

    // 将C函数入栈
    lua_pushcfunction(L, Func1);

    // 将C函数绑定到全局变量
    lua_setglobal(L, "func1");

    const char* LuaCode = Lua_Code(
        result = func1(10, 20)
        print(result)
    );
    luaL_dostring(L, LuaCode);

    lua_close(L);
}

void PCall()
{
    lua_State* L = luaL_newstate();

    luaL_openlibs(L);

    const char* LuaCode1 = Lua_Code(
        function add(a, b)
        return a + b
        end
    );

    if (luaL_loadstring(L, LuaCode1) == LUA_OK)
    {
        // 参数个数,返回值个数,错误处理函数索引
        const int callResult = lua_pcall(L, 0, 0, 0);

        if (callResult == LUA_OK)
        {
            // 调用成功,继续使用lua函数

            // 将lua函数入栈
            lua_getglobal(L, "add");

            // 参数入栈
            lua_pushnumber(L, 6);
            lua_pushnumber(L, 9);

            // 调用Lua函数,2个参数,1个返回值,没有错误处理函数
            const int callStatus = lua_pcall(L, 2, 1, 0);

            if (callStatus == LUA_OK)
            {
                // 获取返回值
                const double result = lua_tonumber(L, -1);
                printf("result: %f\n", result);
            }
            else
            {
                // 获取错误信息
                const char* ErrorMsg = lua_tostring(L, -1);
                printf("Call error : %s\n", ErrorMsg);
            }
        }
        else
        {
            // 获取错误信息
            const char* ErrorMsg = lua_tostring(L, -1);
            printf("Call error : %s\n", ErrorMsg);
        }
    }

    lua_close(L);
}

int Func2(lua_State* L)
{
    // 获取Lua传递的参数
    const int arg1 = lua_tointeger(L, 1); // 10, 20
    const int arg2 = lua_tointeger(L, 2);

    const int result = arg1 * arg2;

    // 将返回值入栈
    lua_pushinteger(L, result);

    // 返回结果个数
    return 1;
}

void Register()
{
    lua_State* L = luaL_newstate();

    luaL_openlibs(L);

    // 将函数注册为全局变量
    lua_register(L, "func2", Func2);

    const char* luaCode = Lua_Code(
        result = func2(2, 3)
        print(result)
    );

    luaL_dostring(L, luaCode);

    lua_close(L);
}

int main()
{
    PushFunc();
    PCall();
    Register();
}

#endif
