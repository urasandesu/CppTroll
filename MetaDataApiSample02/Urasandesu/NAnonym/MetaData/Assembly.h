#pragma once
#ifndef URASANDESU_NANONYM_METADATA_ASSEMBLY_H
#define URASANDESU_NANONYM_METADATA_ASSEMBLY_H

#ifndef URASANDESU_NANONYM_METADATA_IMETADATAOPERABLE_H
#include "Urasandesu/NAnonym/MetaData/IMetaDataOperable.h"
#endif

#ifndef URASANDESU_NANONYM_METADATA_ITOKENIZABLE_H
#include "Urasandesu/NAnonym/MetaData/ITokenizable.h"
#endif

#ifndef URASANDESU_NANONYM_METADATA_MODULE_H
#include "Urasandesu/NAnonym/MetaData/Module.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class MetaDataApiType = boost::use_default>
    class Assembly : public IMetaDataOperable<MetaDataApiType>, public ITokenizable
    {
    public:
        Module<MetaDataApiType> *GetMainModule()
        {
            HRESULT hr = E_FAIL;
            
            Module<MetaDataApiType> *pMod = NULL;
            hr = m_pRuntime->GetHeap<Module<MetaDataApiType>>()->New(&pMod);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));

            pMod->Init(m_pRuntime, m_pApi);
                        
            return pMod;
        }
    };


}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_ASSEMBLY_H