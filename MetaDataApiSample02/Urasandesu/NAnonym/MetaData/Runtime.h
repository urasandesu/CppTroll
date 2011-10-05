#pragma once
#ifndef URASANDESU_NANONYM_METADATA_RUNTIME_H
#define URASANDESU_NANONYM_METADATA_RUNTIME_H

#ifndef URASANDESU_NANONYM_METADATA_USEDEFAULTMETADATAAPIIFNECESSARY_H
#include "Urasandesu/NAnonym/MetaData/UseDefaultMetaDataApiIfNecessary.h"
#endif

#ifndef URASANDESU_NANONYM_SIMPLEHEAP_H
#include "Urasandesu/NAnonym/SimpleHeap.h"
#endif

#ifndef URASANDESU_NANONYM_METADATA_ASSEMBLY_H
#include "Urasandesu/NAnonym/MetaData/Assembly.h"
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
        

    private:
        api_heap_type m_apiFactory;
        assembly_heap_type m_asmFactory;

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
            
            pAsm->Init(pAsm, pApi);
            
            return pAsm;
        }
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_RUNTIME_H