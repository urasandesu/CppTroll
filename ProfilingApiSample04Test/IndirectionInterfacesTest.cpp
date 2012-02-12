#include "stdafx.h"

#ifndef INDIRETIONINTERFACES_H
#include <IndirectionInterfaces.h>
#endif

namespace {

    void Hoge()
    {
    }

    // ProfilingApiSample04Test.exe --gtest_filter=InstanceGettersTestSuite.*
    class InstanceGettersTestSuite : public testing::Test
    {
    protected:
        virtual void SetUp() 
        {
            InstanceGettersUnload();
        }
        
        virtual void TearDown()
        {
            InstanceGettersUnload();
        }
    };

    TEST_F(InstanceGettersTestSuite, InstanceGettersTestRecordExists01)
    {
        using namespace std;
        using namespace boost;

        typedef void (*HogePtr)();

        LPCWSTR key = L"ProfilingApiSample04Framework.IndirectionHolder`1<System.Func`1<System.DateTime>>, ProfilingApiSample04Framework, Version=1.0.0.0, Culture=neutral, PublicKeyToken=6724069a628e8cb0";

        {
            HogePtr pfnHoge = Hoge;
            ASSERT_TRUE(InstanceGettersTryAdd(key, pfnHoge) == TRUE);
        }

        {
            void const *pFuncPtr = NULL;
            ASSERT_TRUE(InstanceGettersTryGet(key, &pFuncPtr) == TRUE);
            ASSERT_EQ(static_cast<HogePtr>(Hoge), pFuncPtr);
        }
    }


    TEST_F(InstanceGettersTestSuite, InstanceGettersTestRecordNotExists01)
    {
        using namespace std;
        using namespace boost;

        typedef void (*HogePtr)();

        {
            LPCWSTR key = L"ProfilingApiSample04Framework.IndirectionHolder`1<System.Func`1<System.DateTime>>, ProfilingApiSample04Framework, Version=1.0.0.0, Culture=neutral, PublicKeyToken=6724069a628e8cb0";
            HogePtr pfnHoge = Hoge;
            ASSERT_TRUE(InstanceGettersTryAdd(key, pfnHoge) == TRUE);
        }

        {
            LPCWSTR key = L"ProfilingApiSample04Framework.IndirectionHolder`1<System.Func`1<System.String>>, ProfilingApiSample04Framework, Version=1.0.0.0, Culture=neutral, PublicKeyToken=6724069a628e8cb0";
            void const *pFuncPtr = NULL;
            ASSERT_TRUE(InstanceGettersTryGet(key, &pFuncPtr) == FALSE);
            ASSERT_EQ(static_cast<HogePtr>(NULL), pFuncPtr);
        }
    }
}
