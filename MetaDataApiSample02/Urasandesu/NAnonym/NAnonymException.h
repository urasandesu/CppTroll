#pragma once
#ifndef URASANDESU_NANONYM_NANONYMEXCEPTION_H
#define URASANDESU_NANONYM_NANONYMEXCEPTION_H

namespace Urasandesu { namespace NAnonym {

    class StackTrace;

    typedef boost::error_info<struct tag_stack_trace, StackTrace*> ThrowStackTrace;

    class NAnonymException : 
        public virtual boost::exception, 
        public virtual std::exception
    {
    public:
        NAnonymException();
        NAnonymException(std::string const &what);
        NAnonymException(std::string const &what, NAnonymException &innerException);
	    virtual const char *__CLR_OR_THIS_CALL what() const;
        
    protected:
        std::string m_what;
        boost::shared_ptr<StackTrace> m_pStackTrace;
    
    private:
        void CaptureStackTrace(NAnonymException *this_);

    };
        
}}  // namespace Urasandesu { namespace NAnonym {

#endif  // URASANDESU_NANONYM_NANONYMEXCEPTION_H