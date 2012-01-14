#include "stdafx.h"

#ifndef INDIRETIONINTERFACES_H
#include <IndiretionInterfaces.h>
#endif

namespace {

    void Hoge()
    {
    }

    // ProfilingApiSample04Test.exe --gtest_filter=IndiretionInterfacesTestSuite.*
    TEST(IndiretionInterfacesTestSuite, Indiretion01Test)
    {
        typedef void (*HogePtr)();
        HogePtr funcPtr = Hoge;
        //using namespace std;
        //using namespace boost;

        //ATL::CComPtr<ICorProfilerCallback2> pCallback;
        //ASSERT_HRESULT_SUCCEEDED(
        //    ::CoCreateInstance(__uuidof(ExeWeaver4), NULL, CLSCTX_INPROC_SERVER, 
        //                       IID_ICorProfilerCallback2, 
        //                       reinterpret_cast<void **>(&pCallback))
        //);
        //ASSERT_TRUE(pCallback.p != NULL);
    }
}
