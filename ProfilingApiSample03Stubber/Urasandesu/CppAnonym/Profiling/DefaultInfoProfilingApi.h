#pragma once
#ifndef URASANDESU_CPPANONYM_PROFILING_DEFAULTINFOPROFILINGAPI_H
#define URASANDESU_CPPANONYM_PROFILING_DEFAULTINFOPROFILINGAPI_H

namespace Urasandesu { namespace CppAnonym { namespace Profiling {

    struct DefaultInfoProfilingApi
    {
        typedef ICorProfilerInfo2 IProfilerInfo;
        static IID const IID_IProfilerInfo;
        CComPtr<IProfilerInfo> ProfilerInfo;
    };
        
}}}  // namespace Urasandesu { namespace CppAnonym { namespace Profiling {

#endif  // URASANDESU_CPPANONYM_PROFILING_DEFAULTINFOPROFILINGAPI_H