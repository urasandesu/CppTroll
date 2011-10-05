﻿#pragma once
#ifndef URASANDESU_NANONYM_METADATA_METHODDEFSIGNATURE_H
#define URASANDESU_NANONYM_METADATA_METHODDEFSIGNATURE_H

#ifndef URASANDESU_NANONYM_METADATA_IMETADATAOPERABLE_H
#include "Urasandesu/NAnonym/MetaData/IMetaDataOperable.h"
#endif

#ifndef URASANDESU_NANONYM_METADATA_TYPESIGNATURE_H
#include "Urasandesu/NAnonym/MetaData/TypeSignature.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class MetaDataApiType = boost::use_default>
    class MethodDefSignature : public IMetaDataOperable<MetaDataApiType>
    {
    public:
        MethodDefSignature() : 
            SignatureBlob(NULL),
            m_pParsedSigBlob(NULL),
            m_callingConv(-1), 
            m_paramCount(-1), 
            m_pRetTypeSig(NULL),
            m_pParamTypeSigs(NULL)
        {
        }

        PCCOR_SIGNATURE SignatureBlob;

        PCCOR_SIGNATURE GetParsedSigBlob()
        {
            FillPropertiesIfNecessary();
            return m_pParsedSigBlob;
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

        TypeSignature<MetaDataApiType> *GetReturnTypeSignature()
        {
            FillPropertiesIfNecessary();
            return m_pRetTypeSig;
        }
                
        std::vector<TypeSignature<MetaDataApiType>*> *GetParameterTypeSignatures()
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
            return m_pParsedSigBlob != NULL && m_callingConv != -1 && m_paramCount != -1 && m_pRetTypeSig != NULL;
        }
        
        void FillProperties()
        {
            HRESULT hr = E_FAIL;
            
            m_pParsedSigBlob = SignatureBlob;

            m_pParsedSigBlob += ::CorSigUncompressData(m_pParsedSigBlob, &m_callingConv);
            m_pParsedSigBlob += ::CorSigUncompressData(m_pParsedSigBlob, &m_paramCount);

            hr = m_pAsm->GetHeap<TypeSignature<MetaDataApiType>>()->New(&m_pRetTypeSig);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));
            
            m_pRetTypeSig->Init(m_pAsm, m_pApi);            
            m_pRetTypeSig->SignatureBlob = m_pParsedSigBlob;
            m_pParsedSigBlob = m_pRetTypeSig->GetParsedSigBlob();

            hr = m_pAsm->GetHeap<std::vector<TypeSignature<MetaDataApiType>*>>()->New(&m_pParamTypeSigs);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));
            for (ULONG i = 0; i < m_paramCount; ++i)   
            {
                TypeSignature<MetaDataApiType> *pTypeSig = NULL;
                hr = m_pAsm->GetHeap<TypeSignature<MetaDataApiType>>()->New(&pTypeSig);
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));
                
                pTypeSig->Init(m_pAsm, m_pApi);
                pTypeSig->SignatureBlob = m_pParsedSigBlob;
                m_pParsedSigBlob = pTypeSig->GetParsedSigBlob();

                m_pParamTypeSigs->push_back(pTypeSig);
            }
        }
        
                
        PCCOR_SIGNATURE m_pParsedSigBlob;
        ULONG m_callingConv;
        ULONG m_paramCount;

        TypeSignature<MetaDataApiType> *m_pRetTypeSig;        
        std::vector<TypeSignature<MetaDataApiType>*> *m_pParamTypeSigs;
    };



}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_METHODDEFSIGNATURE_H