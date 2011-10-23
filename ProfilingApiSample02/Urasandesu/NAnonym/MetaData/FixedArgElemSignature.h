#pragma once
#ifndef URASANDESU_NANONYM_METADATA_FIXEDARGELEMSIGNATURE_H
#define URASANDESU_NANONYM_METADATA_FIXEDARGELEMSIGNATURE_H

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class AssemblyMetaDataApiType>
    class FixedArgSignature;

    template<class AssemblyMetaDataApiType>
    class TypeSignature;

    template<class AssemblyMetaDataApiType>
    class ElemSignature;

    template<class AssemblyMetaDataApiType = boost::use_default>
    class FixedArgElemSignature : public FixedArgSignature<AssemblyMetaDataApiType>
    {
    public:
        FixedArgElemSignature() : 
            m_pElem(NULL)
        { }
        
        virtual ~FixedArgElemSignature() { }
        virtual bool IsArray()
        {
            return false;
        }

        ElemSignature<AssemblyMetaDataApiType> *GetElem()
        {
            FillPropertiesIfNecessary();
            return m_pElem;
        }
    
    protected:
        virtual bool HasGotPropertiesCore()
        {
            return m_pElem != NULL;
        }
        
        virtual void FillPropertiesCore()
        {
            m_pParsedBlob = Blob;
            
            switch (TypeSignature->GetType())
            {
                case ELEMENT_TYPE_I4:
                    m_pElem = m_pAsm->GetHeap<ElemSignatureTrait<ELEMENT_TYPE_I4_TYPE, AssemblyMetaDataApiType>::type>()->New();
                    break;
                case ELEMENT_TYPE_STRING:
                    m_pElem = m_pAsm->GetHeap<ElemSignatureTrait<ELEMENT_TYPE_STRING_TYPE, AssemblyMetaDataApiType>::type>()->New();
                    break;
                default:
                    BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymException("Not Implemented !!"));
                    break;
            }
            
            m_pElem->Init(m_pAsm, m_pApi);
            m_pElem->Blob = m_pParsedBlob;
            m_pElem->TypeSignature = TypeSignature;
            m_pParsedBlob = m_pElem->GetParsedBlob();
        }
        
    private:
        ElemSignature<AssemblyMetaDataApiType> *m_pElem;
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_FIXEDARGELEMSIGNATURE_H