// ProfilingApiSample01Test.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include <boost/test/unit_test.hpp>

namespace {

    BOOST_AUTO_TEST_SUITE(ProfilingApiSample01TestSuite)

    // ProfilingApiSample01Test --log_level=test_suite --run_test=ProfilingApiSample01TestSuite/ProfilingApiSample01Test
    // 
    // SET COR_ENABLE_PROFILING=1
    // SET COR_PROFILER={1DC70D11-5E46-48C6-BB07-75CFFF188327}
    // ProfilingApiSample01Target.exe
    //
    // ildasm /out=ProfilingApiSample01Target.exe.dasm /all /metadata=SCHEMA /metadata=HEAPS /metadata=CSV /source ProfilingApiSample01Target.exe
    BOOST_AUTO_TEST_CASE(ProfilingApiSample01Test)
    {
        HRESULT hr = E_FAIL;
        
        CComPtr<ICorProfilerCallback2> pCallback;
        hr = ::CoCreateInstance(__uuidof(ExeWeaver), NULL, CLSCTX_INPROC_SERVER, 
                                IID_ICorProfilerCallback2, 
                                reinterpret_cast<void**>(&pCallback));
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(pCallback.p != NULL);
    }

    BOOST_AUTO_TEST_SUITE_END()
}
