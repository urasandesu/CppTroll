// ProfilingApiSample02Test.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

//#ifndef URASANDESU_NANONYM_SIMPLEHEAP_H
//#include <Urasandesu/NAnonym/SimpleHeap.h>
//#endif
//
//#ifndef URASANDESU_NANONYM_NANONYMCOMEXCEPTION_H
//#include <Urasandesu/NAnonym/NAnonymCOMException.h>
//#endif

//#ifndef URASANDESU_NANONYM_NANONYMEXCEPTION_H
//#include <Urasandesu/NAnonym/NAnonymException.h>
//#endif

#ifndef URASANDESU_NANONYM_NANONYMSYSTEMEXCEPTION_H
#include <Urasandesu/NAnonym/NAnonymSystemException.h>
#endif

namespace {

    // ProfilingApiSample02Test.exe --gtest_filter=ProfilingApiSample02TestSuite.ProfilingApiSample02Test
    // 
    // SET COR_ENABLE_PROFILING=1
    // SET COR_PROFILER={F60DB91B-5932-4964-818A-CA697CF46A5F}
    // SET NANONYM_TARGET_ASSEMBLY=0x20000001
    // SET NANONYM_REPLACE_TYPE_FROM=0x02000002
    // SET NANONYM_REPLACE_METHOD_FROM=0x06000001
    // SET NANONYM_REPLACE_TYPE_TO=0x02000003
    // SET NANONYM_REPLACE_METHOD_TO=0x06000003
    // ProfilingApiSample02Target.exe
    //
    // ildasm /out=ProfilingApiSample02Target.exe.dasm /all /metadata=SCHEMA /metadata=HEAPS /metadata=CSV /source ProfilingApiSample02Target.exe
    TEST(ProfilingApiSample02TestSuite, ProfilingApiSample02Test)
    {
        using namespace std;
        using namespace boost;
        using namespace Urasandesu::NAnonym;

        try
        {
            BOOST_THROW_EXCEPTION(NAnonymSystemException(ERANGE));
        }
        catch (...)
        {
            cout << diagnostic_information(current_exception()) << endl;
        }
        
        //
        //class A
        //{
        //public:
        //    A() { }
        //    
        //    UINT_PTR GetID()
        //    {
        //        return m_id;
        //    }
        //    
        //    void SetID(UINT_PTR id)
        //    {
        //        m_id = id;
        //    }
        //
        //private:            
        //    UINT_PTR m_id;
        //};
        //
        //SimpleHeap<A, ALotOfAllocAndFreeHeap> aheap;
        //unordered_map<UINT_PTR, SIZE_T> amap;
        //UINT_PTR id = 0;
        //A *pA1 = NULL;
        //A *pA2 = NULL;
        //
        //pA1 = aheap.New();
        //id = 10;
        //pA1->SetID(id);
        //cout << format("ID: %|1$d|, pA1: 0x%|2$08X|") % pA1->GetID() % reinterpret_cast<INT>(pA1) << endl;
        //
        //if (amap.find(id) == amap.end())
        //{
        //    amap[id] = aheap.Size() - 1;
        //}
        //pA2 = aheap[amap[id]];
        //cout << format("ID: %|1$d|, pA2: 0x%|2$08X|") % pA2->GetID() % reinterpret_cast<INT>(pA2) << endl;
        
        //
        //try
        //{
        //    throw 1;
        //}
        //catch (...)
        //{
        //    cout << diagnostic_information(current_exception()) << endl;
        //}
        
        // BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymException("Not Implemented!!"));
        //mdToken mdt = lexical_cast<mdToken>("0x02000002");
        //istringstream is("0x02000002");
        //mdToken mdt = mdTokenNil;
        //is >> hex >> mdt;
        //cout << format("Token: 0x%|1$08X|") % mdt << endl;
        //CComPtr<ICorProfilerCallback2> pCallback;
        //ASSERT_HRESULT_SUCCEEDED(
        //    ::CoCreateInstance(__uuidof(ExeWeaver2), NULL, CLSCTX_INPROC_SERVER, 
        //                       IID_ICorProfilerCallback2, 
        //                       reinterpret_cast<void**>(&pCallback))
        //);
        //ASSERT_TRUE(pCallback.p != NULL);
    }
}
