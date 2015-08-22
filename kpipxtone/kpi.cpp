/* kpi.cpp -- Actual handlers of DLL entry points for KbMedia Player plugin.
 * Copyright (c) 2008, Autch.  Distributed under the terms of zlib/libpng license.
 */

#include "stdafx.h"
#include "kpi.h"
#include "CPxtoneDecoder.h"

char g_szIniFileName[MAX_PATH];

// 本当に使いたいデコーダクラス
typedef CPxtoneDecoder CKpiTargetDecoder;

void WINAPI kpiInit()
{
	char* pDot;

	GetModuleFileName(::g_hModule, ::g_szIniFileName, MAX_PATH);
	pDot = strrchr(g_szIniFileName, '.');
	strncpy_s(pDot, MAX_PATH - (pDot - g_szIniFileName), ".ini", 4);

	pxtone_Ready(NULL, 2, 44100, 16, 0, TRUE, NULL);
}

void WINAPI kpiDeinit()
{
	pxtone_Release();
}

HKMP WINAPI kpiOpen(const char* cszFileName, SOUNDINFO* pInfo)
{
	CKpiTargetDecoder* d = new CKpiTargetDecoder();
	if (d->Open((LPSTR)cszFileName, pInfo))
		return (HKMP)d;
	else
		delete d;
	return NULL;
}

void WINAPI kpiClose(HKMP hKMP)
{
	if (hKMP)
		delete (CKpiTargetDecoder*)hKMP;
}

DWORD WINAPI kpiRender(HKMP hKMP, BYTE* Buffer, DWORD dwSize)
{
	CKpiTargetDecoder* d = (CKpiTargetDecoder*)hKMP;
	if (d)
		return d->Render(Buffer, dwSize);
	return 0;
}

DWORD WINAPI kpiSetPosition(HKMP hKMP, DWORD dwPos)
{
	CKpiTargetDecoder* d = (CKpiTargetDecoder*)hKMP;
	if (d)
		return d->SetPosition(dwPos);
	return 0;
}

UINT GetMyProfileInt(LPSTR szSectionName, LPSTR szKeyName, INT nDefault)
{
	return ::GetPrivateProfileInt(szSectionName, szKeyName, nDefault, ::g_szIniFileName);
}
