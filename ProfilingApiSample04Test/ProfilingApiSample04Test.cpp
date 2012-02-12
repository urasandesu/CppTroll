// ProfilingApiSample04Test.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#import "libid:F2D8B64B-6C50-4484-A3A3-F8351ADB6C42" version("1.0") no_namespace // ProfilingApiSample04 1.0 タイプ ライブラリ


namespace {

    // SET COR_ENABLE_PROFILING=1
    // SET COR_PROFILER={98B5B08A-C625-4CA2-B1C8-157477A58945}
    // SET COMPLUS_ProfAPI_ProfilerCompatibilitySetting=EnableV2Profiler
    // ProfilingApiSample04Target.exe
    // 
    // ProfilingApiSample04Test.exe --gtest_filter=ProfilingApiSample04TestSuite.ProfilingApiSample04Test
    // 
    // "C:\Program Files (x86)\NUnit 2.5.10\bin\net-2.0\nunit-console-x86.exe" ProfilingApiSample04TargetTest.dll /domain=None
    TEST(ProfilingApiSample04TestSuite, ProfilingApiSample04Test)
    {
        using namespace std;
        using namespace boost;

#if 1        
        mdToken mdt = 0x0200000A;
        BYTE pData[4] = { 0 };
        ULONG dataSize = 0;
        
        dataSize = ::CorSigCompressToken(mdt, reinterpret_cast<void *>(pData));
        cout << format("%|1$d| Byte Compressed Token: 0x%|2$08X| => 0x") % dataSize % mdt;
        for (BYTE *i = pData, *i_end = pData + dataSize; i != i_end; ++i)
        {
            cout << format("%|1$02X|") % static_cast<INT>(*i);
        }
        cout << endl;
#else
        
        int iData = 0;
        BYTE pData[4] = { 0 };
        ULONG dataSize = 0;
        
        dataSize = ::CorSigCompressSignedInt(iData, reinterpret_cast<void *>(pData));
        cout << format("%|1$d| Byte Compressed Signed Integer: %|2$d| => ") % dataSize % iData;
        for (BYTE *i = pData, *i_end = pData + dataSize; i != i_end; ++i)
        {
            cout << format("%|1$02X|") % static_cast<INT>(*i);
        }
        cout << endl;
#endif

//inline ULONG CorSigCompressSignedInt(   // return number of bytes that compressed form of iData will take   
//    int         iData,                  // [IN] given integer   
//    void        *pDataOut)              // [OUT] buffer where iLen will be compressed and stored.   

        //ATL::CComPtr<ICorProfilerCallback2> pCallback;
        //ASSERT_HRESULT_SUCCEEDED(
        //    ::CoCreateInstance(__uuidof(ExeWeaver4), NULL, CLSCTX_INPROC_SERVER, 
        //                       IID_ICorProfilerCallback2, 
        //                       reinterpret_cast<void **>(&pCallback))
        //);
        //ASSERT_TRUE(pCallback.p != NULL);
    }
}
