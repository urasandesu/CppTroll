// ExeWeaver2.cpp : CExeWeaver2 の実装

#include "stdafx.h"
#include "ExeWeaver2.h"

namespace Urasandesu { namespace NAnonym {

    struct Environment
    {
        static std::string GetEnvironmentVariable(LPCSTR variable)
        {
            char *pVarValue = NULL;
            size_t varValueSize = 0;
            errno_t err = ::_dupenv_s(&pVarValue, &varValueSize, variable);
            if (err)
                BOOST_THROW_EXCEPTION(NAnonymSystemException(err));
            return std::string(pVarValue, varValueSize);
        }
    };

    template<class Key>
    class ATL_NO_VTABLE IHeapContent
    {
    public:
        IHeapContent() : 
            m_key(Key())
        { }
        
        Key GetKey()
        {
            return m_key;
        }
        
        void SetKey(Key key)
        {
            m_key = key;
        }
        
        bool IsPseudo()
        {
            return m_key == Key();
        }
        
    private:        
        Key m_key;
    }; 

    template<
        class HeapManagerType,
        class ApiType
    >        
    class ATL_NO_VTABLE IApiOperable
    {
    public:
        typedef HeapManagerType heap_manager_type;
        typedef ApiType api_type;
         
        IApiOperable() :
            m_pHeapManager(NULL),
            m_pApi(NULL)
        { }
        
        void Init(HeapManagerType *pHeapManager, ApiType *pApi)
        {
            m_pHeapManager = pHeapManager;
            m_pApi = pApi;
        }

        template<class T>
        T *CreatePseudo()
        {
            T *pObj = m_pHeapManager->NewPseudo<T>();
            pObj->Init(m_pHeapManager, m_pApi);
            return pObj;
        }

        HeapManagerType *GetHeapManager()
        {
            return m_pHeapManager;
        }

        ApiType *GetApi()
        {
            return m_pApi;
        }
    private:
        HeapManagerType *m_pHeapManager;
        ApiType *m_pApi;
    };

}}  // namespace Urasandesu { namespace NAnonym {

//namespace Urasandesu { namespace NAnonym { namespace Traits {
//
//    template<
//        class Type,
//        class DefaultType
//    >
//    struct ATL_NO_VTABLE UseDefaultIfNecessary
//    {
//        typedef typename Replace<Type, boost::use_default, DefaultType>::type type;
//    };
//
//}}}   // namespace Urasandesu { namespace NAnonym { namespace Traits {

namespace Urasandesu { namespace NAnonym { namespace Profiling {

#if 0
    // IMetaDataOperable に対応する IProfilable みたいな。
    // ITokenizable に対応する IIdentifiable みたいな。
    struct DefaultInfoProfilingApi;

    template<class InfoProfilingApiType = boost::use_default>
    struct ATL_NO_VTABLE UseDefaultInfoProfilingApiIfNecessary
    {
        typedef typename Urasandesu::NAnonym::Traits::Replace<InfoProfilingApiType, boost::use_default, DefaultInfoProfilingApi>::type type;
    };

    struct DefaultProcessProfilingApi;

    template<class ProcessProfilingApiType = boost::use_default>
    struct ATL_NO_VTABLE UseDefaultProcessProfilingApiIfNecessary
    {
        typedef typename Urasandesu::NAnonym::Traits::Replace<ProcessProfilingApiType, boost::use_default, DefaultProcessProfilingApi>::type type;
    };
    
    class MethodBodyProfile
    {
    };
    
    class MethodProfile
    {
    public:
        void SetMethodBody(MethodBodyProfile *pBodyProf)
        {
            BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymException("Not Implemented!!"));
        }
    };

    class ModuleProfile
    {
    };

    class AssemblyProfile
    {
    public:
        AssemblyProfile() { }
        
        ModuleProfile *GetModule()
        {
            return NULL;
        }
    };
    
    class ProcessProfile
    {
    public:
        template<class T>
        T *New(UINT_PTR id)
        {
            BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymException("Not Implemented!!"));
            return NULL;
        }
    };

    //template<
    //    class InfoProfilingApiType = boost::use_default,
    //    class ProcessProfilingApiType = boost::use_default
    //>
    //class BasicProfilingInfo
    //{
    //    //BEGIN_NANONYM_HEAP_PROVIDER()
    //    //    DECLARE_NANONYM_HEAP_PROVIDER(AssemblyProfile, m_pAsmProfFactory)
    //    //END_NANONYM_HEAP_PROVIDER()

    //public:
    //    typedef typename UseDefaultInfoProfilingApiIfNecessary<InfoProfilingApiType>::type info_profiling_api_type;
    //    typedef typename UseDefaultProcessProfilingApiIfNecessary<ProcessProfilingApiType>::type process_profiling_api_type;

    //    BasicProfilingInfo() { }
    //    
    //    void Init(IUnknown *pICorProfilerInfoUnk)
    //    {
    //        using namespace Urasandesu::NAnonym;
    //        HRESULT hr = E_FAIL;
    //        
    //        hr = pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo2, 
    //                                                  reinterpret_cast<void**>(&m_pInfo));
    //        if (FAILED(hr)) 
    //            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
    //    }
    //    
    //    void SetEventMask(DWORD events)
    //    {
    //        using namespace Urasandesu::NAnonym;
    //        HRESULT hr = E_FAIL;

    //        hr = m_pInfo->SetEventMask(events);
    //        if (FAILED(hr)) 
    //            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
    //    }
    //    
    //    ProcessProfile *GetCurrentProcess()
    //    {
    //        BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymException("Not Implemented!!"));
    //        return NULL;
    //    }
    //    
    //    //// このメソッドは AppDomain にあるべき！
    //    //AssemblyProfile *GetAssembly(AssemblyID assemblyId)
    //    //{
    //    //    if (m_asmIndexes.find(assemblyId) != m_asmIndexes.end())
    //    //    {
    //    //        return (*GetHeap<AssemblyProfile>())[m_asmIndexes[assemblyId]];
    //    //    }
    //    //    else
    //    //    {
    //    //        AssemblyProfile *pAsmProf = GetHeap<AssemblyProfile>()->New();
    //    //        m_asmIndexes[assemblyId] = GetHeap<AssemblyProfile>()->Size() - 1;
    //    //        
    //    //        // ここで pAsmProf->Init みたいなのが必要。
    //    //        
    //    //        return pAsmProf;
    //    //    }
    //    //}

    ////private:    
    //    CComPtr<ICorProfilerInfo2> m_pInfo;
    //    boost::unordered_map<AssemblyID, SIZE_T> m_asmIndexes;
    //};

#endif

