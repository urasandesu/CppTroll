#include "stdafx.h"

#ifndef INDIRETIONINTERFACES_H
#include <IndiretionInterfaces.h>
#endif

namespace {

    void Hoge()
    {
    }

    // ProfilingApiSample04Test.exe --gtest_filter=IndiretionInterfacesTestSuite.*
    TEST(IndiretionInterfacesTestSuite, IndiretionTestRecordExists01)
    {
        using namespace std;
        using namespace boost;

        typedef void (*HogePtr)();

        IndiretionInfo indInfo;
        indInfo.m_assemblyName = L"mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=x86";
        indInfo.m_typeFullName = L"System.DateTime";
        indInfo.m_methodName = L"get_Now";

        {
            HogePtr pfnHoge = Hoge;
            ASSERT_TRUE(IndiretionSetFunctionPointer(&indInfo, pfnHoge) == TRUE);
        }

        {
            void const *pFuncPtr = NULL;
            ASSERT_TRUE(IndiretionGetFunctionPointer(&indInfo, &pFuncPtr) == TRUE);
            ASSERT_EQ(static_cast<HogePtr>(Hoge), pFuncPtr);
        }
    }


    TEST(IndiretionInterfacesTestSuite, IndiretionTestRecordNotExists01AssemblyNameDoesNotMatch)
    {
        using namespace std;
        using namespace boost;

        typedef void (*HogePtr)();

        {
            IndiretionInfo indInfo;
            indInfo.m_assemblyName = L"mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=x86";
            indInfo.m_typeFullName = L"System.DateTime";
            indInfo.m_methodName = L"get_Now";
            HogePtr pfnHoge = Hoge;
            ASSERT_TRUE(IndiretionSetFunctionPointer(&indInfo, pfnHoge) == TRUE);
        }

        {
            IndiretionInfo indInfo;
            indInfo.m_assemblyName = L"System, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=MSIL";
            indInfo.m_typeFullName = L"System.DateTime";
            indInfo.m_methodName = L"get_Now";
            void const *pFuncPtr = NULL;
            ASSERT_TRUE(IndiretionGetFunctionPointer(&indInfo, &pFuncPtr) == TRUE);
            ASSERT_EQ(static_cast<HogePtr>(NULL), pFuncPtr);
        }
    }


    TEST(IndiretionInterfacesTestSuite, IndiretionTestRecordNotExists02TypeNameDoesNotMatch)
    {
        using namespace std;
        using namespace boost;

        typedef void (*HogePtr)();

        {
            IndiretionInfo indInfo;
            indInfo.m_assemblyName = L"mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=x86";
            indInfo.m_typeFullName = L"System.DateTime";
            indInfo.m_methodName = L"get_Now";
            HogePtr pfnHoge = Hoge;
            ASSERT_TRUE(IndiretionSetFunctionPointer(&indInfo, pfnHoge) == TRUE);
        }

        {
            IndiretionInfo indInfo;
            indInfo.m_assemblyName = L"mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=x86";
            indInfo.m_typeFullName = L"System.Int32";
            indInfo.m_methodName = L"get_Now";
            void const *pFuncPtr = NULL;
            ASSERT_TRUE(IndiretionGetFunctionPointer(&indInfo, &pFuncPtr) == TRUE);
            ASSERT_EQ(static_cast<HogePtr>(NULL), pFuncPtr);
        }
    }


    TEST(IndiretionInterfacesTestSuite, IndiretionTestRecordNotExists03MethodNameDoesNotMatch)
    {
        using namespace std;
        using namespace boost;

        typedef void (*HogePtr)();

        {
            IndiretionInfo indInfo;
            indInfo.m_assemblyName = L"mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=x86";
            indInfo.m_typeFullName = L"System.DateTime";
            indInfo.m_methodName = L"get_Now";
            HogePtr pfnHoge = Hoge;
            ASSERT_TRUE(IndiretionSetFunctionPointer(&indInfo, pfnHoge) == TRUE);
        }

        {
            IndiretionInfo indInfo;
            indInfo.m_assemblyName = L"mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=x86";
            indInfo.m_typeFullName = L"System.DateTime";
            indInfo.m_methodName = L"get_UtcNow";
            void const *pFuncPtr = NULL;
            ASSERT_TRUE(IndiretionGetFunctionPointer(&indInfo, &pFuncPtr) == TRUE);
            ASSERT_EQ(static_cast<HogePtr>(NULL), pFuncPtr);
        }
    }
}
