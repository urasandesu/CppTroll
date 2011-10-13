#pragma once
#ifndef URASANDESU_NANONYM_STACKTRACE_H
#define URASANDESU_NANONYM_STACKTRACE_H

namespace Urasandesu { namespace NAnonym {

    class StackTrace
    {
    public:
        StackTrace() : 
            m_hProcess(NULL),
            m_hThread(NULL),
            m_pContext(NULL),
            m_skips(false)
        { }
        
        ~StackTrace()
        {
            ::SymCleanup(m_hProcess);
        }

        void Capture(HANDLE hProcess = ::GetCurrentProcess(), 
                     HANDLE hThread = ::GetCurrentThread(), 
                     LPCONTEXT pContext = NULL, 
                     LPCWSTR userSearchPath = L".\\")
        {
            using boost::filesystem::path;
            using boost::filesystem::absolute;
            using boost::filesystem::exists;

            m_hProcess = hProcess;
            m_hThread = hThread;
            m_pContext = pContext;
            m_userSearchPath = userSearchPath;
            
            std::string absoluteSearchPath = absolute(m_userSearchPath).string();
            PSTR userSearchPath_ = exists(absoluteSearchPath) ? 
                                     const_cast<PSTR>(absoluteSearchPath.c_str()) : NULL;

            DWORD options = ::SymGetOptions();
            options |= SYMOPT_LOAD_LINES;
            options &= ~SYMOPT_UNDNAME;
            ::SymSetOptions(options); 

            ::SymInitialize(m_hProcess, userSearchPath_, TRUE);

            STACKFRAME sf; 
            ::ZeroMemory(&sf, sizeof(STACKFRAME));
            if (!m_pContext)
            {
                m_pContextReserved = boost::shared_ptr<CONTEXT>(new CONTEXT());
                m_pContext = m_pContextReserved.get();

                ::ZeroMemory(m_pContext, sizeof(CONTEXT));
                m_pContext->ContextFlags = CONTEXT_FULL;

                unsigned long instPtr;
                unsigned long stackPtr;
                unsigned long basePtr; 

                __asm call(x)
                __asm x: pop eax
                __asm mov [instPtr], eax
                __asm mov [stackPtr], esp
                __asm mov [basePtr], ebp

                m_pContext->Eip = instPtr; 
                m_pContext->Esp = stackPtr;
                m_pContext->Ebp = basePtr;

                m_skips = true;
            }
            sf.AddrPC.Offset = m_pContext->Eip;
            sf.AddrPC.Mode = AddrModeFlat;
            sf.AddrStack.Offset = m_pContext->Esp;
            sf.AddrStack.Mode = AddrModeFlat;
            sf.AddrFrame.Offset = m_pContext->Ebp;
            sf.AddrFrame.Mode = AddrModeFlat;

            while (::StackWalk(IMAGE_FILE_MACHINE_I386, m_hProcess, m_hThread, &sf, NULL, NULL, 
                                 ::SymFunctionTableAccess, ::SymGetModuleBase, NULL) == TRUE) 
            {
                if (sf.AddrFrame.Offset == 0) 
                    break;

                if (sf.AddrPC.Offset == 0) 
                    continue;

                if (sf.AddrPC.Offset == sf.AddrReturn.Offset) 
                    continue;

                if (m_skips) 
                {
                    m_skips = false;
                    continue;
                }

                StackFrame *pFrame = new StackFrame();
                pFrame->Init(m_hProcess, sf.AddrPC.Offset);
                m_frames.push_back(pFrame);
            }
        }

        boost::ptr_vector<StackFrame> *GetStackFrames()
        {
            return &m_frames;
        }
        
    private:
        HANDLE m_hProcess;
        HANDLE m_hThread;
        LPCONTEXT m_pContext;
        boost::filesystem::path m_userSearchPath;

        bool m_skips;
        boost::shared_ptr<CONTEXT> m_pContextReserved;
        
        boost::ptr_vector<StackFrame> m_frames;
    };

}}  // namespace Urasandesu { namespace NAnonym {

#endif  // URASANDESU_NANONYM_STACKTRACE_H