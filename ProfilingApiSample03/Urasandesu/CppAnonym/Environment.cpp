
#include "stdafx.h"

#ifndef URASANDESU_CPPANONYM_ENVIRONMENT_H
#include <Urasandesu/CppAnonym/Environment.h>
#endif

#ifndef URASANDESU_CPPANONYM_CPPANONYMSYSTEMEXCEPTION_H
#include <Urasandesu/CppAnonym/CppAnonymSystemException.h>
#endif

namespace Urasandesu { namespace CppAnonym {

    std::string Environment::GetEnvironmentVariable(LPCSTR variable)
    {
        char *pVarValue = NULL;
        size_t varValueSize = 0;
        errno_t err = ::_dupenv_s(&pVarValue, &varValueSize, variable);
        if (err)
            BOOST_THROW_EXCEPTION(CppAnonymSystemException(err));
        return std::string(pVarValue, varValueSize);
    }
        
}}  // namespace Urasandesu { namespace CppAnonym {
