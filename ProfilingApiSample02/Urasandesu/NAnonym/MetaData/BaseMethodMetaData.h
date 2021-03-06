﻿#pragma once
#ifndef URASANDESU_NANONYM_METADATA_BASEMETHODMETADATA_H
#define URASANDESU_NANONYM_METADATA_BASEMETHODMETADATA_H

#ifndef URASANDESU_NANONYM_TRAITS_REPLACE_H
#include <Urasandesu/NAnonym/Traits/Replace.h>
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

    struct DefaultAssemblyMetaDataApi;

    template<
        class AssemblyMetaDataApiType
    >
    class BaseTypeMetaData;

    template<
        class AssemblyMetaDataApiType = boost::use_default
    >
    class BaseMethodMetaData : 
        public IMetaDataApiOperable<
            BaseAssemblyMetaData<AssemblyMetaDataApiType>, 
            typename UNT::Replace<AssemblyMetaDataApiType, boost::use_default, DefaultAssemblyMetaDataApi>::type
        >
    {
    public:
        BaseMethodMetaData() :
            m_pTypeMeta(NULL)
        { }
        
        BaseTypeMetaData<AssemblyMetaDataApiType> *GetDeclaringType()
        {
            HRESULT hr = E_FAIL;
            
            if (m_pTypeMeta == NULL)
            {
                mdTypeDef mdtd = mdTypeDefNil;      
                WCHAR methodName[MAX_SYM_NAME] = { 0 };
                ULONG methodNameSize = sizeof(methodName);
                DWORD methodAttr = 0;
                PCCOR_SIGNATURE pMethodSig = NULL;
                ULONG methodSigSize = 0;
                ULONG methodRva = 0;
                DWORD methodImplFlg = 0;
                hr = GetApi()->Import->GetMethodProps(GetToken(), &mdtd, methodName, 
                                            methodNameSize, &methodNameSize, &methodAttr, 
                                            &pMethodSig, &methodSigSize, &methodRva, 
                                            &methodImplFlg);
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
                
                m_pTypeMeta = CreateIfNecessary<BaseTypeMetaData<AssemblyMetaDataApiType>>(mdtd);
            }
            return m_pTypeMeta;
        }

        //BaseMethodBodyMetaData<AssemblyMetaDataApiType> *GetMethodBody()
        //{
        //    HRESULT hr = E_FAIL;
        //    
        //    CComPtr<ICeeGen> pCeeGen;
        //    hr = GetApi()->Import->QueryInterface(IID_ICeeGen, reinterpret_cast<void **>(&pCeeGen));
        //    if (FAILED(hr))
        //        BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
        //    
        //    BOOST_THROW_EXCEPTION(NAnonymException("Not Implemented!!"));
        //    return NULL;
        //}
        
    private:
        BaseTypeMetaData<AssemblyMetaDataApiType> *m_pTypeMeta;
    };

    typedef BaseMethodMetaData<boost::use_default> MethodMetaData;

#undef UNT

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_BASEMETHODMETADATA_H