// ExeWeaver2.h : CExeWeaver2 の宣言

#pragma once
#include "resource.h"       // メイン シンボル

#include "ProfilingApiSample02_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM の完全サポートを含んでいない Windows Mobile プラットフォームのような Windows CE プラットフォームでは、単一スレッド COM オブジェクトは正しくサポートされていません。ATL が単一スレッド COM オブジェクトの作成をサポートすること、およびその単一スレッド COM オブジェクトの実装の使用を許可することを強制するには、_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA を定義してください。ご使用の rgs ファイルのスレッド モデルは 'Free' に設定されており、DCOM Windows CE 以外のプラットフォームでサポートされる唯一のスレッド モデルと設定されていました。"
#endif



// CExeWeaver2

#ifdef UNM
#error This .h reserves the word "UNM" that means "Urasandesu::NAnonym::MetaData".
#endif
#define UNM Urasandesu::NAnonym::MetaData

#ifdef UNP
#error This .h reserves the word "UNP" that means "Urasandesu::NAnonym::Profiling".
#endif
#define UNP Urasandesu::NAnonym::Profiling

#ifdef UNT
#error This .h reserves the word "UNT" that means "Urasandesu::NAnonym::Traits".
#endif
#define UNT Urasandesu::NAnonym::Traits

#ifdef UNU
#error This .h reserves the word "UNU" that means "Urasandesu::NAnonym::Utilities".
#endif
#define UNU Urasandesu::NAnonym::Utilities

class ATL_NO_VTABLE CExeWeaver2 :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CExeWeaver2, &CLSID_ExeWeaver2>,
	public ISupportErrorInfo,
	public ICorProfilerCallback2,
	public IDispatchImpl<IExeWeaver2, &IID_IExeWeaver2, &LIBID_ProfilingApiSample02Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CExeWeaver2()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EXEWEAVER2)


BEGIN_COM_MAP(CExeWeaver2)
	COM_INTERFACE_ENTRY(IExeWeaver2)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(ICorProfilerCallback2)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICorProfilerCallback
