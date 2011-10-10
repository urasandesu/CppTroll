#pragma once
#ifndef URASANDESU_NANONYM_METADATA_SIMPLEORENUMELEMSIGNATURE_H
#define URASANDESU_NANONYM_METADATA_SIMPLEORENUMELEMSIGNATURE_H

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class AssemblyMetaDataApiType>
    class ElemSignature;

    template<class ValueType, class AssemblyMetaDataApiType = boost::use_default>
    class SimpleOrEnumElemSignature : public ElemSignature<AssemblyMetaDataApiType>
    {
    public:
        SimpleOrEnumElemSignature() : m_value() { }
        virtual ~SimpleOrEnumElemSignature() { }
        
        ValueType GetValue()
        {
            FillPropertiesIfNecessary();
            return m_value;
        }
        
    protected:
        virtual bool HasGotPropertiesCore()
        {
            return true;
        }
        
        virtual void FillPropertiesCore()
        {
		    m_value = *reinterpret_cast<const ValueType*>(m_pParsedBlob); 
		    m_pParsedBlob += sizeof(ValueType); 
        }
    
    private:
        ValueType m_value;
    };


    template<class AssemblyMetaDataApiType = boost::use_default>
    class StringOrTypeElemSignature : public ElemSignature<AssemblyMetaDataApiType>
    {
    public:
        StringOrTypeElemSignature() { }
        virtual ~StringOrTypeElemSignature() { }
        
        std::string &GetValue()
        {
            FillPropertiesIfNecessary();
            return m_value;
        }
        
    protected:
        virtual bool HasGotPropertiesCore()
        {
            return true;
        }
        
        virtual void FillPropertiesCore()
        {
            ULONG strSize = 0;
            std::string::const_pointer pStr = NULL;
            m_pParsedBlob += ::CorSigUncompressSerString(m_pParsedBlob, &pStr, &strSize);
            m_value = std::string(pStr, strSize);
        }
    
    private:
        std::string m_value;
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_SIMPLEORENUMELEMSIGNATURE_H