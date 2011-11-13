#pragma once
#ifndef URASANDESU_CPPANONYM_PROFILING_BASEPROFILINGINFO_H
#define URASANDESU_CPPANONYM_PROFILING_BASEPROFILINGINFO_H

#ifndef URASANDESU_CPPANONYM_TRAITS_REPLACE_H
#include <Urasandesu/CppAnonym/Traits/Replace.h>
#endif

#ifndef URASANDESU_CPPANONYM_HEAPPROVIDER_H
#include <Urasandesu/CppAnonym/HeapProvider.h>
#endif

namespace Urasandesu { namespace CppAnonym { namespace Profiling {

#ifdef UNT
#error This .h reserves the word "UNT" that means "Urasandesu::CppAnonym::Traits".
#endif
#define UNT Urasandesu::CppAnonym::Traits

    struct DefaultInfoProfilingApi;

    template<
        class InfoProfilingApiType
    >
    class BaseProcessProfile;

    template<
        class InfoProfilingApiType = boost::use_default
    >    
    class BaseProfilingInfo
    {
    public:
        typedef typename UNT::Replace<InfoProfilingApiType, boost::use_default, DefaultInfoProfilingApi>::type info_profiling_api_type;
    
    private:
        CPPANONYM_BEGIN_HEAP_PROVIDER_DECLARATION()
            CPPANONYM_HEAP_PROVIDER(info_profiling_api_type, UINT_PTR, m_pInfoProfApiFactory);
            CPPANONYM_HEAP_PROVIDER(BaseProcessProfile<InfoProfilingApiType>, UINT_PTR, m_pProcProfFactory);
        CPPANONYM_END_HEAP_PROVIDER_DECLARATION()

    public:
        BaseProfilingInfo() : 
            m_pInfoProfApi(NULL),
            m_currentProcessId(-1)
        { }
        
        template<class T>
        T *CreatePseudo()
        {
            T *pObj = NewPseudo<T>();
            pObj->Init(pObj, GetInfoProfApi());
            return pObj;
        }
        
        template<class T>
        T *CreateIfNecessary(UINT_PTR id)
        {
            if (Exists<T>(id))
            {
                return Get<T>(id);
            }
            else
            {
                T *pObj = CreatePseudo<T>();
                SetToLast<T>(id);
                return pObj;
            }
        }
        
        void Init(IUnknown *pICorProfilerInfoUnk)
        {
            HRESULT hr = E_FAIL;
            
            hr = pICorProfilerInfoUnk->QueryInterface(info_profiling_api_type::IID_IProfilerInfo, 
                                                      reinterpret_cast<void**>(&GetInfoProfApi()->ProfilerInfo));
            if (FAILED(hr)) 
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        }
        
        void SetEventMask(DWORD events)
        {
            HRESULT hr = E_FAIL;

            hr = GetInfoProfApi()->ProfilerInfo->SetEventMask(events);
            if (FAILED(hr)) 
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        }

        BaseProcessProfile<InfoProfilingApiType> *GetCurrentProcess()
        {
            BaseProcessProfile<InfoProfilingApiType> *pProcProf = NULL;
            pProcProf = CreateIfNecessary<BaseProcessProfile<InfoProfilingApiType>>(CurrentProcessId());
            return pProcProf;
        }

    private:
        info_profiling_api_type *GetInfoProfApi()
        {
            if (!m_pInfoProfApi)
            {
                m_pInfoProfApi = NewPseudo<info_profiling_api_type>();
            }
            return m_pInfoProfApi;
        }

        DWORD CurrentProcessId()
        {
            if (m_currentProcessId == -1)
            {
                m_currentProcessId = ::GetCurrentProcessId();
            }
            return m_currentProcessId;
        }

        info_profiling_api_type *m_pInfoProfApi;
        DWORD m_currentProcessId;
    };

    typedef BaseProfilingInfo<boost::use_default> ProfilingInfo;

#undef UNT

}}}  // namespace Urasandesu { namespace CppAnonym { namespace Profiling {

#endif  // URASANDESU_CPPANONYM_PROFILING_BASEPROFILINGINFO_H