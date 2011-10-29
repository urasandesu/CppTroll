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

// ICorProfilerCallback
HRESULT CExeWeaver::InitializeCore( 
    /* [in] */ IUnknown *pICorProfilerInfoUnk)
{
    using namespace Urasandesu::NAnonym;

    //::_CrtDbgBreak();
    //::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
    HRESULT hr = E_FAIL;
    
    hr = pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo2, 
                                              reinterpret_cast<void**>(&m_pInfo));
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));

    DWORD event_ = COR_PRF_MONITOR_JIT_COMPILATION;

    hr = m_pInfo->SetEventMask(event_);
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));

    return S_OK; 
}

HRESULT CExeWeaver::ShutdownCore(void)
{ 
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
    //using std::cout;
    //using std::dec;
    //using std::endl;
    //using std::hex;
    //using std::uppercase;
    //using std::wcout;
    //using std::wostringstream;
    //using std::wstring;
    //using Urasandesu::NAnonym::PadLeft;
    //using Urasandesu::NAnonym::SimpleBlob;
    
    HRESULT hr = E_FAIL;
    

    //////////////////////////////////////////////////////////////////////////////////////
    // Convert FunctionID to MethodDef token
    // 
    mdMethodDef mdmd = mdMethodDefNil;
    CComPtr<IMetaDataImport2> pImport;
    hr = m_pInfo->GetTokenAndMetaDataFromFunction(functionId, IID_IMetaDataImport2, 
                                                  reinterpret_cast<IUnknown**>(&pImport), 
                                                  &mdmd);
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
        
    cout << format("MethodDef Token: 0x%|1$08X|") % mdmd << endl;



    //////////////////////////////////////////////////////////////////////////////////////
    // Convert FunctionID to ModuleID
    // 
    ModuleID mid = NULL;
    {
        ClassID cid = NULL;
        mdMethodDef mdmd_ = mdMethodDefNil;
        hr = m_pInfo->GetFunctionInfo(functionId, &cid, &mid, &mdmd_);
        if (FAILED(hr)) 
            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
    }
    cout << format("Module ID: 0x%|1$08X|") % mid << endl;



    //////////////////////////////////////////////////////////////////////////////////////
    // Get the method properties
    // * Actually, these are used to identify the instrumentation target.
    // 
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
        BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));

    wcout << "Method Name: " << methodName_ << endl;

    ULONG callConv = IMAGE_CEE_CS_CALLCONV_MAX;
    pMethodSig += ::CorSigUncompressData(pMethodSig, &callConv);
    cout << format("Calling Convention: 0x%|1$08X|") % callConv << endl;

    ULONG paramCount = 0;
    pMethodSig += ::CorSigUncompressData(pMethodSig, &paramCount);
    cout << format("Parameter Count: 0x%|1$08X|") % paramCount << endl;
    
    CorElementType retType = ELEMENT_TYPE_END;
    pMethodSig += ::CorSigUncompressElementType(pMethodSig, &retType);
    cout << format("Return Type: 0x%|1$08X|") % retType << endl;
    if (retType != ELEMENT_TYPE_STRING)
        return S_OK;

    cout << "Target Return Type!" << endl;
    //cout << "Return" << endl;
    //hr = PrintTypeSignatures(pMethodSig);
    //if (FAILED(hr)) 
    //    return COMError(hr, __FILE__, __LINE__);

    //for (ULONG i = 0; i < paramCount; ++i)
    //{
    //    cout << dec;
    //    cout << "Parameter[" << i << "]" << endl;
    //    cout << hex;
    //    
    //    hr = PrintTypeSignatures(pMethodSig);
    //    if (FAILED(hr)) 
    //        return COMError(hr, __FILE__, __LINE__);
    //}



    //////////////////////////////////////////////////////////////////////////////////////
    // Get the IL method body
    // * Actually, these are replaced by the user code called monkey patching.
    // 
    BYTE const *pILFunctionBody = NULL;
    ULONG ilFunctionBodySize = 0;
    hr = m_pInfo->GetILFunctionBody(mid, mdmd, &pILFunctionBody, &ilFunctionBodySize);
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
    
    cout << format("IL Function Body: 0x%|1$08X|") % reinterpret_cast<INT>(pILFunctionBody) << endl;
    cout << format("IL Function Body Size: 0x%|1$d|") % ilFunctionBodySize << endl;


    COR_ILMETHOD const *pILMethod = reinterpret_cast<COR_ILMETHOD*>(
                                                      const_cast<BYTE*>(pILFunctionBody));

    cout << format("IsTiny?: 0x%|1$08X|") % pILMethod->Tiny.IsTiny() << endl;
    
    //if (pILMethod->Fat.IsFat())
    //{
    //    cout << "The method has Fat format header with following values: " << endl;
    //    cout << "  Size: 0x" << PadLeft(8, '0') << pILMethod->Fat.GetSize() << endl;
    //    cout << "  Flags: 0x" << PadLeft(8, '0') << pILMethod->Fat.GetFlags() << endl;
    //    cout << "  IsFat?: 0x" << PadLeft(8, '0') << pILMethod->Fat.IsFat() << endl;
    //    cout << "  MaxStack: 0x" << PadLeft(8, '0') << pILMethod->Fat.GetMaxStack() << endl;
    //    cout << "  LocalVarSigTok: 0x" << PadLeft(8, '0') << pILMethod->Fat.GetLocalVarSigTok() << endl;
    //    cout << "  CodeSize: 0x" << PadLeft(8, '0') << pILMethod->Fat.GetCodeSize() << endl;
    //    cout << "  Code: ";
    //    for (BYTE const *i = pILMethod->Fat.GetCode(), *i_end = i + pILMethod->Fat.GetCodeSize(); i != i_end; ++i)
    //        cout << PadLeft(2, '0') << static_cast<INT>(*i) << " ";
    //    cout << endl;
    //    cout << "  Sect: 0x" << PadLeft(8, '0') << pILMethod->Fat.GetSect() << endl;
    //}
    //else
    //{
    //    cout << "The method has Tiny format header with following values: " << endl;
    //    cout << "  IsTiny?: 0x" << PadLeft(8, '0') << pILMethod->Tiny.IsTiny() << endl;
    //    cout << "  MaxStack: 0x" << PadLeft(8, '0') << pILMethod->Tiny.GetMaxStack() << endl;
    //    cout << "  LocalVarSigTok: 0x" << PadLeft(8, '0') << pILMethod->Tiny.GetLocalVarSigTok() << endl;
    //    cout << "  CodeSize: 0x" << PadLeft(8, '0') << pILMethod->Tiny.GetCodeSize() << endl;
    //    cout << "  Code: ";
    //    for (BYTE const *i = pILMethod->Tiny.GetCode(), *i_end = i + pILMethod->Tiny.GetCodeSize(); i != i_end; ++i)
    //        cout << PadLeft(2, '0') << static_cast<INT>(*i) << " ";
    //    cout << endl;
    //    cout << "  Sect: 0x" << PadLeft(8, '0') << pILMethod->Tiny.GetSect() << endl;
    //}



    //////////////////////////////////////////////////////////////////////////////////////
    // Instrument new IL method body
    // * This time, I decided to replace the method named "Print" to the method which returns the fixed sentence.
    // 
    wstring methodName(methodName_);
    if (methodName == L"Print")
    {
        cout << "*********** This method is the instrumentation target!! ***********" << endl;
        
        CComPtr<IMetaDataEmit2> pEmit;
        hr = pImport->QueryInterface(IID_IMetaDataEmit2, 
                                     reinterpret_cast<void**>(&pEmit));
        if (FAILED(hr)) 
            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));

        mdString mdsMessage = mdStringNil;
        {
            wostringstream s;
            s << hex;
            s << wformat(L"!!!!!!!!!!!!!!!!!!!! Instrumented !!!!!!!!!!!!!!!!!!!!: 0x%|1$08X|") % mdmd;
            hr = pEmit->DefineUserString(s.str().c_str(), s.str().size(), &mdsMessage);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
        }
        cout << format("New message token is 0x%|1$08X|") % mdsMessage << endl;
        

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
            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));

        BYTE *pNewILFunctionBody = reinterpret_cast<BYTE*>(pMethodMalloc->Alloc(totalSize));

        BYTE *pBuffer = pNewILFunctionBody;
        pBuffer += COR_ILMETHOD::Emit(headerSize, &ilMethod.Fat, false, pBuffer);
        ::memcpy_s(pBuffer, totalSize - headerSize, sb.Ptr(), sb.Size());
        
        cout << "  New IL Function Body: ";
        for (BYTE const *i = pNewILFunctionBody, *i_end = i + totalSize; i != i_end; ++i)
            cout << format("%|1$02X|") % static_cast<INT>(*i) << " ";
        cout << endl;

        hr = m_pInfo->SetILFunctionBody(mid, mdmd, pNewILFunctionBody);
        if (FAILED(hr)) 
            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
    }
    
        
    
    return S_OK;
}
