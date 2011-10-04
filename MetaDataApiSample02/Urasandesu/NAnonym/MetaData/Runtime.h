#pragma once
#ifndef URASANDESU_NANONYM_METADATA_RUNTIME_H
#define URASANDESU_NANONYM_METADATA_RUNTIME_H

#ifndef URASANDESU_NANONYM_METADATA_USEDEFAULTMETADATAAPIIFNECESSARY_H
#include "Urasandesu/NAnonym/MetaData/UseDefaultMetaDataApiIfNecessary.h"
#endif

#ifndef URASANDESU_NANONYM_METADATA_ASSEMBLY_H
#include "Urasandesu/NAnonym/MetaData/Assembly.h"
#endif

#ifndef URASANDESU_NANONYM_METADATA_MODULE_H
#include "Urasandesu/NAnonym/MetaData/Module.h"
#endif

#ifndef URASANDESU_NANONYM_METADATA_TYPEENUMERATOR_H
#include "Urasandesu/NAnonym/MetaData/TypeEnumerator.h"
#endif

#ifndef URASANDESU_NANONYM_METADATA_TYPE_H
#include "Urasandesu/NAnonym/MetaData/Type.h"
#endif

#ifndef URASANDESU_NANONYM_METADATA_METHODENUMERATOR_H
#include "Urasandesu/NAnonym/MetaData/MethodEnumerator.h"
#endif

#ifndef URASANDESU_NANONYM_METADATA_METHOD_H
#include "Urasandesu/NAnonym/MetaData/Method.h"
#endif

#ifndef URASANDESU_NANONYM_METADATA_METHODDEFSIGNATURE_H
#include "Urasandesu/NAnonym/MetaData/MethodDefSignature.h"
#endif

#ifndef URASANDESU_NANONYM_METADATA_TYPESIGNATURE_H
#include "Urasandesu/NAnonym/MetaData/TypeSignature.h"
#endif

#ifndef URASANDESU_NANONYM_SIMPLEHEAP_H
#include "Urasandesu/NAnonym/SimpleHeap.h"
#endif

