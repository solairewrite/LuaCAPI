#include "Common.h"
#include <string.h>

#if _03_LuaCallCFunc

#define QUOTE(...) #__VA_ARGS__
static const char *lua_code = QUOTE(
  local parts = {string_split("Hello, Lua C API", " ")}
  print(#parts)
  for i = 1, #parts do
    print(parts[i])
  end
);

/* Output
2
Hello,
Lua C API
 */

// 将str的前len个字符,按照sep分隔为2部分
// 返回lua返回值的个数
static int cstring_split(lua_State* L, const char* str, size_t len, const char sep)
{
    int nresults = 0;

    // 搜索str的前len个字符中第一个sep的位置
    const char* pos = static_cast<const char*>(memchr(str, sep, len));
    if (pos != NULL)
    {
        // 将返回值1压入栈1,返回时,参数已经出栈
        lua_pushlstring(L, str, pos - str);
        len -= pos - str + 1;
        str = pos + 1;
        ++nresults;
    }

    // 将返回值2压入栈2
    lua_pushlstring(L, str, len);
    len = 0;
    ++nresults;

    return nresults;
}

// lua代码string_split("Hello, Lua C API", " ")
// 将参数1压入栈1,参数2压入栈2
static int l_string_split(lua_State* L)
{
    size_t len = 0;
    const char* str = NULL;
    const char* sep = NULL;

    // 参数数量
    const int argc = lua_gettop(L);
    if (argc == 0)
    {
        return 0;
    }
    if (argc > 1)
    {
        // 分隔符
        sep = lua_tostring(L, 2);
    }

    if (sep != NULL)
    {
        str = lua_tolstring(L, 1, &len);
        if (str != NULL)
        {
            return cstring_split(L, str, len, *sep);
        }
    }

    // just returns str
    lua_pushvalue(L, 1);
    return 1;
}

int main(int argc, char* argv[])
{
    int status = 0;

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L, l_string_split);
    lua_setglobal(L, "string_split");

    status = luaL_loadstring(L, lua_code) || lua_pcall(L, 0, 0, 0);
    if (status)
    {
        fprintf(stderr, "%s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    lua_close(L);
    return status;
}

#endif
