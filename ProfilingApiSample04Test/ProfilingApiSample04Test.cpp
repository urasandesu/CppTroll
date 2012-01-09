// ProfilingApiSample04Test.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"


namespace {

    // SET COR_ENABLE_PROFILING=1
    // SET COR_PROFILER={98B5B08A-C625-4CA2-B1C8-157477A58945}
    // ProfilingApiSample04Target.exe
    // 
    // ProfilingApiSample04Test.exe --gtest_filter=ProfilingApiSample04TestSuite.ProfilingApiSample04Test
    TEST(ProfilingApiSample04TestSuite, ProfilingApiSample04Test)
    {
        using namespace std;
        using namespace boost;

        ATL::CComPtr<ICorProfilerCallback2> pCallback;
        ASSERT_HRESULT_SUCCEEDED(
            ::CoCreateInstance(__uuidof(ExeWeaver4), NULL, CLSCTX_INPROC_SERVER, 
                               IID_ICorProfilerCallback2, 
                               reinterpret_cast<void **>(&pCallback))
        );
        ASSERT_TRUE(pCallback.p != NULL);
    }
}
