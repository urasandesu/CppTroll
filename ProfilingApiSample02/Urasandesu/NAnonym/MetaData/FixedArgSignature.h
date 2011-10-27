#pragma once
#ifndef URASANDESU_NANONYM_METADATA_FIXEDARGSIGNATURE_H
#define URASANDESU_NANONYM_METADATA_FIXEDARGSIGNATURE_H

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class AssemblyMetaDataApiType>
    class ATL_NO_VTABLE IMetaDataOperable;

    template<class AssemblyMetaDataApiType = boost::use_default>
    class FixedArgSignature : public IMetaDataOperable<AssemblyMetaDataApiType>
    {
    public:
        virtual ~FixedArgSignature() { }
        virtual bool IsArray() = 0;
        
        PCCOR_SIGNATURE Blob;
        TypeSignature<AssemblyMetaDataApiType> *TypeSignature;        

        PCCOR_SIGNATURE GetParsedBlob()
        {
            FillPropertiesIfNecessary();
            return m_pParsedBlob;
        }

    protected:
        FixedArgSignature() :
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

#endif  // #ifndef URASANDESU_NANONYM_METADATA_FIXEDARGSIGNATURE_H