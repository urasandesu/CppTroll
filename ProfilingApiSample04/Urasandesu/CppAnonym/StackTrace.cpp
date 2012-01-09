
#include "stdafx.h"

#ifndef URASANDESU_CPPANONYM_STACKFRAME_H
#include <Urasandesu/CppAnonym/StackFrame.h>
#endif

#ifndef URASANDESU_CPPANONYM_STACKTRACE_H
#include <Urasandesu/CppAnonym/StackTrace.h>
#endif

namespace Urasandesu { namespace CppAnonym {

    StackTrace::StackTrace() : 
        m_hProcess(NULL)
    { }
    
    StackTrace::~StackTrace()
    {
        ::SymCleanup(m_hProcess);
    }

    void StackTrace::Capture(INT skipCount,
                 HANDLE hProcess, 
                 HANDLE hThread, 
                 LPCWSTR userSearchPath, 
                 LPCONTEXT pContext)
    {
        using boost::filesystem::path;
        using boost::filesystem::absolute;
        using boost::filesystem::exists;

        m_hProcess = hProcess;
        
        std::string absoluteSearchPath = absolute(userSearchPath).string();
        PSTR userSearchPath_ = exists(absoluteSearchPath) ? 
                                 const_cast<PSTR>(absoluteSearchPath.c_str()) : NULL;

        DWORD options = ::SymGetOptions();
        options |= SYMOPT_LOAD_LINES;
        options &= ~SYMOPT_UNDNAME;
        ::SymSetOptions(options); 

        ::SymInitialize(m_hProcess, userSearchPath_, TRUE);

        STACKFRAME sf; 
        ::ZeroMemory(&sf, sizeof(STACKFRAME));
        if (!pContext)
        {
            unsigned long instPtr;
            unsigned long stackPtr;
            unsigned long basePtr; 

            __asm call(x)
            __asm x: pop eax
            __asm mov [instPtr], eax
            __asm mov [stackPtr], esp
            __asm mov [basePtr], ebp

            sf.AddrPC.Offset = instPtr;
            sf.AddrPC.Mode = AddrModeFlat;
            sf.AddrStack.Offset = stackPtr;
            sf.AddrStack.Mode = AddrModeFlat;
            sf.AddrFrame.Offset = basePtr;
            sf.AddrFrame.Mode = AddrModeFlat;
        }
        else
        {
            sf.AddrPC.Offset = pContext->Eip;
            sf.AddrPC.Mode = AddrModeFlat;
            sf.AddrStack.Offset = pContext->Esp;
            sf.AddrStack.Mode = AddrModeFlat;
            sf.AddrFrame.Offset = pContext->Ebp;
            sf.AddrFrame.Mode = AddrModeFlat;
        }

        while (::StackWalk(IMAGE_FILE_MACHINE_I386, m_hProcess, hThread, &sf, NULL, 
                           NULL, ::SymFunctionTableAccess, ::SymGetModuleBase, NULL) == TRUE) 
        {
            if (sf.AddrFrame.Offset == 0) 
                break;

            if (sf.AddrPC.Offset == 0) 
                continue;

            if (sf.AddrPC.Offset == sf.AddrReturn.Offset) 
                continue;

            if (0 < skipCount) 
            {
                --skipCount;
                continue;
            }

            StackFrame *pFrame = new StackFrame();
            pFrame->Init(m_hProcess, sf.AddrPC.Offset);
            m_frames.push_back(pFrame);
        }
    }

    boost::ptr_vector<StackFrame> *StackTrace::GetStackFrames()
    {
        return &m_frames;
    }

}}  // namespace Urasandesu { namespace CppAnonym {
