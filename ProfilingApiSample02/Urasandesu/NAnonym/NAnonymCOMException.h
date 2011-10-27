#pragma once
#ifndef URASANDESU_NANONYM_NANONYMCOMEXCEPTION_H
#define URASANDESU_NANONYM_NANONYMCOMEXCEPTION_H

#ifndef URASANDESU_NANONYM_NANONYMEXCEPTION_H
#include <Urasandesu/NAnonym/NAnonymException.h>
#endif

namespace Urasandesu { namespace NAnonym {

    typedef boost::error_info<struct tag_hresult, std::string> ThrowHResult;
    typedef boost::error_info<struct tag_com_error, _com_error> ThrowCOMError;
    
    struct NAnonymCOMException : NAnonymException
    {
        NAnonymCOMException(HRESULT hr);
    };
        
}}  // namespace Urasandesu { namespace NAnonym {

#endif  // URASANDESU_NANONYM_NANONYMCOMEXCEPTION_H