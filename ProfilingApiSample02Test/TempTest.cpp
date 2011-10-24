// ProfilingApiSample02Test.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#ifndef URASANDESU_NANONYM_TRAITS_REPLACE_H
#include <Urasandesu/NAnonym/Traits/Replace.h>
#endif

#ifndef URASANDESU_NANONYM_HEAPPROVIDER_H
#include <Urasandesu/NAnonym/HeapProvider.h>
#endif

#ifndef URASANDESU_NANONYM_SIMPLEHEAP_H
#include <Urasandesu/NAnonym/SimpleHeap.h>
#endif

namespace {

    struct DefaultInfoProfilingApi;
    struct DefaultProcessProfilingApi;

    template<
        class Type,
        class DefaultType
    >
    struct ATL_NO_VTABLE UseDefaultIfNecessary
    {
        typedef typename Urasandesu::NAnonym::Traits::Replace<Type, boost::use_default, DefaultType>::type type;
    };

    template<
        class HeapManagerType,
        class ApiType
    >        
    class ATL_NO_VTABLE IUnmanagedApiOperable
    {
    public:
        IUnmanagedApiOperable() :
            m_pHeapManager(NULL),
            m_pApi(NULL)
        { }
        
        void Init(HeapManagerType *pHeapManager, ApiType *pApi)
        {
            m_pHeapManager = pHeapManager;
            m_pApi = pApi;
        }

        template<class T>
        T *New()
        {
            T *pObj = m_pHeapManager->GetHeap<T>()->New();
            pObj->Init(m_pHeapManager, m_pApi);
            return pObj;
        }
    protected:
        HeapManagerType *m_pHeapManager;
        ApiType *m_pApi;
    };
    //class IIdentifiable
    //{
    //};

    template<
        class ProcessProfilingApiType
    >
    class BaseProcessProfile;

    template<
        class ProcessProfilingApiType = boost::use_default
    >
    class BaseAssemblyProfile : 
        public IUnmanagedApiOperable<
            BaseProcessProfile<ProcessProfilingApiType>, 
            typename UseDefaultIfNecessary<ProcessProfilingApiType, DefaultProcessProfilingApi>::type
        >
    {
    };

    typedef BaseAssemblyProfile<boost::use_default> AssemblyProfile;



    template<
        class ProcessProfilingApiType = boost::use_default
    >
    class BaseAppDomainProfile : 
        public IUnmanagedApiOperable<
            BaseProcessProfile<ProcessProfilingApiType>, 
            typename UseDefaultIfNecessary<ProcessProfilingApiType, DefaultProcessProfilingApi>::type
        >
    {
    };

    typedef BaseAppDomainProfile<boost::use_default> AppDomainProfile;




    template<
        class ProcessProfilingApiType = boost::use_default
    >
    class BaseProcessProfile : 
        public IUnmanagedApiOperable<
            BaseProcessProfile<ProcessProfilingApiType>, 
            typename UseDefaultIfNecessary<ProcessProfilingApiType, DefaultProcessProfilingApi>::type
        >
    {
        BEGIN_NANONYM_HEAP_PROVIDER()
            DECLARE_NANONYM_HEAP_PROVIDER(BaseAppDomainProfile<ProcessProfilingApiType>, m_pDomainProfFactory);
            DECLARE_NANONYM_HEAP_PROVIDER(BaseAssemblyProfile<ProcessProfilingApiType>, m_pAsmProfFactory);
        END_NANONYM_HEAP_PROVIDER()
    };

    typedef BaseProcessProfile<boost::use_default> ProcessProfile;



    template<
        class InfoProfilingApiType = boost::use_default,
        class ProcessProfilingApiType = boost::use_default
    >    
    class BaseProfilingInfo
    {
        BEGIN_NANONYM_HEAP_PROVIDER()
            DECLARE_NANONYM_HEAP_PROVIDER(BaseProcessProfile<ProcessProfilingApiType>, m_pProcProfFactory);
        END_NANONYM_HEAP_PROVIDER()

    public:
        typedef typename UseDefaultIfNecessary<InfoProfilingApiType, DefaultInfoProfilingApi>::type info_profiling_api_type;
        typedef typename UseDefaultIfNecessary<ProcessProfilingApiType, DefaultProcessProfilingApi>::type process_profiling_api_type;
    
    public:
        template<class T>
        T *New()
        {
            T *pObj = GetHeap<T>()->New();
            pObj->Init(pObj, GetProcProfInfoApi());
            return pObj;
        }
        
    private:
        process_profiling_api_type *GetProcProfInfoApi()
        {
            return NULL;
        }
    };

    typedef BaseProfilingInfo<boost::use_default, boost::use_default> ProfilingInfo;

    // ProfilingApiSample02Test.exe --gtest_filter=ProfilingApiSample02TestSuite.TempTestTest
    TEST(ProfilingApiSample02TestSuite, TempTestTest)
    {
        using namespace std;
        using namespace boost;
        using namespace Urasandesu::NAnonym;
        
        ProfilingInfo profInfo;
        ProcessProfile *pProcProf = profInfo.New<ProcessProfile>();
        AppDomainProfile *pDomainProf = pProcProf->New<AppDomainProfile>();
        AssemblyProfile *pAsmProf = pDomainProf->New<AssemblyProfile>();
        
        SUCCEED();
    }
}
