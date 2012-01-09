#pragma once
#ifndef URASANDESU_CPPANONYM_ENVIRONMENT_H
#define URASANDESU_CPPANONYM_ENVIRONMENT_H

namespace Urasandesu { namespace CppAnonym {

    struct Environment
    {
        static std::string GetEnvironmentVariable(LPCSTR variable);
    };
        
}}  // namespace Urasandesu { namespace CppAnonym {

#endif  // URASANDESU_CPPANONYM_ENVIRONMENT_H