// ExeWeaver.cpp : CExeWeaver ‚ÌŽÀ‘•

#include "stdafx.h"
#include "ExeWeaver.h"


// CExeWeaver

HRESULT CExeWeaver::SystemError(DWORD errorNo, LPCSTR filePath, INT line)
{
    using boost::system::system_category;
    using std::wostringstream;
    using Urasandesu::NAnonym::SystemError;

    wostringstream msg;
    msg << SystemError(errorNo, system_category()).GetBSTRMessage().m_str;
    msg << ", File: " << filePath;
    msg << ", Line: " << line;
    return Error(msg.str().c_str());
}

HRESULT CExeWeaver::COMError(HRESULT hr, LPCSTR filePath, INT line)
{
    using std::wostringstream;

    wostringstream msg;
    msg << _com_error(hr).ErrorMessage();
    msg << ", File: " << filePath;
    msg << ", Line: " << line;
    return Error(msg.str().c_str());
}

STDMETHODIMP CExeWeaver::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IExeWeaver
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// ICorProfilerCallback
HRESULT CExeWeaver::Initialize( 
    /* [in] */ IUnknown *pICorProfilerInfoUnk)
{
    HRESULT hr = E_FAIL;
    
    hr = pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo2, 
                                              reinterpret_cast<void**>(&m_pInfo));
    if (FAILED(hr)) 
        return COMError(hr, __FILE__, __LINE__);

	DWORD event_ = COR_PRF_MONITOR_JIT_COMPILATION;

    hr = m_pInfo->SetEventMask(event_);
    if (FAILED(hr)) 
        return COMError(hr, __FILE__, __LINE__);

    return S_OK; 
}

HRESULT CExeWeaver::Shutdown( void)
{ 
    return S_OK; 
}

HRESULT CExeWeaver::AppDomainCreationStarted( 
    /* [in] */ AppDomainID appDomainId)
{ 
    return S_OK; 
}

HRESULT CExeWeaver::AppDomainCreationFinished( 
    /* [in] */ AppDomainID appDomainId,
    /* [in] */ HRESULT hrStatus)
{ 
    return S_OK; 
}

HRESULT CExeWeaver::AppDomainShutdownStarted( 
    /* [in] */ AppDomainID appDomainId)
{
    return S_OK;
}

HRESULT CExeWeaver::AppDomainShutdownFinished( 
    /* [in] */ AppDomainID appDomainId,
    /* [in] */ HRESULT hrStatus)
{
    return S_OK;
}

HRESULT CExeWeaver::AssemblyLoadStarted( 
    /* [in] */ AssemblyID assemblyId)
{
    return S_OK;
}

HRESULT CExeWeaver::AssemblyLoadFinished( 
    /* [in] */ AssemblyID assemblyId,
    /* [in] */ HRESULT hrStatus)
{
    return S_OK;
}

HRESULT CExeWeaver::AssemblyUnloadStarted( 
    /* [in] */ AssemblyID assemblyId)
{
    return S_OK;
}

HRESULT CExeWeaver::AssemblyUnloadFinished( 
    /* [in] */ AssemblyID assemblyId,
    /* [in] */ HRESULT hrStatus)
{
    return S_OK;
}

HRESULT CExeWeaver::ModuleLoadStarted( 
    /* [in] */ ModuleID moduleId)
{
    return S_OK;
}

HRESULT CExeWeaver::ModuleLoadFinished( 
    /* [in] */ ModuleID moduleId,
    /* [in] */ HRESULT hrStatus)
{
    return S_OK;
}

HRESULT CExeWeaver::ModuleUnloadStarted( 
    /* [in] */ ModuleID moduleId)
{
    return S_OK;
}

HRESULT CExeWeaver::ModuleUnloadFinished( 
    /* [in] */ ModuleID moduleId,
    /* [in] */ HRESULT hrStatus)
{
    return S_OK;
}

HRESULT CExeWeaver::ModuleAttachedToAssembly( 
    /* [in] */ ModuleID moduleId,
    /* [in] */ AssemblyID AssemblyId)
{
    return S_OK;
}

HRESULT CExeWeaver::ClassLoadStarted( 
    /* [in] */ ClassID classId)
{
    return S_OK;
}

HRESULT CExeWeaver::ClassLoadFinished( 
    /* [in] */ ClassID classId,
    /* [in] */ HRESULT hrStatus)
{
    return S_OK;
}

HRESULT CExeWeaver::ClassUnloadStarted( 
    /* [in] */ ClassID classId)
{
    return S_OK;
}

HRESULT CExeWeaver::ClassUnloadFinished( 
    /* [in] */ ClassID classId,
    /* [in] */ HRESULT hrStatus)
{
    return S_OK;
}

HRESULT CExeWeaver::FunctionUnloadStarted( 
    /* [in] */ FunctionID functionId)
{
    return S_OK;
}

HRESULT CExeWeaver::JITCompilationStarted( 
    /* [in] */ FunctionID functionId,
    /* [in] */ BOOL fIsSafeToBlock)
{
    using namespace std;
    cout << "JITCompilationStarted !!, 0x" << uppercase << hex << setw(8) << setfill('0') << functionId << endl;
    return S_OK;
}

