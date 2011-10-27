// ProfilingApiSample02Test.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#ifndef URASANDESU_NANONYM_UTILITIES_VALUECONVERTER_H
#include <Urasandesu/NAnonym/Utilities/ValueConverter.h>
#endif

namespace {

    // ProfilingApiSample02Test.exe --gtest_filter=ProfilingApiSample02TestSuite.TempTestTest
    TEST(ProfilingApiSample02TestSuite, TempTestTest)
    {
        using namespace std;
        using namespace boost;
        using namespace Urasandesu::NAnonym;
        using namespace Urasandesu::NAnonym::MetaData;
        using namespace Urasandesu::NAnonym::Profiling;
        using namespace Urasandesu::NAnonym::Utilities;
        
        
        ValueConverter<AssemblyMetaData *, ProcessProfile *> *pConv;

    }
}
