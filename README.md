# Windows编译Lua源码
## 下载Lua源码
[Lua](https://www.lua.org/download.html)

下载 lua-5.4.6.tar.gz

## 安装MinGW
[SourceForge](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-win32/seh/)

下载 x86_64-8.1.0-release-win32-seh-rt_v6-rev0.7z

配置系统环境变量Path  
D:\SoftwarePackage\MinGW\mingw64\bin

cmd验证安装成功 `gcc -v` 显示8.1.0

## MinGW编译Lua源码
在Makefile同级目录下  
D:\SoftwarePackage\lua5.4.6\lua-5.4.6  
cmd运行 `mingw32-make mingw`

成功后src文件夹生成lua.exe, Lua54.dll, luac.exe文件  

配置系统环境变量Path  
D:\SoftwarePackage\lua5.4.6\lua-5.4.6\src

cmd验证安装成功 `lua -v` 显示5.4.6

## VS2022编译Lua源码,生成静态库Lua.lib
[参考文章](https://blog.csdn.net/weixin_43603958/article/details/109015563)

将生成的lib文件重命名为Lua.lib,放到源码src目录下

## VS2022新项目调用Lua C API
项目属性配置:  

C/C++ -> General -> Additional Include Directories  
D:\SoftwarePackage\lua5.4.6\lua-5.4.6\src

Linker -> General -> Additional Library Directories  
D:\SoftwarePackage\lua5.4.6\lua-5.4.6\src

Linker -> Input  
添加 Lua.lib

添加文件

```
// Main.cpp
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

int main()
{
	lua_State* l = luaL_newstate();
	luaL_openlibs(l);
	luaL_dofile(l, "Main.lua");
	lua_close(l);
}
```

```
// Main.lua
print("sola akuya")
```

运行程序看是否有打印
