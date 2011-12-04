#pragma once
#ifndef URASANDESU_CPPANONYM_PROFILING_BASEPROCESSPROFILE_H
#define URASANDESU_CPPANONYM_PROFILING_BASEPROCESSPROFILE_H

#ifndef URASANDESU_CPPANONYM_TRAITS_REPLACE_H
#include <Urasandesu/CppAnonym/Traits/Replace.h>
#endif

#ifndef URASANDESU_CPPANONYM_HEAPPROVIDER_H
#include <Urasandesu/CppAnonym/HeapProvider.h>
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
        CPPANONYM_BEGIN_HEAP_PROVIDER_DECLARATION()
            CPPANONYM_HEAP_PROVIDER(BaseAppDomainProfile<InfoProfilingApiType>, UINT_PTR, m_pDomainProfFactory);
            CPPANONYM_HEAP_PROVIDER(BaseAssemblyProfile<InfoProfilingApiType>, UINT_PTR, m_pAsmProfFactory);
            CPPANONYM_HEAP_PROVIDER(BaseModuleProfile<InfoProfilingApiType>, UINT_PTR, m_pModProfFactory);
            CPPANONYM_HEAP_PROVIDER(BaseTypeProfile<InfoProfilingApiType>, UINT_PTR, m_pTypeProfFactory);
            CPPANONYM_HEAP_PROVIDER(BaseMethodProfile<InfoProfilingApiType>, UINT_PTR, m_pMethodProfFactory);
            CPPANONYM_HEAP_PROVIDER(BaseMethodBodyProfile<InfoProfilingApiType>, UINT_PTR, m_pMethodBodyProfFactory);
        CPPANONYM_END_HEAP_PROVIDER_DECLARATION()
        
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

}}}  // namespace Urasandesu { namespace CppAnonym { namespace Profiling {

#endif  // URASANDESU_CPPANONYM_PROFILING_BASEPROCESSPROFILE_H