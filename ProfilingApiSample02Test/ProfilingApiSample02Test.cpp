// ProfilingApiSample02Test.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

namespace {

    // ProfilingApiSample02Test.exe --gtest_filter=ProfilingApiSample02TestSuite.ProfilingApiSample02Test
    // 
    // SET COR_ENABLE_PROFILING=1
    // SET COR_PROFILER={F60DB91B-5932-4964-818A-CA697CF46A5F}
    // SET NANONYM_TARGET_ASSEMBLY=ProfilingApiSample02Target
    // SET NANONYM_REPLACE_TYPE_FROM=0x02000002
    // SET NANONYM_REPLACE_METHOD_FROM=0x06000001
    // SET NANONYM_REPLACE_TYPE_TO=0x02000003
    // SET NANONYM_REPLACE_METHOD_TO=0x06000003
    // ProfilingApiSample02Target.exe
    //
    // ildasm /out=ProfilingApiSample02Target.exe.dasm /all /metadata=SCHEMA /metadata=HEAPS /metadata=CSV /source ProfilingApiSample02Target.exe
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
