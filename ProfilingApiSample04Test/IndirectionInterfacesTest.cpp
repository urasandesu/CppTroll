#include "stdafx.h"

#ifndef INDIRETIONINTERFACES_H
#include <IndirectionInterfaces.h>
#endif

namespace {

    void Hoge()
    {
    }

#if 0
    // ProfilingApiSample04Test.exe --gtest_filter=IndirectionInterfacesTestSuite.*
    TEST(IndirectionInterfacesTestSuite, IndirectionTestRecordExists01)
    {
        using namespace std;
        using namespace boost;

        typedef void (*HogePtr)();

        IndirectionInfo indInfo;
        indInfo.m_assemblyName = L"mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=x86";
        indInfo.m_typeFullName = L"System.DateTime";
        indInfo.m_methodName = L"get_Now";

        {
            HogePtr pfnHoge = Hoge;
            ASSERT_TRUE(IndirectionSetFunctionPointer(&indInfo, pfnHoge) == TRUE);
        }

        {
            void const *pFuncPtr = NULL;
            ASSERT_TRUE(IndirectionGetFunctionPointer(&indInfo, &pFuncPtr) == TRUE);
            ASSERT_EQ(static_cast<HogePtr>(Hoge), pFuncPtr);
        }
    }


    TEST(IndirectionInterfacesTestSuite, IndirectionTestRecordNotExists01AssemblyNameDoesNotMatch)
    {
        using namespace std;
        using namespace boost;

        typedef void (*HogePtr)();

        {
            IndirectionInfo indInfo;
            indInfo.m_assemblyName = L"mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=x86";
            indInfo.m_typeFullName = L"System.DateTime";
            indInfo.m_methodName = L"get_Now";
            HogePtr pfnHoge = Hoge;
            ASSERT_TRUE(IndirectionSetFunctionPointer(&indInfo, pfnHoge) == TRUE);
        }

        {
            IndirectionInfo indInfo;
            indInfo.m_assemblyName = L"System, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=MSIL";
            indInfo.m_typeFullName = L"System.DateTime";
            indInfo.m_methodName = L"get_Now";
            void const *pFuncPtr = NULL;
            ASSERT_TRUE(IndirectionGetFunctionPointer(&indInfo, &pFuncPtr) == TRUE);
            ASSERT_EQ(static_cast<HogePtr>(NULL), pFuncPtr);
        }
    }


    TEST(IndirectionInterfacesTestSuite, IndirectionTestRecordNotExists02TypeNameDoesNotMatch)
    {
        using namespace std;
        using namespace boost;

        typedef void (*HogePtr)();

        {
            IndirectionInfo indInfo;
            indInfo.m_assemblyName = L"mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=x86";
            indInfo.m_typeFullName = L"System.DateTime";
            indInfo.m_methodName = L"get_Now";
            HogePtr pfnHoge = Hoge;
            ASSERT_TRUE(IndirectionSetFunctionPointer(&indInfo, pfnHoge) == TRUE);
        }

        {
            IndirectionInfo indInfo;
            indInfo.m_assemblyName = L"mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=x86";
            indInfo.m_typeFullName = L"System.Int32";
            indInfo.m_methodName = L"get_Now";
            void const *pFuncPtr = NULL;
            ASSERT_TRUE(IndirectionGetFunctionPointer(&indInfo, &pFuncPtr) == TRUE);
            ASSERT_EQ(static_cast<HogePtr>(NULL), pFuncPtr);
        }
    }


    TEST(IndirectionInterfacesTestSuite, IndirectionTestRecordNotExists03MethodNameDoesNotMatch)
    {
        using namespace std;
        using namespace boost;

        typedef void (*HogePtr)();

        {
            IndirectionInfo indInfo;
            indInfo.m_assemblyName = L"mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=x86";
            indInfo.m_typeFullName = L"System.DateTime";
            indInfo.m_methodName = L"get_Now";
            HogePtr pfnHoge = Hoge;
            ASSERT_TRUE(IndirectionSetFunctionPointer(&indInfo, pfnHoge) == TRUE);
        }

        {
            IndirectionInfo indInfo;
            indInfo.m_assemblyName = L"mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=x86";
            indInfo.m_typeFullName = L"System.DateTime";
            indInfo.m_methodName = L"get_UtcNow";
            void const *pFuncPtr = NULL;
            ASSERT_TRUE(IndirectionGetFunctionPointer(&indInfo, &pFuncPtr) == TRUE);
            ASSERT_EQ(static_cast<HogePtr>(NULL), pFuncPtr);
        }
    }
#endif

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