#ifndef URASANDESU_NANONYM_NANONYMCOMEXCEPTION_H
#include "Urasandesu/NAnonym/NAnonymCOMException.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class MetaDataApiType = boost::use_default>
    class Runtime : UseDefaultMetaDataApiIfNecessary<MetaDataApiType>
    {
    public:
        typedef Urasandesu::NAnonym::SimpleHeap<meta_data_api_type> api_heap_type;
        typedef Urasandesu::NAnonym::SimpleHeap<Assembly<MetaDataApiType>> assembly_heap_type;
        typedef Urasandesu::NAnonym::SimpleHeap<Module<MetaDataApiType>> module_heap_type;
        typedef Urasandesu::NAnonym::SimpleHeap<TypeEnumerator<MetaDataApiType>> type_enumerator_heap_type;
        typedef Urasandesu::NAnonym::SimpleHeap<Type<MetaDataApiType>> type_heap_type;
        typedef Urasandesu::NAnonym::SimpleHeap<MethodEnumerator<MetaDataApiType>> method_enumerator_heap_type;
        typedef Urasandesu::NAnonym::SimpleHeap<Method<MetaDataApiType>> method_heap_type;
        typedef Urasandesu::NAnonym::SimpleHeap<MethodDefSignature<MetaDataApiType>> method_def_signature_heap_type;
        typedef Urasandesu::NAnonym::SimpleHeap<TypeSignature<MetaDataApiType>> typef_signature_heap_type;
        typedef Urasandesu::NAnonym::SimpleHeap<typename Type<MetaDataApiType>::custom_attribute_enumerator_type> type_custom_attribute_enumerator_type;
        typedef Urasandesu::NAnonym::SimpleHeap<typename Type<MetaDataApiType>::custom_attribute_type> type_custom_attribute_type;
        typedef Urasandesu::NAnonym::SimpleHeap<typename Method<MetaDataApiType>::custom_attribute_enumerator_type> method_custom_attribute_enumerator_type;
        typedef Urasandesu::NAnonym::SimpleHeap<typename Method<MetaDataApiType>::custom_attribute_type> method_custom_attribute_type;
        typedef Urasandesu::NAnonym::SimpleHeap<std::vector<ULONG>> ulong_vector_type;
        typedef Urasandesu::NAnonym::SimpleHeap<std::vector<TypeSignature<MetaDataApiType>*>> type_sig_vector_type;
        

    private:
        api_heap_type m_apiFactory;
        assembly_heap_type m_asmFactory;
        module_heap_type m_modFactory;
        type_enumerator_heap_type m_typeEnumFactory;
        type_heap_type m_typeFactory;
        method_enumerator_heap_type m_methodEnumFactory;
        method_heap_type m_methodFactory;
        method_def_signature_heap_type m_methodDefSigFactory;
        typef_signature_heap_type m_typeSigFactory;
        type_custom_attribute_enumerator_type m_typeCAEnumFactory;
        type_custom_attribute_type m_typeCAFactory;
        method_custom_attribute_enumerator_type m_methodCAEnumFactory;
        method_custom_attribute_type m_methodCAFactory;
        ulong_vector_type m_ulVectorFactory;
        type_sig_vector_type m_typeSigVectorFactory;

    public:
        template<class TokenizableType>
        Urasandesu::NAnonym::SimpleHeap<TokenizableType> *GetHeap();

        template<>
        api_heap_type *GetHeap()
        {
            return &m_apiFactory;
        }

        template<>
        assembly_heap_type *GetHeap()
        {
            return &m_asmFactory;
        }

        template<>
        module_heap_type *GetHeap()
        {
            return &m_modFactory;
        }

        template<>
        type_enumerator_heap_type *GetHeap()
        {
            return &m_typeEnumFactory;
        }

        template<>
        type_heap_type *GetHeap()
        {
            return &m_typeFactory;
        }

        template<>
        method_enumerator_heap_type *GetHeap()
        {
            return &m_methodEnumFactory;
        }

        template<>
        method_heap_type *GetHeap()
        {
            return &m_methodFactory;
        }

        template<>
        method_def_signature_heap_type *GetHeap()
        {
            return &m_methodDefSigFactory;
        }

        template<>
        typef_signature_heap_type *GetHeap()
        {
            return &m_typeSigFactory;
        }

        template<>
        type_custom_attribute_enumerator_type *GetHeap()
        {
            return &m_typeCAEnumFactory;
        }

        template<>
        type_custom_attribute_type *GetHeap()
        {
            return &m_typeCAFactory;
        }

        template<>
        method_custom_attribute_enumerator_type *GetHeap()
        {
            return &m_methodCAEnumFactory;
        }

        template<>
        method_custom_attribute_type *GetHeap()
        {
            return &m_methodCAFactory;
        }

        template<>
        ulong_vector_type *GetHeap()
        {
            return &m_ulVectorFactory;
        }

        template<>
        type_sig_vector_type *GetHeap()
        {
            return &m_typeSigVectorFactory;
        }

        Assembly<MetaDataApiType> *OpenAssembly(LPCWSTR scope, DWORD openFlags)
        {
            HRESULT hr = E_FAIL;

            meta_data_api_type *pApi = NULL;
            hr = GetHeap<meta_data_api_type>()->New(&pApi);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));

            hr = meta_data_api_type::CoCreateInstance(meta_data_api_type::CLSID_Dispenser, 
                                                      NULL, 
                                                      CLSCTX_INPROC_SERVER, 
                                                      meta_data_api_type::IID_IDispenser, 
                                                      reinterpret_cast<void**>(&pApi->Dispenser));
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));

            
            hr = pApi->Dispenser->OpenScope(scope, openFlags, meta_data_api_type::IID_IImport, 
                                            reinterpret_cast<IUnknown**>(&pApi->Import));
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));
            

            Assembly<MetaDataApiType> *pAsm = NULL;
            hr = GetHeap<Assembly<MetaDataApiType>>()->New(&pAsm);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));
            
            pAsm->Init(this, pApi);
            
            return pAsm;
        }
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_RUNTIME_H