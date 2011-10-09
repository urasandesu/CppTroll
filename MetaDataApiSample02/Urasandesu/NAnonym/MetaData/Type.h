#pragma once
#ifndef URASANDESU_NANONYM_METADATA_TYPE_H
#define URASANDESU_NANONYM_METADATA_TYPE_H

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class AssemblyMetaDataApiType>
    class ATL_NO_VTABLE IMetaDataOperable;

    template<class TokenizableType, class AssemblyMetaDataApiType>
    class CustomAttributeEnumerator;

    template<class TokenizableType, class AssemblyMetaDataApiType>
    class CustomAttribute;

    template<class AssemblyMetaDataApiType>
    class MethodEnumerator;

    template<class AssemblyMetaDataApiType = boost::use_default>
    class Type : public IMetaDataOperable<AssemblyMetaDataApiType>, public ITokenizable
    {
    public:
        typedef CustomAttributeEnumerator<Type<AssemblyMetaDataApiType>, AssemblyMetaDataApiType> custom_attribute_enumerator_type;
        typedef CustomAttribute<Type<AssemblyMetaDataApiType>, AssemblyMetaDataApiType> custom_attribute_type;

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
        
        MethodEnumerator<AssemblyMetaDataApiType> *EnumerateMethod()
        {
            HRESULT hr = E_FAIL;
            MethodEnumerator<AssemblyMetaDataApiType> *pMethodEnum = NULL;
            
            hr = m_pAsm->GetHeap<MethodEnumerator<AssemblyMetaDataApiType>>()->New(&pMethodEnum);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));

            pMethodEnum->Init(m_pAsm, m_pApi);
            pMethodEnum->DeclaringType = this;
                        
            return pMethodEnum;
        }
        
    };


}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_TYPE_H