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

}}  // namespace Urasandesu { namespace NAnonym {

namespace Urasandesu { namespace NAnonym { namespace Profiling {

    // IMetaDataOperable に対応する IProfilable みたいな。
    // ITokenizable に対応する IIdentifiable みたいな。
    struct DefaultInfoProfilingApi;

    template<class InfoProfilingApiType = boost::use_default>
    struct ATL_NO_VTABLE UseDefaultInfoProfilingApiIfNecessary
    {
        typedef typename Urasandesu::NAnonym::Traits::Replace<InfoProfilingApiType, boost::use_default, DefaultInfoProfilingApi>::type type;
    };

    struct DefaultAppDomainProfilingApi;

    template<class AppDomainProfilingApiType = boost::use_default>
    struct ATL_NO_VTABLE UseDefaultAppDomainProfilingApiIfNecessary
    {
        typedef typename Urasandesu::NAnonym::Traits::Replace<AppDomainProfilingApiType, boost::use_default, DefaultAppDomainProfilingApi>::type type;
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

    template<
        class InfoProfilingApiType = boost::use_default,
        class AppDomainProfilingApiType = boost::use_default
    >
    class BasicProfilingInfo
    {
        BEGIN_NANONYM_HEAP_PROVIDER()
            DECLARE_NANONYM_HEAP_PROVIDER(AssemblyProfile, m_pAsmProfFactory)
        END_NANONYM_HEAP_PROVIDER()

    public:
        typedef typename UseDefaultInfoProfilingApiIfNecessary<InfoProfilingApiType>::type info_profiling_api_type;
        typedef typename UseDefaultAppDomainProfilingApiIfNecessary<AppDomainProfilingApiType>::type app_domain_profiling_api_type;

        BasicProfilingInfo() { }
        
        void Init(IUnknown *pICorProfilerInfoUnk)
        {
            using namespace Urasandesu::NAnonym;
            HRESULT hr = E_FAIL;
            
            hr = pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo2, 
                                                      reinterpret_cast<void**>(&m_pInfo));
            if (FAILED(hr)) 
                BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
        }
        
        void SetEventMask(DWORD events)
        {
            using namespace Urasandesu::NAnonym;
            HRESULT hr = E_FAIL;

            hr = m_pInfo->SetEventMask(events);
            if (FAILED(hr)) 
                BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
        }
        
        // このメソッドは AppDomain にあるべき！
        AssemblyProfile *GetAssembly(AssemblyID assemblyId)
        {
            if (m_asmIndexes.find(assemblyId) != m_asmIndexes.end())
            {
                return (*GetHeap<AssemblyProfile>())[m_asmIndexes[assemblyId]];
            }
            else
            {
                AssemblyProfile *pAsmProf = GetHeap<AssemblyProfile>()->New();
                m_asmIndexes[assemblyId] = GetHeap<AssemblyProfile>()->Size() - 1;
                
                // ここで pAsmProf->Init みたいなのが必要。
                
                return pAsmProf;
            }
        }

    //private:    
        CComPtr<ICorProfilerInfo2> m_pInfo;
        boost::unordered_map<AssemblyID, SIZE_T> m_asmIndexes;
    };
    
}}}   // namespace Urasandesu { namespace NAnonym { namespace Profiling {

namespace Urasandesu { namespace NAnonym { namespace MetaData2 {
    
    #if 0

    struct DefaultInfoMetaDataApi;

    template<class InfoMetaDataApiType = boost::use_default>
    struct ATL_NO_VTABLE UseDefaultInfoMetaDataApiIfNecessary2
    {
        typedef typename Urasandesu::NAnonym::Traits::Replace<InfoMetaDataApiType, boost::use_default, DefaultInfoMetaDataApi>::type type;
    };







    template<
        class InfoMetaDataApiType = boost::use_default,
        class AssemblyMetaDataApiType = boost::use_default
    >
    class BasicMetaDataInfo
    {
    public:
        typedef typename UseDefaultInfoMetaDataApiIfNecessary<InfoMetaDataApiType>::type info_meta_data_api_type;
        typedef typename UseDefaultAssemblyMetaDataApiIfNecessary<AssemblyMetaDataApiType>::type assembly_meta_data_api_type;
    };
    
