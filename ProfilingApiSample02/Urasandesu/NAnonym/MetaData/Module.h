#pragma once
#ifndef URASANDESU_NANONYM_METADATA_MODULE_H
#define URASANDESU_NANONYM_METADATA_MODULE_H

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class AssemblyMetaDataApiType>
    class ATL_NO_VTABLE IMetaDataOperable;

    template<class AssemblyMetaDataApiType>
    class TypeEnumerator;

    template<class AssemblyMetaDataApiType = boost::use_default>
    class Module : public IMetaDataOperable<AssemblyMetaDataApiType>, public ITokenizable
    {
    public:
        TypeEnumerator<AssemblyMetaDataApiType> *EnumerateType()
        {
            TypeEnumerator<AssemblyMetaDataApiType> *pTypeEnum = NULL;
            
            pTypeEnum = m_pAsm->GetHeap<TypeEnumerator<AssemblyMetaDataApiType>>()->New();
            pTypeEnum->Init(m_pAsm, m_pApi);
                        
            return pTypeEnum;
        }
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_MODULE_H