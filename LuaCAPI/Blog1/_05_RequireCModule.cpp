// 项目属性中设置
// General -> Configuration Type : Dynamic Library (.dll)
// 默认是Application (.exe)

#include "Common.h"

#if _05_RequireCModule

#ifdef _MSC_VER
// 注意要加extern "C",dll用此写法
#define LUA_EXPORT    extern "C" __declspec(dllexport)
#else
// .so用此写法
#define LUA_EXPORT    extern "C" extern
#endif

static int string_split(lua_State* L, const char* str, size_t len, const char sep, lua_Integer count)
{
    int nresults = 0;
    const char* pos = NULL;

    while (count > 1 && len > 0)
    {
        const char* pos = static_cast<const char*>(memchr(str, sep, len));
        if (pos != NULL)
        {
            lua_pushlstring(L, str, pos - str);
            len -= pos - str + 1;
            str = pos + 1;
        }
        else
        {
            lua_pushlstring(L, str, len);
            len = 0;
        }
        ++nresults;
        --count;
    }

    if (len > 0 || pos != NULL)
    {
        lua_pushlstring(L, str, len);
        nresults += 1;
    }

    return nresults;
}

static int l_string_split(lua_State* L)
{
    size_t len = 0;
    const char* str = NULL;
    const char* sep = NULL;
    lua_Integer count = LUA_MAXINTEGER;

    int argc = lua_gettop(L);
    if (argc == 0)
    {
        return 0;
    }
    if (argc > 1)
    {
        sep = lua_tostring(L, 2);
    }
    if (argc > 2)
    {
        count = lua_tointeger(L, 3);
    }

    if (sep != NULL && count > 1)
    {
        str = lua_tolstring(L, 1, &len);
        if (str != NULL)
        {
            return string_split(L, str, len, *sep, count);
        }
    }

    // just returns str
    lua_pushvalue(L, 1);
    return 1;
}

// 定义一个module名，以备在lua中require
// “luaopen_”后面的“LuaCAPI”是require后面的名字,要与dll名字一致
LUA_EXPORT int luaopen_LuaCAPI(lua_State* L)
{
    lua_createtable(L, 0, 1);

    lua_pushcfunction(L, l_string_split);
    lua_setfield(L, -2, "string_split");

    /** 方法很多的时候可以用 luaL_newlib 来注册
    luaL_Reg l[] = {
      { "string_split", l_string_split },
      { NULL, NULL }
    };
    luaL_newlib(L, l);
    */

    return 1;
}

#endif
