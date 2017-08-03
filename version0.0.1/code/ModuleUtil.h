#pragma once
#include <string>
#include <windows.h>

bool LoadModule(HMODULE& hmodule, const std::string& libpath)
{
	if (hmodule == NULL/*INVALID_HANDLE_VALUE*/)
		hmodule = LoadLibraryA(libpath.c_str());

	if (hmodule == NULL/*INVALID_HANDLE_VALUE*/)
	{
		//DBMsg << "LoadLibraryA failed for:" << libpath.c_str() << EndLine;
		return false;
	}
	return true;
}
HMODULE LoadModule(const std::string& libpath)
{
	HMODULE hmodule = NULL;
	LoadModule(hmodule, libpath);
	return hmodule;
}

template <typename TFunc>
bool GetFunctionFromModule(TFunc& ofunc, HMODULE hmodule, const char* pszfuncName)
{
	if (hmodule != INVALID_HANDLE_VALUE)
	{
		TFunc ofunc = GetProcAddress(hmodule, pszfuncName);
		if (ofunc != NULL)
		{
			return true;
		}
	}
	return false;
}

template <typename TFunc>
TFunc GetFunctionFromModule(HMODULE hmodule, const char* pszfuncName)
{
	TFunc ofunc = NULL;
	if (hmodule != INVALID_HANDLE_VALUE)
	{
		ofunc = (TFunc)GetProcAddress(hmodule, pszfuncName);
	}
	return ofunc;
}