    struct DefaultInfoProfilingApi
    {
        typedef ICorProfilerInfo2 IProfilerInfo;
        static IID const IID_IProfilerInfo;
        CComPtr<IProfilerInfo> ProfilerInfo;
    };

    IID const DefaultInfoProfilingApi::IID_IProfilerInfo = IID_ICorProfilerInfo2;


    template<
        class HeapManagerType,
        class ApiType
    >        
    class ATL_NO_VTABLE IProfilingApiOperable : 
        public IApiOperable<HeapManagerType, ApiType>, 
        public IHeapContent<UINT_PTR>
    {
    public:
        IProfilingApiOperable() { }

        template<class T>
        T *CreateIfNecessary(UINT_PTR id)
        {
            if (GetHeapManager()->Exists<T>(id))
            {
                return GetHeapManager()->Get<T>(id);
            }
            else
            {
                T *pObj = IApiOperable<HeapManagerType, ApiType>::CreatePseudo<T>();
                GetHeapManager()->SetToLast<T>(id);
                return pObj;
            }
        }
        
        UINT_PTR GetID()
        {
            return GetKey();
        }
        
        void SetID(UINT_PTR id)
        {
            SetKey(id);
        }
    };


#undef UNT
#define UNT Urasandesu::NAnonym::Traits

    template<
        class InfoProfilingApiType
    >
    class BaseProcessProfile;

    template<
        class InfoProfilingApiType = boost::use_default
    >
    class BaseMethodBodyProfile : 
        public IProfilingApiOperable<
            BaseProcessProfile<InfoProfilingApiType>, 
            typename UNT::Replace<InfoProfilingApiType, boost::use_default, DefaultInfoProfilingApi>::type
        >
    {
    };

    typedef BaseMethodBodyProfile<boost::use_default> MethodBodyProfile;




    template<
        class InfoProfilingApiType = boost::use_default
    >
    class BaseMethodProfile : 
        public IProfilingApiOperable<
            BaseProcessProfile<InfoProfilingApiType>, 
            typename UNT::Replace<InfoProfilingApiType, boost::use_default, DefaultInfoProfilingApi>::type
        >
    {
    public:
        void SetMethodBody(BaseMethodBodyProfile<InfoProfilingApiType> *pBodyProf)
        {
            BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymException("Not Implemented!!"));
        }
    };

    typedef BaseMethodProfile<boost::use_default> MethodProfile;




    template<
        class InfoProfilingApiType = boost::use_default
    >
    class BaseModuleProfile : 
        public IProfilingApiOperable<
            BaseProcessProfile<InfoProfilingApiType>, 
            typename UNT::Replace<InfoProfilingApiType, boost::use_default, DefaultInfoProfilingApi>::type
        >
    {
    };

    typedef BaseModuleProfile<boost::use_default> ModuleProfile;




    template<
        class InfoProfilingApiType = boost::use_default
    >
    class BaseAssemblyProfile : 
        public IProfilingApiOperable<
            BaseProcessProfile<InfoProfilingApiType>, 
            typename UNT::Replace<InfoProfilingApiType, boost::use_default, DefaultInfoProfilingApi>::type
        >
    {
    };

    typedef BaseAssemblyProfile<boost::use_default> AssemblyProfile;



    template<
        class InfoProfilingApiType = boost::use_default
    >
    class BaseAppDomainProfile : 
        public IProfilingApiOperable<
            BaseProcessProfile<InfoProfilingApiType>, 
            typename UNT::Replace<InfoProfilingApiType, boost::use_default, DefaultInfoProfilingApi>::type
        >
    {
    };

    typedef BaseAppDomainProfile<boost::use_default> AppDomainProfile;




    template<
        class InfoProfilingApiType = boost::use_default
    >
    class BaseProcessProfile : 
        public IProfilingApiOperable<
            BaseProcessProfile<InfoProfilingApiType>, 
            typename UNT::Replace<InfoProfilingApiType, boost::use_default, DefaultInfoProfilingApi>::type
        >
    {
        BEGIN_NANONYM_HEAP_PROVIDER()
            DECLARE_NANONYM_HEAP_PROVIDER(BaseAppDomainProfile<InfoProfilingApiType>, UINT_PTR, m_pDomainProfFactory);
            DECLARE_NANONYM_HEAP_PROVIDER(BaseAssemblyProfile<InfoProfilingApiType>, UINT_PTR, m_pAsmProfFactory);
            DECLARE_NANONYM_HEAP_PROVIDER(BaseModuleProfile<InfoProfilingApiType>, UINT_PTR, m_pModProfFactory);
            DECLARE_NANONYM_HEAP_PROVIDER(BaseMethodProfile<InfoProfilingApiType>, UINT_PTR, m_pMethodProfFactory);
            DECLARE_NANONYM_HEAP_PROVIDER(BaseMethodBodyProfile<InfoProfilingApiType>, UINT_PTR, m_pMethodBodyProfFactory);
        END_NANONYM_HEAP_PROVIDER()
    };

    typedef BaseProcessProfile<boost::use_default> ProcessProfile;



    template<
        class InfoProfilingApiType = boost::use_default
    >    
    class BaseProfilingInfo
    {
    public:
        typedef typename UNT::Replace<InfoProfilingApiType, boost::use_default, DefaultInfoProfilingApi>::type info_profiling_api_type;
    
    private:
        BEGIN_NANONYM_HEAP_PROVIDER()
            DECLARE_NANONYM_HEAP_PROVIDER(info_profiling_api_type, UINT_PTR, m_pInfoProfApiFactory);
            DECLARE_NANONYM_HEAP_PROVIDER(BaseProcessProfile<InfoProfilingApiType>, UINT_PTR, m_pProcProfFactory);
        END_NANONYM_HEAP_PROVIDER()

    public:
        BaseProfilingInfo() : 
            m_pInfoProfApi(NULL)
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
                T *pObj = New<T>(id);
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
                BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
        }
        
        void SetEventMask(DWORD events)
        {
            HRESULT hr = E_FAIL;

            hr = GetInfoProfApi()->ProfilerInfo->SetEventMask(events);
            if (FAILED(hr)) 
                BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
        }

        BaseProcessProfile<InfoProfilingApiType> *GetCurrentProcess()
        {
            BaseProcessProfile<InfoProfilingApiType> *pProcProf = NULL;
            pProcProf = CreateIfNecessary<BaseProcessProfile<InfoProfilingApiType>>(::GetCurrentProcessId());
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
        
        info_profiling_api_type *m_pInfoProfApi;
    };

