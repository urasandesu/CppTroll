#pragma once
#ifndef URASANDESU_NANONYM_METADATA_BASEMETADATAINFO_H
#define URASANDESU_NANONYM_METADATA_BASEMETADATAINFO_H

#ifndef URASANDESU_NANONYM_TRAITS_REPLACE_H
#include <Urasandesu/NAnonym/Traits/Replace.h>
#endif

#ifndef URASANDESU_NANONYM_HEAPPROVIDER_H
#include <Urasandesu/NAnonym/HeapProvider.h>
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {

#ifdef UNT
#error This .h reserves the word "UNT" that means "Urasandesu::NAnonym::Traits".
#endif
#define UNT Urasandesu::NAnonym::Traits

    template<
        class HeapManagerType,
        class ApiType
    >        
    class ATL_NO_VTABLE IMetaDataApiOperable;

    template<
        class AssemblyMetaDataApiType
    >
    class BaseAssemblyMetaData;

    struct DefaultInfoMetaDataApi;
    struct DefaultAssemblyMetaDataApi;

    template<
        class InfoMetaDataApiType = boost::use_default,
        class AssemblyMetaDataApiType = boost::use_default
    >    
    class BaseMetaDataInfo
    {
    public:
        typedef typename UNT::Replace<InfoMetaDataApiType, boost::use_default, DefaultInfoMetaDataApi>::type info_meta_data_api_type;
        typedef typename UNT::Replace<AssemblyMetaDataApiType, boost::use_default, DefaultAssemblyMetaDataApi>::type assembly_meta_data_api_type;
    
    private:
        BEGIN_NANONYM_HEAP_PROVIDER()
            DECLARE_NANONYM_HEAP_PROVIDER(info_meta_data_api_type, mdToken, m_pInfoMetaApiFactory);
            DECLARE_NANONYM_HEAP_PROVIDER(assembly_meta_data_api_type, mdToken, m_pAsmMetaApiFactory);
            DECLARE_NANONYM_HEAP_PROVIDER(BaseAssemblyMetaData<AssemblyMetaDataApiType>, mdToken, m_pAsmMetaFactory);
        END_NANONYM_HEAP_PROVIDER()

    public:
        BaseMetaDataInfo() : 
            m_pInfoMetaApi(NULL)
        { }

        template<class T>
        T *CreatePseudo()
        {
            T *pObj = NewPseudo<T>();
            pObj->Init(pObj, NewPseudo<assembly_meta_data_api_type>());
            return pObj;
        }

    private:
        info_meta_data_api_type *GetInfoMetaApi()
        {
            BOOST_THROW_EXCEPTION(NAnonymException("Not Implemented!!"));
            return NULL;
        }
        info_meta_data_api_type *m_pInfoMetaApi;
    };

    typedef BaseMetaDataInfo<boost::use_default, boost::use_default> MetaDataInfo;

#undef UNT

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_BASEMETADATAINFO_H