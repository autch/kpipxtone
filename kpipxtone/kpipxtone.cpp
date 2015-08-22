/* kpipxtone.cpp -- DLL export function for KbMedia Player
 * Copyright (c) 2008, Autch.  Distributed under the terms of zlib/libpng license.
 */
// kpipxtone.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "kpi.h"

#define KPIPXTONE_VERSION   ((1 << 8) | 2)      // 1.02
#ifdef _DEBUG
#define KPIPXTONE_DESC      "Pxtone collage player plugin for KbMedia Player [DEBUG]"
#else
#define KPIPXTONE_DESC      "Pxtone collage player plugin for KbMedia Player"
#endif
#define KPIPXTONE_COPYRIGHT "Copyright (c) 2008, 2015, Autch.  pxtone by Studio Pixel.  All rights reserved."

extern "C"
KMPMODULE* APIENTRY kmp_GetTestModule()
{
  static const char* pszExts[] = { ".pttune", ".ptcop", NULL };
  static KMPMODULE kpiModule =
  {
		KMPMODULE_VERSION,				// DWORD dwVersion;
		KPIPXTONE_VERSION,    			  // DWORD dwPluginVersion;
		KPIPXTONE_COPYRIGHT, 		    // const char	*pszCopyright;
		KPIPXTONE_DESC,							// const char	*pszDescription;
		pszExts,									// const char	**ppszSupportExts;
		(DWORD)-1,												// DWORD dwReentrant;
		kpiInit,									// void (WINAPI *Init)(void);
		kpiDeinit,								// void (WINAPI *Deinit)(void);
		kpiOpen,									// HKMP (WINAPI *Open)(const char *cszFileName, SOUNDINFO *pInfo);
		NULL,	            				// HKMP (WINAPI *OpenFromBuffer)(const BYTE *Buffer, DWORD dwSize, SOUNDINFO *pInfo);
		kpiClose,									// void (WINAPI *Close)(HKMP hKMP);
		kpiRender,								// DWORD (WINAPI *Render)(HKMP hKMP, BYTE* Buffer, DWORD dwSize);
		kpiSetPosition						// DWORD (WINAPI *SetPosition)(HKMP hKMP, DWORD dwPos);
  };
  return &kpiModule;
}

extern "C"
BOOL WINAPI kmp_GetTestTagInfo(const char *cszFileName, IKmpTagInfo *pInfo)
{
	pxtone_Ready(NULL, 2, 44100, 16, 0, TRUE, NULL);

	if (!pxtone_Tune_Load(NULL, NULL, cszFileName)) {
		pxtone_Release();
		return FALSE;
	}

	pInfo->SetValueA(SZ_KMP_TAGINFO_NAME_TITLE, pxtone_Tune_GetName());
	pInfo->SetValueA(SZ_KMP_TAGINFO_NAME_ARTIST, pxtone_Tune_GetComment());

	pxtone_Tune_Release();

	pxtone_Release();

	return TRUE;
}
