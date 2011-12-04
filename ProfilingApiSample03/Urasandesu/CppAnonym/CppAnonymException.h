#pragma once
#ifndef URASANDESU_CPPANONYM_CPPANONYMEXCEPTION_H
#define URASANDESU_CPPANONYM_CPPANONYMEXCEPTION_H

namespace Urasandesu { namespace CppAnonym {

    class StackTrace;

    typedef boost::error_info<struct tag_stack_trace, StackTrace*> ThrowStackTrace;

    class CppAnonymException : 
        public virtual boost::exception, 
        public virtual std::exception
    {
    public:
        CppAnonymException();
        CppAnonymException(std::string const &what);
        CppAnonymException(std::string const &what, CppAnonymException &innerException);
        virtual const char *__CLR_OR_THIS_CALL what() const;
        
    protected:
        std::string m_what;
        boost::shared_ptr<StackTrace> m_pStackTrace;
    
    private:
        void CaptureStackTrace(CppAnonymException *this_);

    };
        
}}  // namespace Urasandesu { namespace CppAnonym {

#endif  // URASANDESU_CPPANONYM_CPPANONYMEXCEPTION_H