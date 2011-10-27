#pragma once
#ifndef URASANDESU_NANONYM_PROFILING_BASEMODULEPROFILE_H
#define URASANDESU_NANONYM_PROFILING_BASEMODULEPROFILE_H

#ifndef URASANDESU_NANONYM_TRAITS_REPLACE_H
#include <Urasandesu/NAnonym/Traits/Replace.h>
#endif

namespace Urasandesu { namespace NAnonym { namespace Profiling {

#ifdef UNT
#error This .h reserves the word "UNT" that means "Urasandesu::NAnonym::Traits".
#endif
#define UNT Urasandesu::NAnonym::Traits

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
    class BaseModuleProfile : 
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
                LPCBYTE pBaseLoadAddress = NULL;
                WCHAR modName[MAX_SYM_NAME] = { 0 };
                ULONG modNameSize = sizeof(modName);
                AssemblyID asmId = 0;
                
                hr = GetApi()->ProfilerInfo->GetModuleInfo(GetID(), &pBaseLoadAddress, 
                                                modNameSize, &modNameSize, modName, &asmId);
                if (hr != CORPROF_E_DATAINCOMPLETE && FAILED(hr))
                    BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
                
                m_name = wstring(modName);
            }
            return m_name;
        }
    
    private:
        std::wstring m_name;
    };

    typedef BaseModuleProfile<boost::use_default> ModuleProfile;

#undef UNT

}}}  // namespace Urasandesu { namespace NAnonym { namespace Profiling {

#endif  // URASANDESU_NANONYM_PROFILING_BASEMODULEPROFILE_H