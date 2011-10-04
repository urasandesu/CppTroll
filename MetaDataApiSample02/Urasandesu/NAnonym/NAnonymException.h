#pragma once
#ifndef URASANDESU_NANONYM_NANONYMEXCEPTION_H
#define URASANDESU_NANONYM_NANONYMEXCEPTION_H

namespace Urasandesu { namespace NAnonym {

    class NAnonymException : 
        public virtual boost::exception, 
        public virtual std::exception
    {
    public:
        NAnonymException()
        { 
        }
        
        NAnonymException(std::string const &what) : 
            m_what(what)
        { 
        }
        
        NAnonymException(std::string const &what, NAnonymException &innerException) : 
            m_what(what)
        {
            *this << boost::errinfo_nested_exception(boost::copy_exception(innerException));
        }
        
	    virtual const char *__CLR_OR_THIS_CALL what() const
	    {
	        return m_what.c_str();
	    }
        
    protected:
        std::string m_what;
    };
        
}}  // namespace Urasandesu { namespace NAnonym {

#endif  // URASANDESU_NANONYM_NANONYMEXCEPTION_H