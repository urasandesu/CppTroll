// ProfilingApiSample03Test.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"


namespace {

    // SET COR_ENABLE_PROFILING=1
    // SET COR_PROFILER={ACC35A1C-B127-4A75-9EB8-B4E54A49F6CF}
    // ProfilingApiSample03Target.exe
    // 
    // ProfilingApiSample03Test.exe --gtest_filter=ProfilingApiSample03TestSuite.ProfilingApiSample03Test
    // 
    // ildasm /out=ProfilingApiSample03Patch.dll.dasm /all /metadata=SCHEMA /metadata=HEAPS /metadata=CSV /source ProfilingApiSample03Patch.dll
    // 
    // ProfilingApiSample03Stubber.exe --input="C:\WINDOWS\Microsoft.NET\Framework\v2.0.50727\mscorlib.dll"
    TEST(ProfilingApiSample03TestSuite, ProfilingApiSample03Test)
    {
        using namespace std;
        using namespace boost;
        
        mdToken mdt = 0x02000032;
        BYTE pData[4] = { 0 };
        ULONG dataSize = 0;
        
        dataSize = ::CorSigCompressToken(mdt, reinterpret_cast<void *>(pData));
        cout << format("%|1$d| Byte Compressed Token: 0x%|2$08X| => 0x") % dataSize % mdt;
        for (BYTE *i = pData, *i_end = pData + dataSize; i != i_end; ++i)
        {
            cout << format("%|1$02X|") % static_cast<INT>(*i);
        }
        cout << endl;

        //CComPtr<ICorProfilerCallback2> pCallback;
        //ASSERT_HRESULT_SUCCEEDED(
        //    ::CoCreateInstance(__uuidof(ExeWeaver3), NULL, CLSCTX_INPROC_SERVER, 
        //                       IID_ICorProfilerCallback2, 
        //                       reinterpret_cast<void**>(&pCallback))
        //);
        //ASSERT_TRUE(pCallback.p != NULL);
    }
}
