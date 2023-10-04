#include "Common.h"

#if _04_MetaTable3

class Student
{
public:
    Student(int age, const string& name)
        : Age(age), Name(name)
    {
        cout << "Constructor Student" << endl;
    }

    virtual ~Student() { cout << "Destructor Student" << endl; }

    void SetAge(int age) { Age = age; }
    int GetAge() const { return Age; }
    void SetName(const string& name) { Name = name; }
    const string& GetName() const { return Name; }

    virtual void ShowSelfInfo()
    {
        cout << "Age:" << Age << " Name:" << Name << endl;
    }

private:
    int Age;
    string Name;
};

Student* GetStudent(lua_State* lua, int arg)
{
    // 从栈顶取userdata，这个是C++的对象指针
    luaL_checktype(lua, arg, LUA_TUSERDATA);
    // 检测[栈arg]是userdata,并且有对应tname的matatable
    void* userData = luaL_checkudata(lua, arg, "MyMetaTable");
    luaL_argcheck(lua, userData != NULL, 1, "user data error");
    return *static_cast<Student**>(userData);
}

int pcf_DeleteStudentClassToLua(lua_State* lua)
{
    const Student* pStu = GetStudent(lua, 1);
    delete pStu;

    return 1;
}

int pcf_SetAge(lua_State* lua)
{
    Student* pStu = GetStudent(lua, 1);
    luaL_checktype(lua, -1, LUA_TNUMBER);
    const int age = static_cast<int>(luaL_checkinteger(lua, -1));
    pStu->SetAge(age);
    return 0;
}

int pcf_GetAge(lua_State* lua)
{
    const Student* pStu = GetStudent(lua, 1);
    const int age = pStu->GetAge();
    lua_pushinteger(lua, age);
    return 1;
}

int pcf_SetName(lua_State* lua)
{
    Student* pStu = GetStudent(lua, 1);
    luaL_checktype(lua, -1, LUA_TSTRING);
    const string name = luaL_checkstring(lua, -1);
    pStu->SetName(name);
    return 0;
}

int pcf_GetName(lua_State* lua)
{
    const Student* pStu = GetStudent(lua, 1);

    const string& name = pStu->GetName();
    lua_pushstring(lua, name.c_str());
    return 1;
}

int pcf_ShowSelfInfo(lua_State* lua)
{
    Student* pStu = GetStudent(lua, 1);
    pStu->ShowSelfInfo();
    return 0;
}

int pcf_CreateStudentClassToLua(lua_State* lua)
{
    const int age = static_cast<int>(luaL_checkinteger(lua, 1));
    const string name = luaL_checkstring(lua, 2);
    // 创建userdata，搞到对象指针
    const auto ppStu = static_cast<Student**>(lua_newuserdata(lua, sizeof(Student)));
    (*ppStu) = new Student(age, name);
    // 获取册表对应MyMetaTable的元表
    luaL_getmetatable(lua, "MyMetaTable"); // obj, metatable
    lua_setmetatable(lua, -2); // obj

    return 1;
}

static constexpr luaL_Reg method[] = {
    {"SetAge", pcf_SetAge},
    {"GetAge", pcf_GetAge},
    {"SetName", pcf_SetName},
    {"GetName", pcf_GetName},
    {"ShowSelfInfo", pcf_ShowSelfInfo},
    {"Student", pcf_CreateStudentClassToLua},
    {"__gc", pcf_DeleteStudentClassToLua},
    {nullptr, nullptr}
};

int luaOpenMyModule(lua_State* lua)
{
    // 创建元表,加入注册表对应MyMetaTable,并入栈
    luaL_newmetatable(lua, "MyMetaTable");
    // 复制栈-1并入栈
    lua_pushvalue(lua, -1);
    // [栈-2].__index = 栈顶,并弹出栈顶
    // 将元表设置成自己
    lua_setfield(lua, -2, "__index");
    // 将method数组中的所有函数注册到table中,0表示不使用upvalue
    luaL_setfuncs(lua, method, 0);
    return 1;
}

static constexpr luaL_Reg libs[] = {
    {"MyModule", luaOpenMyModule},
    {nullptr, nullptr}
};

void luaRegisterCppStudentLibs(lua_State* lua)
{
    const luaL_Reg* lib = libs;
    for (; lib->func; lib++)
    {
        // 调用openf(参数lib->func), 将结果设置到package.loaded[modname]
        // 好像已经require过一样,glb:将模块也存到global
        // 将模块的copy留在栈上
        luaL_requiref(lua, lib->name, lib->func, 1);
        lua_pop(lua, 1);
    }
}

int main()
{
    cout << "---------------- C++ start --------------------" << endl;

    lua_State* lua = luaL_newstate();
    luaL_openlibs(lua);
    luaRegisterCppStudentLibs(lua);
    luaL_dofile(lua, "./Lua/student.lua");
    lua_close(lua);

    cout << "---------------- C++ end --------------------" << endl;
}

#endif