#undef UNT

    
}}}   // namespace Urasandesu { namespace NAnonym { namespace Profiling {

namespace Urasandesu { namespace NAnonym { namespace MetaData2 {
    
    #if 0

    struct DefaultAssemblyMetaDataApi;

    template<class AssemblyMetaDataApiType = boost::use_default>
    struct ATL_NO_VTABLE UseDefaultAssemblyMetaDataApiIfNecessary
    {
        typedef typename Urasandesu::NAnonym::Traits::Replace<AssemblyMetaDataApiType, boost::use_default, DefaultAssemblyMetaDataApi>::type type;
    };

    template<class AssemblyMetaDataApiType>
    class BasicAssemblyMetaData;

    template<class AssemblyMetaDataApiType = boost::use_default>
    class ATL_NO_VTABLE IMetaDataOperable
    {
    public:
        typedef typename UseDefaultAssemblyMetaDataApiIfNecessary<AssemblyMetaDataApiType>::type assembly_meta_data_api_type;
        
        IMetaDataOperable() : m_pAsm(NULL), m_pApi(NULL) { }

        void Init(BasicAssemblyMetaData<AssemblyMetaDataApiType> *pAsm, assembly_meta_data_api_type *pApi)
        {
            m_pAsm = pAsm;
            m_pApi = pApi;
        }
    
    protected:
        BasicAssemblyMetaData<AssemblyMetaDataApiType> *m_pAsm;
        assembly_meta_data_api_type *m_pApi;
    };
    
    
    class ATL_NO_VTABLE ITokenizable
    {
    private:
        mdToken m_token;

    public:
        ITokenizable() : m_token(mdTokenNil) { }
                
        mdToken GetToken()
        {
            return m_token;
        }
        
        void SetToken(mdToken token)
        {
            m_token = token;
        }
    };
    
    class MethodBodyMetaData
    {
    };
    
    class TypeMetaData;

    class MethodMetaData
    {
    public:
        mdToken GetToken()
        {
            BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymException("Not Implemented!!"));
            return mdTokenNil;
        }
        
        TypeMetaData *GetDeclaringType()
        {
            BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymException("Not Implemented!!"));
            return NULL;
        }
        
        MethodBodyMetaData *GetMethodBody()
        {
            BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymException("Not Implemented!!"));
            return NULL;
        }
    };
    
    class ModuleMetaData;
    
    class TypeMetaData
    {
    public:
        mdToken GetToken()
        {
            BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymException("Not Implemented!!"));
            return mdTokenNil;
        }
        
        ModuleMetaData *GetModule()
        {
            BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymException("Not Implemented!!"));
            return NULL;
        }
        
        MethodMetaData *GetMethod(mdMethodDef mdmd)
        {
            BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymException("Not Implemented!!"));
            return NULL;
        }
    };
    
    template<class AssemblyMetaDataApiType>
    class BasicAssemblyMetaData;
    typedef BasicAssemblyMetaData<boost::use_default> AssemblyMetaData;

    class ModuleMetaData
    {
    public:
        AssemblyMetaData *GetAssembly()
        {
            BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymException("Not Implemented!!"));
            return NULL;
        }
        
        TypeMetaData *GetType(mdTypeDef mdtd)
        {
            BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymException("Not Implemented!!"));
            return NULL;
        }
    };

    template<class AssemblyMetaDataApiType = boost::use_default>
    class BasicAssemblyMetaData : public IMetaDataOperable<AssemblyMetaDataApiType>, public ITokenizable
    {
    };
    
    #endif

