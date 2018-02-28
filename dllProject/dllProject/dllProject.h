#pragma once

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}




#ifdef DLLPROJECT_EXPORTS
#define DLLPROJECT_API __declspec(dllexport)
#else
#define DLLPROJECT_API __declspec(dllimport)
#endif

extern "C" DLLPROJECT_API int luaL_dllProject(lua_State* L);


