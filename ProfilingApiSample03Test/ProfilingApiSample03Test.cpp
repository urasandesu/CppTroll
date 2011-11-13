﻿// ProfilingApiSample03Test.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"


namespace {

    // SET COR_ENABLE_PROFILING=1
    // SET COR_PROFILER={ACC35A1C-B127-4A75-9EB8-B4E54A49F6CF}
    // ProfilingApiSample03Target.exe
    // 
    // ProfilingApiSample03Test.exe --gtest_filter=ProfilingApiSample03TestSuite.ProfilingApiSample03Test
    // 
    // ildasm /out=ProfilingApiSample03Patch.dll.dasm /all /metadata=SCHEMA /metadata=HEAPS /metadata=CSV /source ProfilingApiSample03Patch.dll
    // 
    // ProfilingApiSample03Stubber.exe --input="C:\WINDOWS\Microsoft.NET\Framework\v2.0.50727\mscorlib.dll"
    TEST(ProfilingApiSample03TestSuite, ProfilingApiSample03Test)
    {
        CComPtr<ICorProfilerCallback2> pCallback;
        ASSERT_HRESULT_SUCCEEDED(
            ::CoCreateInstance(__uuidof(ExeWeaver3), NULL, CLSCTX_INPROC_SERVER, 
                               IID_ICorProfilerCallback2, 
                               reinterpret_cast<void**>(&pCallback))
        );
        ASSERT_TRUE(pCallback.p != NULL);
    }
}
