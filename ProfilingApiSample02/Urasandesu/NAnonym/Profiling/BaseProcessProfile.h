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
        BEGIN_NANONYM_HEAP_PROVIDER()
            DECLARE_NANONYM_HEAP_PROVIDER(BaseAppDomainProfile<InfoProfilingApiType>, UINT_PTR, m_pDomainProfFactory);
            DECLARE_NANONYM_HEAP_PROVIDER(BaseAssemblyProfile<InfoProfilingApiType>, UINT_PTR, m_pAsmProfFactory);
            DECLARE_NANONYM_HEAP_PROVIDER(BaseModuleProfile<InfoProfilingApiType>, UINT_PTR, m_pModProfFactory);
            DECLARE_NANONYM_HEAP_PROVIDER(BaseTypeProfile<InfoProfilingApiType>, UINT_PTR, m_pTypeProfFactory);
            DECLARE_NANONYM_HEAP_PROVIDER(BaseMethodProfile<InfoProfilingApiType>, UINT_PTR, m_pMethodProfFactory);
            DECLARE_NANONYM_HEAP_PROVIDER(BaseMethodBodyProfile<InfoProfilingApiType>, UINT_PTR, m_pMethodBodyProfFactory);
        END_NANONYM_HEAP_PROVIDER()
        
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