    typedef BasicMetaDataInfo<> MetaDataInfo;
    
       
    
    
    #endif

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

    template<class AssemblyMetaDataApiType = boost::use_default>
    class BasicAssemblyMetaData : public IMetaDataOperable<AssemblyMetaDataApiType>, public ITokenizable
    {
    };
    
    typedef BasicAssemblyMetaData<> AssemblyMetaData;
    
}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData2 {

namespace Urasandesu { namespace NAnonym { namespace Utilities {

    template<class ToInfoType, class FromInfoType>
    struct ValueConverter;

    template<>
    struct ValueConverter<Urasandesu::NAnonym::MetaData2::MetaDataInfo *, Urasandesu::NAnonym::Profiling::ProfilingInfo *>
    {
        ValueConverter() { }
        
        Urasandesu::NAnonym::MetaData2::ModuleMetaData *Convert(Urasandesu::NAnonym::Profiling::ModuleProfile *from)
        {
            return NULL;
        }
        
        Urasandesu::NAnonym::MetaData2::AssemblyMetaData *Convert(Urasandesu::NAnonym::Profiling::AssemblyProfile *from)
        {
            return NULL;
        }
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace Utilities {


// CExeWeaver2
HRESULT CExeWeaver2::FinalConstruct()
{
    using namespace boost;
    using namespace Urasandesu::NAnonym::MetaData2;
    using namespace Urasandesu::NAnonym::Profiling;
    using namespace Urasandesu::NAnonym::Utilities;
    
    m_pProf = make_shared<ProfilingInfo>();
    m_pConv = make_shared<ValueConverter<MetaDataInfo *, ProfilingInfo *>>();
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

void __stdcall FunctionEnter2Impl(FunctionID funcId, UINT_PTR clientData, COR_PRF_FRAME_INFO func, COR_PRF_FUNCTION_ARGUMENT_INFO *argumentInfo)
{
    using namespace std;
    cout << "Enter Function ID: " << funcId << endl;
}

void __declspec(naked) FunctionEnter2Naked(FunctionID funcId, UINT_PTR clientData, COR_PRF_FRAME_INFO func, COR_PRF_FUNCTION_ARGUMENT_INFO *argumentInfo)
{
    __asm
    {
        PUSH EBP
        MOV EBP, ESP

        PUSH EAX
        PUSH ECX
        PUSH EDX
    }

    FunctionEnter2Impl(funcId, clientData, func, argumentInfo);

    __asm
    {
        POP EDX
        POP ECX
        POP EAX

        MOV ESP, EBP
        POP EBP

        RET 16
    }
}

void __stdcall FunctionLeave2Impl(FunctionID funcId, UINT_PTR clientData, COR_PRF_FRAME_INFO func, COR_PRF_FUNCTION_ARGUMENT_RANGE *retvalRange)
{
    using namespace std;
    cout << "Leave Function ID: " << funcId << endl;
}

void __declspec(naked) FunctionLeave2Naked(FunctionID funcId, UINT_PTR clientData, COR_PRF_FRAME_INFO func, COR_PRF_FUNCTION_ARGUMENT_RANGE *retvalRange)
{
    __asm
    {
        PUSH EBP
        MOV EBP, ESP

        PUSH EAX
        PUSH ECX
        PUSH EDX
    }

    FunctionLeave2Impl(funcId, clientData, func, retvalRange);

    __asm
    {
        POP EDX
        POP ECX
        POP EAX

        MOV ESP, EBP
        POP EBP

        RET 16
    }
}

void __stdcall FunctionTailcall2Impl(FunctionID funcId, UINT_PTR clientData, COR_PRF_FRAME_INFO func)
{
    using namespace std;
    cout << "Tailcall Function ID: " << funcId << endl;
}

void __declspec(naked) FunctionTailcall2Naked(FunctionID funcId, UINT_PTR clientData, COR_PRF_FRAME_INFO func)
{
    __asm
    {
        PUSH EBP
        MOV EBP, ESP

        PUSH EAX
        PUSH ECX
        PUSH EDX
    }

    FunctionTailcall2Impl(funcId, clientData, func);

    __asm
    {
        POP EDX
        POP ECX
        POP EAX

        MOV ESP, EBP
        POP EBP

        RET 12
    }
}



// ICorProfilerCallback
HRESULT CExeWeaver2::Initialize( 
    /* [in] */ IUnknown *pICorProfilerInfoUnk)
{
    using namespace std;
    using namespace boost;
    using namespace Urasandesu::NAnonym;
    
    try
    {
        //::_CrtDbgBreak();
        //::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
        m_pProf->Init(pICorProfilerInfoUnk);
        m_pProf->SetEventMask(COR_PRF_MONITOR_ASSEMBLY_LOADS |
                              COR_PRF_MONITOR_APPDOMAIN_LOADS | 
                              COR_PRF_MONITOR_ENTERLEAVE |
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
        
        m_pProf->m_pInfo->SetEnterLeaveFunctionHooks2(FunctionEnter2Naked, FunctionLeave2Naked, FunctionTailcall2Naked);
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
    return S_OK; 
}

HRESULT CExeWeaver2::AppDomainCreationFinished( 
    /* [in] */ AppDomainID appDomainId,
    /* [in] */ HRESULT hrStatus)
{ 
    using namespace std;
    using namespace boost;
    using namespace Urasandesu::NAnonym;
    
    try
    {
        HRESULT hr = E_FAIL;
        
        ULONG nameSize = MAX_SYM_NAME;
        WCHAR name[MAX_SYM_NAME];
        ProcessID processId = 0;
        hr = m_pProf->m_pInfo->GetAppDomainInfo(appDomainId, nameSize, &nameSize, name, &processId);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
        
        cout << format("Profiling API's Process ID: %|1$d|") % processId << endl;
        cout << format("P/Invoke Process ID: %|1$d|") % ::GetCurrentProcessId() << endl;
        
        //virtual HRESULT STDMETHODCALLTYPE GetAppDomainInfo( 
        //    /* [in] */ AppDomainID appDomainId,
        //    /* [in] */ ULONG cchName,
        //    /* [out] */ ULONG *pcchName,
        //    /* [length_is][size_is][out] */ WCHAR szName[  ],
        //    /* [out] */ ProcessID *pProcessId) = 0;
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
    return S_OK;
}

HRESULT CExeWeaver2::AssemblyLoadFinished( 
    /* [in] */ AssemblyID assemblyId,
    /* [in] */ HRESULT hrStatus)
{
    using namespace std;
    using namespace boost;
    using namespace Urasandesu::NAnonym;
    using namespace Urasandesu::NAnonym::Profiling;
    using namespace Urasandesu::NAnonym::MetaData2;
    
    try
    {
        //::_CrtDbgBreak();
        //::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
        //AssemblyProfile *pAsmProf = m_pProf->GetAssembly(assemblyId);
        //AssemblyMetaData *pAsmMeta = m_pConv->Convert(pAsmProf);
        //if (pAsmMeta->GetToken() == m_mdaTargetAssembly)
        //{
        //    ModuleProfile *pModProf = pAsmProf->GetModule();
        //    m_pModMeta = m_pConv->Convert(pModProf);

        //    //TypeMetaData *pReplaceTypeFromMeta = m_pModMeta->GetType(mdtdReplaceTypeFrom);
        //    //m_pReplaceMethodFromMeta = pReplaceTypeFromMeta->GetMethod(mdmdReplaceMethodFrom);
        //    //TypeMetaData *pReplaceTypeToMeta = m_pModMeta->GetType(mdtdReplaceTypeTo);
        //    //m_pReplaceMethodToMeta = pReplaceTypeToMeta->GetMethod(mdtdReplaceMethodTo);
        //}
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
    
    cout << "JITCompilationStarted !!" << endl;
    
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
