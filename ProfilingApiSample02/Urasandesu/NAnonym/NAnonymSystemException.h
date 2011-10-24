#pragma once
#ifndef URASANDESU_NANONYM_NANONYMSYSTEMEXCEPTION_H
#define URASANDESU_NANONYM_NANONYMSYSTEMEXCEPTION_H

#ifndef URASANDESU_NANONYM_NANONYMEXCEPTION_H
#include <Urasandesu/NAnonym/NAnonymException.h>
#endif

namespace Urasandesu { namespace NAnonym {

    typedef boost::error_info<struct tag_errno, errno_t> ThrowErrNo;
    
    struct NAnonymSystemException : NAnonymException
    {
        NAnonymSystemException(errno_t errno_);
    };
        
}}  // namespace Urasandesu { namespace NAnonym {

#endif  // URASANDESU_NANONYM_NANONYMSYSTEMEXCEPTION_H