#if 1
    STDMETHOD(Initialize)( 
        /* [in] */ IUnknown *pICorProfilerInfoUnk);

    STDMETHOD(Shutdown)( void);

    STDMETHOD(AppDomainCreationStarted)( 
        /* [in] */ AppDomainID appDomainId);

    STDMETHOD(AppDomainCreationFinished)( 
        /* [in] */ AppDomainID appDomainId,
        /* [in] */ HRESULT hrStatus);

    STDMETHOD(AppDomainShutdownStarted)( 
        /* [in] */ AppDomainID appDomainId);

    STDMETHOD(AppDomainShutdownFinished)( 
        /* [in] */ AppDomainID appDomainId,
        /* [in] */ HRESULT hrStatus);

    STDMETHOD(AssemblyLoadStarted)( 
        /* [in] */ AssemblyID assemblyId);

    STDMETHOD(AssemblyLoadFinished)( 
        /* [in] */ AssemblyID assemblyId,
        /* [in] */ HRESULT hrStatus);

    STDMETHOD(AssemblyUnloadStarted)( 
        /* [in] */ AssemblyID assemblyId);

    STDMETHOD(AssemblyUnloadFinished)( 
        /* [in] */ AssemblyID assemblyId,
        /* [in] */ HRESULT hrStatus);

    STDMETHOD(ModuleLoadStarted)( 
        /* [in] */ ModuleID moduleId);

    STDMETHOD(ModuleLoadFinished)( 
        /* [in] */ ModuleID moduleId,
        /* [in] */ HRESULT hrStatus);

    STDMETHOD(ModuleUnloadStarted)( 
        /* [in] */ ModuleID moduleId);

    STDMETHOD(ModuleUnloadFinished)( 
        /* [in] */ ModuleID moduleId,
        /* [in] */ HRESULT hrStatus);

    STDMETHOD(ModuleAttachedToAssembly)( 
        /* [in] */ ModuleID moduleId,
        /* [in] */ AssemblyID AssemblyId);

    STDMETHOD(ClassLoadStarted)( 
        /* [in] */ ClassID classId);

    STDMETHOD(ClassLoadFinished)( 
        /* [in] */ ClassID classId,
        /* [in] */ HRESULT hrStatus);

    STDMETHOD(ClassUnloadStarted)( 
        /* [in] */ ClassID classId);

    STDMETHOD(ClassUnloadFinished)( 
        /* [in] */ ClassID classId,
        /* [in] */ HRESULT hrStatus);

    STDMETHOD(FunctionUnloadStarted)( 
        /* [in] */ FunctionID functionId);

    STDMETHOD(JITCompilationStarted)( 
        /* [in] */ FunctionID functionId,
        /* [in] */ BOOL fIsSafeToBlock);

    STDMETHOD(JITCompilationFinished)( 
        /* [in] */ FunctionID functionId,
        /* [in] */ HRESULT hrStatus,
        /* [in] */ BOOL fIsSafeToBlock);

    STDMETHOD(JITCachedFunctionSearchStarted)( 
        /* [in] */ FunctionID functionId,
        /* [out] */ BOOL *pbUseCachedFunction);

    STDMETHOD(JITCachedFunctionSearchFinished)( 
        /* [in] */ FunctionID functionId,
        /* [in] */ COR_PRF_JIT_CACHE result);

    STDMETHOD(JITFunctionPitched)( 
        /* [in] */ FunctionID functionId);

    STDMETHOD(JITInlining)( 
        /* [in] */ FunctionID callerId,
        /* [in] */ FunctionID calleeId,
        /* [out] */ BOOL *pfShouldInline);

    STDMETHOD(ThreadCreated)( 
        /* [in] */ ThreadID threadId);

    STDMETHOD(ThreadDestroyed)( 
        /* [in] */ ThreadID threadId);

    STDMETHOD(ThreadAssignedToOSThread)( 
        /* [in] */ ThreadID managedThreadId,
        /* [in] */ DWORD osThreadId);

    STDMETHOD(RemotingClientInvocationStarted)( void);

    STDMETHOD(RemotingClientSendingMessage)( 
        /* [in] */ GUID *pCookie,
        /* [in] */ BOOL fIsAsync);

    STDMETHOD(RemotingClientReceivingReply)( 
        /* [in] */ GUID *pCookie,
        /* [in] */ BOOL fIsAsync);

    STDMETHOD(RemotingClientInvocationFinished)( void);

    STDMETHOD(RemotingServerReceivingMessage)( 
        /* [in] */ GUID *pCookie,
        /* [in] */ BOOL fIsAsync);

    STDMETHOD(RemotingServerInvocationStarted)( void);

    STDMETHOD(RemotingServerInvocationReturned)( void);

    STDMETHOD(RemotingServerSendingReply)( 
        /* [in] */ GUID *pCookie,
        /* [in] */ BOOL fIsAsync);

    STDMETHOD(UnmanagedToManagedTransition)( 
        /* [in] */ FunctionID functionId,
        /* [in] */ COR_PRF_TRANSITION_REASON reason);

    STDMETHOD(ManagedToUnmanagedTransition)( 
        /* [in] */ FunctionID functionId,
        /* [in] */ COR_PRF_TRANSITION_REASON reason);

    STDMETHOD(RuntimeSuspendStarted)( 
        /* [in] */ COR_PRF_SUSPEND_REASON suspendReason);

    STDMETHOD(RuntimeSuspendFinished)( void);

    STDMETHOD(RuntimeSuspendAborted)( void);

    STDMETHOD(RuntimeResumeStarted)( void);

    STDMETHOD(RuntimeResumeFinished)( void);

    STDMETHOD(RuntimeThreadSuspended)( 
        /* [in] */ ThreadID threadId);

    STDMETHOD(RuntimeThreadResumed)( 
        /* [in] */ ThreadID threadId);

    STDMETHOD(MovedReferences)( 
        /* [in] */ ULONG cMovedObjectIDRanges,
        /* [size_is][in] */ ObjectID oldObjectIDRangeStart[  ],
        /* [size_is][in] */ ObjectID newObjectIDRangeStart[  ],
        /* [size_is][in] */ ULONG cObjectIDRangeLength[  ]);

    STDMETHOD(ObjectAllocated)( 
        /* [in] */ ObjectID objectId,
        /* [in] */ ClassID classId);

    STDMETHOD(ObjectsAllocatedByClass)( 
        /* [in] */ ULONG cClassCount,
        /* [size_is][in] */ ClassID classIds[  ],
        /* [size_is][in] */ ULONG cObjects[  ]);

    STDMETHOD(ObjectReferences)( 
        /* [in] */ ObjectID objectId,
        /* [in] */ ClassID classId,
        /* [in] */ ULONG cObjectRefs,
        /* [size_is][in] */ ObjectID objectRefIds[  ]);

    STDMETHOD(RootReferences)( 
        /* [in] */ ULONG cRootRefs,
        /* [size_is][in] */ ObjectID rootRefIds[  ]);

    STDMETHOD(ExceptionThrown)( 
        /* [in] */ ObjectID thrownObjectId);

    STDMETHOD(ExceptionSearchFunctionEnter)( 
        /* [in] */ FunctionID functionId);

    STDMETHOD(ExceptionSearchFunctionLeave)( void);

    STDMETHOD(ExceptionSearchFilterEnter)( 
        /* [in] */ FunctionID functionId);

    STDMETHOD(ExceptionSearchFilterLeave)( void);

    STDMETHOD(ExceptionSearchCatcherFound)( 
        /* [in] */ FunctionID functionId);

    STDMETHOD(ExceptionOSHandlerEnter)( 
        /* [in] */ UINT_PTR __unused);

    STDMETHOD(ExceptionOSHandlerLeave)( 
        /* [in] */ UINT_PTR __unused);

    STDMETHOD(ExceptionUnwindFunctionEnter)( 
        /* [in] */ FunctionID functionId);

    STDMETHOD(ExceptionUnwindFunctionLeave)( void);

    STDMETHOD(ExceptionUnwindFinallyEnter)( 
        /* [in] */ FunctionID functionId);

    STDMETHOD(ExceptionUnwindFinallyLeave)( void);

    STDMETHOD(ExceptionCatcherEnter)( 
        /* [in] */ FunctionID functionId,
        /* [in] */ ObjectID objectId);

    STDMETHOD(ExceptionCatcherLeave)( void);

    STDMETHOD(COMClassicVTableCreated)( 
        /* [in] */ ClassID wrappedClassId,
        /* [in] */ REFGUID implementedIID,
        /* [in] */ void *pVTable,
        /* [in] */ ULONG cSlots);

    STDMETHOD(COMClassicVTableDestroyed)( 
        /* [in] */ ClassID wrappedClassId,
        /* [in] */ REFGUID implementedIID,
        /* [in] */ void *pVTable);

    STDMETHOD(ExceptionCLRCatcherFound)( void);

    STDMETHOD(ExceptionCLRCatcherExecute)( void);

