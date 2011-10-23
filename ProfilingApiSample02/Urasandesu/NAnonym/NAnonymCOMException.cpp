
#include "stdafx.h"

#ifndef URASANDESU_NANONYM_NANONYMEXCEPTION_H
#include <Urasandesu/NAnonym/NAnonymException.h>
#endif

#ifndef URASANDESU_NANONYM_NANONYMCOMEXCEPTION_H
#include <Urasandesu/NAnonym/NAnonymCOMException.h>
#endif

namespace Urasandesu { namespace NAnonym {

    NAnonymCOMException::NAnonymCOMException(HRESULT hr)
    {
        _com_error ce(hr);    
        m_what = std::string(CW2A(ce.ErrorMessage()));
        *this << ThrowHResult(boost::str(boost::format("0x%|1$08X|") % hr));
        *this << ThrowCOMError(ce);
    }
        
}}  // namespace Urasandesu { namespace NAnonym {
