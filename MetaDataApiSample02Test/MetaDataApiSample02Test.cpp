// MetaDataApiSample02Test.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

namespace {

    // MetaDataApiSample02Test.exe --gtest_filter=MetaDataApiSample02TestSuite.MetaDataApiSample02Test
    TEST(MetaDataApiSample02TestSuite, MetaDataApiSample02Test)
    {
        IMetaDataObjectPtr pMetaDataObject;
        ASSERT_HRESULT_SUCCEEDED(pMetaDataObject.CreateInstance(__uuidof(MetaDataObject)));

        try
        {
            pMetaDataObject->Get(L"..\\MetaDataApiSample02Target\\bin\\Debug\\MetaDataApiSample02Target.exe");
        }
        catch (_com_error& e)
        {
            FAIL() << e.Description();
        }
    }
}
