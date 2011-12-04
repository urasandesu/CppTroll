
#include "stdafx.h"

#ifndef URASANDESU_CPPANONYM_CPPANONYMEXCEPTION_H
#include <Urasandesu/CppAnonym/CppAnonymException.h>
#endif

#ifndef URASANDESU_CPPANONYM_STACKFRAME_H
#include <Urasandesu/CppAnonym/StackFrame.h>
#endif

#ifndef URASANDESU_CPPANONYM_STACKTRACE_H
#include <Urasandesu/CppAnonym/StackTrace.h>
#endif

namespace Urasandesu { namespace CppAnonym {

    CppAnonymException::CppAnonymException() : 
        m_pStackTrace(boost::make_shared<StackTrace>())
    {
        CaptureStackTrace(this);
    }
    
    CppAnonymException::CppAnonymException(std::string const &what) : 
        m_what(what),
        m_pStackTrace(boost::make_shared<StackTrace>())
    { 
        CaptureStackTrace(this);
    }
    
    CppAnonymException::CppAnonymException(std::string const &what, CppAnonymException &innerException) : 
        m_what(what),
        m_pStackTrace(boost::make_shared<StackTrace>())
    {
        CaptureStackTrace(this);
        *this << boost::errinfo_nested_exception(boost::copy_exception(innerException));
    }
    
    const char *CppAnonymException::__CLR_OR_THIS_CALL what() const
    {
        return m_what.c_str();
    }

    void CppAnonymException::CaptureStackTrace(CppAnonymException *this_)
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
        
}}  // namespace Urasandesu { namespace CppAnonym {
