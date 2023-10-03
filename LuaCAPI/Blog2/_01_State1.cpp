#include "Common.h"

#if _01_State1

int main()
{
    lua_State* L = luaL_newstate(); // 创建 Lua 状态,即Lua虚拟机实例

    luaL_openlibs(L); // 初始化 Lua 状态的全局环境和库

    luaL_dostring(L, "print('Hello, Lua!')"); // 执行 Lua 脚本

    lua_close(L); // 关闭并销毁 Lua 状态

    return 0;
}

#endif
