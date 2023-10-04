#include "Common.h"

#if _03_Global1

void GetGlobal()
{
    lua_State* L = luaL_newstate();

    luaL_openlibs(L);

    // 执行lua脚本,定义全局变量
    luaL_dostring(L, "myVariable = 'Akuya'");

    // 获取全局变量并压入堆栈
    lua_getglobal(L, "myVariable");

    // 从堆栈中获取数值
    const char* value = lua_tostring(L, -1);

    printf("myVariable : %s\n", value);

    lua_close(L);
}

void SetGlobal()
{
    lua_State* L = luaL_newstate();

    luaL_openlibs(L);

    lua_pushstring(L, "Akuya");

    // 将栈顶的值设置为全局变量,并出栈
    lua_setglobal(L, "variable1");

    luaL_dostring(L, "print(variable1)");
    luaL_dostring(L, "print('megumin')");

    lua_close(L);
}

int main()
{
    GetGlobal();
    SetGlobal();
}

#endif
