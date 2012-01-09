#pragma once
#ifndef URASANDESU_CPPANONYM_METADATA_BASEASSEMBLYMETADATA_H
#define URASANDESU_CPPANONYM_METADATA_BASEASSEMBLYMETADATA_H

#ifndef URASANDESU_CPPANONYM_TRAITS_REPLACE_H
#include <Urasandesu/CppAnonym/Traits/Replace.h>
#endif

#ifndef URASANDESU_CPPANONYM_HEAPPROVIDER_H
#include <Urasandesu/CppAnonym/HeapProvider.h>
#endif

namespace Urasandesu { namespace CppAnonym { namespace MetaData {

#ifdef UNT
#error This .h reserves the word "UNT" that means "Urasandesu::CppAnonym::Traits".
#endif
#define UNT Urasandesu::CppAnonym::Traits

    template<
        class HeapManagerType,
        class ApiType
    >        
    class ATL_NO_VTABLE IMetaDataApiOperable;

    template<
        class AssemblyMetaDataApiType
    >
    class BaseAssemblyMetaData;

    struct DefaultAssemblyMetaDataApi;

    template<
        class AssemblyMetaDataApiType
    >
    class BaseModuleMetaData;

    template<
        class AssemblyMetaDataApiType
    >
    class BaseTypeMetaData;

    template<
        class AssemblyMetaDataApiType
    >
    class BaseMethodMetaData;

    template<
        class AssemblyMetaDataApiType = boost::use_default
    >
    class BaseAssemblyMetaData : 
        public IMetaDataApiOperable<
            BaseAssemblyMetaData<AssemblyMetaDataApiType>, 
            typename UNT::Replace<AssemblyMetaDataApiType, boost::use_default, DefaultAssemblyMetaDataApi>::type
        >
    {
        CPPANONYM_BEGIN_HEAP_PROVIDER_DECLARATION()
            CPPANONYM_HEAP_PROVIDER(BaseModuleMetaData<AssemblyMetaDataApiType>, mdToken, m_pModMetaFactory);
            CPPANONYM_HEAP_PROVIDER(BaseTypeMetaData<AssemblyMetaDataApiType>, mdToken, m_pTypeMetaFactory);
            CPPANONYM_HEAP_PROVIDER(BaseMethodMetaData<AssemblyMetaDataApiType>, mdToken, m_pMethodMetaFactory);
        CPPANONYM_END_HEAP_PROVIDER_DECLARATION()
    };

    typedef BaseAssemblyMetaData<boost::use_default> AssemblyMetaData;

#undef UNT

}}}   // namespace Urasandesu { namespace CppAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_CPPANONYM_METADATA_BASEASSEMBLYMETADATA_H