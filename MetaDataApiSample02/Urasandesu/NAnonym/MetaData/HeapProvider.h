#pragma once
#ifndef URASANDESU_NANONYM_METADATA_HEAPPROVIDER_H
#define URASANDESU_NANONYM_METADATA_HEAPPROVIDER_H

#ifndef URASANDESU_NANONYM_SIMPLEHEAP_H
#include <Urasandesu/NAnonym/SimpleHeap.h>
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    struct DefaultDispenserMetaDataApi;

    struct DefaultAssemblyMetaDataApi;

    template<class AssemblyMetaDataApiType>
    class Assembly;

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

    template<template<class> class Arg1Type>
    struct Collapse1
    {
        template<class ApplyingType>
        struct apply
        {
            typedef Arg1Type<ApplyingType> type;
        };
    };
    
    template<template<class, class> class Arg2Type, template<class> class Arg1Type>
    struct Collapse2
    {
        template<class ApplyingType>
        struct apply
        {
            typedef Arg2Type<Arg1Type<ApplyingType>, ApplyingType> type;
        };
    };
    
    template<class ContentOrApplyingType, class CollapseType>
    class Heap;
    
    class Void;
    
#undef DECLARE_HEAP_DEFINITIONS
#define DECLARE_HEAP_DEFINITIONS() \
    private: \
        boost::shared_ptr<heap_type> m_pFactory; \
    public: \
        heap_type *GetHeap() \
        { \
            if (!m_pFactory.get()) \
            { \
                m_pFactory = boost::make_shared<heap_type>(); \
            } \
            return m_pFactory.get(); \
        }


#undef DECLARE_HEAP
#define DECLARE_HEAP() \
    template<class ContentOrApplyingType> \
    class Heap<ContentOrApplyingType, Void> \
    { \
    public: \
        typedef Urasandesu::NAnonym::SimpleHeap<ContentOrApplyingType> heap_type; \
        DECLARE_HEAP_DEFINITIONS() \
    };
    
    DECLARE_HEAP()

#undef DECLARE_HEAP



#undef DECLARE_HEAP1
#define DECLARE_HEAP1(type1) \
    template<class ContentOrApplyingType> \
    class Heap<ContentOrApplyingType, Collapse1<type1>> \
    { \
    public: \
        typedef Urasandesu::NAnonym::SimpleHeap<typename Collapse1<type1>::apply<ContentOrApplyingType>::type> heap_type; \
        DECLARE_HEAP_DEFINITIONS() \
    };

    DECLARE_HEAP1(Assembly)
    DECLARE_HEAP1(Module)
    DECLARE_HEAP1(TypeEnumerator)
    DECLARE_HEAP1(Type)
    DECLARE_HEAP1(MethodEnumerator)
    DECLARE_HEAP1(Method)
    DECLARE_HEAP1(MethodDefSignature)
    DECLARE_HEAP1(TypeSignature)

#undef DECLARE_HEAP1



#undef DECLARE_HEAP2
#define DECLARE_HEAP2(type2, type1) \
    template<class ContentOrApplyingType> \
    class Heap<ContentOrApplyingType, Collapse2<type2, type1>> \
    { \
    public: \
        typedef Urasandesu::NAnonym::SimpleHeap<typename Collapse2<type2, type1>::apply<ContentOrApplyingType>::type> heap_type; \
        DECLARE_HEAP_DEFINITIONS() \
    };

    DECLARE_HEAP2(CustomAttributeEnumerator, Type)
    DECLARE_HEAP2(CustomAttribute, Type)
    DECLARE_HEAP2(CustomAttributeEnumerator, Method)
    DECLARE_HEAP2(CustomAttribute, Method)

#undef DECLARE_HEAP2

#undef DECLARE_HEAP_DEFINITIONS




#define BEGIN_META_DATA_HEAP_PROVIDER() \
    public: \
        template<class T> \
        Urasandesu::NAnonym::SimpleHeap<T> *GetHeap();


#define DECLARE_META_DATA_HEAP_PROVIDER(meta_data_api_type, name) \
    private: \
        Urasandesu::NAnonym::MetaData::Heap<meta_data_api_type, Void> name; \
    public: \
        template<> \
        typename Urasandesu::NAnonym::MetaData::Heap<meta_data_api_type, Void>::heap_type *GetHeap() \
        { \
            return name.GetHeap(); \
        }


#define DECLARE_META_DATA_HEAP_PROVIDER1(meta_data_api_type, type1, name) \
    private: \
        Urasandesu::NAnonym::MetaData::Heap<meta_data_api_type, \
            Urasandesu::NAnonym::MetaData::Collapse1<type1>> name; \
    public: \
        template<> \
        typename Urasandesu::NAnonym::MetaData::Heap<meta_data_api_type, \
            Urasandesu::NAnonym::MetaData::Collapse1<type1>>::heap_type *GetHeap() \
        { \
            return name.GetHeap(); \
        }


#define DECLARE_META_DATA_HEAP_PROVIDER2(meta_data_api_type, type2, type1, name) \
    private: \
        Urasandesu::NAnonym::MetaData::Heap<meta_data_api_type, \
            Urasandesu::NAnonym::MetaData::Collapse2<type2, type1>> name; \
    public: \
        template<> \
        typename Urasandesu::NAnonym::MetaData::Heap<meta_data_api_type, \
            Urasandesu::NAnonym::MetaData::Collapse2<type2, type1>>::heap_type *GetHeap() \
        { \
            return name.GetHeap(); \
        }


#define END_META_DATA_HEAP_PROVIDER()

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_HEAPPROVIDER_H