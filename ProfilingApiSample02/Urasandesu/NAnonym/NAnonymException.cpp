
#include "stdafx.h"

#ifndef URASANDESU_NANONYM_NANONYMEXCEPTION_H
#include <Urasandesu/NAnonym/NAnonymException.h>
#endif

#ifndef URASANDESU_NANONYM_STACKFRAME_H
#include <Urasandesu/NAnonym/StackFrame.h>
#endif

#ifndef URASANDESU_NANONYM_STACKTRACE_H
#include <Urasandesu/NAnonym/StackTrace.h>
#endif

namespace Urasandesu { namespace NAnonym {

    NAnonymException::NAnonymException() : 
        m_pStackTrace(boost::make_shared<StackTrace>())
    {
        CaptureStackTrace(this);
    }
    
    NAnonymException::NAnonymException(std::string const &what) : 
        m_what(what),
        m_pStackTrace(boost::make_shared<StackTrace>())
    { 
        CaptureStackTrace(this);
    }
    
    NAnonymException::NAnonymException(std::string const &what, NAnonymException &innerException) : 
        m_what(what),
        m_pStackTrace(boost::make_shared<StackTrace>())
    {
        CaptureStackTrace(this);
        *this << boost::errinfo_nested_exception(boost::copy_exception(innerException));
    }
    
    const char *NAnonymException::__CLR_OR_THIS_CALL what() const
    {
        return m_what.c_str();
    }

    void NAnonymException::CaptureStackTrace(NAnonymException *this_)
    {
        this_->m_pStackTrace->Capture(3);
        *this_ << ThrowStackTrace(this_->m_pStackTrace.get());
    }


    inline std::string to_string(StackTrace *pStackTrace)
    {
        using namespace std;
        using namespace boost;
        
        ostringstream oss;
        ptr_vector<StackFrame> *pFrames = pStackTrace->GetStackFrames();
        for (ptr_vector<StackFrame>::iterator i = pFrames->begin(), i_end = pFrames->end(); i != i_end; ++i)
        {
            oss << "at ";
            oss << i->GetSymbolName();
            oss << " in ";
            oss << i->GetModuleName();
            if (0 < i->GetFileLineNumber())
            {
                oss << "(";
                oss << i->GetFileName();
                oss << ":";
                oss << i->GetFileLineNumber();
                oss << ")";
            }
            oss << "\n";
        }
        return oss.str();
    }
        
}}  // namespace Urasandesu { namespace NAnonym {
