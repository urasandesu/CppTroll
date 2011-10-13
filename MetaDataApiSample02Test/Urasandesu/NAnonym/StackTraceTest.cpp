#include "stdafx.h"

#ifndef URASANDESU_NANONYM_STACKFRAME_H
#include "Urasandesu/NAnonym/StackFrame.h"
#endif

#ifndef URASANDESU_NANONYM_STACKTRACE_H
#include "Urasandesu/NAnonym/StackTrace.h"
#endif

namespace {

    // MetaDataApiSample02Test.exe --gtest_filter=MetaDataApiSample02TestSuite.DefaultStackTraceCapturingTest
    TEST(MetaDataApiSample02TestSuite, DefaultStackTraceCapturingTest)
    {
        using namespace std;
        using namespace boost;
        using namespace Urasandesu::NAnonym;

        StackTrace stackTrace;
        stackTrace.Capture();
        ptr_vector<StackFrame> *pFrames = stackTrace.GetStackFrames();
        ASSERT_LT(0U, pFrames->size());
        for (ptr_vector<StackFrame>::iterator i = pFrames->begin(), i_end = pFrames->end(); i != i_end; ++i)
        {
            cout << format("Offset: 0x%|1$08X|") % i->GetOffset() << endl;
            cout << format("Module Name: %|1|") % i->GetModuleName() << endl;
            EXPECT_STRNE("", i->GetModuleName().c_str());
            cout << format("Symbol Name: %|1|") % i->GetSymbolName() << endl;
            EXPECT_STRNE("", i->GetSymbolName().c_str());
            cout << format("File Name: %|1|") % i->GetFileName() << endl;
            EXPECT_STRNE("", i->GetFileName().c_str());
            cout << format("File Line Number: %|1|") % i->GetFileLineNumber() << endl;
            cout << format("File Column Number: %|1|") % i->GetFileColumnNumber() << endl;
        }
    }

    // MetaDataApiSample02Test.exe --gtest_filter=MetaDataApiSample02TestSuite.ExplicitStackTraceCapturingTest
    TEST(MetaDataApiSample02TestSuite, ExplicitStackTraceCapturingTest)
    {
        using namespace std;
        using namespace boost;
        using namespace Urasandesu::NAnonym;
        
        HANDLE hProcess = ::GetCurrentProcess();
        cout << format("Current Process Pseudo Handle: 0x%|1$08X|") % hProcess << endl;
        
        HANDLE hThread = ::GetCurrentThread();
        cout << format("Current Thread Pseudo Handle: 0x%|1$08X|") % hThread << endl;

        CONTEXT context;
        ::ZeroMemory(&context, sizeof(CONTEXT));
        context.ContextFlags = CONTEXT_FULL;

        unsigned long instPtr;
        unsigned long stackPtr;
        unsigned long basePtr; 

        __asm call(x)
        __asm x: pop eax
        __asm mov [instPtr], eax
        __asm mov [stackPtr], esp
        __asm mov [basePtr], ebp

        context.Eip = instPtr; 
        context.Esp = stackPtr;
        context.Ebp = basePtr;
        cout << format("Current Thread Context Eip: 0x%|1$08X|, Ebp: 0x%|2$08X|, Esp: 0x%|3$08X|") % context.Eip % context.Ebp % context.Esp << endl;
        
        LPCWSTR userSearchPath = L".\\";
        boost::filesystem::path p(userSearchPath);
        cout << boost::filesystem::absolute(p) << endl;

        StackTrace stackTrace;
        stackTrace.Capture(hProcess, hThread, &context, userSearchPath);
        ptr_vector<StackFrame> *pFrames = stackTrace.GetStackFrames();
        ASSERT_LT(0U, pFrames->size());
        for (ptr_vector<StackFrame>::iterator i = pFrames->begin(), i_end = pFrames->end(); i != i_end; ++i)
        {
            cout << format("Offset: 0x%|1$08X|") % i->GetOffset() << endl;
            cout << format("Module Name: %|1|") % i->GetModuleName() << endl;
            EXPECT_STRNE("", i->GetModuleName().c_str());
            cout << format("Symbol Name: %|1|") % i->GetSymbolName() << endl;
            EXPECT_STRNE("", i->GetSymbolName().c_str());
            cout << format("File Name: %|1|") % i->GetFileName() << endl;
            EXPECT_STRNE("", i->GetFileName().c_str());
            cout << format("File Line Number: %|1|") % i->GetFileLineNumber() << endl;
            cout << format("File Column Number: %|1|") % i->GetFileColumnNumber() << endl;
        }
    }
}
