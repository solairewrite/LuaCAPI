#include "Common.h"

#if _07_Error

int Func1(lua_State* L)
{
    constexpr bool bCondition = 1;
    if (bCondition)
    {
        // 将错误信息入栈
        lua_pushstring(L, "an error occured");
        // 触发lua错误并终止当前执行流程
        return lua_error(L);
    }

    // 继续执行其他操作
    return 0;
}

void Error()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    // 注册函数
    lua_register(L, "func1", Func1);
    luaL_dostring(L, "func1()");

    // 捕捉错误
    const char* msg = lua_tostring(L, -1);
    if (msg)
    {
        printf("%s\n", msg);
    }

    lua_close(L);
}

void GetTop()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushinteger(L, 3); // 3
    lua_pushstring(L, "akuya"); // 3, akuya
    lua_pushboolean(L, 1); // 3, akuya, true

    // 获取栈顶索引,即栈元素个数
    const int top = lua_gettop(L);
    printf("stack size: %d\n", top);

    lua_close(L);
}

void SetTop()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushinteger(L, 3); // 3
    lua_pushstring(L, "akuya"); // 3, akuya
    lua_pushboolean(L, 1); // 3, akuya, true

    // 获取栈顶索引,即栈元素个数
    int stackSize = lua_gettop(L);
    printf("stack size before settop: %d\n", stackSize);

    // 设置栈顶索引,多余的被移除,缺少的补充nil
    lua_settop(L, 2);
    stackSize = lua_gettop(L);
    printf("stack size after settop: %d\n", stackSize);

    lua_close(L);
}

int main()
{
    Error();
    GetTop();
    SetTop();
}

#endif
