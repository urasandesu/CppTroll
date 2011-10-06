#pragma once
#ifndef URASANDESU_NANONYM_METADATA_USEDEFAULTMETADATAAPIIFNECESSARY_H
#define URASANDESU_NANONYM_METADATA_USEDEFAULTMETADATAAPIIFNECESSARY_H

#ifndef URASANDESU_NANONYM_TRAITS_REPLACE_H
#include <Urasandesu/NAnonym/Traits/Replace.h>
#endif

#ifndef URASANDESU_NANONYM_METADATA_DEFAULTMETADATAAPI_H
#include <Urasandesu/NAnonym/MetaData/DefaultMetaDataApi.h>
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class DispenserMetaDataApiType = boost::use_default>
    struct ATL_NO_VTABLE UseDefaultDispenserMetaDataApiIfNecessary
    {
        typedef typename Urasandesu::NAnonym::Traits::Replace<DispenserMetaDataApiType, boost::use_default, DefaultDispenserMetaDataApi>::type meta_data_api_type;
    };

    template<class AssemblyMetaDataApiType = boost::use_default>
    struct ATL_NO_VTABLE UseDefaultAssemblyMetaDataApiIfNecessary
    {
        typedef typename Urasandesu::NAnonym::Traits::Replace<AssemblyMetaDataApiType, boost::use_default, DefaultAssemblyMetaDataApi>::type meta_data_api_type;
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_USEDEFAULTMETADATAAPIIFNECESSARY_H