// ProfilingApiSample03Test.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"


namespace {

    // SET COR_ENABLE_PROFILING=1
    // SET COR_PROFILER={ACC35A1C-B127-4A75-9EB8-B4E54A49F6CF}
    // ProfilingApiSample03Target.exe
    // 
    // ProfilingApiSample03Test.exe --gtest_filter=ProfilingApiSample03TestSuite.ProfilingApiSample03Test
    // 
    // ildasm /out=ProfilingApiSample03Patch.dll.dasm /all /metadata ProfilingApiSample03Patch.dll
    // 
    // ProfilingApiSample03Stubber.exe
    // 
    // "C:\Program Files\xunit-1.8\xunit.console.x86.exe" ProfilingApiSample03TargetTest.dll /noshadow
    TEST(ProfilingApiSample03TestSuite, ProfilingApiSample03Test)
    {
        using namespace std;
        using namespace boost;

        CComPtr<ICorProfilerCallback2> pCallback;
        ASSERT_HRESULT_SUCCEEDED(
            ::CoCreateInstance(__uuidof(ExeWeaver3), NULL, CLSCTX_INPROC_SERVER, 
                               IID_ICorProfilerCallback2, 
                               reinterpret_cast<void**>(&pCallback))
        );
        ASSERT_TRUE(pCallback.p != NULL);
    }
}
