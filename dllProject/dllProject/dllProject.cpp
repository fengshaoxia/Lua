// dllProject.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "dllProject.h"

extern "C" int lua_calulateStringSize(lua_State* L)
{
	const char* winName = lua_tostring(L, -1);
	HWND hq = FindWindow(NULL, winName);
	HDC hdc = GetDC(hq);

	ReleaseDC(hq, hdc);
	return 0;
}

static const struct luaL_reg dllProject[] = {
	{"calulateStringSize", lua_calulateStringSize },
	{NULL, NULL}
};

extern "C" __declspec(dllexport)
DLLPROJECT_API int luaL_dllProject(lua_State* L)
{
	luaL_register(L, "dllProject", dllProject);
	return 1;
}
