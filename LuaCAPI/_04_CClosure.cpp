#include "Common.h"

#if _04_CClosure

#define QUOTE(...) #__VA_ARGS__
static const char* lua_code = QUOTE(
    random = random_generator(1234);
    print(random());
    print(random());
);
/* Output
3558
1960
*/

// 算法提取自 POSIX.1-2001 rand()实现
static int l_random_next(lua_State* L)
{
    // 获取闭包参数1
    uint32_t seed = (uint32_t)lua_tointeger(L, lua_upvalueindex(1));
    int32_t next_number;
    seed = seed * (uint32_t)1103515245 + (uint32_t)12345;
    next_number = (int32_t)((uint32_t)seed / (int32_t)65536) % (int32_t)32768;

    // update upvalue
    lua_pushinteger(L, seed);
    // 修改闭包参数1的值
    lua_replace(L, lua_upvalueindex(1));

    // 将返回值入栈
    lua_pushinteger(L, next_number);
    return 1;
}

static int l_random_generator(lua_State* L)
{
    // 获取lua参数1
    lua_Integer seed = (lua_Integer)lua_tointeger(L, 1);

    lua_pushinteger(L, seed);
    // 将闭包函数入栈,入栈1个闭包参数seed
    lua_pushcclosure(L, l_random_next, 1);

    return 1;
}

int main(int argc, char* argv[])
{
    int status = 0;

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L, l_random_generator);
    lua_setglobal(L, "random_generator");

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
