#pragma once
#ifndef URASANDESU_NANONYM_STACKTRACE_H
#define URASANDESU_NANONYM_STACKTRACE_H

namespace Urasandesu { namespace NAnonym {

    class StackFrame;

    class StackTrace
    {
    public:
        StackTrace();
        ~StackTrace();
        void Capture(INT skipCount = 1,
                     HANDLE hProcess = ::GetCurrentProcess(), 
                     HANDLE hThread = ::GetCurrentThread(), 
                     LPCWSTR userSearchPath = L".\\", 
                     LPCONTEXT pContext = NULL);

        boost::ptr_vector<StackFrame> *GetStackFrames();
        
    private:
        HANDLE m_hProcess;
        boost::ptr_vector<StackFrame> m_frames;
    };

}}  // namespace Urasandesu { namespace NAnonym {

#endif  // URASANDESU_NANONYM_STACKTRACE_H