// MetaDataApiSample02Test.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

namespace {

    // MetaDataApiSample02Test.exe --gtest_filter=MetaDataApiSample02TestSuite.MetaDataApiSample02Test
    TEST(MetaDataApiSample02TestSuite, MetaDataApiSample02Test)
    {
        IMetaDataInfoPtr pMetaDataInfo;
        ASSERT_HRESULT_SUCCEEDED(pMetaDataInfo.CreateInstance(__uuidof(MetaDataInfo)));

        try
        {
            pMetaDataInfo->Get(L"..\\MetaDataApiSample02Target\\bin\\Debug\\MetaDataApiSample02Target.exe");
        }
        catch (_com_error& e)
        {
            FAIL() << e.Description();
        }
    }
}
