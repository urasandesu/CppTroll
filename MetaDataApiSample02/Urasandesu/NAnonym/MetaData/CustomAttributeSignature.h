#pragma once
#ifndef URASANDESU_NANONYM_METADATA_CUSTOMATTRIBUTESIGNATURE_H
#define URASANDESU_NANONYM_METADATA_CUSTOMATTRIBUTESIGNATURE_H

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class AssemblyMetaDataApiType>
    class ATL_NO_VTABLE IMetaDataOperable;

    template<class AssemblyMetaDataApiType>
    class Method;

    template<class AssemblyMetaDataApiType>
    class FixedArgSignature;

    template<class AssemblyMetaDataApiType = boost::use_default>
    class CustomAttributeSignature : public IMetaDataOperable<AssemblyMetaDataApiType>
    {
    public:
        CustomAttributeSignature() :
            Blob(NULL), 
            Constructor(NULL),
            m_pParsedBlob(NULL), 
            m_prolog(-1), 
            m_pFixedArgSigs(NULL),
            m_pNamedArgSigs(NULL)
        { }
        
        PCCOR_SIGNATURE Blob;
        Method<AssemblyMetaDataApiType> *Constructor;

        USHORT GetPrologue()
        {
            FillPropertiesIfNecessary();
            return m_prolog;
        }

        std::vector<FixedArgSignature<AssemblyMetaDataApiType>*> *GetFixedArgSignatures()
        {
            FillPropertiesIfNecessary();
            return m_pFixedArgSigs;
        }

        std::vector<NamedArgSignature<AssemblyMetaDataApiType>*> *GetNamedArgSignatures()
        {
            FillPropertiesIfNecessary();
            return m_pNamedArgSigs;
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
                   m_prolog != -1 && 
                   m_pFixedArgSigs != NULL &&
                   m_pNamedArgSigs != NULL;
        }
        
        void FillProperties()
        {
            m_pParsedBlob = Blob;

		    
		    
		    m_prolog = *reinterpret_cast<const USHORT*>(m_pParsedBlob); 
		    m_pParsedBlob += sizeof(USHORT); 
		    
		    
		    
		    m_pFixedArgSigs = m_pAsm->GetHeap<std::vector<FixedArgSignature<AssemblyMetaDataApiType>*>>()->New();

            MethodDefSignature<AssemblyMetaDataApiType> *pMethodSig = Constructor->GetMethodSignature();
            typedef std::vector<TypeSignature<AssemblyMetaDataApiType>*>::iterator type_sig_vector_iterator;
            for (type_sig_vector_iterator i = pMethodSig->GetParameterTypeSignatures()->begin(), 
                                          i_end = pMethodSig->GetParameterTypeSignatures()->end();
                 i != i_end;
                 ++i)
            {
                if ((*i)->IsArray())
                {
                    BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymException("Not Implemented !!"));
                }
                else
                {
                    FixedArgElemSignature<AssemblyMetaDataApiType> *pFixedArgElemSig = NULL;
                    pFixedArgElemSig = m_pAsm->GetHeap<FixedArgElemSignature<AssemblyMetaDataApiType>>()->New();
                    pFixedArgElemSig->Init(m_pAsm, m_pApi);
                    pFixedArgElemSig->Blob = m_pParsedBlob;
                    pFixedArgElemSig->TypeSignature = *i;
                    m_pParsedBlob = pFixedArgElemSig->GetParsedBlob();
                    m_pFixedArgSigs->push_back(pFixedArgElemSig);
                }
            }
		    
		    
		    
            m_pNamedArgSigs = m_pAsm->GetHeap<std::vector<NamedArgSignature<AssemblyMetaDataApiType>*>>()->New();
            UINT16 namedArgSigsCount = 0;
            namedArgSigsCount = *reinterpret_cast<const UINT16*>(m_pParsedBlob);
            m_pParsedBlob += sizeof(UINT16);
            for (UINT16 i = 0; i < namedArgSigsCount; ++i)
            {
                NamedArgSignature<AssemblyMetaDataApiType> *pNamedArgSig = NULL;
                pNamedArgSig = m_pAsm->GetHeap<NamedArgSignature<AssemblyMetaDataApiType>>()->New();
                pNamedArgSig->Init(m_pAsm, m_pApi);
                pNamedArgSig->Blob = m_pParsedBlob;
                m_pParsedBlob = pNamedArgSig->GetParsedBlob();
                m_pNamedArgSigs->push_back(pNamedArgSig);
            }
        }
        
        PCCOR_SIGNATURE m_pParsedBlob;
        USHORT m_prolog;
        std::vector<FixedArgSignature<AssemblyMetaDataApiType>*> *m_pFixedArgSigs;
        std::vector<NamedArgSignature<AssemblyMetaDataApiType>*> *m_pNamedArgSigs;
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_CUSTOMATTRIBUTESIGNATURE_H