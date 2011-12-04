#pragma once
#ifndef URASANDESU_CPPANONYM_CPPANONYMSYSTEMEXCEPTION_H
#define URASANDESU_CPPANONYM_CPPANONYMSYSTEMEXCEPTION_H

#ifndef URASANDESU_CPPANONYM_CPPANONYMEXCEPTION_H
#include <Urasandesu/CppAnonym/CppAnonymException.h>
#endif

namespace Urasandesu { namespace CppAnonym {

    typedef boost::error_info<struct tag_errno, errno_t> ThrowErrNo;
    
    struct CppAnonymSystemException : CppAnonymException
    {
        CppAnonymSystemException(errno_t errno_);
    };
        
}}  // namespace Urasandesu { namespace CppAnonym {

#endif  // URASANDESU_CPPANONYM_CPPANONYMSYSTEMEXCEPTION_H