#undef UNT
#define UNT Urasandesu::NAnonym::Traits

    struct DefaultInfoMetaDataApi
    {
        typedef IMetaDataDispenserEx IDispenser;
        static IID const CLSID_Dispenser;
        static IID const IID_IDispenser;
        CComPtr<IDispenser> Dispenser;
        
        inline static HRESULT CoCreateInstance(REFCLSID rclsid, 
                                             LPUNKNOWN pUnkOuter,
                                             DWORD dwClsContext, 
                                             REFIID riid, 
                                             LPVOID FAR* ppv)
        {
            return ::CoCreateInstance(rclsid, pUnkOuter, dwClsContext, riid, ppv);
        }
    };
    IID const DefaultInfoMetaDataApi::CLSID_Dispenser = CLSID_CorMetaDataDispenser;
    IID const DefaultInfoMetaDataApi::IID_IDispenser = IID_IMetaDataDispenserEx;

    struct DefaultAssemblyMetaDataApi
    {        
        typedef IMetaDataImport2 IImport;
        static IID const IID_IImport;
        CComPtr<IImport> Import;
        typedef IMetaDataAssemblyImport IAssemblyImport;
        static IID const IID_IAssemblyImport;
        CComPtr<IAssemblyImport> AssemblyImport;
    };
    IID const DefaultAssemblyMetaDataApi::IID_IImport = IID_IMetaDataImport2;
    IID const DefaultAssemblyMetaDataApi::IID_IAssemblyImport = IID_IMetaDataAssemblyImport;


    template<
        class HeapManagerType,
        class ApiType
    >        
    class ATL_NO_VTABLE IMetaDataApiOperable : 
        public IApiOperable<HeapManagerType, ApiType>, 
        public IHeapContent<mdToken>
    {
    public:
        IMetaDataApiOperable() { }

        template<class T>
        T *CreateIfNecessary(mdToken token)
        {
            if (GetHeapManager()->Exists<T>(token))
            {
                return GetHeapManager()->Get<T>(token);
            }
            else
            {
                T *pObj = IApiOperable<HeapManagerType, ApiType>::CreatePseudo<T>();
                GetHeapManager()->SetToLast<T>(token);
                return pObj;
            }
        }
        
        mdToken GetToken()
        {
            return GetKey();
        }
        
        void SetToken(mdToken token)
        {
            SetKey(token);
        }
    };


    template<
        class AssemblyMetaDataApiType
    >
    class BaseAssemblyMetaData;

    template<
        class AssemblyMetaDataApiType = boost::use_default
    >
    class BaseMethodBodyMetaData : 
        public IMetaDataApiOperable<
            BaseAssemblyMetaData<AssemblyMetaDataApiType>, 
            typename UNT::Replace<AssemblyMetaDataApiType, boost::use_default, DefaultAssemblyMetaDataApi>::type
        >
    {
    };

    typedef BaseMethodBodyMetaData<boost::use_default> MethodBodyMetaData;




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
                WCHAR methodName[MAX_SYM_NAME];
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

        BaseMethodBodyMetaData<AssemblyMetaDataApiType> *GetMethodBody()
        {
            BOOST_THROW_EXCEPTION(NAnonymException("Not Implemented!!"));
            return NULL;
        }
        
    private:
        BaseTypeMetaData<AssemblyMetaDataApiType> *m_pTypeMeta;
    };

    typedef BaseMethodMetaData<boost::use_default> MethodMetaData;




    template<
        class AssemblyMetaDataApiType
    >
    class BaseModuleMetaData;

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
                    BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
                
                m_pModMeta = CreateIfNecessary<BaseModuleMetaData<AssemblyMetaDataApiType>>(mdm);
    //STDMETHOD(GetModuleFromScope)(          // S_OK.
    //    mdModule    *pmd) PURE;             // [OUT] Put mdModule token here.
            }
            return m_pModMeta;
        }

        BaseMethodMetaData<AssemblyMetaDataApiType> *GetMethod(mdMethodDef mdmd)
        {
            BOOST_THROW_EXCEPTION(NAnonymException("Not Implemented!!"));
            return NULL;
    //STDMETHOD (GetMethodProps)( 
    //    mdMethodDef mb,                     // The method for which to get props.   
    //    mdTypeDef   *pClass,                // Put method's class here. 
    //  __out_ecount_part_opt(cchMethod, *pchMethod)
    //    LPWSTR      szMethod,               // Put method's name here.  
    //    ULONG       cchMethod,              // Size of szMethod buffer in wide chars.   
    //    ULONG       *pchMethod,             // Put actual size here 
    //    DWORD       *pdwAttr,               // Put flags here.  
    //    PCCOR_SIGNATURE *ppvSigBlob,        // [OUT] point to the blob value of meta data   
    //    ULONG       *pcbSigBlob,            // [OUT] actual size of signature blob  
    //    ULONG       *pulCodeRVA,            // [OUT] codeRVA    
    //    DWORD       *pdwImplFlags) PURE;    // [OUT] Impl. Flags    
        }
        
    private:
        BaseModuleMetaData<AssemblyMetaDataApiType> *m_pModMeta;
    };

    typedef BaseTypeMetaData<boost::use_default> TypeMetaData;




    template<
        class AssemblyMetaDataApiType
    >
    class BaseAssemblyMetaData;

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
                        BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
                }
                
                mdAssembly mda = mdAssemblyNil;
                hr = GetApi()->AssemblyImport->GetAssemblyFromScope(&mda);
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
                
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




    template<
        class AssemblyMetaDataApiType = boost::use_default
    >
    class BaseAssemblyMetaData : 
        public IMetaDataApiOperable<
            BaseAssemblyMetaData<AssemblyMetaDataApiType>, 
            typename UNT::Replace<AssemblyMetaDataApiType, boost::use_default, DefaultAssemblyMetaDataApi>::type
        >
    {
        BEGIN_NANONYM_HEAP_PROVIDER()
            DECLARE_NANONYM_HEAP_PROVIDER(BaseModuleMetaData<AssemblyMetaDataApiType>, mdToken, m_pModMetaFactory);
            DECLARE_NANONYM_HEAP_PROVIDER(BaseTypeMetaData<AssemblyMetaDataApiType>, mdToken, m_pTypeMetaFactory);
            DECLARE_NANONYM_HEAP_PROVIDER(BaseMethodMetaData<AssemblyMetaDataApiType>, mdToken, m_pMethodMetaFactory);
        END_NANONYM_HEAP_PROVIDER()
    };




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
        
        //template<class T>
        //T *New()
        //{
        //    T *pObj = GetHeap<T>()->New();
        //    pObj->Init(pObj, GetInfoMetaApi());
        //    return pObj;
        //}

        template<class T>
        T *Create()
        {
            T *pObj = New<T>();
            pObj->Init(pObj, NewPseudo<assembly_meta_data_api_type>());
            return pObj;
        }

    private:
        info_meta_data_api_type *GetInfoMetaApi()
        {
            BOOST_THROW_EXCEPTION(NAnonymException("Not Implemented!!"));
            //if (!m_pDispApi)
            //{
            //    HRESULT hr = E_FAIL;

            //    m_pDispApi = GetHeap<dispenser_meta_data_api_type>()->New();
            //    hr = dispenser_meta_data_api_type::CoCreateInstance(
            //                                dispenser_meta_data_api_type::CLSID_Dispenser, 
            //                                NULL, 
            //                                CLSCTX_INPROC_SERVER, 
            //                                dispenser_meta_data_api_type::IID_IDispenser, 
            //                                reinterpret_cast<void**>(&m_pDispApi->Dispenser));
            //    if (FAILED(hr))
            //        BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));
            //}
            
            return m_pInfoMetaApi;
        }
        info_meta_data_api_type *m_pInfoMetaApi;
    };
    
