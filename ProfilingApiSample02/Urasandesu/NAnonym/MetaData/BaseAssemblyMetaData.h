#pragma once
#ifndef URASANDESU_NANONYM_METADATA_BASEASSEMBLYMETADATA_H
#define URASANDESU_NANONYM_METADATA_BASEASSEMBLYMETADATA_H

#ifndef URASANDESU_NANONYM_TRAITS_REPLACE_H
#include <Urasandesu/NAnonym/Traits/Replace.h>
#endif

#ifndef URASANDESU_NANONYM_HEAPPROVIDER_H
#include <Urasandesu/NAnonym/HeapProvider.h>
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {

#ifdef UNT
#error This .h reserves the word "UNT" that means "Urasandesu::NAnonym::Traits".
#endif
#define UNT Urasandesu::NAnonym::Traits

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
        BEGIN_NANONYM_HEAP_PROVIDER()
            DECLARE_NANONYM_HEAP_PROVIDER(BaseModuleMetaData<AssemblyMetaDataApiType>, mdToken, m_pModMetaFactory);
            DECLARE_NANONYM_HEAP_PROVIDER(BaseTypeMetaData<AssemblyMetaDataApiType>, mdToken, m_pTypeMetaFactory);
            DECLARE_NANONYM_HEAP_PROVIDER(BaseMethodMetaData<AssemblyMetaDataApiType>, mdToken, m_pMethodMetaFactory);
        END_NANONYM_HEAP_PROVIDER()
    };

    typedef BaseAssemblyMetaData<boost::use_default> AssemblyMetaData;

#undef UNT

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_BASEASSEMBLYMETADATA_H