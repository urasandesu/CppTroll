#pragma once
#ifndef URASANDESU_NANONYM_METADATA_CUSTOMATTRIBUTEENUMERATOR_H
#define URASANDESU_NANONYM_METADATA_CUSTOMATTRIBUTEENUMERATOR_H

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class AssemblyMetaDataApiType>
    class ATL_NO_VTABLE IMetaDataOperable;

    template<class TokenizableType, class AssemblyMetaDataApiType>
    class CustomAttribute;

    template<class TokenizableType, class AssemblyMetaDataApiType = boost::use_default>
    class CustomAttributeEnumerator : public IMetaDataOperable<AssemblyMetaDataApiType>, public ITokenizable
    {
    public:
        TokenizableType *Target;
        
        CustomAttributeEnumerator() : Target(NULL), m_hcaEnum(NULL), m_count(0), m_current(-1) { }
        ~CustomAttributeEnumerator()
        {
            if (m_hcaEnum)
                m_pApi->Import->CloseEnum(m_hcaEnum);
        }
        
        CustomAttribute<TokenizableType, AssemblyMetaDataApiType> *Next()
        {
            HRESULT hr = E_FAIL;
            
            if (++m_current <= 0 || m_count <= m_current)
            {
                hr = m_pApi->Import->EnumCustomAttributes(&m_hcaEnum, Target->GetToken(), 0, 
                                                  m_mdtrs.c_array(), m_mdtrs.size(), &m_count);
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));
                if (m_count <= 0)
                    return NULL;
            }

            CustomAttribute<TokenizableType, AssemblyMetaDataApiType> *pCA = NULL;
            hr = m_pAsm->GetHeap<CustomAttribute<TokenizableType, AssemblyMetaDataApiType>>()->New(&pCA);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));

            pCA->Init(m_pAsm, m_pApi);
            pCA->SetToken(m_mdtrs[m_current]);
            pCA->Target = Target;

            return pCA;
        }
    
    private:
        HCORENUM m_hcaEnum;
        boost::array<mdTypeRef, 16> m_mdtrs;
        ULONG m_count;
        ULONG m_current;
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_CUSTOMATTRIBUTEENUMERATOR_H