HRESULT CExeWeaver::JITCompilationFinished( 
    /* [in] */ FunctionID functionId,
    /* [in] */ HRESULT hrStatus,
    /* [in] */ BOOL fIsSafeToBlock)
{
    return S_OK;
}

HRESULT CExeWeaver::JITCachedFunctionSearchStarted( 
    /* [in] */ FunctionID functionId,
    /* [out] */ BOOL *pbUseCachedFunction)
{
    return S_OK;
}

HRESULT CExeWeaver::JITCachedFunctionSearchFinished( 
    /* [in] */ FunctionID functionId,
    /* [in] */ COR_PRF_JIT_CACHE result)
{
    return S_OK;
}

HRESULT CExeWeaver::JITFunctionPitched( 
    /* [in] */ FunctionID functionId)
{
    return S_OK;
}

HRESULT CExeWeaver::JITInlining( 
    /* [in] */ FunctionID callerId,
    /* [in] */ FunctionID calleeId,
    /* [out] */ BOOL *pfShouldInline)
{
    return S_OK;
}

HRESULT CExeWeaver::ThreadCreated( 
    /* [in] */ ThreadID threadId)
{
    return S_OK;
}

HRESULT CExeWeaver::ThreadDestroyed( 
    /* [in] */ ThreadID threadId)
{
    return S_OK;
}

HRESULT CExeWeaver::ThreadAssignedToOSThread( 
    /* [in] */ ThreadID managedThreadId,
    /* [in] */ DWORD osThreadId)
{
    return S_OK;
}

HRESULT CExeWeaver::RemotingClientInvocationStarted( void)
{
    return S_OK;
}

HRESULT CExeWeaver::RemotingClientSendingMessage( 
    /* [in] */ GUID *pCookie,
    /* [in] */ BOOL fIsAsync)
{
    return S_OK;
}

HRESULT CExeWeaver::RemotingClientReceivingReply( 
    /* [in] */ GUID *pCookie,
    /* [in] */ BOOL fIsAsync)
{
    return S_OK;
}

HRESULT CExeWeaver::RemotingClientInvocationFinished( void)
{
    return S_OK;
}

HRESULT CExeWeaver::RemotingServerReceivingMessage( 
    /* [in] */ GUID *pCookie,
    /* [in] */ BOOL fIsAsync)
{
    return S_OK;
}

HRESULT CExeWeaver::RemotingServerInvocationStarted( void)
{
    return S_OK;
}

HRESULT CExeWeaver::RemotingServerInvocationReturned( void)
{
    return S_OK;
}

HRESULT CExeWeaver::RemotingServerSendingReply( 
    /* [in] */ GUID *pCookie,
    /* [in] */ BOOL fIsAsync)
{
    return S_OK;
}

HRESULT CExeWeaver::UnmanagedToManagedTransition( 
    /* [in] */ FunctionID functionId,
    /* [in] */ COR_PRF_TRANSITION_REASON reason)
{
    return S_OK;
}

HRESULT CExeWeaver::ManagedToUnmanagedTransition( 
    /* [in] */ FunctionID functionId,
    /* [in] */ COR_PRF_TRANSITION_REASON reason)
{
    return S_OK;
}

HRESULT CExeWeaver::RuntimeSuspendStarted( 
    /* [in] */ COR_PRF_SUSPEND_REASON suspendReason)
{
    return S_OK;
}

HRESULT CExeWeaver::RuntimeSuspendFinished( void)
{
    return S_OK;
}

HRESULT CExeWeaver::RuntimeSuspendAborted( void)
{
    return S_OK;
}

HRESULT CExeWeaver::RuntimeResumeStarted( void)
{
    return S_OK;
}

HRESULT CExeWeaver::RuntimeResumeFinished( void)
{
    return S_OK;
}

HRESULT CExeWeaver::RuntimeThreadSuspended( 
    /* [in] */ ThreadID threadId)
{
    return S_OK;
}

HRESULT CExeWeaver::RuntimeThreadResumed( 
    /* [in] */ ThreadID threadId)
{
    return S_OK;
}

HRESULT CExeWeaver::MovedReferences( 
    /* [in] */ ULONG cMovedObjectIDRanges,
    /* [size_is][in] */ ObjectID oldObjectIDRangeStart[  ],
    /* [size_is][in] */ ObjectID newObjectIDRangeStart[  ],
    /* [size_is][in] */ ULONG cObjectIDRangeLength[  ])
{
    return S_OK;
}

HRESULT CExeWeaver::ObjectAllocated( 
    /* [in] */ ObjectID objectId,
    /* [in] */ ClassID classId)
{
    return S_OK;
}

HRESULT CExeWeaver::ObjectsAllocatedByClass( 
    /* [in] */ ULONG cClassCount,
    /* [size_is][in] */ ClassID classIds[  ],
    /* [size_is][in] */ ULONG cObjects[  ])
{
    return S_OK;
}

