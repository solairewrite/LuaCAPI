// 失败
#include "Common.h"

#if _03_MetaTable2

#define FOO "Foo"

typedef struct Foo {
	int x;
	int y;
} Foo;


static Foo *toFoo(lua_State *L, int index)
{

	Foo *bar = (Foo *)lua_touserdata(L, index);
	// if (bar == NULL) luaL_typerror(L, index, FOO);
	return bar;
}

static Foo *checkFoo(lua_State *L, int index)
{
	Foo *bar;
	luaL_checktype(L, index, LUA_TUSERDATA);
	bar = (Foo *)luaL_checkudata(L, index, FOO);
	// if (bar == NULL) luaL_typerror(L, index, FOO);
	return bar;
}

static Foo *pushFoo(lua_State *L)
{
	Foo *bar = (Foo *)lua_newuserdata(L, sizeof(Foo));

	luaL_getmetatable(L, FOO);
	lua_setmetatable(L, -2);
	return bar;
}


static int Foo_new(lua_State *L)
{
	int x = luaL_optinteger(L, 1, 0);
	int y = luaL_optinteger(L, 2, 0);
	Foo *bar = pushFoo(L);
	bar->x = x;
	bar->y = y;
	return 1;
}

static int Foo_yourCfunction(lua_State *L)
{
	Foo *bar = checkFoo(L, 1);
	printf("this is yourCfunction\t");
	lua_pushnumber(L, bar->x);
	lua_pushnumber(L, bar->y);
	return 2;
}

static int Foo_setx(lua_State *L)
{

	Foo *bar = checkFoo(L, 1);
	bar->x = luaL_checkinteger(L, 2);
	lua_settop(L, 1);
	return 1;
}

static int Foo_sety(lua_State *L)
{
	Foo *bar = checkFoo(L, 1);
	bar->y = luaL_checkinteger(L, 2);
	lua_settop(L, 1);
	return 1;
}

static int Foo_add(lua_State *L)
{
	Foo *bar1 = checkFoo(L, 1);
	Foo *bar2 = checkFoo(L, 2);
	Foo *sum = pushFoo(L);
	sum->x = bar1->x + bar2->x;
	sum->y = bar1->y + bar2->y;
	return 1;
}

static int Foo_dot(lua_State *L)
{
	Foo *bar1 = checkFoo(L, 1);
	Foo *bar2 = checkFoo(L, 2);
	lua_pushnumber(L, bar1->x * bar2->x + bar1->y * bar2->y);
	return 1;
}

static const luaL_Reg Foo_methods[] = {
	{ "new",           Foo_new },
	{ "yourCfunction", Foo_yourCfunction },
	{ "setx",          Foo_setx },
	{ "sety",          Foo_sety },
	{ "add",           Foo_add },
	{ "dot",           Foo_dot },
	{ 0, 0 }
};

static int Foo_gc(lua_State *L)
{
	printf("bye, bye, bar = %p\n", toFoo(L, 1));
	return 0;
}

static int Foo_tostring(lua_State *L)
{
	char buff[32];
	sprintf_s(buff, "%p", toFoo(L, 1));
	lua_pushfstring(L, "Foo (%s)", buff);
	return 1;
}

static int average(lua_State *L)
{
	return 0;
}

static const luaL_Reg Foo_meta[] = {
	{ "__gc",       Foo_gc },
	{ "__tostring", Foo_tostring },
	{ "__add",      Foo_add },
	{ "__call",      average },
	{ 0, 0 }
};



int Foo_register(lua_State *L)
{
	lua_getglobal(L, FOO);
	if (lua_isnil(L, -1)) {
		lua_pop(L, 1);
		lua_newtable(L);
	}
	luaL_setfuncs(L, Foo_methods, 0);
	lua_setglobal(L, FOO);
	//luaL_openlib(L, FOO, Foo_methods, 0);  /* create methods table,
										   //add it to the globals */
	luaL_newmetatable(L, "Foo");          /* create metatable for Foo,
										  and add it to the Lua registry */

	lua_getglobal(L, "BBB");
	if (lua_isnil(L, -1)) {
		lua_pop(L, 1);
		lua_newtable(L);
	}
	luaL_setfuncs(L, Foo_meta, 0);
	lua_setglobal(L, "BBB");
	//luaL_openlib(L, 0, Foo_meta, 0);    /* fill metatable */
	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3);               /* dup methods table*/
	lua_rawset(L, -3);                  /* metatable.__index = methods */
										//lua_pushliteral(L, "__metatable");
										//lua_pushvalue(L, -3);               /* dup methods table*/
										//lua_rawset(L, -3);                  /* hide metatable:
										//									metatable.__metatable = methods */

	lua_pop(L, 1);                      /* drop metatable */


	return 1;                           /* return methods on the stack */
}

int main()
{
	// 失败
	lua_State *L = luaL_newstate();

	luaopen_base(L);
	luaopen_table(L);
	luaopen_io(L);
	luaopen_string(L);
	luaopen_math(L);
	luaopen_debug(L);

	Foo_register(L);
	lua_pop(L, 1); //After foo register the methods are still on the stack, remove them.

	// luaL_dofile(L, "a.lua");
	const char* str = Lua_Code(
	for n,v in Foo do print(n,v) end
	local a = Foo.new()
	a()
	Foo.setx(a,1)
	);
	luaL_dostring(L, str);

	lua_close(L);

	return 0;
}


#endif