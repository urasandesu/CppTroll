#pragma once
#ifndef URASANDESU_NANONYM_METADATA_CUSTOMATTRIBUTE_H
#define URASANDESU_NANONYM_METADATA_CUSTOMATTRIBUTE_H

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class AssemblyMetaDataApiType>
    class ATL_NO_VTABLE IMetaDataOperable;

    template<class AssemblyMetaDataApiType>
    class Method;

    template<class AssemblyMetaDataApiType>
    class CustomAttributeSignature;

    template<class TokenizableType, class AssemblyMetaDataApiType = boost::use_default>
    class CustomAttribute : public IMetaDataOperable<AssemblyMetaDataApiType>, public ITokenizable
    {
    public:
        TokenizableType *Target;
        
        CustomAttribute() : m_pMethod(NULL), m_pSignature(NULL) { }
    
        Method<AssemblyMetaDataApiType> *GetConstructor()
        {
            FillPropertiesIfNecessary();
            return m_pMethod;
        }
    
        CustomAttributeSignature<AssemblyMetaDataApiType> *GetSignature()
        {
            FillPropertiesIfNecessary();
            return m_pSignature;
        }
    
    private:
        void FillPropertiesIfNecessary()
        {
            if (!HasGotProperties())
                FillProperties();
        }
        
        bool HasGotProperties()
        {
            return m_pMethod != NULL && m_pSignature != NULL;
        }
        
        void FillProperties()
        {
            HRESULT hr = E_FAIL;
            
            mdToken mdtTarget = mdTokenNil;
            mdToken mdtCtor = mdTokenNil;
            void const *pBlob = NULL;
            ULONG blobSize = 0;
            hr = m_pApi->Import->GetCustomAttributeProps(GetToken(), &mdtTarget, &mdtCtor, &pBlob, &blobSize);
            if (FAILED(hr)) 
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));


            m_pMethod = m_pAsm->GetHeap<Method<AssemblyMetaDataApiType>>()->New();
            m_pMethod->Init(m_pAsm, m_pApi);
            m_pMethod->SetToken(mdtCtor);


            m_pSignature = m_pAsm->GetHeap<CustomAttributeSignature<AssemblyMetaDataApiType>>()->New();
            m_pSignature->Init(m_pAsm, m_pApi);
            m_pSignature->Blob = reinterpret_cast<PCCOR_SIGNATURE>(pBlob);
            m_pSignature->Constructor = m_pMethod;
        }
        
        Method<AssemblyMetaDataApiType> *m_pMethod;    
        CustomAttributeSignature<AssemblyMetaDataApiType> *m_pSignature;
    };


}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_CUSTOMATTRIBUTE_H