#undef UNT

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData2 {

namespace Urasandesu { namespace NAnonym { namespace Utilities {

    template<class ToHeapManagerType, class FromHeapManagerType>
    struct ValueConverter;

#undef UNM
#define UNM Urasandesu::NAnonym::MetaData2
#undef UNP
#define UNP Urasandesu::NAnonym::Profiling
#undef UNT
#define UNT Urasandesu::NAnonym::Traits

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
            m_pProcProf(NULL)
        {
        }
        
        void Init(UNM::BaseAssemblyMetaData<AssemblyMetaDataApiType> *pAsmMeta, UNP::BaseProcessProfile<InfoProfilingApiType> *pProcProf)
        {
            m_pAsmMeta = pAsmMeta;
            m_pProcProf = pProcProf;
        }
        
        bool Initialized()
        {
            return m_pAsmMeta != NULL && m_pProcProf != NULL;
        }

        //UNM::BaseModuleMetaData<AssemblyMetaDataApiType> *Convert(UNP::BaseModuleProfile<InfoProfilingApiType> *from)
        //{
        //    BOOST_THROW_EXCEPTION(NAnonymException("Not Implemented!!"));
        //    return NULL;
        //}
        //
        //UNM::BaseAssemblyMetaData<AssemblyMetaDataApiType> *Convert(UNP::BaseAssemblyProfile<InfoProfilingApiType> *from)
        //{
        //    BOOST_THROW_EXCEPTION(NAnonymException("Not Implemented!!"));
        //    return NULL;
        //}
        
        UNM::BaseMethodMetaData<AssemblyMetaDataApiType> *Convert(UNP::BaseMethodProfile<InfoProfilingApiType> *from)
        {
            HRESULT hr = E_FAIL;
            
            CComPtr<assembly_meta_data_api_type::IImport> pImport;
            IUnknown **ppImport = GetInitializingImport(pImport);
            mdToken mdt = mdTokenNil;
            hr = from->GetApi()->ProfilerInfo->GetTokenAndMetaDataFromFunction(from->GetID(), 
                                        assembly_meta_data_api_type::IID_IImport, ppImport, &mdt);
            
            UNM::BaseMethodMetaData<AssemblyMetaDataApiType> *pMethodMeta = NULL;
            pMethodMeta = m_pAsmMeta->New<UNM::BaseMethodMetaData<AssemblyMetaDataApiType>>(mdt);
            return pMethodMeta;
        }
        
        UNP::BaseMethodBodyProfile<InfoProfilingApiType> *ConvertBack(UNM::BaseMethodBodyMetaData<AssemblyMetaDataApiType> *to)
        {
            BOOST_THROW_EXCEPTION(NAnonymException("Not Implemented!!"));
            return NULL;
        }
    private:
        IUnknown **GetInitializingImport(CComPtr<typename assembly_meta_data_api_type::IImport> &pImport)
        {
            if (m_pAsmMeta->GetApi()->Import.p == NULL)
                return reinterpret_cast<IUnknown **>(&m_pAsmMeta->GetApi()->Import);
            else
                return reinterpret_cast<IUnknown **>(&pImport);
        }
    
        UNM::BaseAssemblyMetaData<AssemblyMetaDataApiType> *m_pAsmMeta;
        UNP::BaseProcessProfile<InfoProfilingApiType> *m_pProcProf;
    };

#undef UNT
#undef UNM
#undef UNP

}}}   // namespace Urasandesu { namespace NAnonym { namespace Utilities {


// CExeWeaver2
HRESULT CExeWeaver2::FinalConstruct()
{
    using namespace boost;
    using namespace Urasandesu::NAnonym::MetaData2;
    using namespace Urasandesu::NAnonym::Profiling;
    using namespace Urasandesu::NAnonym::Utilities;
    
    m_pProfInfo = make_shared<ProfilingInfo>();
    m_pMetaInfo = make_shared<MetaDataInfo>();
    m_pConv = make_shared<ValueConverter<AssemblyMetaData *, ProcessProfile *>>();
    m_mdaTargetAssembly = mdAssemblyNil;
    m_mdtdReplaceTypeFrom = mdTypeDefNil;
    m_mdmdReplaceMethodFrom = mdMethodDefNil;
    m_mdtdReplaceTypeTo = mdTypeDefNil;
    m_mdtdReplaceMethodTo = mdMethodDefNil;

	return S_OK;
}

void CExeWeaver2::FinalRelease()
{
}

HRESULT CExeWeaver2::COMError(HRESULT hr, LPCSTR filePath, INT line)
{
    using std::wostringstream;

    wostringstream msg;
    msg << _com_error(hr).ErrorMessage();
    msg << ", File: " << filePath;
    msg << ", Line: " << line;
    return Error(msg.str().c_str());
}

STDMETHODIMP CExeWeaver2::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IExeWeaver2
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}



// ICorProfilerCallback
HRESULT CExeWeaver2::Initialize( 
    /* [in] */ IUnknown *pICorProfilerInfoUnk)
{
    using namespace std;
    using namespace boost;
    using namespace Urasandesu::NAnonym;
    using namespace Urasandesu::NAnonym::MetaData2;
    
    try
    {
        //::_CrtDbgBreak();
        //::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

        // Initialize the unmanaged profiling API.
        m_pProfInfo->Init(pICorProfilerInfoUnk);
        m_pProfInfo->SetEventMask(COR_PRF_MONITOR_ASSEMBLY_LOADS | 
                                  COR_PRF_MONITOR_MODULE_LOADS | 
                                  COR_PRF_MONITOR_APPDOMAIN_LOADS | 
                                  COR_PRF_MONITOR_CLASS_LOADS | 
                                  COR_PRF_MONITOR_JIT_COMPILATION);


        // Get token of the target assembly.
        {
            istringstream is(Environment::GetEnvironmentVariable("NANONYM_TARGET_ASSEMBLY"));
            is >> hex >> m_mdaTargetAssembly;
            cout << format("Target Assembly Token: 0x%|1$08X|") % m_mdaTargetAssembly << endl;
        }
        
        // Get token of the replaced type.
        {
            istringstream is(Environment::GetEnvironmentVariable("NANONYM_REPLACE_TYPE_FROM"));
            is >> hex >> m_mdtdReplaceTypeFrom;
            cout << format("Replaced Type Token: 0x%|1$08X|") % m_mdtdReplaceTypeFrom << endl;
        }
        
        // Get token of the replaced method.
        {
            istringstream is(Environment::GetEnvironmentVariable("NANONYM_REPLACE_METHOD_FROM"));
            is >> hex >> m_mdmdReplaceMethodFrom;
            cout << format("Replaced Method Token: 0x%|1$08X|") % m_mdmdReplaceMethodFrom << endl;
        }
        
        // Get token of the replacing type.
        {
            istringstream is(Environment::GetEnvironmentVariable("NANONYM_REPLACE_TYPE_TO"));
            is >> hex >> m_mdtdReplaceTypeTo;
            cout << format("Replacing Type Token: 0x%|1$08X|") % m_mdtdReplaceTypeTo << endl;
        }
        
        // Get token of the replacing method.
        {
            istringstream is(Environment::GetEnvironmentVariable("NANONYM_REPLACE_METHOD_TO"));
            is >> hex >> m_mdtdReplaceMethodTo;
            cout << format("Replacing Method Token: 0x%|1$08X|") % m_mdtdReplaceMethodTo << endl;
        }
        
        m_pProcProf = m_pProfInfo->GetCurrentProcess();
        //m_pProcProf->GetPseudoDomain();
    }
    catch (NAnonymException &e)
    {
        cout << diagnostic_information(e) << endl;
    }
    catch (...)
    {
        cout << diagnostic_information(current_exception()) << endl;
    }

    return S_OK;
}

HRESULT CExeWeaver2::Shutdown( void)
{ 
    return S_OK; 
}

