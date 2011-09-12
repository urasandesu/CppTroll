// MetaDataApiSample01Test.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include <boost/test/unit_test.hpp>

namespace {

    BOOST_AUTO_TEST_SUITE(MetaDataApiSample01TestSuite)

    // MetaDataApiSample01Test --log_level=test_suite --run_test=MetaDataApiSample01TestSuite/MetaDataApiSample01Test
    // ildasm /out=hello.dasm /all /metadata=SCHEMA /metadata=HEAPS /metadata=CSV /source hello.exe
    BOOST_AUTO_TEST_CASE(MetaDataApiSample01Test)
    {
        IExeCreatorPtr pExeCreator;
        HRESULT hr = pExeCreator.CreateInstance(__uuidof(ExeCreator));
        BOOST_REQUIRE(SUCCEEDED(hr));

        try
        {
            hr = pExeCreator->Create(L"hello.exe");
            BOOST_REQUIRE(SUCCEEDED(hr));
        }
        catch (_com_error& e)
        {
            BOOST_FAIL(e.Description());
        }
    }

    BOOST_AUTO_TEST_SUITE_END()
}
