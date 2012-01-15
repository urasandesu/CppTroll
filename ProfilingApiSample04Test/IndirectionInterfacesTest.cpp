#include "stdafx.h"

#ifndef INDIRETIONINTERFACES_H
#include <IndirectionInterfaces.h>
#endif

namespace {

    void Hoge()
    {
    }

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
}
