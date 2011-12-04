
#include "stdafx.h"

#ifndef URASANDESU_CPPANONYM_CPPANONYMEXCEPTION_H
#include <Urasandesu/CppAnonym/CppAnonymException.h>
#endif

#ifndef URASANDESU_CPPANONYM_CPPANONYMSYSTEMEXCEPTION_H
#include <Urasandesu/CppAnonym/CppAnonymSystemException.h>
#endif

namespace Urasandesu { namespace CppAnonym {

    CppAnonymSystemException::CppAnonymSystemException(errno_t errno_)
    {
        using namespace boost::system;
        
        error_code ec(errno_, system_category());
        m_what = ec.message();
        *this << ThrowErrNo(errno_);
    }
        
}}  // namespace Urasandesu { namespace CppAnonym {
