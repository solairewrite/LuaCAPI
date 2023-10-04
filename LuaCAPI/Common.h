#pragma once

#include "lua.hpp"

#include <iostream>

using namespace std;

#define Lua_Code(...) #__VA_ARGS__

#define _00_Main 0

#define _01_Global 0
#define _02_CallLuaFunc 0
#define _03_LuaCallCFunc 0
#define _04_CClosure 0
#define _05_RequireCModule 0
#define _06_RequireCModule2 0

#define _01_State1 0
#define _02_Stack1 0
#define _03_Global1 0
#define _04_Table1 0
#define _05_Func1 0
#define _06_Func2 1