HRESULT CExeWeaver2::AppDomainCreationStarted( 
    /* [in] */ AppDomainID appDomainId)
{ 
    using namespace std;
    using namespace boost;
    using namespace Urasandesu::NAnonym;
    using namespace Urasandesu::NAnonym::MetaData2;
    
    try
    {
        cout << "AppDomainCreationStarted !!" << endl;
        //m_pProcProf->CreateIfNecessary<AppDomainProfile>(appDomainId);
    }
    catch (NAnonymException &e)
    {
        cout << diagnostic_information(e) << endl;
    }
    catch (...)
    {
        cout << diagnostic_information(current_exception()) << endl;
    }

    return S_OK; 
}

HRESULT CExeWeaver2::AppDomainCreationFinished( 
    /* [in] */ AppDomainID appDomainId,
    /* [in] */ HRESULT hrStatus)
{ 
    return S_OK;
}

HRESULT CExeWeaver2::AppDomainShutdownStarted( 
    /* [in] */ AppDomainID appDomainId)
{
    return S_OK;
}

HRESULT CExeWeaver2::AppDomainShutdownFinished( 
    /* [in] */ AppDomainID appDomainId,
    /* [in] */ HRESULT hrStatus)
{
    return S_OK;
}

HRESULT CExeWeaver2::AssemblyLoadStarted( 
    /* [in] */ AssemblyID assemblyId)
{
    using namespace std;
    using namespace boost;
    using namespace Urasandesu::NAnonym;
    using namespace Urasandesu::NAnonym::MetaData2;
    
    try
    {
        //AppDomainProfile *pDomainProf = m_pProcProf->GetCurrentDomain();
        //AssemblyProfile *pAsmProf = pDomainProf->CreateIfNecessary<AssemblyProfile>(assemblyId);
        //if (pAsmProf->GetName() != m_targetAssemblyName)
        //    return S_OK;
        //
        //m_pAsmProf = pAsmProf;
        //m_pModConv->
        //m_pAsmMeta = m_pMetaInfo->Create<AssemblyMetaData>();
        //m_pConv->Init(m_pAsmMeta, m_pProcProf);
        //
        //HRESULT hr = E_FAIL;
        //
        //WCHAR asmName[MAX_SYM_NAME];
        //ULONG asmNameSize = sizeof(asmName);
        //AppDomainID domainId = 0;
        //ModuleID modId = 0;
        //hr = m_pProcProf->GetApi()->ProfilerInfo->GetAssemblyInfo(assemblyId, asmNameSize, &asmNameSize, asmName, &domainId, &modId);
        //if (hr != CORPROF_E_DATAINCOMPLETE && FAILED(hr))
        //    BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
        //
        //wcout << L"AssemblyLoadStarted: " << asmName << endl;
        ////virtual HRESULT STDMETHODCALLTYPE GetAssemblyInfo( 
        //                    //    /* [in] */ AssemblyID assemblyId,
        //                    //    /* [in] */ ULONG cchName,
        //                    //    /* [out] */ ULONG *pcchName,
        //                    //    /* [length_is][size_is][out] */ WCHAR szName[  ],
        //                    //    /* [out] */ AppDomainID *pAppDomainId,
        ////    /* [out] */ ModuleID *pModuleId) = 0;
    }
    catch (NAnonymException &e)
    {
        cout << diagnostic_information(e) << endl;
    }
    catch (...)
    {
        cout << diagnostic_information(current_exception()) << endl;
    }

    return S_OK;
}

HRESULT CExeWeaver2::AssemblyLoadFinished( 
    /* [in] */ AssemblyID assemblyId,
    /* [in] */ HRESULT hrStatus)
{
    return S_OK;
}

HRESULT CExeWeaver2::AssemblyUnloadStarted( 
    /* [in] */ AssemblyID assemblyId)
{
    return S_OK;
}

HRESULT CExeWeaver2::AssemblyUnloadFinished( 
    /* [in] */ AssemblyID assemblyId,
    /* [in] */ HRESULT hrStatus)
{
    return S_OK;
}

HRESULT CExeWeaver2::ModuleLoadStarted( 
    /* [in] */ ModuleID moduleId)
{
    using namespace std;
    using namespace boost;
    using namespace Urasandesu::NAnonym;
    using namespace Urasandesu::NAnonym::MetaData2;
    
    try
    {
        cout << "ModuleLoadStarted !!" << endl;
        //if (m_pAsmProf == NULL)
        //    return S_OK;
        
        //ModuleProfile *pModProf = m_pAsmProf->CreateIfNecessary<ModuleProfile>(moduleId);
        //m_pAsmMeta = m_pMetaInfo->Create<AssemblyMetaData>();
        //m_pConv->Init(m_pAsmMeta, m_pProcProf);
        //virtual HRESULT STDMETHODCALLTYPE GetModuleMetaData( 
        //    /* [in] */ ModuleID moduleId,
        //    /* [in] */ DWORD dwOpenFlags,
        //    /* [in] */ REFIID riid,
        //    /* [out] */ IUnknown **ppOut) = 0;
    }
    catch (NAnonymException &e)
    {
        cout << diagnostic_information(e) << endl;
    }
    catch (...)
    {
        cout << diagnostic_information(current_exception()) << endl;
    }

    return S_OK;
}

HRESULT CExeWeaver2::ModuleLoadFinished( 
    /* [in] */ ModuleID moduleId,
    /* [in] */ HRESULT hrStatus)
{
    return S_OK;
}

HRESULT CExeWeaver2::ModuleUnloadStarted( 
    /* [in] */ ModuleID moduleId)
{
    return S_OK;
}

HRESULT CExeWeaver2::ModuleUnloadFinished( 
    /* [in] */ ModuleID moduleId,
    /* [in] */ HRESULT hrStatus)
{
    return S_OK;
}

HRESULT CExeWeaver2::ModuleAttachedToAssembly( 
    /* [in] */ ModuleID moduleId,
    /* [in] */ AssemblyID AssemblyId)
{
    return S_OK;
}

HRESULT CExeWeaver2::ClassLoadStarted( 
    /* [in] */ ClassID classId)
{
    using namespace std;
    using namespace boost;
    using namespace Urasandesu::NAnonym;
    using namespace Urasandesu::NAnonym::MetaData2;
    
    try
    {
        cout << "ClassLoadStarted !!" << endl;
    }
    catch (NAnonymException &e)
    {
        cout << diagnostic_information(e) << endl;
    }
    catch (...)
    {
        cout << diagnostic_information(current_exception()) << endl;
    }

    return S_OK;
}

HRESULT CExeWeaver2::ClassLoadFinished( 
    /* [in] */ ClassID classId,
    /* [in] */ HRESULT hrStatus)
{
    return S_OK; 
}

HRESULT CExeWeaver2::ClassUnloadStarted( 
    /* [in] */ ClassID classId)
{
    return S_OK;
}

