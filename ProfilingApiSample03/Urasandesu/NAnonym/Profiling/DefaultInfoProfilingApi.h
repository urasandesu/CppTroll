#pragma once
#ifndef URASANDESU_NANONYM_PROFILING_DEFAULTINFOPROFILINGAPI_H
#define URASANDESU_NANONYM_PROFILING_DEFAULTINFOPROFILINGAPI_H

namespace Urasandesu { namespace NAnonym { namespace Profiling {

    struct DefaultInfoProfilingApi
    {
        typedef ICorProfilerInfo2 IProfilerInfo;
        static IID const IID_IProfilerInfo;
        CComPtr<IProfilerInfo> ProfilerInfo;
    };
        
}}}  // namespace Urasandesu { namespace NAnonym { namespace Profiling {

#endif  // URASANDESU_NANONYM_PROFILING_DEFAULTINFOPROFILINGAPI_H