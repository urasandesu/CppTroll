
#include "stdafx.h"

#ifndef URASANDESU_NANONYM_NANONYMEXCEPTION_H
#include <Urasandesu/NAnonym/NAnonymException.h>
#endif

#ifndef URASANDESU_NANONYM_NANONYMSYSTEMEXCEPTION_H
#include <Urasandesu/NAnonym/NAnonymSystemException.h>
#endif

namespace Urasandesu { namespace NAnonym {

    NAnonymSystemException::NAnonymSystemException(errno_t errno_)
    {
        using namespace boost::system;
        
        error_code ec(errno_, system_category());
        m_what = ec.message();
        *this << ThrowErrNo(errno_);
    }
        
}}  // namespace Urasandesu { namespace NAnonym {
