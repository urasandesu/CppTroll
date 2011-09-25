// MetaDataApiSample02Test.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include <boost/test/unit_test.hpp>

namespace {

    BOOST_AUTO_TEST_SUITE(MetaDataApiSample02TestSuite)

    // MetaDataApiSample02Test --log_level=test_suite --run_test=MetaDataApiSample02TestSuite/MetaDataApiSample02Test
    BOOST_AUTO_TEST_CASE(MetaDataApiSample02Test)
    {
        IMetaDataInfoPtr pMetaDataInfo;
        HRESULT hr = pMetaDataInfo.CreateInstance(__uuidof(MetaDataInfo));
        BOOST_REQUIRE(SUCCEEDED(hr));

        try
        {
            hr = pMetaDataInfo->Get(L"..\\MetaDataApiSample02Target\\bin\\Debug\\MetaDataApiSample02Target.exe");
            BOOST_REQUIRE(SUCCEEDED(hr));
        }
        catch (_com_error& e)
        {
            BOOST_FAIL(e.Description());
        }
    }

    BOOST_AUTO_TEST_SUITE_END()
}
