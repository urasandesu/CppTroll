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
        HogePtr pfnHoge = Hoge;

        IndiretionInfo indInfo;
        indInfo.m_assemblyName = L"mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=x86";
        indInfo.m_typeFullName = L"System.DateTime";
        indInfo.m_methodName = L"get_Now";

        {
            INT funcPtr = reinterpret_cast<INT>(pfnHoge);
            ASSERT_TRUE(IndiretionSetFunctionPointer(&indInfo, funcPtr) == TRUE);
        }

        {
            INT funcPtr = 0;
            ASSERT_TRUE(IndiretionGetFunctionPointer(&indInfo, &funcPtr) == TRUE);
            ASSERT_EQ(pfnHoge, reinterpret_cast<HogePtr>(funcPtr));
        }
    }


    TEST(IndiretionInterfacesTestSuite, IndiretionTestRecordNotExists01AssemblyNameDoesNotMatch)
    {
        using namespace std;
        using namespace boost;

        typedef void (*HogePtr)();
        HogePtr pfnHoge = Hoge;

        {
            IndiretionInfo indInfo;
            indInfo.m_assemblyName = L"mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=x86";
            indInfo.m_typeFullName = L"System.DateTime";
            indInfo.m_methodName = L"get_Now";
            INT funcPtr = reinterpret_cast<INT>(pfnHoge);
            ASSERT_TRUE(IndiretionSetFunctionPointer(&indInfo, funcPtr) == TRUE);
        }

        {
            IndiretionInfo indInfo;
            indInfo.m_assemblyName = L"System, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=MSIL";
            indInfo.m_typeFullName = L"System.DateTime";
            indInfo.m_methodName = L"get_Now";
            INT funcPtr = 0;
            ASSERT_TRUE(IndiretionGetFunctionPointer(&indInfo, &funcPtr) == TRUE);
            ASSERT_EQ(NULL, reinterpret_cast<HogePtr>(funcPtr));
        }
    }


    TEST(IndiretionInterfacesTestSuite, IndiretionTestRecordNotExists02TypeNameDoesNotMatch)
    {
        using namespace std;
        using namespace boost;

        typedef void (*HogePtr)();
        HogePtr pfnHoge = Hoge;

        {
            IndiretionInfo indInfo;
            indInfo.m_assemblyName = L"mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=x86";
            indInfo.m_typeFullName = L"System.DateTime";
            indInfo.m_methodName = L"get_Now";
            INT funcPtr = reinterpret_cast<INT>(pfnHoge);
            ASSERT_TRUE(IndiretionSetFunctionPointer(&indInfo, funcPtr) == TRUE);
        }

        {
            IndiretionInfo indInfo;
            indInfo.m_assemblyName = L"mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=x86";
            indInfo.m_typeFullName = L"System.Int32";
            indInfo.m_methodName = L"get_Now";
            INT funcPtr = 0;
            ASSERT_TRUE(IndiretionGetFunctionPointer(&indInfo, &funcPtr) == TRUE);
            ASSERT_EQ(NULL, reinterpret_cast<HogePtr>(funcPtr));
        }
    }


    TEST(IndiretionInterfacesTestSuite, IndiretionTestRecordNotExists03MethodNameDoesNotMatch)
    {
        using namespace std;
        using namespace boost;

        typedef void (*HogePtr)();
        HogePtr pfnHoge = Hoge;

        {
            IndiretionInfo indInfo;
            indInfo.m_assemblyName = L"mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=x86";
            indInfo.m_typeFullName = L"System.DateTime";
            indInfo.m_methodName = L"get_Now";
            INT funcPtr = reinterpret_cast<INT>(pfnHoge);
            ASSERT_TRUE(IndiretionSetFunctionPointer(&indInfo, funcPtr) == TRUE);
        }

        {
            IndiretionInfo indInfo;
            indInfo.m_assemblyName = L"mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=x86";
            indInfo.m_typeFullName = L"System.DateTime";
            indInfo.m_methodName = L"get_UtcNow";
            INT funcPtr = 0;
            ASSERT_TRUE(IndiretionGetFunctionPointer(&indInfo, &funcPtr) == TRUE);
            ASSERT_EQ(NULL, reinterpret_cast<HogePtr>(funcPtr));
        }
    }
}