HRESULT CExeWeaver2::ClassUnloadFinished( 
    /* [in] */ ClassID classId,
    /* [in] */ HRESULT hrStatus)
{
    return S_OK;
}

HRESULT CExeWeaver2::FunctionUnloadStarted( 
    /* [in] */ FunctionID functionId)
{
    return S_OK;
}

HRESULT CExeWeaver2::JITCompilationStarted( 
    /* [in] */ FunctionID functionId,
    /* [in] */ BOOL fIsSafeToBlock)
{
    using namespace std;
    using namespace boost;
    using namespace Urasandesu::NAnonym;
    using namespace Urasandesu::NAnonym::MetaData2;
    using namespace Urasandesu::NAnonym::Profiling;
    
    try
    {
        if (!m_pConv->Initialized())
            return S_OK;

        MethodProfile *pMethodProfFrom = m_pProcProf->CreateIfNecessary<MethodProfile>(functionId);
        MethodMetaData *pMethodMetaFrom = m_pConv->Convert(pMethodProfFrom);
        cout << format("Current Method Token: 0x%|1$08X|") % pMethodMetaFrom->GetToken() << endl;
        if (pMethodMetaFrom->GetToken() != m_mdmdReplaceMethodFrom)
            return S_OK;


        TypeMetaData *pTypeMetaFrom = pMethodMetaFrom->GetDeclaringType();
        cout << format("Current Type Token: 0x%|1$08X|") % pTypeMetaFrom->GetToken() << endl;
        if (pTypeMetaFrom->GetToken() != m_mdtdReplaceTypeFrom)
            return S_OK;


        ModuleMetaData *pModMetaFrom = pTypeMetaFrom->GetModule();
        cout << format("Current Module Token: 0x%|1$08X|") % pModMetaFrom->GetToken() << endl;
        AssemblyMetaData *pTargetAsmMeta = pModMetaFrom->GetAssembly();
        cout << format("Current Assembly Token: 0x%|1$08X|") % pTargetAsmMeta->GetToken() << endl;
        if (pTargetAsmMeta->GetToken() != m_mdaTargetAssembly)
            return S_OK;


        TypeMetaData *pTypeMetaTo = pModMetaFrom->GetType(m_mdtdReplaceTypeTo);
        MethodMetaData *pMethodMetaTo = pTypeMetaTo->GetMethod(m_mdtdReplaceMethodTo);
        MethodBodyMetaData *pBodyMetaTo = pMethodMetaTo->GetMethodBody();
        MethodBodyProfile *pBodyProfTo = m_pConv->ConvertBack(pBodyMetaTo);
        pMethodProfFrom->SetMethodBody(pBodyProfTo);
    }
    catch (NAnonymException &e)
    {
        cout << diagnostic_information(e) << endl;
    }
    catch (...)
    {
        cout << diagnostic_information(current_exception()) << endl;
    }

    return S_OK;
}

HRESULT CExeWeaver2::JITCompilationFinished( 
    /* [in] */ FunctionID functionId,
    /* [in] */ HRESULT hrStatus,
    /* [in] */ BOOL fIsSafeToBlock)
{
    return S_OK;
}

HRESULT CExeWeaver2::JITCachedFunctionSearchStarted( 
    /* [in] */ FunctionID functionId,
    /* [out] */ BOOL *pbUseCachedFunction)
{
    return S_OK;
}

HRESULT CExeWeaver2::JITCachedFunctionSearchFinished( 
    /* [in] */ FunctionID functionId,
    /* [in] */ COR_PRF_JIT_CACHE result)
{
    return S_OK;
}

HRESULT CExeWeaver2::JITFunctionPitched( 
    /* [in] */ FunctionID functionId)
{
    return S_OK;
}

HRESULT CExeWeaver2::JITInlining( 
    /* [in] */ FunctionID callerId,
    /* [in] */ FunctionID calleeId,
    /* [out] */ BOOL *pfShouldInline)
{
    return S_OK;
}

HRESULT CExeWeaver2::ThreadCreated( 
    /* [in] */ ThreadID threadId)
{
    return S_OK;
}

HRESULT CExeWeaver2::ThreadDestroyed( 
    /* [in] */ ThreadID threadId)
{
    return S_OK;
}

HRESULT CExeWeaver2::ThreadAssignedToOSThread( 
    /* [in] */ ThreadID managedThreadId,
    /* [in] */ DWORD osThreadId)
{
    return S_OK;
}

HRESULT CExeWeaver2::RemotingClientInvocationStarted( void)
{
    return S_OK;
}

HRESULT CExeWeaver2::RemotingClientSendingMessage( 
    /* [in] */ GUID *pCookie,
    /* [in] */ BOOL fIsAsync)
{
    return S_OK;
}

HRESULT CExeWeaver2::RemotingClientReceivingReply( 
    /* [in] */ GUID *pCookie,
    /* [in] */ BOOL fIsAsync)
{
    return S_OK;
}

HRESULT CExeWeaver2::RemotingClientInvocationFinished( void)
{
    return S_OK;
}

HRESULT CExeWeaver2::RemotingServerReceivingMessage( 
    /* [in] */ GUID *pCookie,
    /* [in] */ BOOL fIsAsync)
{
    return S_OK;
}

HRESULT CExeWeaver2::RemotingServerInvocationStarted( void)
{
    return S_OK;
}

HRESULT CExeWeaver2::RemotingServerInvocationReturned( void)
{
    return S_OK;
}

HRESULT CExeWeaver2::RemotingServerSendingReply( 
    /* [in] */ GUID *pCookie,
    /* [in] */ BOOL fIsAsync)
{
    return S_OK;
}

HRESULT CExeWeaver2::UnmanagedToManagedTransition( 
    /* [in] */ FunctionID functionId,
    /* [in] */ COR_PRF_TRANSITION_REASON reason)
{
    return S_OK;
}

HRESULT CExeWeaver2::ManagedToUnmanagedTransition( 
    /* [in] */ FunctionID functionId,
    /* [in] */ COR_PRF_TRANSITION_REASON reason)
{
    return S_OK;
}

HRESULT CExeWeaver2::RuntimeSuspendStarted( 
    /* [in] */ COR_PRF_SUSPEND_REASON suspendReason)
{
    return S_OK;
}

HRESULT CExeWeaver2::RuntimeSuspendFinished( void)
{
    return S_OK;
}

HRESULT CExeWeaver2::RuntimeSuspendAborted( void)
{
    return S_OK;
}

