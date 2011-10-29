// ExeWeaver.cpp : CExeWeaver の実装

#include "stdafx.h"
#include "ExeWeaver.h"

// CExeWeaver

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

HRESULT CExeWeaver::InitializeCore( 
    /* [in] */ IUnknown *pICorProfilerInfoUnk)
{
    using namespace std;
    using namespace Urasandesu::NAnonym;
    HRESULT hr = E_FAIL;


    // Reset the timer.
    m_timer.restart();
    

    // Initialize the profiling API.
    hr = pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo2, 
                                              reinterpret_cast<void**>(&m_pInfo));
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));


    // Set a value that specifies the types of events for which the profiler 
    // wants to receive notification from CLR.
    DWORD event_ = COR_PRF_MONITOR_JIT_COMPILATION;
    hr = m_pInfo->SetEventMask(event_);
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));

    
    // Get the name of the target method and the new message.
    m_targetMethodName = wstring(CA2W(Environment::GetEnvironmentVariable("NANONYM_TARGET_METHOD").c_str()));
    m_newMessage = wstring(CA2W(Environment::GetEnvironmentVariable("NANONYM_NEW_MESSAGE").c_str()));


    return S_OK; 
}

HRESULT CExeWeaver::ShutdownCore(void)
{ 
    using namespace std;
    using namespace boost;
    
    // Display the time elapsed.
    cout << format("Time Elapsed: %|1$f|s") % m_timer.elapsed() << endl;

    return S_OK; 
}

HRESULT CExeWeaver::JITCompilationStartedCore( 
    /* [in] */ FunctionID functionId,
    /* [in] */ BOOL fIsSafeToBlock)
{
    namespace OpCodes = Urasandesu::NAnonym::MetaData::OpCodes;
    using namespace std;
    using namespace boost;
    using namespace Urasandesu::NAnonym;
    HRESULT hr = E_FAIL;
    

    // Convert FunctionID to MethodDef token.
    mdMethodDef mdmd = mdMethodDefNil;
    CComPtr<IMetaDataImport2> pImport;
    hr = m_pInfo->GetTokenAndMetaDataFromFunction(functionId, IID_IMetaDataImport2, 
                                                  reinterpret_cast<IUnknown**>(&pImport), 
                                                  &mdmd);
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
    

    // Get the properties of this method.
    mdTypeDef mdtd = mdTypeDefNil;
    WCHAR methodName[MAX_SYM_NAME] = { 0 };
    {
        ULONG methodNameSize = sizeof(methodName);
        DWORD methodAttr = 0;
        PCCOR_SIGNATURE pMethodSig = NULL;
        ULONG methodSigSize = 0;
        ULONG methodRVA = 0;
        DWORD methodImplFlag = 0;
        hr = pImport->GetMethodProps(mdmd, &mdtd, methodName, methodNameSize, 
                                     &methodNameSize, &methodAttr, &pMethodSig, 
                                     &methodSigSize, &methodRVA, &methodImplFlag);
        if (FAILED(hr)) 
            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
        
        ULONG callConv = IMAGE_CEE_CS_CALLCONV_MAX;
        pMethodSig += ::CorSigUncompressData(pMethodSig, &callConv);

        ULONG paramCount = 0;
        pMethodSig += ::CorSigUncompressData(pMethodSig, &paramCount);

        CorElementType retType = ELEMENT_TYPE_END;
        pMethodSig += ::CorSigUncompressElementType(pMethodSig, &retType);
        if (retType != ELEMENT_TYPE_STRING)
            return S_OK;
    }
    

    // Get the properties of type that this method is declared.
    WCHAR typeName[MAX_SYM_NAME] = { 0 };
    {
        ULONG typeNameSize = sizeof(typeName);
        DWORD typeAttr = 0;
        mdToken mdtTypeExtends = mdTokenNil;
        hr = pImport->GetTypeDefProps(mdtd, typeName, typeNameSize, &typeNameSize, 
                                      &typeAttr, &mdtTypeExtends);
        if (FAILED(hr)) 
            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
    }
    

    // Check, is this method the instrumentation target?
    wstring methodFullName(typeName);
    methodFullName += L".";
    methodFullName += methodName;
    if (methodFullName != m_targetMethodName)
        return S_OK;
    

    // Define the new message to #US heap.
    CComPtr<IMetaDataEmit2> pEmit;
    hr = pImport->QueryInterface(IID_IMetaDataEmit2, 
                                 reinterpret_cast<void**>(&pEmit));
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));

    mdString mdsMessage = mdStringNil;
    hr = pEmit->DefineUserString(m_newMessage.c_str(), m_newMessage.size(), &mdsMessage);
    if (FAILED(hr))
        BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
    

    // Emit the new IL method body.
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
    

    // Allocate the area for new IL method body and set it.
    ModuleID mid = NULL;
    {
        ClassID cid = NULL;
        mdMethodDef mdmd_ = mdMethodDefNil;
        hr = m_pInfo->GetFunctionInfo(functionId, &cid, &mid, &mdmd_);
        if (FAILED(hr)) 
            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
    }

    CComPtr<IMethodMalloc> pMethodMalloc;
    hr = m_pInfo->GetILFunctionBodyAllocator(mid, &pMethodMalloc);
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));

    BYTE *pNewILFunctionBody = reinterpret_cast<BYTE*>(pMethodMalloc->Alloc(totalSize));

    BYTE *pBuffer = pNewILFunctionBody;
    pBuffer += COR_ILMETHOD::Emit(headerSize, &ilMethod.Fat, false, pBuffer);
    ::memcpy_s(pBuffer, totalSize - headerSize, sb.Ptr(), sb.Size());

    hr = m_pInfo->SetILFunctionBody(mid, mdmd, pNewILFunctionBody);
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
    

    return S_OK;
}
