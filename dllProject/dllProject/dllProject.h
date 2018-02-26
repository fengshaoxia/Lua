#pragma once

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <string>
using namespace std;

#ifdef DLLPROJECT_EXPORTS
#define DLLPROJECT_API __declspec(dllexport)
#else
#define DLLPROJECT_API __declspec(dllimport)
#endif

extern "C" __declspec(dllexport)DLLPROJECT_API int luaL_dllProject(lua_State* L);