HRESULT CExeWeaver2::RuntimeResumeStarted( void)
{
    return S_OK;
}

HRESULT CExeWeaver2::RuntimeResumeFinished( void)
{
    return S_OK;
}

HRESULT CExeWeaver2::RuntimeThreadSuspended( 
    /* [in] */ ThreadID threadId)
{
    return S_OK;
}

HRESULT CExeWeaver2::RuntimeThreadResumed( 
    /* [in] */ ThreadID threadId)
{
    return S_OK;
}

HRESULT CExeWeaver2::MovedReferences( 
    /* [in] */ ULONG cMovedObjectIDRanges,
    /* [size_is][in] */ ObjectID oldObjectIDRangeStart[  ],
    /* [size_is][in] */ ObjectID newObjectIDRangeStart[  ],
    /* [size_is][in] */ ULONG cObjectIDRangeLength[  ])
{
    return S_OK;
}

HRESULT CExeWeaver2::ObjectAllocated( 
    /* [in] */ ObjectID objectId,
    /* [in] */ ClassID classId)
{
    return S_OK;
}

HRESULT CExeWeaver2::ObjectsAllocatedByClass( 
    /* [in] */ ULONG cClassCount,
    /* [size_is][in] */ ClassID classIds[  ],
    /* [size_is][in] */ ULONG cObjects[  ])
{
    return S_OK;
}

HRESULT CExeWeaver2::ObjectReferences( 
    /* [in] */ ObjectID objectId,
    /* [in] */ ClassID classId,
    /* [in] */ ULONG cObjectRefs,
    /* [size_is][in] */ ObjectID objectRefIds[  ])
{
    return S_OK;
}

HRESULT CExeWeaver2::RootReferences( 
    /* [in] */ ULONG cRootRefs,
    /* [size_is][in] */ ObjectID rootRefIds[  ])
{
    return S_OK;
}

HRESULT CExeWeaver2::ExceptionThrown( 
    /* [in] */ ObjectID thrownObjectId)
{
    return S_OK;
}

HRESULT CExeWeaver2::ExceptionSearchFunctionEnter( 
    /* [in] */ FunctionID functionId)
{
    return S_OK;
}

HRESULT CExeWeaver2::ExceptionSearchFunctionLeave( void)
{
    return S_OK;
}

HRESULT CExeWeaver2::ExceptionSearchFilterEnter( 
    /* [in] */ FunctionID functionId)
{
    return S_OK;
}

HRESULT CExeWeaver2::ExceptionSearchFilterLeave( void)
{
    return S_OK;
}

HRESULT CExeWeaver2::ExceptionSearchCatcherFound( 
    /* [in] */ FunctionID functionId)
{
    return S_OK;
}

HRESULT CExeWeaver2::ExceptionOSHandlerEnter( 
    /* [in] */ UINT_PTR __unused)
{
    return S_OK;
}

HRESULT CExeWeaver2::ExceptionOSHandlerLeave( 
    /* [in] */ UINT_PTR __unused)
{
    return S_OK;
}

HRESULT CExeWeaver2::ExceptionUnwindFunctionEnter( 
    /* [in] */ FunctionID functionId)
{
    return S_OK;
}

HRESULT CExeWeaver2::ExceptionUnwindFunctionLeave( void)
{
    return S_OK;
}

HRESULT CExeWeaver2::ExceptionUnwindFinallyEnter( 
    /* [in] */ FunctionID functionId)
{
    return S_OK;
}

HRESULT CExeWeaver2::ExceptionUnwindFinallyLeave( void)
{
    return S_OK;
}

HRESULT CExeWeaver2::ExceptionCatcherEnter( 
    /* [in] */ FunctionID functionId,
    /* [in] */ ObjectID objectId)
{
    return S_OK;
}

HRESULT CExeWeaver2::ExceptionCatcherLeave( void)
{
    return S_OK;
}

HRESULT CExeWeaver2::COMClassicVTableCreated( 
    /* [in] */ ClassID wrappedClassId,
    /* [in] */ REFGUID implementedIID,
    /* [in] */ void *pVTable,
    /* [in] */ ULONG cSlots)
{
    return S_OK;
}

HRESULT CExeWeaver2::COMClassicVTableDestroyed( 
    /* [in] */ ClassID wrappedClassId,
    /* [in] */ REFGUID implementedIID,
    /* [in] */ void *pVTable)
{
    return S_OK;
}

HRESULT CExeWeaver2::ExceptionCLRCatcherFound( void)
{
    return S_OK;
}

HRESULT CExeWeaver2::ExceptionCLRCatcherExecute( void)
{
    return S_OK;
}

// ICorProfilerCallback2
HRESULT CExeWeaver2::ThreadNameChanged( 
    /* [in] */ ThreadID threadId,
    /* [in] */ ULONG cchName,
    /* [in] */ WCHAR name[  ])
{
    return S_OK;
}

HRESULT CExeWeaver2::GarbageCollectionStarted( 
    /* [in] */ int cGenerations,
    /* [length_is][size_is][in] */ BOOL generationCollected[  ],
    /* [in] */ COR_PRF_GC_REASON reason)
{
    return S_OK;
}

HRESULT CExeWeaver2::SurvivingReferences( 
    /* [in] */ ULONG cSurvivingObjectIDRanges,
    /* [size_is][in] */ ObjectID objectIDRangeStart[  ],
    /* [size_is][in] */ ULONG cObjectIDRangeLength[  ])
{
    return S_OK;
}

HRESULT CExeWeaver2::GarbageCollectionFinished( void)
{
    return S_OK;
}

HRESULT CExeWeaver2::FinalizeableObjectQueued( 
    /* [in] */ DWORD finalizerFlags,
    /* [in] */ ObjectID objectID)
{
    return S_OK;
}

HRESULT CExeWeaver2::RootReferences2( 
    /* [in] */ ULONG cRootRefs,
    /* [size_is][in] */ ObjectID rootRefIds[  ],
    /* [size_is][in] */ COR_PRF_GC_ROOT_KIND rootKinds[  ],
    /* [size_is][in] */ COR_PRF_GC_ROOT_FLAGS rootFlags[  ],
    /* [size_is][in] */ UINT_PTR rootIds[  ])
{
    return S_OK;
}

HRESULT CExeWeaver2::HandleCreated( 
    /* [in] */ GCHandleID handleId,
    /* [in] */ ObjectID initialObjectId)
{
    return S_OK;
}

HRESULT CExeWeaver2::HandleDestroyed( 
    /* [in] */ GCHandleID handleId)
{
    return S_OK;
}
