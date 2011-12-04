#pragma once
#ifndef URASANDESU_CPPANONYM_METADATA_BASEMODULEMETADATA_H
#define URASANDESU_CPPANONYM_METADATA_BASEMODULEMETADATA_H

#ifndef URASANDESU_CPPANONYM_TRAITS_REPLACE_H
#include <Urasandesu/CppAnonym/Traits/Replace.h>
#endif

namespace Urasandesu { namespace CppAnonym { namespace MetaData {

#ifdef UNT
#error This .h reserves the word "UNT" that means "Urasandesu::CppAnonym::Traits".
#endif
#define UNT Urasandesu::CppAnonym::Traits

    template<
        class HeapManagerType,
        class ApiType
    >        
    class ATL_NO_VTABLE IMetaDataApiOperable;

    template<
        class AssemblyMetaDataApiType
    >
    class BaseAssemblyMetaData;

    struct DefaultAssemblyMetaDataApi;

    template<
        class AssemblyMetaDataApiType
    >
    class BaseTypeMetaData;

    template<
        class AssemblyMetaDataApiType = boost::use_default
    >
    class BaseModuleMetaData : 
        public IMetaDataApiOperable<
            BaseAssemblyMetaData<AssemblyMetaDataApiType>, 
            typename UNT::Replace<AssemblyMetaDataApiType, boost::use_default, DefaultAssemblyMetaDataApi>::type
        >
    {
    public:
        BaseAssemblyMetaData<AssemblyMetaDataApiType> *GetAssembly()
        {
            HRESULT hr = E_FAIL;
            
            BaseAssemblyMetaData<AssemblyMetaDataApiType> *pAsmMeta = NULL;
            pAsmMeta = GetHeapManager();
            if (pAsmMeta->GetToken() == -1)
            {
                if (GetApi()->AssemblyImport.p == NULL)
                {
                    hr = GetApi()->Import->QueryInterface(api_type::IID_IAssemblyImport, 
                                    reinterpret_cast<void **>(&GetApi()->AssemblyImport));
                    if (FAILED(hr))
                        BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
                }
                
                mdAssembly mda = mdAssemblyNil;
                hr = GetApi()->AssemblyImport->GetAssemblyFromScope(&mda);
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
                
                pAsmMeta->SetToken(mda);
            }
            return pAsmMeta;
        }
        
        BaseTypeMetaData<AssemblyMetaDataApiType> *GetType(mdTypeDef mdtd)
        {
            BaseTypeMetaData<AssemblyMetaDataApiType> *pTypeMeta = NULL;
            pTypeMeta = CreateIfNecessary<BaseTypeMetaData<AssemblyMetaDataApiType>>(mdtd);
            return pTypeMeta;
        }
        
    private:
        boost::unordered_map<mdToken, SIZE_T> m_typeIndexes;
    };

    typedef BaseModuleMetaData<boost::use_default> ModuleMetaData;

#undef UNT

}}}   // namespace Urasandesu { namespace CppAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_CPPANONYM_METADATA_BASEMODULEMETADATA_H