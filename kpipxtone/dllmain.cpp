/* dllmain.cpp -- DllMain()
 * Copyright (c) 2008, Autch.  Distributed under the terms of zlib/libpng license.
 */
 // dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "stdafx.h"

HMODULE g_hModule;

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		g_hModule = hModule;
		DisableThreadLibraryCalls(hModule);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

