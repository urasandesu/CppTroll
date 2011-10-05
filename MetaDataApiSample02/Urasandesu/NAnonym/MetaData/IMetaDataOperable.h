#pragma once
#ifndef URASANDESU_NANONYM_METADATA_IMETADATAOPERABLE_H
#define URASANDESU_NANONYM_METADATA_IMETADATAOPERABLE_H

#ifndef URASANDESU_NANONYM_METADATA_USEDEFAULTMETADATAAPIIFNECESSARY_H
#include "Urasandesu/NAnonym/MetaData/UseDefaultMetaDataApiIfNecessary.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class MetaDataApiType>
    class Assembly;

    template<class MetaDataApiType = boost::use_default>
    class ATL_NO_VTABLE IMetaDataOperable : UseDefaultMetaDataApiIfNecessary<MetaDataApiType>
    {
    public:
        IMetaDataOperable() : m_pAsm(NULL), m_pApi(NULL) { }

        void Init(Assembly<MetaDataApiType> *pAsm, meta_data_api_type *pApi)
        {
            m_pAsm = pAsm;
            m_pApi = pApi;
        }
    
    protected:
        Assembly<MetaDataApiType> *m_pAsm;
        meta_data_api_type *m_pApi;
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_IMETADATAOPERABLE_H