#pragma once
#ifndef URASANDESU_CPPANONYM_PROFILING_BASEASSEMBLYPROFILE_H
#define URASANDESU_CPPANONYM_PROFILING_BASEASSEMBLYPROFILE_H

#ifndef URASANDESU_CPPANONYM_TRAITS_REPLACE_H
#include <Urasandesu/CppAnonym/Traits/Replace.h>
#endif

namespace Urasandesu { namespace CppAnonym { namespace Profiling {

#ifdef UNT
#error This .h reserves the word "UNT" that means "Urasandesu::CppAnonym::Traits".
#endif
#define UNT Urasandesu::CppAnonym::Traits

    template<
        class HeapManagerType,
        class ApiType
    >        
    class ATL_NO_VTABLE IProfilingApiOperable;

    template<
        class InfoProfilingApiType
    >
    class BaseProcessProfile;

    struct DefaultInfoProfilingApi;

    template<
        class InfoProfilingApiType = boost::use_default
    >
    class BaseAssemblyProfile : 
        public IProfilingApiOperable<
            BaseProcessProfile<InfoProfilingApiType>, 
            typename UNT::Replace<InfoProfilingApiType, boost::use_default, DefaultInfoProfilingApi>::type
        >
    {
    public:
        std::wstring GetName()
        {
            using namespace std;
            HRESULT hr = E_FAIL;
        
            if (m_name == L"")
            {
                WCHAR asmName[MAX_SYM_NAME] = { 0 };
                ULONG asmNameSize = sizeof(asmName);
                AppDomainID domainId = 0;
                ModuleID modId = 0;
                hr = GetApi()->ProfilerInfo->GetAssemblyInfo(GetID(), asmNameSize, 
                                                             &asmNameSize, asmName, &domainId, &modId);

                if (hr != CORPROF_E_DATAINCOMPLETE && FAILED(hr))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
                
                m_name = wstring(asmName);
            }
            return m_name;    
        }
        
    private:
        std::wstring m_name;
    };

    typedef BaseAssemblyProfile<boost::use_default> AssemblyProfile;

#undef UNT

}}}  // namespace Urasandesu { namespace CppAnonym { namespace Profiling {

#endif  // URASANDESU_CPPANONYM_PROFILING_BASEASSEMBLYPROFILE_H