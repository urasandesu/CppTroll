#include "stdafx.h"

#ifndef URASANDESU_NANONYM_NANONYMEXCEPTION_H
#include "Urasandesu/NAnonym/NAnonymException.h"
#endif

#ifndef URASANDESU_NANONYM_STACKFRAME_H
#include "Urasandesu/NAnonym/StackFrame.h"
#endif

#ifndef URASANDESU_NANONYM_STACKTRACE_H
#include "Urasandesu/NAnonym/StackTrace.h"
#endif

namespace {

    // MetaDataApiSample02Test.exe --gtest_filter=MetaDataApiSample02TestSuite.NAnonymExceptionTest
    TEST(MetaDataApiSample02TestSuite, NAnonymExceptionTest)
    {
        using namespace std;
        using namespace boost;
        using namespace Urasandesu::NAnonym;
        
        try
        {
            BOOST_THROW_EXCEPTION(NAnonymException());
        }
        catch (NAnonymException &e)
        {
            string msg = diagnostic_information(e);
            cout << msg << endl;
            string expectContaining = "testing";
            ASSERT_TRUE(msg.find(expectContaining) != string::npos);
        }
    }
}
