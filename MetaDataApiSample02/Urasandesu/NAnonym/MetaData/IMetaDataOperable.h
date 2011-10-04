#pragma once
#ifndef URASANDESU_NANONYM_METADATA_IMETADATAOPERABLE_H
#define URASANDESU_NANONYM_METADATA_IMETADATAOPERABLE_H

#ifndef URASANDESU_NANONYM_METADATA_USEDEFAULTMETADATAAPIIFNECESSARY_H
#include "Urasandesu/NAnonym/MetaData/UseDefaultMetaDataApiIfNecessary.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class MetaDataApiType>
    class Runtime;

    template<class MetaDataApiType = boost::use_default>
    class ATL_NO_VTABLE IMetaDataOperable : UseDefaultMetaDataApiIfNecessary<MetaDataApiType>
    {
    public:
        IMetaDataOperable() : m_pRuntime(NULL), m_pApi(NULL) { }

        void Init(Runtime<MetaDataApiType> *pRuntime, meta_data_api_type *pApi)
        {
            m_pRuntime = pRuntime;
            m_pApi = pApi;
        }
    
    protected:
        Runtime<MetaDataApiType> *m_pRuntime;
        meta_data_api_type *m_pApi;
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_IMETADATAOPERABLE_H