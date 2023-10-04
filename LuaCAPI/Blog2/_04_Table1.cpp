#include "Common.h"

#if _04_Table1

void CreateTable()
{
    lua_State* L = luaL_newstate();

    luaL_openlibs(L);

    // 创建一个空表并入栈
    // 参数: 预分配数组部分大小,预分配哈希部分大小
    lua_createtable(L, 0, 0);

    // 对表进行操作
    lua_pushstring(L, "name");
    lua_pushstring(L, "akuya");
    // 将键值对出栈,表还在栈内
    lua_settable(L, -3);

    lua_pushstring(L, "age");
    lua_pushnumber(L, 18);
    lua_settable(L, -3);

    // 将栈顶的表设置为全局变量,并出栈
    lua_setglobal(L, "myTable");

    luaL_dostring(L, "print(myTable.name, myTable.age)");

    lua_close(L);
}

void GetTable()
{
    lua_State* L = luaL_newstate();

    luaL_openlibs(L);

    // 创建新表并入栈
    lua_newtable(L);

    // 操作表
    lua_pushstring(L, "name");
    lua_pushstring(L, "megumin");
    lua_settable(L, -3);

    lua_pushstring(L, "age");
    lua_pushnumber(L, 17);
    lua_settable(L, -3);

    // 获取表的值
    lua_pushstring(L, "name"); // -1, 2, table[1, -2]
    lua_gettable(L, -2); // 从-2处获取表,将表的键name的值入栈,并将键出栈
    const char* name = lua_tostring(L, -1);

    lua_pushstring(L, "age"); // {}, "megumin", "age"
    lua_gettable(L, -3); // {}, "megumin", 17
    const int age = lua_tointeger(L, -1);

    printf("name: %s, age: %d\n", name, age);

    lua_close(L);
}

void SetTable()
{
    lua_State* L = luaL_newstate();

    luaL_openlibs(L);

    lua_newtable(L); // {}

    lua_pushstring(L, "name"); // {}, name
    lua_pushstring(L, "darkness"); // {}, name, darkness
    lua_settable(L, -3); // {}

    lua_pushstring(L, "age"); // {}, age
    lua_pushnumber(L, 19); // {}, age, 19
    lua_settable(L, -3); // {}

    lua_setglobal(L, "myTable");

    luaL_dostring(L, "print(myTable.name, myTable.age)");

    lua_close(L);
}

int main()
{
    CreateTable();
    GetTable();

    SetTable();
}

#endif
