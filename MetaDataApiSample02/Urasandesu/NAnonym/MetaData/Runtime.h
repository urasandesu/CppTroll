#pragma once
#ifndef URASANDESU_NANONYM_METADATA_RUNTIME_H
#define URASANDESU_NANONYM_METADATA_RUNTIME_H

#ifndef URASANDESU_NANONYM_METADATA_USEDEFAULTMETADATAAPIIFNECESSARY_H
#include <Urasandesu/NAnonym/MetaData/UseDefaultMetaDataApiIfNecessary.h>
#endif

#ifndef URASANDESU_NANONYM_METADATA_HEAPPROVIDER_H
#include <Urasandesu/NAnonym/MetaData/HeapProvider.h>
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {


    template<
        class DispenserMetaDataApiType = boost::use_default,
        class AssemblyMetaDataApiType = boost::use_default
    >
    class Runtime
    {
    public:
        typedef typename UseDefaultDispenserMetaDataApiIfNecessary<DispenserMetaDataApiType>::meta_data_api_type dispenser_meta_data_api_type;
        typedef typename UseDefaultAssemblyMetaDataApiIfNecessary<AssemblyMetaDataApiType>::meta_data_api_type assembly_meta_data_api_type;
    
    private:
        BEGIN_META_DATA_HEAP_PROVIDER()
            DECLARE_META_DATA_HEAP_PROVIDER(dispenser_meta_data_api_type, m_dispApiFactory)
            DECLARE_META_DATA_HEAP_PROVIDER(assembly_meta_data_api_type, m_asmApiFactory)
            DECLARE_META_DATA_HEAP_PROVIDER1(AssemblyMetaDataApiType, Assembly, m_asmFactory)
        END_META_DATA_HEAP_PROVIDER()

    public:
        Runtime() : m_pDispApi(NULL) { }

        Assembly<AssemblyMetaDataApiType> *OpenAssembly(LPCWSTR scope, DWORD openFlags)
        {
            HRESULT hr = E_FAIL;

            assembly_meta_data_api_type *pAsmApi = NULL;
            hr = GetHeap<assembly_meta_data_api_type>()->New(&pAsmApi);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));

            hr = GetDispApi()->Dispenser->OpenScope(scope, openFlags, 
                                                    assembly_meta_data_api_type::IID_IImport, 
                                                    reinterpret_cast<IUnknown**>(&pAsmApi->Import));
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));
            

            Assembly<AssemblyMetaDataApiType> *pAsm = NULL;
            hr = GetHeap<Assembly<AssemblyMetaDataApiType>>()->New(&pAsm);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));
            
            pAsm->Init(pAsm, pAsmApi);
            
            return pAsm;
        }
        
    private:
        dispenser_meta_data_api_type *GetDispApi()
        {
            if (!m_pDispApi)
            {
                HRESULT hr = E_FAIL;

                hr = GetHeap<dispenser_meta_data_api_type>()->New(&m_pDispApi);
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));

                hr = dispenser_meta_data_api_type::CoCreateInstance(
                                            dispenser_meta_data_api_type::CLSID_Dispenser, 
                                            NULL, 
                                            CLSCTX_INPROC_SERVER, 
                                            dispenser_meta_data_api_type::IID_IDispenser, 
                                            reinterpret_cast<void**>(&m_pDispApi->Dispenser));
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));
            }
            
            return m_pDispApi;
        }
        dispenser_meta_data_api_type *m_pDispApi;
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_RUNTIME_H