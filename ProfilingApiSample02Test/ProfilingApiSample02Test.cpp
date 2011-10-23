// ProfilingApiSample02Test.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

namespace {

    // ProfilingApiSample02Test.exe --gtest_filter=ProfilingApiSample02TestSuite.ProfilingApiSample02Test
    TEST(ProfilingApiSample02TestSuite, ProfilingApiSample02Test)
    {
        CComPtr<ICorProfilerCallback2> pCallback;
        ASSERT_HRESULT_SUCCEEDED(
            ::CoCreateInstance(__uuidof(ExeWeaver2), NULL, CLSCTX_INPROC_SERVER, 
                               IID_ICorProfilerCallback2, 
                               reinterpret_cast<void**>(&pCallback))
        );
        ASSERT_TRUE(pCallback.p != NULL);
    }
}
