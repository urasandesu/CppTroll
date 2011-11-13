#pragma once
#ifndef URASANDESU_CPPANONYM_CPPANONYMCOMEXCEPTION_H
#define URASANDESU_CPPANONYM_CPPANONYMCOMEXCEPTION_H

#ifndef URASANDESU_CPPANONYM_CPPANONYMEXCEPTION_H
#include <Urasandesu/CppAnonym/CppAnonymException.h>
#endif

namespace Urasandesu { namespace CppAnonym {

    typedef boost::error_info<struct tag_hresult, std::string> ThrowHResult;
    typedef boost::error_info<struct tag_com_error, _com_error> ThrowCOMError;
    
    struct CppAnonymCOMException : CppAnonymException
    {
        CppAnonymCOMException(HRESULT hr);
    };
        
}}  // namespace Urasandesu { namespace CppAnonym {

#endif  // URASANDESU_CPPANONYM_CPPANONYMCOMEXCEPTION_H