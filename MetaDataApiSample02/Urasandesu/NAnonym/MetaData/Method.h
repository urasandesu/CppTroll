#pragma once
#ifndef URASANDESU_NANONYM_METADATA_METHOD_H
#define URASANDESU_NANONYM_METADATA_METHOD_H

#ifndef URASANDESU_NANONYM_METADATA_IMETADATAOPERABLE_H
#include "Urasandesu/NAnonym/MetaData/IMetaDataOperable.h"
#endif

#ifndef URASANDESU_NANONYM_METADATA_ITOKENIZABLE_H
#include "Urasandesu/NAnonym/MetaData/ITokenizable.h"
#endif

#ifndef URASANDESU_NANONYM_METADATA_METHODDEFSIGNATURE_H
#include "Urasandesu/NAnonym/MetaData/MethodDefSignature.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class MetaDataApiType = boost::use_default>
    class Method : public IMetaDataOperable<MetaDataApiType>, public ITokenizable
    {
    public:
        typedef CustomAttributeEnumerator<Method<MetaDataApiType>, MetaDataApiType> custom_attribute_enumerator_type;
        typedef CustomAttribute<Method<MetaDataApiType>, MetaDataApiType> custom_attribute_type;
        
        Method() : m_pMethodSig(NULL) { }

        Type<MetaDataApiType> *DeclaringType;
        
        custom_attribute_enumerator_type *EnumerateCustomAttribute()
        {
            HRESULT hr = E_FAIL;
            custom_attribute_enumerator_type *pCAEnum = NULL;
            
            hr = m_pAsm->GetHeap<custom_attribute_enumerator_type>()->New(&pCAEnum);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));

            pCAEnum->Init(m_pAsm, m_pApi);
            pCAEnum->Target = this;
                        
            return pCAEnum;
        }
        
        MethodDefSignature<MetaDataApiType> *GetMethodSignature()
        {
            FillPropertiesIfNecessary();
            return m_pMethodSig;
        }
            
    private:
        void FillPropertiesIfNecessary()
        {
            if (!HasGotProperties())
                FillProperties();
        }
        
        bool HasGotProperties()
        {
            return m_pMethodSig != NULL;
        }
        
        void FillProperties()
        {
            HRESULT hr = E_FAIL;
            
            mdTypeDef mdtd = mdTypeDefNil;
            PCCOR_SIGNATURE pSigBlob = NULL;
            ULONG sigBlobSize = 0;
            hr = m_pApi->Import->GetMethodProps(GetToken(), &mdtd, 0, 0, 0, 0, &pSigBlob, &sigBlobSize, 0, 0);
            if (FAILED(hr)) 
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));
            
            hr = m_pAsm->GetHeap<MethodDefSignature<MetaDataApiType>>()->New(&m_pMethodSig);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));

            m_pMethodSig->Init(m_pAsm, m_pApi);
            m_pMethodSig->SignatureBlob = pSigBlob;
        }

        MethodDefSignature<MetaDataApiType> *m_pMethodSig;
    };


}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_METHOD_H