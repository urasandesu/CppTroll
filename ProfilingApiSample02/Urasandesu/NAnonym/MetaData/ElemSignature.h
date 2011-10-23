#pragma once
#ifndef URASANDESU_NANONYM_METADATA_ELEMSIGNATURE_H
#define URASANDESU_NANONYM_METADATA_ELEMSIGNATURE_H

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class AssemblyMetaDataApiType>
    class ATL_NO_VTABLE IMetaDataOperable;

    template<class AssemblyMetaDataApiType>
    class TypeSignature;

    template<class AssemblyMetaDataApiType = boost::use_default>
    class ElemSignature : public IMetaDataOperable<AssemblyMetaDataApiType>
    {
    public:        
        virtual ~ElemSignature() { }

        PCCOR_SIGNATURE Blob;
        TypeSignature<AssemblyMetaDataApiType> *TypeSignature;        

        CorElementType GetType()
        {
            return TypeSignature->GetType();
        }
        
        PCCOR_SIGNATURE GetParsedBlob()
        {
            FillPropertiesIfNecessary();
            return m_pParsedBlob;
        }

    protected:
        ElemSignature() :
            Blob(NULL),
            TypeSignature(NULL),        
            m_pParsedBlob(NULL)
        { }

        void FillPropertiesIfNecessary()
        {
            if (!HasGotProperties())
                FillProperties();
        }
        
        virtual bool HasGotPropertiesCore() = 0;
        virtual void FillPropertiesCore() = 0;
        
        PCCOR_SIGNATURE m_pParsedBlob;

    private:
        bool HasGotProperties()
        {
            return m_pParsedBlob != NULL && HasGotPropertiesCore();
        }
        
        void FillProperties()
        {
            m_pParsedBlob = Blob;
            FillPropertiesCore();
        }
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_ELEMSIGNATURE_H