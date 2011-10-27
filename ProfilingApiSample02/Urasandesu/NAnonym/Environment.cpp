
#include "stdafx.h"

#ifndef URASANDESU_NANONYM_ENVIRONMENT_H
#include <Urasandesu/NAnonym/Environment.h>
#endif

#ifndef URASANDESU_NANONYM_NANONYMSYSTEMEXCEPTION_H
#include <Urasandesu/NAnonym/NAnonymSystemException.h>
#endif

namespace Urasandesu { namespace NAnonym {

    std::string Environment::GetEnvironmentVariable(LPCSTR variable)
    {
        char *pVarValue = NULL;
        size_t varValueSize = 0;
        errno_t err = ::_dupenv_s(&pVarValue, &varValueSize, variable);
        if (err)
            BOOST_THROW_EXCEPTION(NAnonymSystemException(err));
        return std::string(pVarValue, varValueSize);
    }
        
}}  // namespace Urasandesu { namespace NAnonym {
