﻿// dllmain.cpp : DllMain の実装

#include "stdafx.h"
#include "resource.h"
#include "ProfilingApiSample03_i.h"
#include "dllmain.h"

CProfilingApiSample03Module _AtlModule;

// DLL エントリ ポイント
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved); 
}
