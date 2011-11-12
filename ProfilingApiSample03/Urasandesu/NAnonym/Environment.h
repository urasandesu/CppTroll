#pragma once
#ifndef URASANDESU_NANONYM_ENVIRONMENT_H
#define URASANDESU_NANONYM_ENVIRONMENT_H

namespace Urasandesu { namespace NAnonym {

    struct Environment
    {
        static std::string GetEnvironmentVariable(LPCSTR variable);
    };
        
}}  // namespace Urasandesu { namespace NAnonym {

#endif  // URASANDESU_NANONYM_ENVIRONMENT_H