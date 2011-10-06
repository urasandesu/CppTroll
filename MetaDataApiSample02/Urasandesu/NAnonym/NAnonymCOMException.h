#pragma once
#ifndef URASANDESU_NANONYM_NANONYMCOMEXCEPTION_H
#define URASANDESU_NANONYM_NANONYMCOMEXCEPTION_H

#ifndef URASANDESU_NANONYM_NANONYMEXCEPTION_H
#include <Urasandesu/NAnonym/NAnonymException.h>
#endif

namespace Urasandesu { namespace NAnonym {

    typedef boost::error_info<struct tag_hresult, std::string> ThrowHResult;
    typedef boost::error_info<struct tag_hresult, _com_error> ThrowCOMError;
    
    struct NAnonymCOMException : NAnonymException
    {
        NAnonymCOMException(HRESULT hr)
        {
            _com_error ce(hr);    
            m_what = std::string(CW2A(ce.ErrorMessage()));
            *this << ThrowHResult(boost::str(boost::format("0x%|1$08X|") % hr));
            *this << ThrowCOMError(ce);
        }
    };
        
}}  // namespace Urasandesu { namespace NAnonym {

#endif  // URASANDESU_NANONYM_NANONYMCOMEXCEPTION_H