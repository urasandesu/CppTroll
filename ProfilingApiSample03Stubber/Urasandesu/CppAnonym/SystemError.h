#pragma once
#ifndef URASANDESU_CPPANONYM_SYSTEMERROR_H
#define URASANDESU_CPPANONYM_SYSTEMERROR_H

namespace Urasandesu { namespace CppAnonym {
    
    class SystemError : public boost::system::error_code
    {
    public:
        SystemError() : boost::system::error_code() { }
        SystemError(int val, const boost::system::error_category& cat)
            : boost::system::error_code(val, cat), 
              m_message(CComBSTR(category().message(value()).data()))
        { 
        }

        template <class ErrorCodeEnum>
        SystemError(ErrorCodeEnum e, 
                     typename boost::enable_if<
                        boost::system::is_error_code_enum<ErrorCodeEnum>>::type* = 0)
        {
            *this = boost::system::errcmake_error_code(e);
        }
        
        CComBSTR GetBSTRMessage() const { return m_message; }

    private:
        CComBSTR m_message;
    };
    
}}  // namespace Urasandesu { namespace CppAnonym {

#endif  // URASANDESU_CPPANONYM_SYSTEMERROR_H