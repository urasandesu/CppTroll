#pragma once
#ifndef URASANDESU_NANONYM_METADATA_MODULE_H
#define URASANDESU_NANONYM_METADATA_MODULE_H

#ifndef URASANDESU_NANONYM_METADATA_IMETADATAOPERABLE_H
#include <Urasandesu/NAnonym/MetaData/IMetaDataOperable.h>
#endif

#ifndef URASANDESU_NANONYM_METADATA_ITOKENIZABLE_H
#include <Urasandesu/NAnonym/MetaData/ITokenizable.h>
#endif

#ifndef URASANDESU_NANONYM_METADATA_TYPEENUMERATOR_H
#include <Urasandesu/NAnonym/MetaData/TypeEnumerator.h>
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class AssemblyMetaDataApiType = boost::use_default>
    class Module : public IMetaDataOperable<AssemblyMetaDataApiType>, public ITokenizable
    {
    public:
        TypeEnumerator<AssemblyMetaDataApiType> *EnumerateType()
        {
            HRESULT hr = E_FAIL;
            TypeEnumerator<AssemblyMetaDataApiType> *pTypeEnum = NULL;
            
            hr = m_pAsm->GetHeap<TypeEnumerator<AssemblyMetaDataApiType>>()->New(&pTypeEnum);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));

            pTypeEnum->Init(m_pAsm, m_pApi);
                        
            return pTypeEnum;
        }
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_MODULE_H