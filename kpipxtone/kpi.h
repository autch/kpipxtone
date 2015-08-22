
#pragma once

void WINAPI kpiInit();
void WINAPI kpiDeinit();
HKMP WINAPI kpiOpen(const char* cszFileName, SOUNDINFO* pInfo);
void WINAPI kpiClose(HKMP hKMP);
DWORD WINAPI kpiRender(HKMP hKMP, BYTE* Buffer, DWORD dwSize);
DWORD WINAPI kpiSetPosition(HKMP hKMP, DWORD dwPos);

extern HMODULE g_hModule;                 // dllmain.cpp

UINT GetMyProfileInt(LPSTR szSectionName, LPSTR szKeyName, INT nDefault = 0);
