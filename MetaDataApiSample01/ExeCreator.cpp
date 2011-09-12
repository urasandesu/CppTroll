// ExeCreator.cpp : CExeCreator の実装

#include "stdafx.h"
#include "ExeCreator.h"

// CExeCreator

namespace OpCodes {

    enum Types_ {
        #define OPDEF(canonicalName, stringName, stackBehaviour0, stackBehaviour1, \
                      operandParams, opcodeKind, length, byte1, byte2, controlFlow) \
                      canonicalName,
        #include "opcode.def"
        #undef  OPDEF
        CEE_COUNT,
        CEE_UNREACHED
    };
    
    struct CEncoding {
        BYTE byte1;
        BYTE byte2;
    };

    CEncoding const Encodings[] = {
        #define OPDEF(canonicalName, stringName, stackBehaviour0, stackBehaviour1, \
                      operandParams, opcodeKind, length, byte1, byte2, controlFlow) \
                      { byte1, byte2 },
        #include "opcode.def"
        #undef  OPDEF
        { 0, 0 },
        { 0, 0 }
    };

}   // namespace OpCodes_


namespace Urasandesu { namespace NAnonym {
    
    using boost::enable_if;
    using boost::system::error_category;
    using boost::system::error_code;
    using boost::system::is_error_code_enum;
    
    class CSystemError : public error_code
    {
    public:
        CSystemError() : error_code() { }
        CSystemError(int val, const error_category& cat)
            : error_code(val, cat), 
              m_bstrMessage(CComBSTR(category().message(value()).data()))
        { 
        }

        template <class ErrorCodeEnum>
        CSystemError(ErrorCodeEnum e, 
                     typename enable_if<is_error_code_enum<ErrorCodeEnum>>::type* = 0)
        {
            using namespace boost::system::errc;
            *this = make_error_code(e);
        }
        
        CComBSTR GetBSTRMessage() const { return m_bstrMessage; }

    private:
        CComBSTR m_bstrMessage;
    };
    
    
    class CSimpleBlob
    {
        typedef CQuickArray<BYTE> ByteArray;        

        ByteArray m_buffer;
        BYTE *m_pCurrent;

    public:
        CSimpleBlob() : m_pCurrent(m_buffer.Ptr()) { }

        template<class T>
        HRESULT Put(T val)
        {
            using namespace boost;            
            using namespace boost::mpl;
            
            BOOST_MPL_ASSERT((or_<is_arithmetic<T>, is_pod<T>>));

            return Put(&val, sizeof(T));
        }
        
        HRESULT Put(void const *p, SIZE_T size)
        {
            _ASSERT(0 <= size);
            HRESULT hr = m_buffer.ReSizeNoThrow(m_buffer.Size() + size);
            if (FAILED(hr))
                return hr;
            ::memcpy_s(m_pCurrent, size, p, size);
            m_pCurrent += size;
            return S_OK;
        }
        
        BYTE *Ptr()
        {
            return m_buffer.Ptr();
        }
        
        BYTE const *Ptr() const
        {
            return m_buffer.Ptr();
        }
        
        SIZE_T Size() const
        { 
            return m_buffer.Size();
        }

        SIZE_T MaxSize() const
        { 
            return m_buffer.MaxSize();
        }

        BYTE& operator[] (SIZE_T ix)
        { 
            return m_buffer[ix];
        }

        const BYTE& operator[] (SIZE_T ix) const
        { 
            return m_buffer[ix];
        }
    };
    
}}  // namespace Urasandesu { namespace NAnonym {

// TODO: ファイルパス、行番号などをマクロで出力できるよう拡張する。
HRESULT CExeCreator::SystemError(DWORD errorNo)
{
    using Urasandesu::NAnonym::CSystemError;
    using boost::system::system_category;

    return Error(CSystemError(errorNo, system_category()).GetBSTRMessage());
}

// TODO: ファイルパス、行番号などをマクロで出力できるよう拡張する。
HRESULT CExeCreator::COMError(HRESULT hr)
{
    return Error(_com_error(hr).ErrorMessage());
}


