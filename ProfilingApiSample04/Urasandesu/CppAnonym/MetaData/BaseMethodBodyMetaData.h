#pragma once
#ifndef URASANDESU_CPPANONYM_METADATA_BASEMETHODBODYMETADATA_H
#define URASANDESU_CPPANONYM_METADATA_BASEMETHODBODYMETADATA_H

#ifndef URASANDESU_CPPANONYM_TRAITS_REPLACE_H
#include <Urasandesu/CppAnonym/Traits/Replace.h>
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
        class AssemblyMetaDataApiType = boost::use_default
    >
    class BaseMethodBodyMetaData : 
        public IMetaDataApiOperable<
            BaseAssemblyMetaData<AssemblyMetaDataApiType>, 
            typename UNT::Replace<AssemblyMetaDataApiType, boost::use_default, DefaultAssemblyMetaDataApi>::type
        >
    {
    };

    typedef BaseMethodBodyMetaData<boost::use_default> MethodBodyMetaData;

#undef UNT

}}}   // namespace Urasandesu { namespace CppAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_CPPANONYM_METADATA_BASEMETHODBODYMETADATA_H