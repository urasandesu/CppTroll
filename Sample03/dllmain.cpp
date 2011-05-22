// dllmain.cpp : DllMain の実装

#include "stdafx.h"
#include "resource.h"
#include "Sample03_i.h"
#include "dllmain.h"

CSample03Module _AtlModule;

// DLL エントリ ポイント
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved); 
}
