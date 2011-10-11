#pragma once
#ifndef URASANDESU_NANONYM_METADATA_METHODDEFSIGNATURE_H
#define URASANDESU_NANONYM_METADATA_METHODDEFSIGNATURE_H

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class AssemblyMetaDataApiType>
    class TypeSignature;

    template<class AssemblyMetaDataApiType = boost::use_default>
    class MethodDefSignature : public IMetaDataOperable<AssemblyMetaDataApiType>
    {
    public:
        MethodDefSignature() : 
            Blob(NULL),
            m_pParsedBlob(NULL),
            m_callingConv(-1), 
            m_paramCount(-1), 
            m_pRetTypeSig(NULL),
            m_pParamTypeSigs(NULL)
        {
        }

        PCCOR_SIGNATURE Blob;

        PCCOR_SIGNATURE GetParsedBlob()
        {
            FillPropertiesIfNecessary();
            return m_pParsedBlob;
        }

        ULONG GetCallingConversion()
        {
            FillPropertiesIfNecessary();
            return m_callingConv;
        }
        
        ULONG GetParameterCount()
        {
            FillPropertiesIfNecessary();
            return m_paramCount;
        }

        TypeSignature<AssemblyMetaDataApiType> *GetReturnTypeSignature()
        {
            FillPropertiesIfNecessary();
            return m_pRetTypeSig;
        }
                
        std::vector<TypeSignature<AssemblyMetaDataApiType>*> *GetParameterTypeSignatures()
        {
            FillPropertiesIfNecessary();
            return m_pParamTypeSigs;
        }

    private:
        void FillPropertiesIfNecessary()
        {
            if (!HasGotProperties())
                FillProperties();
        }
        
        bool HasGotProperties()
        {
            return m_pParsedBlob != NULL && 
                   m_callingConv != -1 && 
                   m_paramCount != -1 && 
                   m_pRetTypeSig != NULL;
        }
        
        void FillProperties()
        {
            HRESULT hr = E_FAIL;
            
            m_pParsedBlob = Blob;

            m_pParsedBlob += ::CorSigUncompressData(m_pParsedBlob, &m_callingConv);
            m_pParsedBlob += ::CorSigUncompressData(m_pParsedBlob, &m_paramCount);

            m_pRetTypeSig = m_pAsm->GetHeap<TypeSignature<AssemblyMetaDataApiType>>()->New();
            m_pRetTypeSig->Init(m_pAsm, m_pApi);            
            m_pRetTypeSig->Blob = m_pParsedBlob;
            m_pParsedBlob = m_pRetTypeSig->GetParsedBlob();

            m_pParamTypeSigs = m_pAsm->GetHeap<std::vector<TypeSignature<AssemblyMetaDataApiType>*>>()->New();
            for (ULONG i = 0; i < m_paramCount; ++i)   
            {
                TypeSignature<AssemblyMetaDataApiType> *pTypeSig = NULL;
                pTypeSig = m_pAsm->GetHeap<TypeSignature<AssemblyMetaDataApiType>>()->New();
                pTypeSig->Init(m_pAsm, m_pApi);
                pTypeSig->Blob = m_pParsedBlob;
                m_pParsedBlob = pTypeSig->GetParsedBlob();

                m_pParamTypeSigs->push_back(pTypeSig);
            }
        }
        
                
        PCCOR_SIGNATURE m_pParsedBlob;
        ULONG m_callingConv;
        ULONG m_paramCount;

        TypeSignature<AssemblyMetaDataApiType> *m_pRetTypeSig;        
        std::vector<TypeSignature<AssemblyMetaDataApiType>*> *m_pParamTypeSigs;
    };



}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_METHODDEFSIGNATURE_H