HRESULT CExeWeaver::ObjectReferences( 
    /* [in] */ ObjectID objectId,
    /* [in] */ ClassID classId,
    /* [in] */ ULONG cObjectRefs,
    /* [size_is][in] */ ObjectID objectRefIds[  ])
{
    return S_OK;
}

HRESULT CExeWeaver::RootReferences( 
    /* [in] */ ULONG cRootRefs,
    /* [size_is][in] */ ObjectID rootRefIds[  ])
{
    return S_OK;
}

HRESULT CExeWeaver::ExceptionThrown( 
    /* [in] */ ObjectID thrownObjectId)
{
    return S_OK;
}

HRESULT CExeWeaver::ExceptionSearchFunctionEnter( 
    /* [in] */ FunctionID functionId)
{
    return S_OK;
}

HRESULT CExeWeaver::ExceptionSearchFunctionLeave( void)
{
    return S_OK;
}

HRESULT CExeWeaver::ExceptionSearchFilterEnter( 
    /* [in] */ FunctionID functionId)
{
    return S_OK;
}

HRESULT CExeWeaver::ExceptionSearchFilterLeave( void)
{
    return S_OK;
}

HRESULT CExeWeaver::ExceptionSearchCatcherFound( 
    /* [in] */ FunctionID functionId)
{
    return S_OK;
}

HRESULT CExeWeaver::ExceptionOSHandlerEnter( 
    /* [in] */ UINT_PTR __unused)
{
    return S_OK;
}

HRESULT CExeWeaver::ExceptionOSHandlerLeave( 
    /* [in] */ UINT_PTR __unused)
{
    return S_OK;
}

HRESULT CExeWeaver::ExceptionUnwindFunctionEnter( 
    /* [in] */ FunctionID functionId)
{
    return S_OK;
}

HRESULT CExeWeaver::ExceptionUnwindFunctionLeave( void)
{
    return S_OK;
}

HRESULT CExeWeaver::ExceptionUnwindFinallyEnter( 
    /* [in] */ FunctionID functionId)
{
    return S_OK;
}

HRESULT CExeWeaver::ExceptionUnwindFinallyLeave( void)
{
    return S_OK;
}

HRESULT CExeWeaver::ExceptionCatcherEnter( 
    /* [in] */ FunctionID functionId,
    /* [in] */ ObjectID objectId)
{
    return S_OK;
}

HRESULT CExeWeaver::ExceptionCatcherLeave( void)
{
    return S_OK;
}

HRESULT CExeWeaver::COMClassicVTableCreated( 
    /* [in] */ ClassID wrappedClassId,
    /* [in] */ REFGUID implementedIID,
    /* [in] */ void *pVTable,
    /* [in] */ ULONG cSlots)
{
    return S_OK;
}

HRESULT CExeWeaver::COMClassicVTableDestroyed( 
    /* [in] */ ClassID wrappedClassId,
    /* [in] */ REFGUID implementedIID,
    /* [in] */ void *pVTable)
{
    return S_OK;
}

HRESULT CExeWeaver::ExceptionCLRCatcherFound( void)
{
    return S_OK;
}

HRESULT CExeWeaver::ExceptionCLRCatcherExecute( void)
{
    return S_OK;
}

// ICorProfilerCallback2
HRESULT CExeWeaver::ThreadNameChanged( 
    /* [in] */ ThreadID threadId,
    /* [in] */ ULONG cchName,
    /* [in] */ WCHAR name[  ])
{
    return S_OK;
}

HRESULT CExeWeaver::GarbageCollectionStarted( 
    /* [in] */ int cGenerations,
    /* [length_is][size_is][in] */ BOOL generationCollected[  ],
    /* [in] */ COR_PRF_GC_REASON reason)
{
    return S_OK;
}

HRESULT CExeWeaver::SurvivingReferences( 
    /* [in] */ ULONG cSurvivingObjectIDRanges,
    /* [size_is][in] */ ObjectID objectIDRangeStart[  ],
    /* [size_is][in] */ ULONG cObjectIDRangeLength[  ])
{
    return S_OK;
}

HRESULT CExeWeaver::GarbageCollectionFinished( void)
{
    return S_OK;
}

HRESULT CExeWeaver::FinalizeableObjectQueued( 
    /* [in] */ DWORD finalizerFlags,
    /* [in] */ ObjectID objectID)
{
    return S_OK;
}

HRESULT CExeWeaver::RootReferences2( 
    /* [in] */ ULONG cRootRefs,
    /* [size_is][in] */ ObjectID rootRefIds[  ],
    /* [size_is][in] */ COR_PRF_GC_ROOT_KIND rootKinds[  ],
    /* [size_is][in] */ COR_PRF_GC_ROOT_FLAGS rootFlags[  ],
    /* [size_is][in] */ UINT_PTR rootIds[  ])
{
    return S_OK;
}

HRESULT CExeWeaver::HandleCreated( 
    /* [in] */ GCHandleID handleId,
    /* [in] */ ObjectID initialObjectId)
{
    return S_OK;
}

HRESULT CExeWeaver::HandleDestroyed( 
    /* [in] */ GCHandleID handleId)
{
    return S_OK;
}
