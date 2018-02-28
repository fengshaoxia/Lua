// dllProject.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "dllProject.h"

#include "gdiplus.h"

using namespace Gdiplus;

void char2TCHAR(const char* instr, TCHAR outstr[MAX_PATH])
{
#ifdef UNICODE
	MultiByteToWideChar(CP_ACP, 0, instr, -1, outstr, MAX_PATH);
#else
	strcpy_s(outstr, instr);
#endif
}

void TCHAR2char(const LPTSTR instr, char outstr[MAX_PATH])
{
#ifdef UNICODE
	if (NULL != instr) {
		int nInputStrLen = wcslen(instr);
		WideCharToMultiByte(CP_ACP, 0, instr, nInputStrLen, outstr, MAX_PATH, 0, 0);
	}
#else
	strcpy_s(instr, outstr);
#endif
}

//初始化gdiplus环境
extern "C" int lua_initGdiplus(lua_State* L)
{
	//init gdiplus
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	lua_pushnumber(L, gdiplusToken);

	return 1;
}

//release gdiplus
extern "C" int lua_releaseGdiplus(lua_State* L)
{
	ULONG_PTR gdiplusToken = lua_tonumber(L, -1);
	GdiplusShutdown(gdiplusToken);
	return 0;
}

extern "C" int lua_initFont(lua_State* L)
{
	//get font's file path
	const char* szFontFilePath = lua_tostring(L, -1);
	if (NULL == szFontFilePath) {
		lua_pushstring(L, "");
		return 1;
	}

	PrivateFontCollection pfc;
	TCHAR tFilePath[MAX_PATH] = { 0 };
	char2TCHAR(szFontFilePath, tFilePath);
	pfc.AddFontFile(tFilePath);

	int nCount = pfc.GetFamilyCount();

	FontFamily* pFontFamily = (FontFamily*)new FontFamily[nCount];
	int nFound = 0;
	pfc.GetFamilies(nCount, pFontFamily, &nFound);
	if (nFound <= 0) {
		lua_pushstring(L, "");
		return 1;
	}

	TCHAR szFamilyName[100] = { 0 };
	pFontFamily[0].GetFamilyName(szFamilyName);

	char fontName[MAX_PATH] = { 0 };

	TCHAR2char(szFamilyName, fontName);

	lua_pushstring(L, fontName);

	return 1;
}

extern "C" int lua_calulateStringSize(lua_State* L)
{
	return 0;
}

static const struct luaL_reg dllProject[] = {
	{"calulateStringSize", lua_calulateStringSize },
	{NULL, NULL}
};

extern "C" DLLPROJECT_API int luaL_dllProject(lua_State* L)
{
	luaL_register(L, "dllProject", dllProject);
	return 1;
}
