// ExeWeaver.cpp : CExeWeaver の実装

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

HRESULT CExeWeaver::PrintTypeSignatures(PCCOR_SIGNATURE &pMethodSig)
{
    using std::cout;
    using std::wcout;
    using std::uppercase;
    using std::hex;
    using std::setw;
    using std::setfill;
    using std::endl;
    using std::dec;

    _ASSERTE(pMethodSig != NULL);
    
    HRESULT hr = E_FAIL;

    CorElementType retType = ELEMENT_TYPE_END;
    pMethodSig += ::CorSigUncompressElementType(pMethodSig, &retType);
    cout << "  Type: 0x" << setw(8) << setfill('0') << retType << endl;
    switch (retType)
    {
        case ELEMENT_TYPE_CLASS:    
        case ELEMENT_TYPE_VALUETYPE:
        case ELEMENT_TYPE_CMOD_REQD:
        case ELEMENT_TYPE_CMOD_OPT:
            {
                mdToken mdt = mdTokenNil;    
                pMethodSig += ::CorSigUncompressToken(pMethodSig, &mdt); 
                cout << "    Token: 0x" << setw(8) << setfill('0') << mdt << endl;
            }
            break;
        case ELEMENT_TYPE_SZARRAY:     
            cout << "  Single dimension zero lower bound array --- " << endl;
            hr = PrintTypeSignatures(pMethodSig);
            if (FAILED(hr)) 
                return COMError(hr, __FILE__, __LINE__);
            break;
        case ELEMENT_TYPE_ARRAY:    
            {
                cout << "  Multi dimension variable lower/upper boud array --- " << endl;
                hr = PrintTypeSignatures(pMethodSig);
                if (FAILED(hr)) 
                    return COMError(hr, __FILE__, __LINE__);
                
                ULONG rank = ::CorSigUncompressData(pMethodSig);                                                    
                if (rank == 0) 
                {
                    cout << "    Rank: 0x00000000" << endl;
                }
                else 
                {
                    cout << "    Rank: 0x" << setw(8) << setfill('0') << rank << endl;
                    ULONG size = sizeof(ULONG) * rank;

                    ULONG sizesSize = ::CorSigUncompressData(pMethodSig);
                    _ASSERTE(sizesSize <= rank);
                    cout << "    Sizes size: 0x" << setw(8) << setfill('0') << sizesSize << endl;
                    
                    ULONG *pSizes = reinterpret_cast<ULONG*>(_malloca(size));
                    BOOST_SCOPE_EXIT((pSizes))
                    {
                        _freea(pSizes);
                    }
                    BOOST_SCOPE_EXIT_END
                    ::ZeroMemory(pSizes, size);
                    
                    for (ULONG i = 0; i < sizesSize; ++i)
                        pSizes[i] = ::CorSigUncompressData(pMethodSig);
                    
                    

                    ULONG lowersSize = ::CorSigUncompressData(pMethodSig);
                    _ASSERTE(lowersSize <= rank);
                    cout << "    Lowers size: 0x" << setw(8) << setfill('0') << lowersSize << endl;
                    
                    ULONG *pLowers = reinterpret_cast<ULONG*>(_malloca(size));
                    BOOST_SCOPE_EXIT((pLowers))
                    {
                        _freea(pLowers);
                    }
                    BOOST_SCOPE_EXIT_END
                    ::ZeroMemory(pLowers, size);

                    for (ULONG i = 0; i < lowersSize; ++i)
                        pLowers[i] = ::CorSigUncompressData(pMethodSig);
                    
                    
                    cout << dec;
                    for (ULONG i = 0; i < rank; ++i)
                    {
                        if (0 < pSizes[i])
                        {
                            cout << "        [" << pLowers[i] << "..." << pLowers[i] + pSizes[i] + 1 << "]" << endl;
                        }
                        else
                        {
                            cout << "        [" << pLowers[i] << "...?]" << endl;
                        }
                    }
                    cout << hex;
                }
            } 
            break;    
        case ELEMENT_TYPE_PINNED:
            cout << "  Pinned Type --- " << endl;
            hr = PrintTypeSignatures(pMethodSig);
            if (FAILED(hr)) 
                return COMError(hr, __FILE__, __LINE__);
            break;    
        case ELEMENT_TYPE_PTR:   
            cout << "  Pointer Type --- " << endl;
            hr = PrintTypeSignatures(pMethodSig);
            if (FAILED(hr)) 
                return COMError(hr, __FILE__, __LINE__);
            break;    
        case ELEMENT_TYPE_BYREF:   
            cout << "  ByRef Type --- " << endl;
            hr = PrintTypeSignatures(pMethodSig);
            if (FAILED(hr)) 
                return COMError(hr, __FILE__, __LINE__);
            break;    
        case ELEMENT_TYPE_END:    
        case ELEMENT_TYPE_SENTINEL:    
            cout << "  Unknown Type --- " << endl;
            break;                                                                  
    }
    return S_OK;
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
    //::_CrtDbgBreak();
    //::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
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
    using std::cout;
    using std::wcout;
    using std::uppercase;
    using std::hex;
    using std::dec;
    using std::setw;
    using std::setfill;
    using std::endl;
    using std::wstring;
    using std::wostringstream;
    using Urasandesu::NAnonym::min;
    using Urasandesu::NAnonym::SimpleBlob;
    namespace OpCodes = Urasandesu::NAnonym::MetaData::OpCodes;
    
    HRESULT hr = E_FAIL;
    cout << hex << uppercase;
    
    mdMethodDef mdmd = mdMethodDefNil;
    CComPtr<IMetaDataImport2> pImport;
    hr = m_pInfo->GetTokenAndMetaDataFromFunction(functionId, IID_IMetaDataImport2, 
                                                  reinterpret_cast<IUnknown**>(&pImport), 
                                                  &mdmd);
    if (FAILED(hr)) 
        return COMError(hr, __FILE__, __LINE__);
        
    cout << "MethodDef Token: 0x" << setw(8) << setfill('0') << mdmd << endl;



    ModuleID mid = NULL;
    {
        ClassID cid = NULL;
        mdMethodDef mdmd_ = mdMethodDefNil;
        hr = m_pInfo->GetFunctionInfo(functionId, &cid, &mid, &mdmd_);
        if (FAILED(hr)) 
            return COMError(hr, __FILE__, __LINE__);
    }
    cout << "Module ID: 0x" << setw(8) << setfill('0') << mid << endl;


    mdTypeDef mdtd = mdTypeDefNil;
    WCHAR methodName_[MAX_PATH] = { 0 };
    ULONG methodName_Size = sizeof(methodName_) / sizeof(WCHAR);
    ULONG methodName_Length = 0;
    DWORD methodAttr = 0;
    PCCOR_SIGNATURE pMethodSig = NULL;
    ULONG methodSigSize = 0;
    ULONG methodRVA = 0;
    DWORD methodImplFlag = 0;
    hr = pImport->GetMethodProps(mdmd, &mdtd, methodName_, methodName_Size, 
                                 &methodName_Length, &methodAttr, &pMethodSig, 
                                 &methodSigSize, &methodRVA, &methodImplFlag);
    if (FAILED(hr)) 
        return COMError(hr, __FILE__, __LINE__);

    wcout << "Method Name: " << methodName_ << endl;

    ULONG callConv = IMAGE_CEE_CS_CALLCONV_MAX;
    pMethodSig += ::CorSigUncompressData(pMethodSig, &callConv);
    cout << "Calling Convention: 0x" << setw(8) << setfill('0') << callConv << endl;

    ULONG paramCount = 0;
    pMethodSig += ::CorSigUncompressData(pMethodSig, &paramCount);
    cout << "Parameter Count: 0x" << setw(8) << setfill('0') << paramCount << endl;
    
    cout << "Return" << endl;
    hr = PrintTypeSignatures(pMethodSig);
    if (FAILED(hr)) 
        return COMError(hr, __FILE__, __LINE__);

    for (ULONG i = 0; i < paramCount; ++i)
    {
        cout << dec;
        cout << "Parameter[" << i << "]" << endl;
        cout << hex;
        
        hr = PrintTypeSignatures(pMethodSig);
        if (FAILED(hr)) 
            return COMError(hr, __FILE__, __LINE__);
    }





    BYTE const *pILFunctionBody = NULL;
    ULONG ilFunctionBodySize = 0;
    hr = m_pInfo->GetILFunctionBody(mid, mdmd, &pILFunctionBody, &ilFunctionBodySize);
    if (FAILED(hr)) 
        return COMError(hr, __FILE__, __LINE__);
    
    cout << "IL Function Body: 0x" << setw(8) << setfill('0') << reinterpret_cast<INT>(pILFunctionBody) << endl;
    cout << "IL Function Body Size: 0x" << setw(8) << setfill('0') << ilFunctionBodySize << endl;


    COR_ILMETHOD const *pILMethod = reinterpret_cast<COR_ILMETHOD*>(
                                                      const_cast<BYTE*>(pILFunctionBody));

    cout << "IsTiny?: 0x" << setw(8) << setfill('0') << pILMethod->Tiny.IsTiny() << endl;
    
    if (pILMethod->Fat.IsFat())
    {
        cout << "The method has Fat format header with following values: " << endl;
        cout << "  Size: 0x" << setw(8) << setfill('0') << pILMethod->Fat.GetSize() << endl;
        cout << "  Flags: 0x" << setw(8) << setfill('0') << pILMethod->Fat.GetFlags() << endl;
        cout << "  IsFat?: 0x" << setw(8) << setfill('0') << pILMethod->Fat.IsFat() << endl;
        cout << "  MaxStack: 0x" << setw(8) << setfill('0') << pILMethod->Fat.GetMaxStack() << endl;
        cout << "  LocalVarSigTok: 0x" << setw(8) << setfill('0') << pILMethod->Fat.GetLocalVarSigTok() << endl;
        cout << "  CodeSize: 0x" << setw(8) << setfill('0') << pILMethod->Fat.GetCodeSize() << endl;
        cout << "  Code: ";
        for (BYTE const *i = pILMethod->Fat.GetCode(), *i_end = i + pILMethod->Fat.GetCodeSize(); i != i_end; ++i)
            cout << setw(2) << setfill('0') << static_cast<INT>(*i) << " ";
        cout << endl;
        cout << "  Sect: 0x" << setw(8) << setfill('0') << pILMethod->Fat.GetSect() << endl;
    }
    else
    {
        cout << "The method has Tiny format header with following values: " << endl;
        cout << "  IsTiny?: 0x" << setw(8) << setfill('0') << pILMethod->Tiny.IsTiny() << endl;
        cout << "  MaxStack: 0x" << setw(8) << setfill('0') << pILMethod->Tiny.GetMaxStack() << endl;
        cout << "  LocalVarSigTok: 0x" << setw(8) << setfill('0') << pILMethod->Tiny.GetLocalVarSigTok() << endl;
        cout << "  CodeSize: 0x" << setw(8) << setfill('0') << pILMethod->Tiny.GetCodeSize() << endl;
        cout << "  Code: ";
        for (BYTE const *i = pILMethod->Tiny.GetCode(), *i_end = i + pILMethod->Tiny.GetCodeSize(); i != i_end; ++i)
            cout << setw(2) << setfill('0') << static_cast<INT>(*i) << " ";
        cout << endl;
        cout << "  Sect: 0x" << setw(8) << setfill('0') << pILMethod->Tiny.GetSect() << endl;
    }
    
    
    wstring methodName(methodName_);
    if (methodName == L"Print")
    {
        cout << "*********** This method is the instrumentation target!! ***********" << endl;
        
        CComPtr<IMetaDataEmit2> pEmit;
        hr = pImport->QueryInterface(IID_IMetaDataEmit2, 
                                     reinterpret_cast<void**>(&pEmit));
        if (FAILED(hr)) 
            return COMError(hr, __FILE__, __LINE__);

        mdString mdsMessage = mdStringNil;
        {
            wostringstream s;
            s << hex;
            s << L"Instrumented: 0x" << setw(8) << setfill(L'0') << mdmd;
            hr = pEmit->DefineUserString(s.str().c_str(), s.str().size(), &mdsMessage);
            if (FAILED(hr))
                return COMError(hr, __FILE__, __LINE__);
        }
        cout << "New message token is 0x" << setw(8) << setfill('0') << mdsMessage << endl;
        

        SimpleBlob sb;
        sb.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_LDSTR].byte2);
        sb.Put<DWORD>(mdsMessage);
        sb.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_RET].byte2);

        
        COR_ILMETHOD ilMethod;
        ::ZeroMemory(&ilMethod, sizeof(COR_ILMETHOD));
        ilMethod.Fat.SetMaxStack(1);
        ilMethod.Fat.SetCodeSize(sb.Size());
        ilMethod.Fat.SetLocalVarSigTok(mdTokenNil);
        ilMethod.Fat.SetFlags(0);
        
        unsigned headerSize = COR_ILMETHOD::Size(&ilMethod.Fat, false);
        unsigned totalSize = headerSize + sb.Size();
        
        CComPtr<IMethodMalloc> pMethodMalloc;
        hr = m_pInfo->GetILFunctionBodyAllocator(mid, &pMethodMalloc);
        if (FAILED(hr)) 
            return COMError(hr, __FILE__, __LINE__);

        BYTE *pNewILFunctionBody = reinterpret_cast<BYTE*>(pMethodMalloc->Alloc(totalSize));

        BYTE *pBuffer = pNewILFunctionBody;
        pBuffer += COR_ILMETHOD::Emit(headerSize, &ilMethod.Fat, false, pBuffer);
        ::memcpy_s(pBuffer, totalSize - headerSize, sb.Ptr(), sb.Size());
        
        cout << "  New IL Function Body: ";
        for (BYTE const *i = pNewILFunctionBody, *i_end = i + totalSize; i != i_end; ++i)
            cout << setw(2) << setfill('0') << static_cast<INT>(*i) << " ";
        cout << endl;

        hr = m_pInfo->SetILFunctionBody(mid, mdmd, pNewILFunctionBody);
        if (FAILED(hr)) 
            return COMError(hr, __FILE__, __LINE__);
    }
    
        
    
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
