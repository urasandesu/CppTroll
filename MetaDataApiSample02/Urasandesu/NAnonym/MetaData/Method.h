#pragma once
#ifndef URASANDESU_NANONYM_METADATA_METHOD_H
#define URASANDESU_NANONYM_METADATA_METHOD_H

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class AssemblyMetaDataApiType>
    class ATL_NO_VTABLE IMetaDataOperable;

    template<class TokenizableType, class AssemblyMetaDataApiType>
    class CustomAttributeEnumerator;

    template<class TokenizableType, class AssemblyMetaDataApiType>
    class CustomAttribute;

    template<class AssemblyMetaDataApiType>
    class Type;

    template<class AssemblyMetaDataApiType>
    class MethodDefSignature;

    template<class AssemblyMetaDataApiType = boost::use_default>
    class Method : public IMetaDataOperable<AssemblyMetaDataApiType>, public ITokenizable
    {
    public:
        typedef CustomAttributeEnumerator<Method<AssemblyMetaDataApiType>, AssemblyMetaDataApiType> custom_attribute_enumerator_type;
        typedef CustomAttribute<Method<AssemblyMetaDataApiType>, AssemblyMetaDataApiType> custom_attribute_type;
        
        Method() : m_pMethodSig(NULL) { }

        Type<AssemblyMetaDataApiType> *DeclaringType;
        
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
        
        MethodDefSignature<AssemblyMetaDataApiType> *GetMethodSignature()
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
            
            hr = m_pAsm->GetHeap<MethodDefSignature<AssemblyMetaDataApiType>>()->New(&m_pMethodSig);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));

            m_pMethodSig->Init(m_pAsm, m_pApi);
            m_pMethodSig->Blob = pSigBlob;
        }

        MethodDefSignature<AssemblyMetaDataApiType> *m_pMethodSig;
    };


}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_METHOD_H