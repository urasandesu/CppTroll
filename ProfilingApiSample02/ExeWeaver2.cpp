// ExeWeaver2.cpp : CExeWeaver2 の実装

#include "stdafx.h"
#include "ExeWeaver2.h"


// CExeWeaver2

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
