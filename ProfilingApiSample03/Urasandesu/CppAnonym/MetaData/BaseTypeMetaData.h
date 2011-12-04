#pragma once
#ifndef URASANDESU_CPPANONYM_METADATA_BASETYPEMETADATA_H
#define URASANDESU_CPPANONYM_METADATA_BASETYPEMETADATA_H

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
    class BaseModuleMetaData;

    template<
        class AssemblyMetaDataApiType
    >
    class BaseMethodMetaData;

    template<
        class AssemblyMetaDataApiType = boost::use_default
    >
    class BaseTypeMetaData : 
        public IMetaDataApiOperable<
            BaseAssemblyMetaData<AssemblyMetaDataApiType>, 
            typename UNT::Replace<AssemblyMetaDataApiType, boost::use_default, DefaultAssemblyMetaDataApi>::type
        >
    {
    public:
        BaseTypeMetaData() : 
            m_pModMeta(NULL)
        { }
        
        BaseModuleMetaData<AssemblyMetaDataApiType> *GetModule()
        {
            HRESULT hr = E_FAIL;
            
            if (m_pModMeta == NULL)
            {
                mdModule mdm = mdModuleNil;
                hr = GetApi()->Import->GetModuleFromScope(&mdm);
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
                
                m_pModMeta = CreateIfNecessary<BaseModuleMetaData<AssemblyMetaDataApiType>>(mdm);
            }
            return m_pModMeta;
        }

        BaseMethodMetaData<AssemblyMetaDataApiType> *GetMethod(mdMethodDef mdmd)
        {
            HRESULT hr = E_FAIL;
            
            // TODO: Set its properties if the token is valid.
            mdTypeDef mdtd = mdTypeDefNil;      
            WCHAR methodName[MAX_SYM_NAME] = { 0 };
            ULONG methodNameSize = sizeof(methodName);
            DWORD methodAttr = 0;
            PCCOR_SIGNATURE pMethodSig = NULL;
            ULONG methodSigSize = 0;
            ULONG methodRva = 0;
            DWORD methodImplFlg = 0;            
            hr = GetApi()->Import->GetMethodProps(mdmd, &mdtd, methodName, 
                                            methodNameSize, &methodNameSize, &methodAttr, 
                                            &pMethodSig, &methodSigSize, &methodRva, 
                                            &methodImplFlg);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
            
            return CreateIfNecessary<BaseMethodMetaData<AssemblyMetaDataApiType>>(mdmd);
        }
        
    private:
        BaseModuleMetaData<AssemblyMetaDataApiType> *m_pModMeta;
    };

    typedef BaseTypeMetaData<boost::use_default> TypeMetaData;

#undef UNT

}}}   // namespace Urasandesu { namespace CppAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_CPPANONYM_METADATA_BASETYPEMETADATA_H