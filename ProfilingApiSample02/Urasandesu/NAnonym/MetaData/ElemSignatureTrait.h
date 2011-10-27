#pragma once
#ifndef URASANDESU_NANONYM_METADATA_ELEMSIGNATURETRAIT_H
#define URASANDESU_NANONYM_METADATA_ELEMSIGNATURETRAIT_H

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class AssemblyMetaDataApiType>
    class ElemSignature;

    template<class ValueType, class AssemblyMetaDataApiType>
    class SimpleOrEnumElemSignature;

    template<class AssemblyMetaDataApiType>
    class StringOrTypeElemSignature;

    template<class ElementType, class AssemblyMetaDataApiType = boost::use_default>
    struct ElemSignatureTrait;

#define DECLARE_SIMPLE_OR_ENUM_ELEM_SIGNATURE(cor_element_type, value_type) \
    typedef boost::mpl::int_<cor_element_type> cor_element_type##_TYPE; \
    template<class AssemblyMetaDataApiType> \
    struct ElemSignatureTrait<cor_element_type##_TYPE, AssemblyMetaDataApiType> \
    { \
        typedef SimpleOrEnumElemSignature<value_type, AssemblyMetaDataApiType> type; \
        static type *ToConcrete(ElemSignature<AssemblyMetaDataApiType> *pElemSig) \
        { \
            return dynamic_cast<type*>(pElemSig); \
        } \
    };
    
    DECLARE_SIMPLE_OR_ENUM_ELEM_SIGNATURE(ELEMENT_TYPE_I4, signed __int32)




#define DECLARE_STRING_OR_TYPE_ELEM_SIGNATURE(cor_element_type) \
    typedef boost::mpl::int_<cor_element_type> cor_element_type##_TYPE; \
    template<class AssemblyMetaDataApiType> \
    struct ElemSignatureTrait<cor_element_type##_TYPE, AssemblyMetaDataApiType> \
    { \
        typedef StringOrTypeElemSignature<AssemblyMetaDataApiType> type; \
        static type *ToConcrete(ElemSignature<AssemblyMetaDataApiType> *pElemSig) \
        { \
            return dynamic_cast<type*>(pElemSig); \
        } \
    };
    
    DECLARE_STRING_OR_TYPE_ELEM_SIGNATURE(ELEMENT_TYPE_STRING)

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_ELEMSIGNATURETRAIT_H