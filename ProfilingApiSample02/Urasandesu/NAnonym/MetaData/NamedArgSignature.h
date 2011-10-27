#pragma once
#ifndef URASANDESU_NANONYM_METADATA_NAMEDARGSIGNATURE_H
#define URASANDESU_NANONYM_METADATA_NAMEDARGSIGNATURE_H

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class AssemblyMetaDataApiType>
    class ATL_NO_VTABLE IMetaDataOperable;

    template<class AssemblyMetaDataApiType>
    class TypeSignature;

    template<class AssemblyMetaDataApiType>
    class FixedArgSignature;

    template<class AssemblyMetaDataApiType = boost::use_default>
    class NamedArgSignature : public IMetaDataOperable<AssemblyMetaDataApiType>
    {
    public:
        NamedArgSignature() :
            Blob(NULL),
            m_pParsedBlob(NULL),
            m_kind(static_cast<CorSerializationType>(0)),
            m_pTypeSig(NULL),
            m_pFixedArgSig(NULL)
        { }

        PCCOR_SIGNATURE Blob;

        PCCOR_SIGNATURE GetParsedBlob()
        {
            FillPropertiesIfNecessary();
            return m_pParsedBlob;
        }

        CorSerializationType GetKind()
        {
            FillPropertiesIfNecessary();
            return m_kind;
        }
        
        TypeSignature<AssemblyMetaDataApiType> *GetTypeSignature()
        {
            FillPropertiesIfNecessary();
            return m_pTypeSig;
        }

        std::string const &GetName()
        {
            FillPropertiesIfNecessary();
            return m_name;
        }
        
        FixedArgSignature<AssemblyMetaDataApiType> *GetFixedArgSignature()
        {
            FillPropertiesIfNecessary();
            return m_pFixedArgSig;
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
                   m_kind != -1 &&
                   m_pTypeSig != NULL &&
                   m_pFixedArgSig != NULL;
        }
        
        void FillProperties()
        {
            m_pParsedBlob = Blob;
            


		    m_kind = static_cast<CorSerializationType>(*reinterpret_cast<PCCOR_SIGNATURE>(m_pParsedBlob));
		    m_pParsedBlob += sizeof(COR_SIGNATURE); 
            
            

            m_pTypeSig = m_pAsm->GetHeap<TypeSignature<AssemblyMetaDataApiType>>()->New();
            m_pTypeSig->Init(m_pAsm, m_pApi);            
            m_pTypeSig->Blob = m_pParsedBlob;
            m_pParsedBlob = m_pTypeSig->GetParsedBlob();
            
            

            ULONG strSize = 0;
            std::string::const_pointer pStr = NULL;
            m_pParsedBlob += CorSigUncompressSerString(m_pParsedBlob, &pStr, &strSize);
            m_name = std::string(pStr, strSize);
            
            

            if (m_pTypeSig->IsArray())
            {
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymException("Not Implemented !!"));
            }
            else
            {
                m_pFixedArgSig = m_pAsm->GetHeap<FixedArgElemSignature<AssemblyMetaDataApiType>>()->New();
                m_pFixedArgSig->Init(m_pAsm, m_pApi);
                m_pFixedArgSig->Blob = m_pParsedBlob;
                m_pFixedArgSig->TypeSignature = m_pTypeSig;
                m_pParsedBlob = m_pFixedArgSig->GetParsedBlob();
            }
        }
        
        PCCOR_SIGNATURE m_pParsedBlob;
        CorSerializationType m_kind;    // At now, the kind of Named Arg signature is only
                                        // set SERIALIZATION_TYPE_FIELD or SERIALIZATION_TYPE_PROPERTY.
        TypeSignature<AssemblyMetaDataApiType> *m_pTypeSig;
        std::string m_name;        
        FixedArgSignature<AssemblyMetaDataApiType> *m_pFixedArgSig;
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_NAMEDARGSIGNATURE_H