STDMETHODIMP CExeCreator::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* arr[] = 
    {
        &IID_IExeCreator
    };

    for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (InlineIsEqualGUID(*arr[i],riid))
            return S_OK;
    }
    return S_FALSE;
}

STDMETHODIMP CExeCreator::Create(BSTR fileName)
{
    using boost::filesystem::path;
    using std::auto_ptr;
    using std::string;
    using std::wstring;    
    using Urasandesu::NAnonym::CSimpleBlob;

    HRESULT hr = E_FAIL;

    //////////////////////////////////////////////////////////////////////////////////////
    // Import meta data with using IMetaDataImport
    // 

    //////////////////////////////////////////////////////////////////////////////////////
    // Open mscorlib.dll to get importing members, types and the assembly
    // 
    path corSystemDirectoryPath;
    path mscorlibPath;
    {
        WCHAR buffer[MAX_PATH] = { 0 };
        DWORD length = 0;
        hr = ::GetCORSystemDirectory(buffer, MAX_PATH, &length);
        if (FAILED(hr)) 
            return COMError(hr);

        corSystemDirectoryPath = buffer;
        mscorlibPath = buffer;
        mscorlibPath /= L"mscorlib.dll";
    }

    CComPtr<IMetaDataDispenserEx> pDispMSCorLib;
    hr = ::CoCreateInstance(CLSID_CorMetaDataDispenser, NULL, CLSCTX_INPROC_SERVER, 
                            IID_IMetaDataDispenserEx, 
                            reinterpret_cast<void**>(&pDispMSCorLib));
    if (FAILED(hr))
        return COMError(hr);
    
    
    CComPtr<IMetaDataImport2> pImpMSCorLib;
    hr = pDispMSCorLib->OpenScope(mscorlibPath.wstring().c_str(), ofRead, 
                                  IID_IMetaDataImport2, 
                                  reinterpret_cast<IUnknown**>(&pImpMSCorLib));
    if (FAILED(hr))
        return COMError(hr);



    //////////////////////////////////////////////////////////////////////////////////////
    // Find importing types
    // 
    mdTypeDef mdtdObject = mdTypeDefNil;
    hr = pImpMSCorLib->FindTypeDefByName(L"System.Object", NULL, &mdtdObject);
    if (FAILED(hr))
        return COMError(hr);
    
    mdTypeDef mdtdCompilationRelaxationsAttribute = mdTypeDefNil;
    hr = pImpMSCorLib->FindTypeDefByName(
                       L"System.Runtime.CompilerServices.CompilationRelaxationsAttribute",
                       NULL, &mdtdCompilationRelaxationsAttribute);
    if (FAILED(hr))
        return COMError(hr);
    
    mdTypeDef mdtdRuntimeCompatibilityAttribute = mdTypeDefNil;
    hr = pImpMSCorLib->FindTypeDefByName(
                         L"System.Runtime.CompilerServices.RuntimeCompatibilityAttribute",
                         NULL, &mdtdRuntimeCompatibilityAttribute);
    if (FAILED(hr))
        return COMError(hr);
    
    mdTypeDef mdtdConsole = mdTypeDefNil;
    hr = pImpMSCorLib->FindTypeDefByName(L"System.Console", NULL, &mdtdConsole);
    if (FAILED(hr))
        return COMError(hr);



    //////////////////////////////////////////////////////////////////////////////////////
    // Find importing members
    // 
    mdMethodDef mdmdCompilationRelaxationsAttributeCtor = mdMethodDefNil;
    {
        COR_SIGNATURE pSigBlob[] = { 
            IMAGE_CEE_CS_CALLCONV_HASTHIS,  // HASTHIS 
            1,                              // ParamCount
            ELEMENT_TYPE_VOID,              // RetType
            ELEMENT_TYPE_I4                 // ParamType
        };
        ULONG sigBlobSize = sizeof(pSigBlob) / sizeof(COR_SIGNATURE);
        hr = pImpMSCorLib->FindMethod(mdtdCompilationRelaxationsAttribute, L".ctor", 
                                      pSigBlob, sigBlobSize, 
                                      &mdmdCompilationRelaxationsAttributeCtor);
        if (FAILED(hr))
            return COMError(hr);
    }
    
    mdMethodDef mdmdRuntimeCompatibilityAttributeCtor = mdMethodDefNil;
    {
        COR_SIGNATURE pSigBlob[] = { 
            IMAGE_CEE_CS_CALLCONV_HASTHIS,  // HASTHIS  
            0,                              // ParamCount
            ELEMENT_TYPE_VOID               // RetType
        };                                  
        ULONG sigBlobSize = sizeof(pSigBlob) / sizeof(COR_SIGNATURE);
        hr = pImpMSCorLib->FindMethod(mdtdRuntimeCompatibilityAttribute, L".ctor", 
                                      pSigBlob, sigBlobSize, 
                                      &mdmdRuntimeCompatibilityAttributeCtor);
        if (FAILED(hr))
            return COMError(hr);
    }
    
    mdMethodDef mdmdConsoleWriteLine = mdMethodDefNil;
    {
        COR_SIGNATURE pSigBlob[] = { 
            IMAGE_CEE_CS_CALLCONV_DEFAULT,  // DEFAULT  
            1,                              // ParamCount
            ELEMENT_TYPE_VOID,              // RetType
            ELEMENT_TYPE_STRING             // ParamType
        };
        ULONG sigBlobSize = sizeof(pSigBlob) / sizeof(COR_SIGNATURE);
        hr = pImpMSCorLib->FindMethod(mdtdConsole, L"WriteLine", pSigBlob, sigBlobSize, 
                                      &mdmdConsoleWriteLine);            
        
        if (FAILED(hr))
            return COMError(hr);
    }
    
    mdMethodDef mdmdObjectCtor = mdMethodDefNil;
    {
        COR_SIGNATURE pSigBlob[] = { 
            IMAGE_CEE_CS_CALLCONV_HASTHIS,  // HASTHIS  
            0,                              // ParamCount
            ELEMENT_TYPE_VOID               // RetType
        };                                  
        ULONG sigBlobSize = sizeof(pSigBlob) / sizeof(COR_SIGNATURE);
        hr = pImpMSCorLib->FindMethod(mdtdObject, L".ctor", pSigBlob, sigBlobSize, 
                                      &mdmdObjectCtor);            
        
        if (FAILED(hr))
            return COMError(hr);
    }



    //////////////////////////////////////////////////////////////////////////////////////
    // Prepare importing assembly
    // 
    CComPtr<IMetaDataAssemblyImport> pAsmImpMSCorLib;
    hr = pImpMSCorLib->QueryInterface(IID_IMetaDataAssemblyImport, 
                                      reinterpret_cast<void**>(&pAsmImpMSCorLib));
    if (FAILED(hr))
        return COMError(hr);

    mdAssembly mdaMSCorLib = mdAssemblyNil;
    hr = pAsmImpMSCorLib->GetAssemblyFromScope(&mdaMSCorLib);
    if (FAILED(hr))
        return COMError(hr);

    auto_ptr<PublicKeyBlob> pMSCorLibPubKey;
    DWORD msCorLibPubKeySize = 0;
    auto_ptr<WCHAR> msCorLibName;
    ASSEMBLYMETADATA amdMSCorLib;
    ::ZeroMemory(&amdMSCorLib, sizeof(ASSEMBLYMETADATA));
    DWORD msCorLibAsmFlags = 0;
    {
        ULONG nameSize = 0;
        DWORD asmFlags = 0;
        hr = pAsmImpMSCorLib->GetAssemblyProps(mdaMSCorLib, NULL, NULL, NULL, NULL, 0, 
                                               &nameSize, &amdMSCorLib, 
                                               &asmFlags);
        if (FAILED(hr))
            return COMError(hr);

        msCorLibAsmFlags |= (asmFlags & ~afPublicKey);
        msCorLibName = auto_ptr<WCHAR>(new WCHAR[nameSize]);
        amdMSCorLib.szLocale = amdMSCorLib.cbLocale ? 
                                    new WCHAR[amdMSCorLib.cbLocale] : NULL;
        amdMSCorLib.rOS = amdMSCorLib.ulOS ? new OSINFO[amdMSCorLib.ulOS] : NULL;
        amdMSCorLib.rProcessor = amdMSCorLib.ulProcessor ? 
                                    new ULONG[amdMSCorLib.ulProcessor] : NULL;

        void *pPubKey = NULL;
        hr = pAsmImpMSCorLib->GetAssemblyProps(mdaMSCorLib, 
                                               const_cast<const void**>(&pPubKey), 
                                               &msCorLibPubKeySize, NULL, 
                                               msCorLibName.get(), nameSize, NULL, 
                                               &amdMSCorLib, NULL);
        if (FAILED(hr))
            return COMError(hr);

        if (msCorLibPubKeySize)
            if (!::StrongNameTokenFromPublicKey(reinterpret_cast<BYTE*>(pPubKey), 
                                                msCorLibPubKeySize, 
                                                reinterpret_cast<BYTE**>(&pPubKey), 
                                                &msCorLibPubKeySize))
                return COMError(::StrongNameErrorInfo());

        pMSCorLibPubKey = auto_ptr<PublicKeyBlob>(
                        reinterpret_cast<PublicKeyBlob*>(new BYTE[msCorLibPubKeySize]));
        ::memcpy_s(pMSCorLibPubKey.get(), msCorLibPubKeySize, pPubKey, 
                   msCorLibPubKeySize);

        if (msCorLibPubKeySize)
            ::StrongNameFreeBuffer(reinterpret_cast<BYTE*>(pPubKey));
    }






    //////////////////////////////////////////////////////////////////////////////////////
    // Emit meta data with using IMetaDataEmit
    // 

    //////////////////////////////////////////////////////////////////////////////////////
    // Define hello.exe to store emitting members, types and the assembly
    // 
    CComPtr<IMetaDataDispenserEx> pDispHello;
    hr = ::CoCreateInstance(CLSID_CorMetaDataDispenser, NULL, CLSCTX_INPROC_SERVER, 
                                       IID_IMetaDataDispenserEx, 
                                       reinterpret_cast<void**>(&pDispHello));
    if (FAILED(hr))
        return COMError(hr);

    CComPtr<IMetaDataEmit2> pEmtHello;
    hr = pDispHello->DefineScope(CLSID_CorMetaDataRuntime, 0, IID_IMetaDataEmit2, 
                                 reinterpret_cast<IUnknown**>(&pEmtHello));
    if (FAILED(hr))
        return COMError(hr);



    //////////////////////////////////////////////////////////////////////////////////////
    // Prepare emitting assembly
    // 
    CComPtr<IMetaDataAssemblyEmit> pAsmEmtHello;
    hr = pEmtHello->QueryInterface(IID_IMetaDataAssemblyEmit, 
                                   reinterpret_cast<void**>(&pAsmEmtHello));
    if (FAILED(hr))
        return COMError(hr);


    //////////////////////////////////////////////////////////////////////////////////////
    // Create AssemblyRef table
    // 
    mdAssemblyRef mdarMSCorLib = mdAssemblyRefNil;
    hr = pAsmEmtHello->DefineAssemblyRef(pMSCorLibPubKey.get(), msCorLibPubKeySize, 
                                         msCorLibName.get(), &amdMSCorLib, 
                                         NULL, 0, 
                                         msCorLibAsmFlags, &mdarMSCorLib);
    if (FAILED(hr))
        return COMError(hr);
    


    //////////////////////////////////////////////////////////////////////////////////////
    // Create TypeRef table
    // 
    mdTypeRef mdtrObject = mdTypeRefNil;
    hr = pEmtHello->DefineTypeRefByName(mdarMSCorLib, L"System.Object", &mdtrObject);
    if (FAILED(hr))
        return COMError(hr);

    mdTypeRef mdtrCompilationRelaxationsAttribute = mdTypeRefNil;
    hr = pEmtHello->DefineTypeRefByName(mdarMSCorLib, 
                       L"System.Runtime.CompilerServices.CompilationRelaxationsAttribute", 
                       &mdtrCompilationRelaxationsAttribute);
    if (FAILED(hr))
        return COMError(hr);

    mdTypeRef mdtrRuntimeCompatibilityAttribute = mdTypeRefNil;
    hr = pEmtHello->DefineTypeRefByName(mdarMSCorLib, 
                         L"System.Runtime.CompilerServices.RuntimeCompatibilityAttribute", 
                         &mdtrRuntimeCompatibilityAttribute);
    if (FAILED(hr))
        return COMError(hr);

    mdTypeRef mdtrConsole = mdTypeRefNil;
    hr = pEmtHello->DefineTypeRefByName(mdarMSCorLib, L"System.Console", &mdtrConsole);
    if (FAILED(hr))
        return COMError(hr);



    //////////////////////////////////////////////////////////////////////////////////////
    // Create MemberRef table
    // 
    mdMemberRef mdmrCompilationRelaxationsAttributeCtor = mdMemberRefNil;
    hr = pEmtHello->DefineImportMember(pAsmImpMSCorLib, NULL, 0, pImpMSCorLib, 
                                       mdmdCompilationRelaxationsAttributeCtor, 
                                       pAsmEmtHello, 
                                       mdtrCompilationRelaxationsAttribute, 
                                       &mdmrCompilationRelaxationsAttributeCtor);
    if (FAILED(hr))
        return COMError(hr);

    mdMemberRef mdmrRuntimeCompatibilityAttributeCtor = mdMemberRefNil;
    hr = pEmtHello->DefineImportMember(pAsmImpMSCorLib, NULL, 0, pImpMSCorLib, 
                                       mdmdRuntimeCompatibilityAttributeCtor, 
                                       pAsmEmtHello, 
                                       mdtrRuntimeCompatibilityAttribute, 
                                       &mdmrRuntimeCompatibilityAttributeCtor);
    if (FAILED(hr))
        return COMError(hr);

    mdMemberRef mdmrConsoleWriteLine = mdMemberRefNil;
    hr = pEmtHello->DefineImportMember(pAsmImpMSCorLib, NULL, 0, pImpMSCorLib, 
                                       mdmdConsoleWriteLine, 
                                       pAsmEmtHello, 
                                       mdtrConsole, 
                                       &mdmrConsoleWriteLine);
    if (FAILED(hr))
        return COMError(hr);

    mdMemberRef mdmrObjectCtor = mdMemberRefNil;
    hr = pEmtHello->DefineImportMember(pAsmImpMSCorLib, NULL, 0, pImpMSCorLib, 
                                       mdmdObjectCtor, 
                                       pAsmEmtHello, 
                                       mdtrObject, 
                                       &mdmrObjectCtor);
    if (FAILED(hr))
        return COMError(hr);



    //////////////////////////////////////////////////////////////////////////////////////
    // Create Assembly table
    // 
    mdAssembly mdaHello = mdAssemblyNil;
    ASSEMBLYMETADATA amdHello;
    ::ZeroMemory(&amdHello, sizeof(ASSEMBLYMETADATA));
    hr = pAsmEmtHello->DefineAssembly(NULL, 0, CALG_SHA1, L"hello", &amdHello, afPA_None, 
                                      &mdaHello);
    if (FAILED(hr))
        return COMError(hr);



    //////////////////////////////////////////////////////////////////////////////////////
    // Create CustomAttribute table
    // 
    WORD const CustomAttributeProlog = 0x0001;

    mdCustomAttribute mdcaCompilationRelaxationsAttribute = mdCustomAttributeNil;
    {
        CSimpleBlob sb;
        sb.Put<WORD>(CustomAttributeProlog);        // Prolog
        sb.Put<DWORD>(8);                           // FixedArg, int32: 8
        sb.Put<WORD>(0);                            // NumNamed, Count: 0
        hr = pEmtHello->DefineCustomAttribute(mdaHello, 
                                              mdmrCompilationRelaxationsAttributeCtor, 
                                              sb.Ptr(), 
                                              sb.Size(), 
                                              &mdcaCompilationRelaxationsAttribute);
        if (FAILED(hr))
            return COMError(hr);
    }

    mdCustomAttribute mdcaRuntimeCompatibilityAttribute = mdCustomAttributeNil;
    {
        CSimpleBlob sb;
        sb.Put<WORD>(CustomAttributeProlog);        // Prolog
        sb.Put<WORD>(1);                            // NumNamed, Count: 1
        sb.Put<BYTE>(SERIALIZATION_TYPE_PROPERTY);  // PROPERTY
        sb.Put<BYTE>(ELEMENT_TYPE_BOOLEAN);         // FieldOrPropType: bool
        {
            string name("WrapNonExceptionThrows");
            sb.Put<BYTE>(name.size());              // Name Length: 22
            sb.Put(name.c_str(), name.size());      // Name: "WrapNonExceptionThrows"
        }
        sb.Put<BYTE>(1);                            // FixedArg, bool: 1
        hr = pEmtHello->DefineCustomAttribute(mdaHello, 
                                              mdmrRuntimeCompatibilityAttributeCtor, 
                                              sb.Ptr(), 
                                              sb.Size(), 
                                              &mdcaRuntimeCompatibilityAttribute);
        if (FAILED(hr))
            return COMError(hr);
    }



    //////////////////////////////////////////////////////////////////////////////////////
    // Create TypeDef table
    // 
    mdTypeDef mdtdMainApp = mdTypeDefNil;
    hr = pEmtHello->DefineTypeDef(L"MainApp", tdNotPublic | tdBeforeFieldInit, mdtrObject, 
                                  NULL, &mdtdMainApp);
    if (FAILED(hr))
        return COMError(hr);



    //////////////////////////////////////////////////////////////////////////////////////
    // Create MethodDef table
    // 
    mdMethodDef mdmdMainAppMain = mdMethodDefNil;
    {
        COR_SIGNATURE pSigBlob[] = {
            IMAGE_CEE_CS_CALLCONV_DEFAULT,  // DEFAULT   
            0,                              // ParamCount
            ELEMENT_TYPE_VOID               // RetType
        };                                  
        ULONG sigBlobSize = sizeof(pSigBlob) / sizeof(COR_SIGNATURE);
        hr = pEmtHello->DefineMethod(mdtdMainApp, L"Main", 
                                     fdPublic | mdHideBySig | mdStatic, pSigBlob, 
                                     sigBlobSize, 0, 0, &mdmdMainAppMain);
        if (FAILED(hr))
            return COMError(hr);
    }

    mdMethodDef mdmdMainAppCtor = mdMethodDefNil;
    {
        COR_SIGNATURE pSigBlob[] = {
            IMAGE_CEE_CS_CALLCONV_HASTHIS,  // HASTHIS  
            0,                              // ParamCount
            ELEMENT_TYPE_VOID               // RetType
        };                                  
        ULONG sigBlobSize = sizeof(pSigBlob) / sizeof(COR_SIGNATURE);
        hr = pEmtHello->DefineMethod(mdtdMainApp, L".ctor", 
                                     fdPublic | mdHideBySig | mdSpecialName, pSigBlob, 
                                     sigBlobSize, 0, 0, &mdmdMainAppCtor);
        if (FAILED(hr))
            return COMError(hr);
    }



    //////////////////////////////////////////////////////////////////////////////////////
    // Create #US stream
    // 
    mdString mdsHelloWorld = mdStringNil;
    {
        wstring text(L"Hello World!");
        hr = pEmtHello->DefineUserString(text.c_str(), text.size(), &mdsHelloWorld);
        if (FAILED(hr))
            return COMError(hr);
    }



    //////////////////////////////////////////////////////////////////////////////////////
    // Set Module name
    hr = pEmtHello->SetModuleProps(L"hello.exe");
    if (FAILED(hr))
        return COMError(hr);






    //////////////////////////////////////////////////////////////////////////////////////
    // Emit Method body
    // 
    CSimpleBlob mbMainAppMain;
    mbMainAppMain.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_NOP].byte2);
    mbMainAppMain.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_LDSTR].byte2);
    mbMainAppMain.Put<DWORD>(mdsHelloWorld);
    mbMainAppMain.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_CALL].byte2);
    mbMainAppMain.Put<DWORD>(mdmrConsoleWriteLine);
    mbMainAppMain.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_NOP].byte2);
    mbMainAppMain.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_RET].byte2);
    
    CSimpleBlob mbMainAppCtor;
    mbMainAppCtor.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_LDARG_0].byte2);
    mbMainAppCtor.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_CALL].byte2);
    mbMainAppCtor.Put<DWORD>(mdmrObjectCtor);
    mbMainAppCtor.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_RET].byte2);






    //////////////////////////////////////////////////////////////////////////////////////
    // Generate the PE format file with using ICeeFileGen
    // 
    path mscorpePath(corSystemDirectoryPath);
    mscorpePath /= L"mscorpe.dll";
    HMODULE hmodCorPE = ::LoadLibraryW(mscorpePath.wstring().c_str());
    if (!hmodCorPE)
        return SystemError(::GetLastError());
    BOOST_SCOPE_EXIT((hmodCorPE))
    {
        ::FreeLibrary(hmodCorPE);
    }
    BOOST_SCOPE_EXIT_END

    {
        //////////////////////////////////////////////////////////////////////////////////
        // Extract the creating/destroying methods for ICeeFileGen
        // 
        typedef HRESULT (__stdcall *CreateCeeFileGenPtr)(ICeeFileGen **ceeFileGen);
        typedef HRESULT (__stdcall *DestroyCeeFileGenPtr)(ICeeFileGen **ceeFileGen);
        
        CreateCeeFileGenPtr pfnCreateCeeFileGen = NULL;
        DestroyCeeFileGenPtr pfnDestroyCeeFileGen = NULL;

        pfnCreateCeeFileGen = reinterpret_cast<CreateCeeFileGenPtr>(
                                        ::GetProcAddress(hmodCorPE, "CreateICeeFileGen"));
        if (!pfnCreateCeeFileGen)
            return SystemError(::GetLastError());
            
        pfnDestroyCeeFileGen = reinterpret_cast<DestroyCeeFileGenPtr>(
                                       ::GetProcAddress(hmodCorPE, "DestroyICeeFileGen"));
        if (!pfnDestroyCeeFileGen)
            return SystemError(::GetLastError());

        ICeeFileGen* pCeeFileGen = NULL;
        hr = pfnCreateCeeFileGen(&pCeeFileGen);
        if (FAILED(hr))
            return COMError(hr);
        BOOST_SCOPE_EXIT((pCeeFileGen)(pfnDestroyCeeFileGen))
        {
            pfnDestroyCeeFileGen(&pCeeFileGen);
        }
        BOOST_SCOPE_EXIT_END
        
        
        
        //////////////////////////////////////////////////////////////////////////////////
        // Prepare to generate the PE format file
        // 
        HCEEFILE ceeFile = NULL;
        hr = pCeeFileGen->CreateCeeFileEx(&ceeFile, ICEE_CREATE_FILE_PURE_IL);
        if (FAILED(hr))
            return COMError(hr);
        BOOST_SCOPE_EXIT((ceeFile)(pCeeFileGen))
        {
            pCeeFileGen->DestroyCeeFile(&ceeFile);
        }
        BOOST_SCOPE_EXIT_END
        
        hr = pCeeFileGen->SetOutputFileName(ceeFile, L"hello.exe");
        if (FAILED(hr))
            return COMError(hr);
        
        hr = pCeeFileGen->SetComImageFlags(ceeFile, COMIMAGE_FLAGS_ILONLY);
        if (FAILED(hr))
            return COMError(hr);
        
        hr = pCeeFileGen->SetSubsystem(ceeFile, IMAGE_SUBSYSTEM_WINDOWS_CUI, 4, 0);
        if (FAILED(hr))
            return COMError(hr);
        
        
        
        //////////////////////////////////////////////////////////////////////////////////
        // Merge the meta data created above and the PE format file
        // 
        HCEESECTION textSection = NULL;
        hr = pCeeFileGen->GetIlSection(ceeFile, &textSection);
        if (FAILED(hr))
            return COMError(hr);
        
        {
            COR_ILMETHOD_FAT fatHeader;
            ::ZeroMemory(&fatHeader, sizeof(COR_ILMETHOD_FAT));
            fatHeader.SetMaxStack(1);
            fatHeader.SetCodeSize(mbMainAppMain.Size());
            fatHeader.SetLocalVarSigTok(mdTokenNil);
            fatHeader.SetFlags(0);
            
            unsigned headerSize = COR_ILMETHOD::Size(&fatHeader, false);
            unsigned totalSize = headerSize + mbMainAppMain.Size();

            BYTE *pBuffer = NULL;
            hr = pCeeFileGen->GetSectionBlock(textSection, totalSize, 1, 
                                              reinterpret_cast<void**>(&pBuffer));
            if (FAILED(hr))
                return COMError(hr);

            ULONG offset = 0;
            hr = pCeeFileGen->GetSectionDataLen(textSection, &offset);
            if (FAILED(hr))
                return COMError(hr);

            offset -= totalSize;
            ULONG codeRVA = 0;
            hr = pCeeFileGen->GetMethodRVA(ceeFile, offset, &codeRVA);
            if (FAILED(hr))
                return COMError(hr);
            
            hr = pEmtHello->SetMethodProps(mdmdMainAppMain, -1, codeRVA, 0);
            if (FAILED(hr))
                return COMError(hr);

            pBuffer += COR_ILMETHOD::Emit(headerSize, &fatHeader, false, pBuffer);
            ::memcpy_s(pBuffer, totalSize - headerSize, mbMainAppMain.Ptr(), 
                       mbMainAppMain.Size());
        }
        
        {
            COR_ILMETHOD_FAT fatHeader;
            ::ZeroMemory(&fatHeader, sizeof(COR_ILMETHOD_FAT));
            fatHeader.SetMaxStack(1);
            fatHeader.SetCodeSize(mbMainAppCtor.Size());
            fatHeader.SetLocalVarSigTok(mdTokenNil);
            fatHeader.SetFlags(0);
            
            unsigned headerSize = COR_ILMETHOD::Size(&fatHeader, false);
            unsigned totalSize = headerSize + mbMainAppCtor.Size();

            BYTE *pBuffer = NULL;
            hr = pCeeFileGen->GetSectionBlock(textSection, totalSize, 1, 
                                              reinterpret_cast<void**>(&pBuffer));
            if (FAILED(hr))
                return COMError(hr);

            ULONG offset = 0;
            hr = pCeeFileGen->GetSectionDataLen(textSection, &offset);
            if (FAILED(hr))
                return COMError(hr);

            offset -= totalSize;
            ULONG codeRVA = 0;
            hr = pCeeFileGen->GetMethodRVA(ceeFile, offset, &codeRVA);
            if (FAILED(hr))
                return COMError(hr);
            
            hr = pEmtHello->SetMethodProps(mdmdMainAppCtor, -1, codeRVA, 0);
            if (FAILED(hr))
                return COMError(hr);

            pBuffer += COR_ILMETHOD::Emit(headerSize, &fatHeader, false, pBuffer);
            ::memcpy_s(pBuffer, totalSize - headerSize, mbMainAppCtor.Ptr(), 
                       mbMainAppCtor.Size());
        }
        
        pCeeFileGen->SetEntryPoint(ceeFile, mdmdMainAppMain);
        if (FAILED(hr))
            return COMError(hr);
        
        hr = pCeeFileGen->EmitMetaDataEx(ceeFile, pEmtHello);
        if (FAILED(hr))
            return COMError(hr);
        
        
        
        //////////////////////////////////////////////////////////////////////////////////
        // Write all data to the PE format file
        // 
        hr = pCeeFileGen->GenerateCeeFile(ceeFile);
        if (FAILED(hr))
            return COMError(hr);
    }


    return S_OK;
}


