#pragma once
#ifndef URASANDESU_NANONYM_METADATA_IMETADATAOPERABLE_H
#define URASANDESU_NANONYM_METADATA_IMETADATAOPERABLE_H

#ifndef URASANDESU_NANONYM_METADATA_USEDEFAULTMETADATAAPIIFNECESSARY_H
#include <Urasandesu/NAnonym/MetaData/UseDefaultMetaDataApiIfNecessary.h>
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class AssemblyMetaDataApiType>
    struct ATL_NO_VTABLE UseDefaultAssemblyMetaDataApiIfNecessary;

    template<class AssemblyMetaDataApiType>
    class Assembly;

    template<class AssemblyMetaDataApiType = boost::use_default>
    class ATL_NO_VTABLE IMetaDataOperable : UseDefaultAssemblyMetaDataApiIfNecessary<AssemblyMetaDataApiType>
    {
    public:
        IMetaDataOperable() : m_pAsm(NULL), m_pApi(NULL) { }

        void Init(Assembly<AssemblyMetaDataApiType> *pAsm, meta_data_api_type *pApi)
        {
            m_pAsm = pAsm;
            m_pApi = pApi;
        }
    
    protected:
        Assembly<AssemblyMetaDataApiType> *m_pAsm;
        meta_data_api_type *m_pApi;
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_IMETADATAOPERABLE_H