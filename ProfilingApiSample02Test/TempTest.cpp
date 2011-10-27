// ProfilingApiSample02Test.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#ifndef URASANDESU_NANONYM_PROFILING_ICORPROFILERCALLBACK2IMPL_H
#include <Urasandesu/NAnonym/Profiling/ICorProfilerCallback2Impl.h>
#endif

namespace {

    class ATL_NO_VTABLE ICorProfilerCallback2ImplTester;
    typedef CComObject<ICorProfilerCallback2ImplTester> ICorProfilerCallback2ImplTesterObject;

    class ATL_NO_VTABLE ICorProfilerCallback2ImplTester : 
        public CComObjectRootEx<CComSingleThreadModel>,
        public Urasandesu::NAnonym::Profiling::ICorProfilerCallback2Impl<ICorProfilerCallback2>
    {
    public:
        ICorProfilerCallback2ImplTester() { }

    BEGIN_COM_MAP(ICorProfilerCallback2ImplTester)
        COM_INTERFACE_ENTRY(ICorProfilerCallback2)
    END_COM_MAP()

        DECLARE_PROTECT_FINAL_CONSTRUCT()

        HRESULT FinalConstruct() { return S_OK; }
        void FinalRelease() { }
    };

    // ProfilingApiSample02Test.exe --gtest_filter=ProfilingApiSample02TestSuite.TempTestTest
    TEST(ProfilingApiSample02TestSuite, TempTestTest)
    {
        using namespace std;
        using namespace boost;
        using namespace Urasandesu::NAnonym;
        using namespace Urasandesu::NAnonym::MetaData;
        using namespace Urasandesu::NAnonym::Profiling;
        using namespace Urasandesu::NAnonym::Utilities;

        ICorProfilerCallback2ImplTesterObject tester;

    }
}
