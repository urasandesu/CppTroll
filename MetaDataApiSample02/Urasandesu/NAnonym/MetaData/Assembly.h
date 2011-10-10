#pragma once
#ifndef URASANDESU_NANONYM_METADATA_ASSEMBLY_H
#define URASANDESU_NANONYM_METADATA_ASSEMBLY_H

#ifndef URASANDESU_NANONYM_METADATA_HEAPPROVIDER_H
#include <Urasandesu/NAnonym/MetaData/HeapProvider.h>
#endif

#ifndef URASANDESU_NANONYM_METADATA_ELEMSIGNATURETRAIT_H
#include <Urasandesu/NAnonym/MetaData/ElemSignatureTrait.h>
#endif

inline ULONG CorSigUncompressSerString( // return number of bytes of that compressed string occupied in pData 
    PCCOR_SIGNATURE pData,              // [IN] compressed data 
    CHAR const **ppStr,                 // [OUT] string value of the expanded *pData    
    ULONG *pStrSize)                    // [OUT] string size of the expanded *pData    
{
    PCCOR_SIGNATURE pTmpData = pData;
    if (*pTmpData == 0xFF)
    {
        // NULL pointer
        *pStrSize = 0;
        *ppStr = NULL;
        return 1;
    }
    else
    {
        pTmpData += ::CorSigUncompressData(pTmpData, pStrSize);
        *ppStr = reinterpret_cast<CHAR const*>(pTmpData);
        pTmpData += sizeof(CHAR) * *pStrSize;
        return (pTmpData - pData) / sizeof(COR_SIGNATURE);
    }
}

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class AssemblyMetaDataApiType>
    class ATL_NO_VTABLE IMetaDataOperable;

    template<class AssemblyMetaDataApiType>
    class Module;

    template<class AssemblyMetaDataApiType>
    class TypeEnumerator;

    template<class AssemblyMetaDataApiType>
    class Type;

    template<class AssemblyMetaDataApiType>
    class MethodEnumerator;

    template<class AssemblyMetaDataApiType>
    class Method;

    template<class AssemblyMetaDataApiType>
    class MethodDefSignature;

    template<class AssemblyMetaDataApiType>
    class TypeSignature;

    template<class TokenizableType, class AssemblyMetaDataApiType>
    class CustomAttributeEnumerator;

    template<class TokenizableType, class AssemblyMetaDataApiType>
    class CustomAttribute;

    template<class AssemblyMetaDataApiType>
    class CustomAttributeSignature;

    template<class AssemblyMetaDataApiType>
    class FixedArgSignature;

    template<class AssemblyMetaDataApiType>
    class FixedArgArraySignature;

    template<class AssemblyMetaDataApiType>
    class FixedArgElemSignature;

    template<class AssemblyMetaDataApiType>
    class ElemSignature;

    template<class ValueType, class AssemblyMetaDataApiType>
    class SimpleOrEnumElemSignature;

    template<class AssemblyMetaDataApiType>
    class NamedArgSignature;

    template<class AssemblyMetaDataApiType = boost::use_default>
    class Assembly : public IMetaDataOperable<AssemblyMetaDataApiType>, public ITokenizable
    {
        BEGIN_META_DATA_HEAP_PROVIDER()
            DECLARE_META_DATA_HEAP_PROVIDER(Module<AssemblyMetaDataApiType>, m_pModFactory)
            DECLARE_META_DATA_HEAP_PROVIDER(TypeEnumerator<AssemblyMetaDataApiType>, m_pTypeEnumFactory)
            DECLARE_META_DATA_HEAP_PROVIDER(Type<AssemblyMetaDataApiType>, m_pTypeFactory)
            DECLARE_META_DATA_HEAP_PROVIDER(MethodEnumerator<AssemblyMetaDataApiType>, m_pMethodEnumFactory)
            DECLARE_META_DATA_HEAP_PROVIDER(Method<AssemblyMetaDataApiType>, m_pMethodFactory)
            DECLARE_META_DATA_HEAP_PROVIDER(MethodDefSignature<AssemblyMetaDataApiType>, m_pMethodDefSigFactory)
            DECLARE_META_DATA_HEAP_PROVIDER(TypeSignature<AssemblyMetaDataApiType>, m_pTypeSigFactory)
            typedef CustomAttributeEnumerator<Type<AssemblyMetaDataApiType>, AssemblyMetaDataApiType> type_custom_attribute_enumerator_type;
            DECLARE_META_DATA_HEAP_PROVIDER(type_custom_attribute_enumerator_type, m_pTypeCAEnumFactory)
            typedef CustomAttribute<Type<AssemblyMetaDataApiType>, AssemblyMetaDataApiType> type_custom_attribute_type;
            DECLARE_META_DATA_HEAP_PROVIDER(type_custom_attribute_type, m_pTypeCAFactory)
            typedef CustomAttributeEnumerator<Method<AssemblyMetaDataApiType>, AssemblyMetaDataApiType> method_custom_attribute_enumerator_type;
            DECLARE_META_DATA_HEAP_PROVIDER(method_custom_attribute_enumerator_type, m_pMethodCAEnumFactory)
            typedef CustomAttribute<Method<AssemblyMetaDataApiType>, AssemblyMetaDataApiType> method_custom_attribute_type;
            DECLARE_META_DATA_HEAP_PROVIDER(method_custom_attribute_type, m_pMethodCAFactory)
            DECLARE_META_DATA_HEAP_PROVIDER(CustomAttributeSignature<AssemblyMetaDataApiType>, m_pCASigFactory)
            DECLARE_META_DATA_HEAP_PROVIDER(FixedArgArraySignature<AssemblyMetaDataApiType>, m_pFixedArgArraySigFactory)
            DECLARE_META_DATA_HEAP_PROVIDER(FixedArgElemSignature<AssemblyMetaDataApiType>, m_pFixedArgElemSigFactory)
            typedef typename ElemSignatureTrait<ELEMENT_TYPE_I4_TYPE, AssemblyMetaDataApiType>::type i4_elem_signature_type;
            DECLARE_META_DATA_HEAP_PROVIDER(i4_elem_signature_type, m_pI4ElemSigFactory)
            typedef typename ElemSignatureTrait<ELEMENT_TYPE_STRING_TYPE, AssemblyMetaDataApiType>::type str_elem_signature_type;
            DECLARE_META_DATA_HEAP_PROVIDER(str_elem_signature_type, m_pStrElemSigFactory)
            DECLARE_META_DATA_HEAP_PROVIDER(NamedArgSignature<AssemblyMetaDataApiType>, m_pNamedArgSigFactory)
            DECLARE_META_DATA_HEAP_PROVIDER(std::vector<ULONG>, m_pULVectorFactory)
            DECLARE_META_DATA_HEAP_PROVIDER(std::vector<TypeSignature<AssemblyMetaDataApiType>*>, m_pTypeSigVectorFactory)
            DECLARE_META_DATA_HEAP_PROVIDER(std::vector<FixedArgSignature<AssemblyMetaDataApiType>*>, m_pFixedArgSigVectorFactory)
            DECLARE_META_DATA_HEAP_PROVIDER(std::vector<NamedArgSignature<AssemblyMetaDataApiType>*>, m_pNamedArgSigVectorFactory)
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