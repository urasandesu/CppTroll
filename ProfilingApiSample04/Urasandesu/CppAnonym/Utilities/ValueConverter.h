#pragma once
#ifndef URASANDESU_CPPANONYM_UTILITIES_VALUECONVERTER_H
#define URASANDESU_CPPANONYM_UTILITIES_VALUECONVERTER_H

#ifndef URASANDESU_CPPANONYM_TRAITS_REPLACE_H
#include <Urasandesu/CppAnonym/Traits/Replace.h>
#endif

namespace Urasandesu { namespace CppAnonym { namespace MetaData {

    template<
        class AssemblyMetaDataApiType
    >
    class BaseAssemblyMetaData;

    typedef BaseAssemblyMetaData<boost::use_default> AssemblyMetaData;

    struct DefaultAssemblyMetaDataApi;

    template<
        class AssemblyMetaDataApiType
    >
    class BaseMethodMetaData;

    template<
        class AssemblyMetaDataApiType
    >
    class BaseTypeMetaData;

}}}   // namespace Urasandesu { namespace CppAnonym { namespace MetaData {

namespace Urasandesu { namespace CppAnonym { namespace Profiling {

    template<
        class InfoProfilingApiType
    >
    class BaseProcessProfile;

    typedef BaseProcessProfile<boost::use_default> ProcessProfile;

    struct DefaultInfoProfilingApi;
    
    template<
        class InfoProfilingApiType
    >
    class BaseModuleProfile;

    template<
        class InfoProfilingApiType
    >
    class BaseMethodProfile;

    template<
        class InfoProfilingApiType
    >
    class BaseTypeProfile;

}}}  // namespace Urasandesu { namespace CppAnonym { namespace Profiling {

namespace Urasandesu { namespace CppAnonym { namespace Utilities {

#ifdef UNP
#error This .h reserves the word "UNP" that means "Urasandesu::CppAnonym::Profiling".
#endif
#define UNP Urasandesu::CppAnonym::Profiling

#ifdef UNM
#error This .h reserves the word "UNM" that means "Urasandesu::CppAnonym::MetaData".
#endif
#define UNM Urasandesu::CppAnonym::MetaData

#ifdef UNT
#error This .h reserves the word "UNT" that means "Urasandesu::CppAnonym::Traits".
#endif
#define UNT Urasandesu::CppAnonym::Traits

    template<class ToHeapManagerType, class FromHeapManagerType>
    struct ValueConverter;


    template<
        class AssemblyMetaDataApiType,
        class InfoProfilingApiType
    >
    class ValueConverter<
        UNM::BaseAssemblyMetaData<AssemblyMetaDataApiType> *, 
        UNP::BaseProcessProfile<InfoProfilingApiType> *
    >
    {
    public:
        typedef typename UNT::Replace<AssemblyMetaDataApiType, boost::use_default, UNM::DefaultAssemblyMetaDataApi>::type assembly_meta_data_api_type;
        typedef typename UNT::Replace<InfoProfilingApiType, boost::use_default, UNP::DefaultInfoProfilingApi>::type info_profiling_api_type;

        ValueConverter() : 
            m_pAsmMeta(NULL),
            m_pProcProf(NULL),
            m_pModProf(NULL)
        {
        }
        
        void Initialize(UNM::BaseAssemblyMetaData<AssemblyMetaDataApiType> *pAsmMeta, 
                        UNP::BaseProcessProfile<InfoProfilingApiType> *pProcProf, 
                        UNP::BaseModuleProfile<InfoProfilingApiType> *pModProf)
        {
            
            HRESULT hr = E_FAIL;
            
            hr = pProcProf->GetApi()->ProfilerInfo->GetModuleMetaData(
                                                pModProf->GetID(), ofRead, 
                                                assembly_meta_data_api_type::IID_IImport, 
                                                reinterpret_cast<IUnknown **>(&pAsmMeta->GetApi()->Import));
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
            
            m_pAsmMeta = pAsmMeta;
            m_pProcProf = pProcProf;
            m_pModProf = pModProf;
        }

        bool HasInitialized()
        {
            return m_pAsmMeta != NULL && m_pProcProf != NULL && m_pModProf != NULL;
        }

        UNM::BaseMethodMetaData<AssemblyMetaDataApiType> *Convert(UNP::BaseMethodProfile<InfoProfilingApiType> *from)
        {
            using namespace Urasandesu::CppAnonym::MetaData;
            HRESULT hr = E_FAIL;
            
            CComPtr<assembly_meta_data_api_type::IImport> pImport;
            mdToken mdt = mdTokenNil;
            hr = m_pProcProf->GetApi()->ProfilerInfo->GetTokenAndMetaDataFromFunction(from->GetID(), 
                                                assembly_meta_data_api_type::IID_IImport, 
                                                reinterpret_cast<IUnknown **>(&pImport), &mdt);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
            
            BaseMethodMetaData<AssemblyMetaDataApiType> *pMethodMeta = NULL;
            pMethodMeta = m_pAsmMeta->CreateIfNecessary<BaseMethodMetaData<AssemblyMetaDataApiType>>(mdt);
            return pMethodMeta;
        }

        UNP::BaseTypeProfile<InfoProfilingApiType> *ConvertBack(UNM::BaseTypeMetaData<AssemblyMetaDataApiType> *to)
        {
            using namespace Urasandesu::CppAnonym::Profiling;
            HRESULT hr = E_FAIL;
            
            ClassID classId = 0;
            hr = m_pProcProf->GetApi()->ProfilerInfo->GetClassFromToken(m_pModProf->GetID(), to->GetToken(), &classId);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
            
            BaseTypeProfile<InfoProfilingApiType> *pTypeProf = NULL;
            pTypeProf = m_pProcProf->CreateIfNecessary<BaseTypeProfile<InfoProfilingApiType>>(classId);
            return pTypeProf;
        }
        
        UNP::BaseMethodProfile<InfoProfilingApiType> *ConvertBack(UNM::BaseMethodMetaData<AssemblyMetaDataApiType> *to)
        {
            using namespace Urasandesu::CppAnonym::Profiling;
            HRESULT hr = E_FAIL;
            
            FunctionID funcId = 0;
            hr = m_pProcProf->GetApi()->ProfilerInfo->GetFunctionFromToken(m_pModProf->GetID(), to->GetToken(), &funcId);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
            
            BaseMethodProfile<InfoProfilingApiType> *pMethodProf = NULL;
            pMethodProf = m_pProcProf->CreateIfNecessary<BaseMethodProfile<InfoProfilingApiType>>(funcId);
            return pMethodProf;
        }

    private:
        UNM::BaseAssemblyMetaData<AssemblyMetaDataApiType> *m_pAsmMeta;
        UNP::BaseProcessProfile<InfoProfilingApiType> *m_pProcProf;
        UNP::BaseModuleProfile<InfoProfilingApiType> *m_pModProf;
    };

#undef UNT
#undef UNM
#undef UNP

}}}   // namespace Urasandesu { namespace CppAnonym { namespace Utilities {

#endif  // #ifndef URASANDESU_CPPANONYM_UTILITIES_VALUECONVERTER_H