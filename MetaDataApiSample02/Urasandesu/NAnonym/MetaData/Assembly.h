#pragma once
#ifndef URASANDESU_NANONYM_METADATA_ASSEMBLY_H
#define URASANDESU_NANONYM_METADATA_ASSEMBLY_H

#ifndef URASANDESU_NANONYM_METADATA_HEAPPROVIDER_H
#include <Urasandesu/NAnonym/MetaData/HeapProvider.h>
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class AssemblyMetaDataApiType>
    class ATL_NO_VTABLE IMetaDataOperable;

    template<class AssemblyMetaDataApiType = boost::use_default>
    class Assembly : public IMetaDataOperable<AssemblyMetaDataApiType>, public ITokenizable
    {
        BEGIN_META_DATA_HEAP_PROVIDER()
            DECLARE_META_DATA_HEAP_PROVIDER1(AssemblyMetaDataApiType, Module, m_modFactory)
            DECLARE_META_DATA_HEAP_PROVIDER1(AssemblyMetaDataApiType, TypeEnumerator, m_typeEnumFactory)
            DECLARE_META_DATA_HEAP_PROVIDER1(AssemblyMetaDataApiType, Type, m_typeFactory)
            DECLARE_META_DATA_HEAP_PROVIDER1(AssemblyMetaDataApiType, MethodEnumerator, m_methodEnumFactory)
            DECLARE_META_DATA_HEAP_PROVIDER1(AssemblyMetaDataApiType, Method, m_methodFactory)
            DECLARE_META_DATA_HEAP_PROVIDER1(AssemblyMetaDataApiType, MethodDefSignature, m_methodDefSigFactory)
            DECLARE_META_DATA_HEAP_PROVIDER1(AssemblyMetaDataApiType, TypeSignature, m_typeSigFactory)
            DECLARE_META_DATA_HEAP_PROVIDER2(AssemblyMetaDataApiType, CustomAttributeEnumerator, Type, m_typeCAEnumFactory)
            DECLARE_META_DATA_HEAP_PROVIDER2(AssemblyMetaDataApiType, CustomAttribute, Type, m_typeCAFactory)
            DECLARE_META_DATA_HEAP_PROVIDER2(AssemblyMetaDataApiType, CustomAttributeEnumerator, Method, m_methodCAEnumFactory)
            DECLARE_META_DATA_HEAP_PROVIDER2(AssemblyMetaDataApiType, CustomAttribute, Method, m_methodCAFactory)
            DECLARE_META_DATA_HEAP_PROVIDER(std::vector<ULONG>, m_ulVectorFactory)
            DECLARE_META_DATA_HEAP_PROVIDER(std::vector<TypeSignature<AssemblyMetaDataApiType>*>, m_typeSigVectorFactory)
        END_META_DATA_HEAP_PROVIDER()

    public:
        Module<AssemblyMetaDataApiType> *GetMainModule()
        {
            HRESULT hr = E_FAIL;
            
            Module<AssemblyMetaDataApiType> *pMod = NULL;
            hr = m_pAsm->GetHeap<Module<AssemblyMetaDataApiType>>()->New(&pMod);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));

            pMod->Init(m_pAsm, m_pApi);
                        
            return pMod;
        }
    };


}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_ASSEMBLY_H