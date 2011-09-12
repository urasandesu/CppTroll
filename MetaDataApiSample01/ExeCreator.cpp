// ExeCreator.cpp : CExeCreator の実装

#include "stdafx.h"
#include "ExeCreator.h"

// CExeCreator


HRESULT CExeCreator::SystemError(DWORD errorNo, LPCSTR filePath, INT line)
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

HRESULT CExeCreator::COMError(HRESULT hr, LPCSTR filePath, INT line)
{
    using std::wostringstream;

    wostringstream msg;
    msg << _com_error(hr).ErrorMessage();
    msg << ", File: " << filePath;
    msg << ", Line: " << line;
    return Error(msg.str().c_str());
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
    namespace OpCodes = Urasandesu::NAnonym::MetaData::OpCodes;
    using boost::filesystem::path;
    using std::auto_ptr;
    using std::string;
    using std::wstring;    
    using Urasandesu::NAnonym::SimpleBlob;

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
            return COMError(hr, __FILE__, __LINE__);

        corSystemDirectoryPath = buffer;
        mscorlibPath = buffer;
        mscorlibPath /= L"mscorlib.dll";
    }

    CComPtr<IMetaDataDispenserEx> pDispMSCorLib;
    hr = ::CoCreateInstance(CLSID_CorMetaDataDispenser, NULL, CLSCTX_INPROC_SERVER, 
                            IID_IMetaDataDispenserEx, 
                            reinterpret_cast<void**>(&pDispMSCorLib));
    if (FAILED(hr))
        return COMError(hr, __FILE__, __LINE__);
    
    
    CComPtr<IMetaDataImport2> pImpMSCorLib;
    hr = pDispMSCorLib->OpenScope(mscorlibPath.wstring().c_str(), ofRead, 
                                  IID_IMetaDataImport2, 
                                  reinterpret_cast<IUnknown**>(&pImpMSCorLib));
    if (FAILED(hr))
        return COMError(hr, __FILE__, __LINE__);



    //////////////////////////////////////////////////////////////////////////////////////
    // Find importing types
    // 
    mdTypeDef mdtdObject = mdTypeDefNil;
    hr = pImpMSCorLib->FindTypeDefByName(L"System.Object", NULL, &mdtdObject);
    if (FAILED(hr))
        return COMError(hr, __FILE__, __LINE__);
    
    mdTypeDef mdtdCompilationRelaxationsAttribute = mdTypeDefNil;
    hr = pImpMSCorLib->FindTypeDefByName(
                       L"System.Runtime.CompilerServices.CompilationRelaxationsAttribute",
                       NULL, &mdtdCompilationRelaxationsAttribute);
    if (FAILED(hr))
        return COMError(hr, __FILE__, __LINE__);
    
    mdTypeDef mdtdRuntimeCompatibilityAttribute = mdTypeDefNil;
    hr = pImpMSCorLib->FindTypeDefByName(
                         L"System.Runtime.CompilerServices.RuntimeCompatibilityAttribute",
                         NULL, &mdtdRuntimeCompatibilityAttribute);
    if (FAILED(hr))
        return COMError(hr, __FILE__, __LINE__);
    
    mdTypeDef mdtdConsole = mdTypeDefNil;
    hr = pImpMSCorLib->FindTypeDefByName(L"System.Console", NULL, &mdtdConsole);
    if (FAILED(hr))
        return COMError(hr, __FILE__, __LINE__);



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
            return COMError(hr, __FILE__, __LINE__);
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
            return COMError(hr, __FILE__, __LINE__);
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
            return COMError(hr, __FILE__, __LINE__);
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
            return COMError(hr, __FILE__, __LINE__);
    }



    //////////////////////////////////////////////////////////////////////////////////////
    // Prepare importing assembly
    // 
    CComPtr<IMetaDataAssemblyImport> pAsmImpMSCorLib;
    hr = pImpMSCorLib->QueryInterface(IID_IMetaDataAssemblyImport, 
                                      reinterpret_cast<void**>(&pAsmImpMSCorLib));
    if (FAILED(hr))
        return COMError(hr, __FILE__, __LINE__);

    mdAssembly mdaMSCorLib = mdAssemblyNil;
    hr = pAsmImpMSCorLib->GetAssemblyFromScope(&mdaMSCorLib);
    if (FAILED(hr))
        return COMError(hr, __FILE__, __LINE__);

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
            return COMError(hr, __FILE__, __LINE__);

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
            return COMError(hr, __FILE__, __LINE__);

        if (msCorLibPubKeySize)
            if (!::StrongNameTokenFromPublicKey(reinterpret_cast<BYTE*>(pPubKey), 
                                                msCorLibPubKeySize, 
                                                reinterpret_cast<BYTE**>(&pPubKey), 
                                                &msCorLibPubKeySize))
                return COMError(::StrongNameErrorInfo(), __FILE__, __LINE__);

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
        return COMError(hr, __FILE__, __LINE__);

    CComPtr<IMetaDataEmit2> pEmtHello;
    hr = pDispHello->DefineScope(CLSID_CorMetaDataRuntime, 0, IID_IMetaDataEmit2, 
                                 reinterpret_cast<IUnknown**>(&pEmtHello));
    if (FAILED(hr))
        return COMError(hr, __FILE__, __LINE__);



    //////////////////////////////////////////////////////////////////////////////////////
    // Prepare emitting assembly
    // 
    CComPtr<IMetaDataAssemblyEmit> pAsmEmtHello;
    hr = pEmtHello->QueryInterface(IID_IMetaDataAssemblyEmit, 
                                   reinterpret_cast<void**>(&pAsmEmtHello));
    if (FAILED(hr))
        return COMError(hr, __FILE__, __LINE__);


    //////////////////////////////////////////////////////////////////////////////////////
    // Create AssemblyRef table
    // 
    mdAssemblyRef mdarMSCorLib = mdAssemblyRefNil;
    hr = pAsmEmtHello->DefineAssemblyRef(pMSCorLibPubKey.get(), msCorLibPubKeySize, 
                                         msCorLibName.get(), &amdMSCorLib, 
                                         NULL, 0, 
                                         msCorLibAsmFlags, &mdarMSCorLib);
    if (FAILED(hr))
        return COMError(hr, __FILE__, __LINE__);
    


    //////////////////////////////////////////////////////////////////////////////////////
    // Create TypeRef table
    // 
    mdTypeRef mdtrObject = mdTypeRefNil;
    hr = pEmtHello->DefineTypeRefByName(mdarMSCorLib, L"System.Object", &mdtrObject);
    if (FAILED(hr))
        return COMError(hr, __FILE__, __LINE__);

    mdTypeRef mdtrCompilationRelaxationsAttribute = mdTypeRefNil;
    hr = pEmtHello->DefineTypeRefByName(mdarMSCorLib, 
                       L"System.Runtime.CompilerServices.CompilationRelaxationsAttribute", 
                       &mdtrCompilationRelaxationsAttribute);
    if (FAILED(hr))
        return COMError(hr, __FILE__, __LINE__);

    mdTypeRef mdtrRuntimeCompatibilityAttribute = mdTypeRefNil;
    hr = pEmtHello->DefineTypeRefByName(mdarMSCorLib, 
                         L"System.Runtime.CompilerServices.RuntimeCompatibilityAttribute", 
                         &mdtrRuntimeCompatibilityAttribute);
    if (FAILED(hr))
        return COMError(hr, __FILE__, __LINE__);

    mdTypeRef mdtrConsole = mdTypeRefNil;
    hr = pEmtHello->DefineTypeRefByName(mdarMSCorLib, L"System.Console", &mdtrConsole);
    if (FAILED(hr))
        return COMError(hr, __FILE__, __LINE__);



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
        return COMError(hr, __FILE__, __LINE__);

    mdMemberRef mdmrRuntimeCompatibilityAttributeCtor = mdMemberRefNil;
    hr = pEmtHello->DefineImportMember(pAsmImpMSCorLib, NULL, 0, pImpMSCorLib, 
                                       mdmdRuntimeCompatibilityAttributeCtor, 
                                       pAsmEmtHello, 
                                       mdtrRuntimeCompatibilityAttribute, 
                                       &mdmrRuntimeCompatibilityAttributeCtor);
    if (FAILED(hr))
        return COMError(hr, __FILE__, __LINE__);

    mdMemberRef mdmrConsoleWriteLine = mdMemberRefNil;
    hr = pEmtHello->DefineImportMember(pAsmImpMSCorLib, NULL, 0, pImpMSCorLib, 
                                       mdmdConsoleWriteLine, 
                                       pAsmEmtHello, 
                                       mdtrConsole, 
                                       &mdmrConsoleWriteLine);
    if (FAILED(hr))
        return COMError(hr, __FILE__, __LINE__);

    mdMemberRef mdmrObjectCtor = mdMemberRefNil;
    hr = pEmtHello->DefineImportMember(pAsmImpMSCorLib, NULL, 0, pImpMSCorLib, 
                                       mdmdObjectCtor, 
                                       pAsmEmtHello, 
                                       mdtrObject, 
                                       &mdmrObjectCtor);
    if (FAILED(hr))
        return COMError(hr, __FILE__, __LINE__);



    //////////////////////////////////////////////////////////////////////////////////////
    // Create Assembly table
    // 
    mdAssembly mdaHello = mdAssemblyNil;
    ASSEMBLYMETADATA amdHello;
    ::ZeroMemory(&amdHello, sizeof(ASSEMBLYMETADATA));
    hr = pAsmEmtHello->DefineAssembly(NULL, 0, CALG_SHA1, L"hello", &amdHello, afPA_None, 
                                      &mdaHello);
    if (FAILED(hr))
        return COMError(hr, __FILE__, __LINE__);



    //////////////////////////////////////////////////////////////////////////////////////
    // Create CustomAttribute table
    // 
    WORD const CustomAttributeProlog = 0x0001;

    mdCustomAttribute mdcaCompilationRelaxationsAttribute = mdCustomAttributeNil;
    {
        SimpleBlob sb;
        sb.Put<WORD>(CustomAttributeProlog);        // Prolog
        sb.Put<DWORD>(8);                           // FixedArg, int32: 8
        sb.Put<WORD>(0);                            // NumNamed, Count: 0
        hr = pEmtHello->DefineCustomAttribute(mdaHello, 
                                              mdmrCompilationRelaxationsAttributeCtor, 
                                              sb.Ptr(), 
                                              sb.Size(), 
                                              &mdcaCompilationRelaxationsAttribute);
        if (FAILED(hr))
            return COMError(hr, __FILE__, __LINE__);
    }

    mdCustomAttribute mdcaRuntimeCompatibilityAttribute = mdCustomAttributeNil;
    {
        SimpleBlob sb;
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
            return COMError(hr, __FILE__, __LINE__);
    }



    //////////////////////////////////////////////////////////////////////////////////////
    // Create TypeDef table
    // 
    mdTypeDef mdtdMainApp = mdTypeDefNil;
    hr = pEmtHello->DefineTypeDef(L"MainApp", tdNotPublic | tdBeforeFieldInit, mdtrObject, 
                                  NULL, &mdtdMainApp);
    if (FAILED(hr))
        return COMError(hr, __FILE__, __LINE__);



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
            return COMError(hr, __FILE__, __LINE__);
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
            return COMError(hr, __FILE__, __LINE__);
    }



    //////////////////////////////////////////////////////////////////////////////////////
    // Create #US stream
    // 
    mdString mdsHelloWorld = mdStringNil;
    {
        wstring text(L"Hello World!");
        hr = pEmtHello->DefineUserString(text.c_str(), text.size(), &mdsHelloWorld);
        if (FAILED(hr))
            return COMError(hr, __FILE__, __LINE__);
    }



    //////////////////////////////////////////////////////////////////////////////////////
    // Set Module name
    hr = pEmtHello->SetModuleProps(L"hello.exe");
    if (FAILED(hr))
        return COMError(hr, __FILE__, __LINE__);






    //////////////////////////////////////////////////////////////////////////////////////
    // Emit Method body
    // 
    SimpleBlob mbMainAppMain;
    mbMainAppMain.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_NOP].byte2);
    mbMainAppMain.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_LDSTR].byte2);
    mbMainAppMain.Put<DWORD>(mdsHelloWorld);
    mbMainAppMain.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_CALL].byte2);
    mbMainAppMain.Put<DWORD>(mdmrConsoleWriteLine);
    mbMainAppMain.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_NOP].byte2);
    mbMainAppMain.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_RET].byte2);
    
    SimpleBlob mbMainAppCtor;
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
        return SystemError(::GetLastError(), __FILE__, __LINE__);
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
            return SystemError(::GetLastError(), __FILE__, __LINE__);
            
        pfnDestroyCeeFileGen = reinterpret_cast<DestroyCeeFileGenPtr>(
                                       ::GetProcAddress(hmodCorPE, "DestroyICeeFileGen"));
        if (!pfnDestroyCeeFileGen)
            return SystemError(::GetLastError(), __FILE__, __LINE__);

        ICeeFileGen* pCeeFileGen = NULL;
        hr = pfnCreateCeeFileGen(&pCeeFileGen);
        if (FAILED(hr))
            return COMError(hr, __FILE__, __LINE__);
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
            return COMError(hr, __FILE__, __LINE__);
        BOOST_SCOPE_EXIT((ceeFile)(pCeeFileGen))
        {
            pCeeFileGen->DestroyCeeFile(&ceeFile);
        }
        BOOST_SCOPE_EXIT_END
        
        hr = pCeeFileGen->SetOutputFileName(ceeFile, L"hello.exe");
        if (FAILED(hr))
            return COMError(hr, __FILE__, __LINE__);
        
        hr = pCeeFileGen->SetComImageFlags(ceeFile, COMIMAGE_FLAGS_ILONLY);
        if (FAILED(hr))
            return COMError(hr, __FILE__, __LINE__);
        
        hr = pCeeFileGen->SetSubsystem(ceeFile, IMAGE_SUBSYSTEM_WINDOWS_CUI, 4, 0);
        if (FAILED(hr))
            return COMError(hr, __FILE__, __LINE__);
        
        
        
        //////////////////////////////////////////////////////////////////////////////////
        // Merge the meta data created above and the PE format file
        // 
        HCEESECTION textSection = NULL;
        hr = pCeeFileGen->GetIlSection(ceeFile, &textSection);
        if (FAILED(hr))
            return COMError(hr, __FILE__, __LINE__);
        
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
                return COMError(hr, __FILE__, __LINE__);

            ULONG offset = 0;
            hr = pCeeFileGen->GetSectionDataLen(textSection, &offset);
            if (FAILED(hr))
                return COMError(hr, __FILE__, __LINE__);

            offset -= totalSize;
            ULONG codeRVA = 0;
            hr = pCeeFileGen->GetMethodRVA(ceeFile, offset, &codeRVA);
            if (FAILED(hr))
                return COMError(hr, __FILE__, __LINE__);
            
            hr = pEmtHello->SetMethodProps(mdmdMainAppMain, -1, codeRVA, 0);
            if (FAILED(hr))
                return COMError(hr, __FILE__, __LINE__);

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
                return COMError(hr, __FILE__, __LINE__);

            ULONG offset = 0;
            hr = pCeeFileGen->GetSectionDataLen(textSection, &offset);
            if (FAILED(hr))
                return COMError(hr, __FILE__, __LINE__);

            offset -= totalSize;
            ULONG codeRVA = 0;
            hr = pCeeFileGen->GetMethodRVA(ceeFile, offset, &codeRVA);
            if (FAILED(hr))
                return COMError(hr, __FILE__, __LINE__);
            
            hr = pEmtHello->SetMethodProps(mdmdMainAppCtor, -1, codeRVA, 0);
            if (FAILED(hr))
                return COMError(hr, __FILE__, __LINE__);

            pBuffer += COR_ILMETHOD::Emit(headerSize, &fatHeader, false, pBuffer);
            ::memcpy_s(pBuffer, totalSize - headerSize, mbMainAppCtor.Ptr(), 
                       mbMainAppCtor.Size());
        }
        
        pCeeFileGen->SetEntryPoint(ceeFile, mdmdMainAppMain);
        if (FAILED(hr))
            return COMError(hr, __FILE__, __LINE__);
        
        hr = pCeeFileGen->EmitMetaDataEx(ceeFile, pEmtHello);
        if (FAILED(hr))
            return COMError(hr, __FILE__, __LINE__);
        
        
        
        //////////////////////////////////////////////////////////////////////////////////
        // Write all data to the PE format file
        // 
        hr = pCeeFileGen->GenerateCeeFile(ceeFile);
        if (FAILED(hr))
            return COMError(hr, __FILE__, __LINE__);
    }


    return S_OK;
}


