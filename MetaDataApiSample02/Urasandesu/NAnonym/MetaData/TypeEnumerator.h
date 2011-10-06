#pragma once
#ifndef URASANDESU_NANONYM_METADATA_TYPEENUMERATOR_H
#define URASANDESU_NANONYM_METADATA_TYPEENUMERATOR_H

#ifndef URASANDESU_NANONYM_METADATA_IMETADATAOPERABLE_H
#include <Urasandesu/NAnonym/MetaData/IMetaDataOperable.h>
#endif

#ifndef URASANDESU_NANONYM_METADATA_ITOKENIZABLE_H
#include <Urasandesu/NAnonym/MetaData/ITokenizable.h>
#endif

#ifndef URASANDESU_NANONYM_METADATA_TYPE_H
#include <Urasandesu/NAnonym/MetaData/Type.h>
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class AssemblyMetaDataApiType = boost::use_default>
    class TypeEnumerator : public IMetaDataOperable<AssemblyMetaDataApiType>, public ITokenizable
    {
    public:
        TypeEnumerator() : m_htdEnum(NULL), m_count(0), m_current(-1) { }
        ~TypeEnumerator()
        {
            if (m_htdEnum)
                m_pApi->Import->CloseEnum(m_htdEnum);
        }

        Type<AssemblyMetaDataApiType> *Next()
        {
            HRESULT hr = E_FAIL;
            
            if (++m_current <= 0 || m_count <= m_current)
            {
                hr = m_pApi->Import->EnumTypeDefs(&m_htdEnum, m_mdtds.c_array(), m_mdtds.size(), &m_count);
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));
                if (m_count <= 0)
                    return NULL;
            }
            
            Type<AssemblyMetaDataApiType> *pType = NULL;
            hr = m_pAsm->GetHeap<Type<AssemblyMetaDataApiType>>()->New(&pType);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));

            pType->Init(m_pAsm, m_pApi);
            pType->SetToken(m_mdtds[m_current]);
            
            return pType;
        }
        
    private:
        HCORENUM m_htdEnum;
        boost::array<mdTypeDef, 16> m_mdtds;
        ULONG m_count;
        ULONG m_current;
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_TYPEENUMERATOR_H