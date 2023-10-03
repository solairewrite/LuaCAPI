#include "Common.h"

#include <windows.h>

#if _06_RequireCModule2

// 这里可以这样写，也可以写成static
extern "C" int Func1(lua_State* luaEnv)
{
    cout << "Func1 start Sleep 1s" << endl;
    Sleep(1000);
    cout << "Func1 end" << endl;
    return 0;
}

// 在lua中，调用这个函数时，需要传入两个number类型值
static int Func2(lua_State* luaEnv)
{
    // 检查栈顶的元素是不是number类型，然后赋值给op1
    auto op1 = luaL_checknumber(luaEnv, 1);
    auto op2 = luaL_checknumber(luaEnv, 2);
    // 计算op1+op2的结果值，然后压入lua栈顶（返回给lua）
    lua_pushnumber(luaEnv, op1 + op2);
    // 再返回给lua一个字符串
    lua_pushstring(luaEnv, "Func2 end");
    // 返回2个值
    return 2;
}

// 创建一个表,内容是要导出的函数
static luaL_Reg mylibs[]
    =
    {
        // func1是lua调用时的函数名
        {"func1", Func1},
        {"func2", Func2},
        // 用null收尾
        {NULL, NULL}
    };

// 定义一个module名，以备在lua中require
// “luaopen_”后面的“LuaCAPI”是require后面的名字,要与dll名字一致
extern "C" __declspec(dllexport)
int luaopen_LuaCAPI(lua_State* luaEnv)
{
    // 导出表
    luaL_newlib(luaEnv, mylibs);
    return 1;
}

#endif
