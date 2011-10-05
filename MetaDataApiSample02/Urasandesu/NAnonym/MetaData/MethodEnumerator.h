#pragma once
#ifndef URASANDESU_NANONYM_METADATA_METHODENUMERATOR_H
#define URASANDESU_NANONYM_METADATA_METHODENUMERATOR_H

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class MetaDataApiType>
    class Type;

    template<class MetaDataApiType = boost::use_default>
    class MethodEnumerator : public IMetaDataOperable<MetaDataApiType>, public ITokenizable
    {
    public:
        MethodEnumerator() : DeclaringType(NULL), m_hmdEnum(NULL), m_count(0), m_current(-1) { }
        ~MethodEnumerator()
        {
            if (m_hmdEnum)
                m_pApi->Import->CloseEnum(m_hmdEnum);
        }

        Type<MetaDataApiType> *DeclaringType;

        Method<MetaDataApiType> *Next()
        {
            HRESULT hr = E_FAIL;
            
            if (++m_current <= 0 || m_count <= m_current)
            {
                hr = m_pApi->Import->EnumMethods(&m_hmdEnum, DeclaringType->GetToken(),  
                                                  m_mdmds.c_array(), m_mdmds.size(), &m_count);
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));
                if (m_count <= 0)
                    return NULL;
            }

            Method<MetaDataApiType> *pMethod = NULL;
            hr = m_pAsm->GetHeap<Method<MetaDataApiType>>()->New(&pMethod);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));

            pMethod->Init(m_pAsm, m_pApi);
            pMethod->SetToken(m_mdmds[m_current]);
            pMethod->DeclaringType = DeclaringType;

            return pMethod;
        }
    
    private:
        HCORENUM m_hmdEnum;
        boost::array<mdMethodDef, 16> m_mdmds;
        ULONG m_count;
        ULONG m_current;
    };



}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_METHODENUMERATOR_H