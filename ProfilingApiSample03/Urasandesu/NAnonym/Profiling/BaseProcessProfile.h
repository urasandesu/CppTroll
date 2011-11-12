#pragma once
#ifndef URASANDESU_NANONYM_PROFILING_BASEPROCESSPROFILE_H
#define URASANDESU_NANONYM_PROFILING_BASEPROCESSPROFILE_H

#ifndef URASANDESU_NANONYM_TRAITS_REPLACE_H
#include <Urasandesu/NAnonym/Traits/Replace.h>
#endif

#ifndef URASANDESU_NANONYM_HEAPPROVIDER_H
#include <Urasandesu/NAnonym/HeapProvider.h>
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

    struct DefaultInfoProfilingApi;

    template<
        class InfoProfilingApiType
    >
    class BaseAppDomainProfile;

    template<
        class InfoProfilingApiType
    >
    class BaseAssemblyProfile;

    template<
        class InfoProfilingApiType
    >
    class BaseModuleProfile;

    template<
        class InfoProfilingApiType
    >
    class BaseTypeProfile;

    template<
        class InfoProfilingApiType
    >
    class BaseMethodProfile;

    template<
        class InfoProfilingApiType
    >
    class BaseMethodBodyProfile;

    template<
        class InfoProfilingApiType = boost::use_default
    >
    class BaseProcessProfile : 
        public IProfilingApiOperable<
            BaseProcessProfile<InfoProfilingApiType>, 
            typename UNT::Replace<InfoProfilingApiType, boost::use_default, DefaultInfoProfilingApi>::type
        >
    {
        NANONYM_BEGIN_HEAP_PROVIDER_DECLARATION()
            NANONYM_HEAP_PROVIDER(BaseAppDomainProfile<InfoProfilingApiType>, UINT_PTR, m_pDomainProfFactory);
            NANONYM_HEAP_PROVIDER(BaseAssemblyProfile<InfoProfilingApiType>, UINT_PTR, m_pAsmProfFactory);
            NANONYM_HEAP_PROVIDER(BaseModuleProfile<InfoProfilingApiType>, UINT_PTR, m_pModProfFactory);
            NANONYM_HEAP_PROVIDER(BaseTypeProfile<InfoProfilingApiType>, UINT_PTR, m_pTypeProfFactory);
            NANONYM_HEAP_PROVIDER(BaseMethodProfile<InfoProfilingApiType>, UINT_PTR, m_pMethodProfFactory);
            NANONYM_HEAP_PROVIDER(BaseMethodBodyProfile<InfoProfilingApiType>, UINT_PTR, m_pMethodBodyProfFactory);
        NANONYM_END_HEAP_PROVIDER_DECLARATION()
        
    public:
        BaseAppDomainProfile<InfoProfilingApiType> *GetPseudoDomain()
        {
            return CreatePseudo<BaseAppDomainProfile<InfoProfilingApiType>>();
        }
        
        BaseAppDomainProfile<InfoProfilingApiType> *GetCurrentDomain()
        {
            return GetHeapManager()->Peek<BaseAppDomainProfile<InfoProfilingApiType>>();
        }
    };

    typedef BaseProcessProfile<boost::use_default> ProcessProfile;

#undef UNT

}}}  // namespace Urasandesu { namespace NAnonym { namespace Profiling {

#endif  // URASANDESU_NANONYM_PROFILING_BASEPROCESSPROFILE_H