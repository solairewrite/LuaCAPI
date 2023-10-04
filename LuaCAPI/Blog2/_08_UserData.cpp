// 失败
#include <windows.h>

#include "Common.h"

#if _08_UserData

typedef struct
{
    int X;
    int Y;
} Point;


void UserData()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // 创建用户数据类型,并入栈,返回指向用户数据的指针
    Point* P = (Point*)lua_newuserdata(L, sizeof(Point));
    P->X = 3;
    P->Y = 4;

    // 将用户数据关联到元表
    luaL_newmetatable(L, "Point");
    lua_setmetatable(L, -2);

    Point* P2 = (Point*)luaL_testudata(L, 1, "Point");
    if (P2)
    {
        printf("megumin %d %d\n", P2->X, P2->Y);
    }
    Point* P3 = (Point*)luaL_testudata(L, 1, "Point");
    if (P3)
    {
        printf("megumin %d %d\n", P3->X, P3->Y);
    }

    // lua中使用用户数据
    // lua_pushlightuserdata(L, P);
    lua_setglobal(L, "pt");
    luaL_dostring(L, "print(\"akuya\"); print(pt.X, pt.Y)");

    lua_close(L);
}

int main()
{
    // 失败
    UserData();
}

#endif