// ICorProfilerCallback2
    STDMETHOD(ThreadNameChanged)( 
        /* [in] */ ThreadID threadId,
        /* [in] */ ULONG cchName,
        /* [in] */ WCHAR name[  ]);

    STDMETHOD(GarbageCollectionStarted)( 
        /* [in] */ int cGenerations,
        /* [length_is][size_is][in] */ BOOL generationCollected[  ],
        /* [in] */ COR_PRF_GC_REASON reason);

    STDMETHOD(SurvivingReferences)( 
        /* [in] */ ULONG cSurvivingObjectIDRanges,
        /* [size_is][in] */ ObjectID objectIDRangeStart[  ],
        /* [size_is][in] */ ULONG cObjectIDRangeLength[  ]);

    STDMETHOD(GarbageCollectionFinished)( void);

    STDMETHOD(FinalizeableObjectQueued)( 
        /* [in] */ DWORD finalizerFlags,
        /* [in] */ ObjectID objectID);

    STDMETHOD(RootReferences2)( 
        /* [in] */ ULONG cRootRefs,
        /* [size_is][in] */ ObjectID rootRefIds[  ],
        /* [size_is][in] */ COR_PRF_GC_ROOT_KIND rootKinds[  ],
        /* [size_is][in] */ COR_PRF_GC_ROOT_FLAGS rootFlags[  ],
        /* [size_is][in] */ UINT_PTR rootIds[  ]);

    STDMETHOD(HandleCreated)( 
        /* [in] */ GCHandleID handleId,
        /* [in] */ ObjectID initialObjectId);

    STDMETHOD(HandleDestroyed)( 
        /* [in] */ GCHandleID handleId);

#endif


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();

	void FinalRelease();

	HRESULT COMError(HRESULT hr, LPCSTR filePath, INT line);

public:

private:
    boost::shared_ptr<UNP::ProfilingInfo> m_pProfInfo;
    boost::shared_ptr<UNM::MetaDataInfo> m_pMetaInfo;
    boost::shared_ptr<UNU::ValueConverter<UNM::AssemblyMetaData *, UNP::ProcessProfile *>> m_pConv;

    UNP::AssemblyProfile *m_pTargetAssemblyProf;
    std::wstring m_targetAssemblyName;    
    mdTypeDef m_mdtdReplaceTypeFrom;
    mdMethodDef m_mdmdReplaceMethodFrom;
    mdTypeDef m_mdtdReplaceTypeTo;
    mdMethodDef m_mdtdReplaceMethodTo;
};

#undef UNU
#undef UNT
#undef UNM
#undef UNP

OBJECT_ENTRY_AUTO(__uuidof(ExeWeaver2), CExeWeaver2)
