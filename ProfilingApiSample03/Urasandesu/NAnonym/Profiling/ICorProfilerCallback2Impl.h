#pragma once
#ifndef URASANDESU_NANONYM_PROFILING_ICORPROFILERCALLBACK2IMPL_H
#define URASANDESU_NANONYM_PROFILING_ICORPROFILERCALLBACK2IMPL_H

#ifndef URASANDESU_NANONYM_DEFAULTSTDMETHODWRAPPER_H
#include <Urasandesu/NAnonym/DefaultSTDMETHODWrapper.h>
#endif

namespace Urasandesu { namespace NAnonym { namespace Profiling {

    template<
        class Base
    >
    class ATL_NO_VTABLE ICorProfilerCallback2Impl : public Base
    {
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(Initialize, ((IUnknown*,pICorProfilerInfoUnk)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(Shutdown, BOOST_PP_EMPTY())
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(AppDomainCreationStarted, ((AppDomainID,appDomainId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(AppDomainCreationFinished, ((AppDomainID,appDomainId))((HRESULT,hrStatus)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(AppDomainShutdownStarted, ((AppDomainID,appDomainId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(AppDomainShutdownFinished, ((AppDomainID,appDomainId))((HRESULT,hrStatus)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(AssemblyLoadStarted, ((AssemblyID,assemblyId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(AssemblyLoadFinished, ((AssemblyID,assemblyId))((HRESULT,hrStatus)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(AssemblyUnloadStarted, ((AssemblyID,assemblyId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(AssemblyUnloadFinished, ((AssemblyID,assemblyId))((HRESULT,hrStatus)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ModuleLoadStarted, ((ModuleID,moduleId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ModuleLoadFinished, ((ModuleID,moduleId))((HRESULT,hrStatus)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ModuleUnloadStarted, ((ModuleID,moduleId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ModuleUnloadFinished, ((ModuleID,moduleId))((HRESULT,hrStatus)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ModuleAttachedToAssembly, ((ModuleID,moduleId))((AssemblyID,AssemblyId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ClassLoadStarted, ((ClassID,classId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ClassLoadFinished, ((ClassID,classId))((HRESULT,hrStatus)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ClassUnloadStarted, ((ClassID,classId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ClassUnloadFinished, ((ClassID,classId))((HRESULT,hrStatus)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(FunctionUnloadStarted, ((FunctionID,functionId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(JITCompilationStarted, ((FunctionID,functionId))((BOOL,fIsSafeToBlock)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(JITCompilationFinished, ((FunctionID,functionId))((HRESULT,hrStatus))((BOOL,fIsSafeToBlock)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(JITCachedFunctionSearchStarted, ((FunctionID,functionId))((BOOL*,pbUseCachedFunction)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(JITCachedFunctionSearchFinished, ((FunctionID,functionId))((COR_PRF_JIT_CACHE,result)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(JITFunctionPitched, ((FunctionID,functionId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(JITInlining, ((FunctionID,callerId))((FunctionID,calleeId))((BOOL*,pfShouldInline)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ThreadCreated, ((ThreadID,threadId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ThreadDestroyed, ((ThreadID,threadId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ThreadAssignedToOSThread, ((ThreadID,managedThreadId))((DWORD,osThreadId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(RemotingClientInvocationStarted, BOOST_PP_EMPTY())
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(RemotingClientSendingMessage, ((GUID*,pCookie))((BOOL,fIsAsync)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(RemotingClientReceivingReply, ((GUID*,pCookie))((BOOL,fIsAsync)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(RemotingClientInvocationFinished, BOOST_PP_EMPTY())
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(RemotingServerReceivingMessage, ((GUID*,pCookie))((BOOL,fIsAsync)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(RemotingServerInvocationStarted, BOOST_PP_EMPTY())
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(RemotingServerInvocationReturned, BOOST_PP_EMPTY())
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(RemotingServerSendingReply, ((GUID*,pCookie))((BOOL,fIsAsync)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(UnmanagedToManagedTransition, ((FunctionID,functionId))((COR_PRF_TRANSITION_REASON,reason)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ManagedToUnmanagedTransition, ((FunctionID,functionId))((COR_PRF_TRANSITION_REASON,reason)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(RuntimeSuspendStarted, ((COR_PRF_SUSPEND_REASON,suspendReason)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(RuntimeSuspendFinished, BOOST_PP_EMPTY())
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(RuntimeSuspendAborted, BOOST_PP_EMPTY())
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(RuntimeResumeStarted, BOOST_PP_EMPTY())
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(RuntimeResumeFinished, BOOST_PP_EMPTY())
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(RuntimeThreadSuspended, ((ThreadID,threadId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(RuntimeThreadResumed, ((ThreadID,threadId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(MovedReferences, ((ULONG,cMovedObjectIDRanges))((ObjectID*,oldObjectIDRangeStart))((ObjectID*,newObjectIDRangeStart))((ULONG*,cObjectIDRangeLength)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ObjectAllocated, ((ObjectID,objectId))((ClassID,classId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ObjectsAllocatedByClass, ((ULONG,cClassCount))((ClassID*,classIds))((ULONG*,cObjects)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ObjectReferences, ((ObjectID,objectId))((ClassID,classId))((ULONG,cObjectRefs))((ObjectID*,objectRefIds)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(RootReferences, ((ULONG,cRootRefs))((ObjectID*,rootRefIds)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ExceptionThrown, ((ObjectID,thrownObjectId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ExceptionSearchFunctionEnter, ((FunctionID,functionId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ExceptionSearchFunctionLeave, BOOST_PP_EMPTY())
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ExceptionSearchFilterEnter, ((FunctionID,functionId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ExceptionSearchFilterLeave, BOOST_PP_EMPTY())
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ExceptionSearchCatcherFound, ((FunctionID,functionId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ExceptionOSHandlerEnter, ((UINT_PTR,__unused)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ExceptionOSHandlerLeave, ((UINT_PTR,__unused)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ExceptionUnwindFunctionEnter, ((FunctionID,functionId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ExceptionUnwindFunctionLeave, BOOST_PP_EMPTY())
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ExceptionUnwindFinallyEnter, ((FunctionID,functionId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ExceptionUnwindFinallyLeave, BOOST_PP_EMPTY())
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ExceptionCatcherEnter, ((FunctionID,functionId))((ObjectID,objectId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ExceptionCatcherLeave, BOOST_PP_EMPTY())
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(COMClassicVTableCreated, ((ClassID,wrappedClassId))((REFGUID,implementedIID))((void*,pVTable))((ULONG,cSlots)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(COMClassicVTableDestroyed, ((ClassID,wrappedClassId))((REFGUID,implementedIID))((void*,pVTable)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ExceptionCLRCatcherFound, BOOST_PP_EMPTY())
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ExceptionCLRCatcherExecute, BOOST_PP_EMPTY())
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(ThreadNameChanged, ((ThreadID,threadId))((ULONG,cchName))((WCHAR*,name)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(GarbageCollectionStarted, ((int,cGenerations))((BOOL*,generationCollected))((COR_PRF_GC_REASON,reason)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(SurvivingReferences, ((ULONG,cSurvivingObjectIDRanges))((ObjectID*,objectIDRangeStart))((ULONG*,cObjectIDRangeLength)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(GarbageCollectionFinished, BOOST_PP_EMPTY())
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(FinalizeableObjectQueued, ((DWORD,finalizerFlags))((ObjectID,objectID)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(RootReferences2, ((ULONG,cRootRefs))((ObjectID*,rootRefIds))((COR_PRF_GC_ROOT_KIND*,rootKinds))((COR_PRF_GC_ROOT_FLAGS*,rootFlags))((UINT_PTR*,rootIds)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(HandleCreated, ((GCHandleID,handleId))((ObjectID,initialObjectId)))
        NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(HandleDestroyed, ((GCHandleID,handleId)))
    };

}}}  // namespace Urasandesu { namespace NAnonym { namespace Profiling {

#endif  // URASANDESU_NANONYM_PROFILING_ICORPROFILERCALLBACK2IMPL_H