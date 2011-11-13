
#include "stdafx.h"

#ifndef URASANDESU_CPPANONYM_CPPANONYMEXCEPTION_H
#include <Urasandesu/CppAnonym/CppAnonymException.h>
#endif

#ifndef URASANDESU_CPPANONYM_CPPANONYMCOMEXCEPTION_H
#include <Urasandesu/CppAnonym/CppAnonymCOMException.h>
#endif

namespace Urasandesu { namespace CppAnonym {

    CppAnonymCOMException::CppAnonymCOMException(HRESULT hr)
    {
        _com_error ce(hr);    
        m_what = std::string(CW2A(ce.ErrorMessage()));
        *this << ThrowHResult(boost::str(boost::format("0x%|1$08X|") % hr));
        *this << ThrowCOMError(ce);
    }
        
}}  // namespace Urasandesu { namespace CppAnonym {
