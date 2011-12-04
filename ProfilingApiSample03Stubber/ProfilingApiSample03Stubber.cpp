// ProfilingApiSample03Stubber.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

struct OleCom 
{
    OleCom() { ::CoInitialize(NULL); }
    ~OleCom() { ::CoUninitialize(); }
} olecom;

template<class T>
std::ostream &operator<<(std::ostream &os, std::vector<T> const &v)
{
    using namespace std;
    copy(v.begin(), v.end(), ostream_iterator<T>(cout, " ")); 
    return os;
}

int _tmain(int argc, _TCHAR* argv[])
{
    namespace OpCodes = Urasandesu::CppAnonym::MetaData::OpCodes;
    using namespace std;
    using namespace boost;
    using namespace boost::filesystem;
    using namespace boost::program_options;
    using namespace Urasandesu::CppAnonym;
    HRESULT hr = E_FAIL;
    
    try
    {
        positional_options_description p;
        p.add("input", -1);
        
        options_description desc("Allowed options");
        desc.add_options()
            ("input", value<vector<string>>(), "stubbing files")
        ;
        
        variables_map vm;
        store(wcommand_line_parser(argc, argv).options(desc).positional(p).run(), vm);
        notify(vm);

        if (!vm.count("input"))
            return 0;
        
        vector<string> const &inputs = vm["input"].as<vector<string>>();
        cout << "Input files are: " << inputs << endl;



        
        
        path corSystemDirectoryPath;
        path fusionPath;
        {
            WCHAR buffer[MAX_PATH] = { 0 };
            DWORD length = 0;
            hr = ::GetCORSystemDirectory(buffer, MAX_PATH, &length);
            if (FAILED(hr)) 
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

            corSystemDirectoryPath = buffer;
            fusionPath = buffer;
            fusionPath /= L"fusion.dll";
        }

        HMODULE hmodCorEE = ::LoadLibraryW(fusionPath.c_str());
        if (!hmodCorEE)
            BOOST_THROW_EXCEPTION(CppAnonymSystemException(::GetLastError()));
        BOOST_SCOPE_EXIT((hmodCorEE))
        {
            ::FreeLibrary(hmodCorEE);
        }
        BOOST_SCOPE_EXIT_END

        typedef HRESULT (__stdcall *CreateAsmCachePtr)(IAssemblyCache **ppAsmCache, DWORD dwReserved);

        CreateAsmCachePtr pfnCreateAsmCache = NULL;
        pfnCreateAsmCache = reinterpret_cast<CreateAsmCachePtr>(
                                        ::GetProcAddress(hmodCorEE, "CreateAssemblyCache"));
        if (!pfnCreateAsmCache)
            BOOST_THROW_EXCEPTION(CppAnonymSystemException(::GetLastError()));
        
        CComPtr<IAssemblyCache> pAsmCache;
        hr = pfnCreateAsmCache(&pAsmCache, 0);
        if (FAILED(hr)) 
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

        
        
        
        
        path systemCorePath;
        {
            WCHAR buffer[MAX_PATH] = { 0 };
            ASSEMBLY_INFO asmInfo;
            ::ZeroMemory(&asmInfo, sizeof(ASSEMBLY_INFO));
            asmInfo.cbAssemblyInfo = sizeof(ASSEMBLY_INFO);
            asmInfo.pszCurrentAssemblyPathBuf = buffer;
            asmInfo.cchBuf = MAX_PATH;
            hr = pAsmCache->QueryAssemblyInfo(0, L"System.Core, Version=3.5.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=MSIL", &asmInfo);
            if (FAILED(hr)) 
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
            
            wcout << L"System.Core is here: " << buffer << endl;
            systemCorePath = buffer;
        }

        CComPtr<IMetaDataDispenserEx> pDispSystemCore;
        hr = ::CoCreateInstance(CLSID_CorMetaDataDispenser, NULL, CLSCTX_INPROC_SERVER, 
                                IID_IMetaDataDispenserEx, 
                                reinterpret_cast<void **>(&pDispSystemCore));
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));



        CComPtr<IMetaDataImport2> pImpSystemCore;
        hr = pDispSystemCore->OpenScope(systemCorePath.c_str(), ofRead, 
                                        IID_IMetaDataImport2, 
                                        reinterpret_cast<IUnknown **>(&pImpSystemCore));
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));



        mdTypeDef mdtdFunc1 = mdTypeDefNil;
        hr = pImpSystemCore->FindTypeDefByName(L"System.Func`1", NULL, &mdtdFunc1);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of TypeDef for System.Func<T>: 0x%|1$08X|") % mdtdFunc1 << endl;



        mdMethodDef mdmdFunc1Ctor = mdMethodDefNil;
        {
            COR_SIGNATURE pSigBlob[] = { 
                IMAGE_CEE_CS_CALLCONV_HASTHIS,  // HASTHIS 
                2,                              // ParamCount
                ELEMENT_TYPE_VOID,              // RetType
                ELEMENT_TYPE_OBJECT,            // ParamType[0]: object
                ELEMENT_TYPE_I                  // ParamType[1]: native int
            };
            ULONG sigBlobSize = sizeof(pSigBlob) / sizeof(COR_SIGNATURE);
            hr = pImpSystemCore->FindMethod(mdtdFunc1, L".ctor", 
                                            pSigBlob, sigBlobSize, 
                                            &mdmdFunc1Ctor);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        }
        
        cout << format("Token of MethodDef for System.Func<T>..ctor: 0x%|1$08X|") % mdmdFunc1Ctor << endl;



        CComPtr<IMetaDataAssemblyImport> pAsmImpSystemCore;
        hr = pImpSystemCore->QueryInterface(IID_IMetaDataAssemblyImport, 
                                          reinterpret_cast<void **>(&pAsmImpSystemCore));
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

        mdAssembly mdaSystemCore = mdAssemblyNil;
        hr = pAsmImpSystemCore->GetAssemblyFromScope(&mdaSystemCore);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of Assembly for System.Core.dll: 0x%|1$08X|") % mdaSystemCore << endl;

        auto_ptr<PublicKeyBlob> pSystemCorePubKey;
        DWORD systemCorePubKeySize = 0;
        auto_ptr<WCHAR> systemCoreName;
        ASSEMBLYMETADATA amdSystemCore;
        ::ZeroMemory(&amdSystemCore, sizeof(ASSEMBLYMETADATA));
        DWORD systemCoreAsmFlags = 0;
        {
            ULONG nameSize = 0;
            DWORD asmFlags = 0;
            hr = pAsmImpSystemCore->GetAssemblyProps(mdaSystemCore, NULL, NULL, NULL, NULL, 0, 
                                                     &nameSize, &amdSystemCore, 
                                                     &asmFlags);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

            systemCoreAsmFlags |= (asmFlags & ~afPublicKey);
            systemCoreName = auto_ptr<WCHAR>(new WCHAR[nameSize]);
            amdSystemCore.szLocale = amdSystemCore.cbLocale ? 
                                        new WCHAR[amdSystemCore.cbLocale] : NULL;
            amdSystemCore.rOS = amdSystemCore.ulOS ? new OSINFO[amdSystemCore.ulOS] : NULL;
            amdSystemCore.rProcessor = amdSystemCore.ulProcessor ? 
                                        new ULONG[amdSystemCore.ulProcessor] : NULL;

            void *pPubKey = NULL;
            hr = pAsmImpSystemCore->GetAssemblyProps(mdaSystemCore, 
                                                     const_cast<const void**>(&pPubKey), 
                                                     &systemCorePubKeySize, NULL, 
                                                     systemCoreName.get(), nameSize, NULL, 
                                                     &amdSystemCore, NULL);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

            if (systemCorePubKeySize)
                if (!::StrongNameTokenFromPublicKey(reinterpret_cast<BYTE*>(pPubKey), 
                                                    systemCorePubKeySize, 
                                                    reinterpret_cast<BYTE**>(&pPubKey), 
                                                    &systemCorePubKeySize))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(::StrongNameErrorInfo()));

            pSystemCorePubKey = auto_ptr<PublicKeyBlob>(
                            reinterpret_cast<PublicKeyBlob*>(new BYTE[systemCorePubKeySize]));
            ::memcpy_s(pSystemCorePubKey.get(), systemCorePubKeySize, pPubKey, 
                       systemCorePubKeySize);

            if (systemCorePubKeySize)
                ::StrongNameFreeBuffer(reinterpret_cast<BYTE*>(pPubKey));
        }

        wcout << wformat(L"Assembly Name: %|1$s|") % systemCoreName.get() << endl;

        
        
        
        path mscorlibPath;
        {
            WCHAR buffer[MAX_PATH] = { 0 };
            ASSEMBLY_INFO asmInfo;
            ::ZeroMemory(&asmInfo, sizeof(ASSEMBLY_INFO));
            asmInfo.cbAssemblyInfo = sizeof(ASSEMBLY_INFO);
            asmInfo.pszCurrentAssemblyPathBuf = buffer;
            asmInfo.cchBuf = MAX_PATH;
            hr = pAsmCache->QueryAssemblyInfo(0, L"mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=x86", &asmInfo);
            if (FAILED(hr)) 
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
            
            wcout << L"mscorlib is here: " << buffer << endl;
            mscorlibPath = buffer;
        }

        CComPtr<IMetaDataDispenserEx> pDispMSCorLib;
        hr = ::CoCreateInstance(CLSID_CorMetaDataDispenser, NULL, CLSCTX_INPROC_SERVER, 
                                IID_IMetaDataDispenserEx, 
                                reinterpret_cast<void **>(&pDispMSCorLib));
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));



        CComPtr<IMetaDataImport2> pImpMSCorLib;
        hr = pDispMSCorLib->OpenScope(mscorlibPath.c_str(), ofRead, 
                                      IID_IMetaDataImport2, 
                                      reinterpret_cast<IUnknown **>(&pImpMSCorLib));
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

        
        
        mdTypeDef mdtdObject = mdTypeDefNil;
        hr = pImpMSCorLib->FindTypeDefByName(L"System.Object", NULL, &mdtdObject);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of TypeDef for System.Object: 0x%|1$08X|") % mdtdObject << endl;
        
        mdTypeDef mdtdDateTime = mdTypeDefNil;
        hr = pImpMSCorLib->FindTypeDefByName(L"System.DateTime", NULL, &mdtdDateTime);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of TypeDef for System.DateTime: 0x%|1$08X|") % mdtdDateTime << endl;

        mdTypeDef mdtdCompilationRelaxationsAttribute = mdTypeDefNil;
        hr = pImpMSCorLib->FindTypeDefByName(
                           L"System.Runtime.CompilerServices.CompilationRelaxationsAttribute",
                           NULL, &mdtdCompilationRelaxationsAttribute);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of TypeDef for System.Runtime.CompilerServices.CompilationRelaxationsAttribute: 0x%|1$08X|") % mdtdCompilationRelaxationsAttribute << endl;
        
        mdTypeDef mdtdRuntimeCompatibilityAttribute = mdTypeDefNil;
        hr = pImpMSCorLib->FindTypeDefByName(
                             L"System.Runtime.CompilerServices.RuntimeCompatibilityAttribute",
                             NULL, &mdtdRuntimeCompatibilityAttribute);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of TypeDef for System.Runtime.CompilerServices.RuntimeCompatibilityAttribute: 0x%|1$08X|") % mdtdCompilationRelaxationsAttribute << endl;



        mdMethodDef mdmdDateTimeget_Now = mdMethodDefNil;
        {
            COR_SIGNATURE pSigBlob[] = { 
                IMAGE_CEE_CS_CALLCONV_DEFAULT,  // DEFAULT
                0,                              // ParamCount
                ELEMENT_TYPE_VALUETYPE,         // RetType: VALUETYPE
                0x80,                           //   TypeDef: 0x02000032(System.DateTime)
                0xC8                            //   
            };
            ULONG sigBlobSize = sizeof(pSigBlob) / sizeof(COR_SIGNATURE);
            hr = pImpMSCorLib->FindMethod(mdtdDateTime, L"get_Now", 
                                          pSigBlob, sigBlobSize, 
                                          &mdmdDateTimeget_Now);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        }
        
        cout << format("Token of MethodDef for System.DateTime.get_Now: 0x%|1$08X|") % mdmdDateTimeget_Now << endl;

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
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        }
        
        cout << format("Token of MethodDef for System.Runtime.CompilerServices.CompilationRelaxationsAttribute..ctor: 0x%|1$08X|") % mdmdCompilationRelaxationsAttributeCtor << endl;
        
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
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        }
        
        cout << format("Token of MethodDef for System.Runtime.CompilerServices.RuntimeCompatibilityAttribute..ctor: 0x%|1$08X|") % mdmdRuntimeCompatibilityAttributeCtor << endl;


        CComPtr<IMetaDataAssemblyImport> pAsmImpMSCorLib;
        hr = pImpMSCorLib->QueryInterface(IID_IMetaDataAssemblyImport, 
                                          reinterpret_cast<void **>(&pAsmImpMSCorLib));
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

        mdAssembly mdaMSCorLib = mdAssemblyNil;
        hr = pAsmImpMSCorLib->GetAssemblyFromScope(&mdaMSCorLib);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of Assembly for mscorlib.dll: 0x%|1$08X|") % mdaMSCorLib << endl;

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
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

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
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

            if (msCorLibPubKeySize)
                if (!::StrongNameTokenFromPublicKey(reinterpret_cast<BYTE*>(pPubKey), 
                                                    msCorLibPubKeySize, 
                                                    reinterpret_cast<BYTE**>(&pPubKey), 
                                                    &msCorLibPubKeySize))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

            pMSCorLibPubKey = auto_ptr<PublicKeyBlob>(
                            reinterpret_cast<PublicKeyBlob*>(new BYTE[msCorLibPubKeySize]));
            ::memcpy_s(pMSCorLibPubKey.get(), msCorLibPubKeySize, pPubKey, 
                       msCorLibPubKeySize);

            if (msCorLibPubKeySize)
                ::StrongNameFreeBuffer(reinterpret_cast<BYTE*>(pPubKey));
        }

        wcout << wformat(L"Assembly Name: %|1$s|") % msCorLibName.get() << endl;


        


        CComPtr<IMetaDataDispenserEx> pDispMSCorLibPrig;
        hr = ::CoCreateInstance(CLSID_CorMetaDataDispenser, NULL, CLSCTX_INPROC_SERVER, 
                                           IID_IMetaDataDispenserEx, 
                                           reinterpret_cast<void**>(&pDispMSCorLibPrig));
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

        CComPtr<IMetaDataEmit2> pEmtMSCorLibPrig;
        hr = pDispMSCorLibPrig->DefineScope(CLSID_CorMetaDataRuntime, 0, IID_IMetaDataEmit2, 
                                            reinterpret_cast<IUnknown**>(&pEmtMSCorLibPrig));
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));



        CComPtr<IMetaDataAssemblyEmit> pAsmEmtMSCorLibPrig;
        hr = pEmtMSCorLibPrig->QueryInterface(IID_IMetaDataAssemblyEmit, 
                                              reinterpret_cast<void**>(&pAsmEmtMSCorLibPrig));
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));



        mdAssemblyRef mdarMSCorLib = mdAssemblyRefNil;
        hr = pAsmEmtMSCorLibPrig->DefineAssemblyRef(pMSCorLibPubKey.get(), msCorLibPubKeySize, 
                                                    msCorLibName.get(), &amdMSCorLib, 
                                                    NULL, 0, 
                                                    msCorLibAsmFlags, &mdarMSCorLib);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of AssemblyRef for mscorlib.dll: 0x%|1$08X|") % mdarMSCorLib << endl;

        mdAssemblyRef mdarSystemCore = mdAssemblyRefNil;
        hr = pAsmEmtMSCorLibPrig->DefineAssemblyRef(pSystemCorePubKey.get(), systemCorePubKeySize, 
                                                    systemCoreName.get(), &amdSystemCore, 
                                                    NULL, 0, 
                                                    systemCoreAsmFlags, &mdarSystemCore);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of AssemblyRef for System.Core.dll: 0x%|1$08X|") % mdarSystemCore << endl;



        mdTypeRef mdtrFunc1 = mdTypeRefNil;
        hr = pEmtMSCorLibPrig->DefineTypeRefByName(mdarSystemCore, L"System.Func`1", &mdtrFunc1);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of TypeRef for System.Func`1: 0x%|1$08X|") % mdtrFunc1 << endl;

        mdTypeRef mdtrObject = mdTypeRefNil;
        hr = pEmtMSCorLibPrig->DefineTypeRefByName(mdarMSCorLib, L"System.Object", &mdtrObject);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of TypeRef for System.Object: 0x%|1$08X|") % mdtrObject << endl;

        mdTypeRef mdtrDateTime = mdTypeRefNil;
        hr = pEmtMSCorLibPrig->DefineTypeRefByName(mdarMSCorLib, L"System.DateTime", &mdtrDateTime);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of TypeRef for System.DateTime: 0x%|1$08X|") % mdtrDateTime << endl;

        mdTypeRef mdtrCompilationRelaxationsAttribute = mdTypeRefNil;
        hr = pEmtMSCorLibPrig->DefineTypeRefByName(mdarMSCorLib, 
                           L"System.Runtime.CompilerServices.CompilationRelaxationsAttribute", 
                           &mdtrCompilationRelaxationsAttribute);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of TypeRef for System.Runtime.CompilerServices.CompilationRelaxationsAttribute: 0x%|1$08X|") % mdtrCompilationRelaxationsAttribute << endl;

        mdTypeRef mdtrRuntimeCompatibilityAttribute = mdTypeRefNil;
        hr = pEmtMSCorLibPrig->DefineTypeRefByName(mdarMSCorLib, 
                             L"System.Runtime.CompilerServices.RuntimeCompatibilityAttribute", 
                             &mdtrRuntimeCompatibilityAttribute);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of TypeRef for System.Runtime.CompilerServices.RuntimeCompatibilityAttribute: 0x%|1$08X|") % mdtrRuntimeCompatibilityAttribute << endl;



        mdTypeSpec mdtsSystemFunc1DateTime = mdTypeSpecNil;
        {
            COR_SIGNATURE pSigBlob[] = {
                ELEMENT_TYPE_GENERICINST,       // GENERICINST
                ELEMENT_TYPE_CLASS,             // CLASS
                0x05,                           // TypeRef: 0x01000001(System.Func`1)
                1,                              // Generics Arguments Count: 1
                ELEMENT_TYPE_VALUETYPE,         // VALUETYPE
                0x0D                            // TypeRef: 0x01000003(System.DateTime)
            };                                  
            ULONG sigBlobSize = sizeof(pSigBlob) / sizeof(COR_SIGNATURE);
            hr = pEmtMSCorLibPrig->GetTokenFromTypeSpec(pSigBlob, sigBlobSize, 
                                                        &mdtsSystemFunc1DateTime);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        }
        
        cout << format("Token of TypeSpec for System.Func<DateTime>: 0x%|1$08X|") % mdtsSystemFunc1DateTime << endl;



        mdMemberRef mdmrFunc1DateTimector = mdMemberRefNil;
        hr = pEmtMSCorLibPrig->DefineImportMember(pAsmImpSystemCore, NULL, 0, pImpSystemCore, 
                                                  mdmdFunc1Ctor, 
                                                  pAsmEmtMSCorLibPrig, 
                                                  mdtsSystemFunc1DateTime, 
                                                  &mdmrFunc1DateTimector);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of MemberRef for System.Func<DateTime>..ctor: 0x%|1$08X|") % mdmrFunc1DateTimector << endl;

        mdMemberRef mdmrDateTimeget_Now = mdMemberRefNil;
        hr = pEmtMSCorLibPrig->DefineImportMember(pAsmImpMSCorLib, NULL, 0, pImpMSCorLib, 
                                                  mdmdDateTimeget_Now, 
                                                  pAsmEmtMSCorLibPrig, 
                                                  mdtrDateTime, 
                                                  &mdmrDateTimeget_Now);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of MemberRef for System.DateTime.get_Now: 0x%|1$08X|") % mdmrDateTimeget_Now << endl;

        mdMemberRef mdmrCompilationRelaxationsAttributeCtor = mdMemberRefNil;
        hr = pEmtMSCorLibPrig->DefineImportMember(pAsmImpMSCorLib, NULL, 0, pImpMSCorLib, 
                                                  mdmdCompilationRelaxationsAttributeCtor, 
                                                  pAsmEmtMSCorLibPrig, 
                                                  mdtrCompilationRelaxationsAttribute, 
                                                  &mdmrCompilationRelaxationsAttributeCtor);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of MemberRef for System.Runtime.CompilerServices.CompilationRelaxationsAttribute..ctor: 0x%|1$08X|") % mdmrCompilationRelaxationsAttributeCtor << endl;

        mdMemberRef mdmrRuntimeCompatibilityAttributeCtor = mdMemberRefNil;
        hr = pEmtMSCorLibPrig->DefineImportMember(pAsmImpMSCorLib, NULL, 0, pImpMSCorLib, 
                                                  mdmdRuntimeCompatibilityAttributeCtor, 
                                                  pAsmEmtMSCorLibPrig, 
                                                  mdtrRuntimeCompatibilityAttribute, 
                                                  &mdmrRuntimeCompatibilityAttributeCtor);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of MemberRef for System.Runtime.CompilerServices.RuntimeCompatibilityAttribute..ctor: 0x%|1$08X|") % mdmrRuntimeCompatibilityAttributeCtor << endl;
        
        
        
        path msCorLibPrigKeyPairPath = L"..\\ProfilingApiSample03Patch\\ProfilingApiSample03Patch.snk";
        auto_ptr<BYTE> pMSCorLibPrigKeyPair;
        DWORD msCorLibPrigKeyPairSize = 0;
        auto_ptr<PublicKeyBlob> pMSCorLibPrigPubKey;
        DWORD msCorLibPrigPubKeySize = 0;
        {
            HANDLE hSnk = NULL;
            hSnk = ::CreateFileW(msCorLibPrigKeyPairPath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, 
                                 OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
            if (hSnk == INVALID_HANDLE_VALUE)
                BOOST_THROW_EXCEPTION(CppAnonymSystemException(::GetLastError()));
            BOOST_SCOPE_EXIT((hSnk))
            {
                ::CloseHandle(hSnk);
            }
            BOOST_SCOPE_EXIT_END
            
            msCorLibPrigKeyPairSize = ::GetFileSize(hSnk, NULL);
            if (msCorLibPrigKeyPairSize == -1)
                BOOST_THROW_EXCEPTION(CppAnonymSystemException(::GetLastError()));

            pMSCorLibPrigKeyPair = auto_ptr<BYTE>(new BYTE[msCorLibPrigKeyPairSize]);   
            if (::ReadFile(hSnk, pMSCorLibPrigKeyPair.get(), msCorLibPrigKeyPairSize, &msCorLibPrigKeyPairSize, NULL) == FALSE)
                BOOST_THROW_EXCEPTION(CppAnonymSystemException(::GetLastError()));

            BYTE *pPubKey = NULL;
            if (!::StrongNameGetPublicKey(NULL, pMSCorLibPrigKeyPair.get(), msCorLibPrigKeyPairSize, &pPubKey, &msCorLibPrigPubKeySize))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(::StrongNameErrorInfo()));
            
            pMSCorLibPrigPubKey = auto_ptr<PublicKeyBlob>(
                            reinterpret_cast<PublicKeyBlob*>(new BYTE[msCorLibPrigPubKeySize]));
            ::memcpy_s(pMSCorLibPrigPubKey.get(), msCorLibPrigPubKeySize, pPubKey, 
                       msCorLibPrigPubKeySize);

            if (msCorLibPrigPubKeySize)
                ::StrongNameFreeBuffer(pPubKey);
        }

        cout << "Public Key Blob of mscorlib.Prig: " << endl;
        cout << format("    SigAlgID: 0x%|1$08X|") % pMSCorLibPrigPubKey->SigAlgID << endl;
        cout << format("    HashAlgID: 0x%|1$08X|") % pMSCorLibPrigPubKey->HashAlgID << endl;
        cout << "    Public Key: ";
        for (BYTE *i = pMSCorLibPrigPubKey->PublicKey, *i_end = i + pMSCorLibPrigPubKey->cbPublicKey; i != i_end; ++i)
        {
            cout << format("%|1$02X|") % static_cast<INT>(*i);
        }
        cout << endl;
        cout << "    Raw data: ";
        for (BYTE *i = reinterpret_cast<BYTE *>(pMSCorLibPrigPubKey.get()), *i_end = i + msCorLibPrigPubKeySize; i != i_end; ++i)
        {
            cout << format("%|1$02X|") % static_cast<INT>(*i);
        }
        cout << endl;

        
        mdAssembly mdaMSCorLibPrig = mdAssemblyNil;
        ASSEMBLYMETADATA amdMSCorLibPrig;
        ::ZeroMemory(&amdMSCorLibPrig, sizeof(ASSEMBLYMETADATA));
        hr = pAsmEmtMSCorLibPrig->DefineAssembly(pMSCorLibPrigPubKey.get(), msCorLibPrigPubKeySize, 
                                                 CALG_SHA1, L"mscorlib.Prig", &amdMSCorLibPrig, 
                                                 afPA_None, &mdaMSCorLibPrig);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of Assembly for mscorlib.Prig: 0x%|1$08X|") % mdaMSCorLibPrig << endl;



        WORD const CustomAttributeProlog = 0x0001;

        mdCustomAttribute mdcaCompilationRelaxationsAttribute = mdCustomAttributeNil;
        {
            SimpleBlob sb;
            sb.Put<WORD>(CustomAttributeProlog);        // Prolog
            sb.Put<DWORD>(8);                           // FixedArg, int32: 8
            sb.Put<WORD>(0);                            // NumNamed, Count: 0
            hr = pEmtMSCorLibPrig->DefineCustomAttribute(mdaMSCorLibPrig, 
                                                  mdmrCompilationRelaxationsAttributeCtor, 
                                                  sb.Ptr(), 
                                                  sb.Size(), 
                                                  &mdcaCompilationRelaxationsAttribute);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        }
        
        cout << format("Token of CustomAttribute for System.Runtime.CompilerServices.CompilationRelaxationsAttribute: 0x%|1$08X|") % mdcaCompilationRelaxationsAttribute << endl;

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
            hr = pEmtMSCorLibPrig->DefineCustomAttribute(mdaMSCorLibPrig, 
                                                  mdmrRuntimeCompatibilityAttributeCtor, 
                                                  sb.Ptr(), 
                                                  sb.Size(), 
                                                  &mdcaRuntimeCompatibilityAttribute);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        }
        
        cout << format("Token of CustomAttribute for System.Runtime.CompilerServices.RuntimeCompatibilityAttribute: 0x%|1$08X|") % mdcaRuntimeCompatibilityAttribute << endl;



        mdTypeDef mdtdPDateTime = mdTypeDefNil;
        hr = pEmtMSCorLibPrig->DefineTypeDef(L"System.Prig.PDateTime", 
                                             tdPublic | tdAbstract | 
                                             tdAnsiClass | tdSealed | tdBeforeFieldInit, 
                                             mdtrObject, NULL, &mdtdPDateTime);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of TypeDef for System.Prig.PDateTime: 0x%|1$08X|") % mdtdPDateTime << endl;



        mdTypeDef mdtdNowGet = mdTypeDefNil;
        hr = pEmtMSCorLibPrig->DefineNestedType(L"NowGet", 
                                                tdAbstract | tdAnsiClass | 
                                                tdSealed | tdNestedPublic | tdBeforeFieldInit, 
                                                mdtrObject, NULL, mdtdPDateTime, &mdtdNowGet);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of TypeDef for System.Prig.PDateTime.NowGet: 0x%|1$08X|") % mdtdNowGet << endl;



        mdFieldDef mdfdNowGetm_body = mdFieldDefNil;
        {
            COR_SIGNATURE pSigBlob[] = {
                IMAGE_CEE_CS_CALLCONV_FIELD,    // FIELD
                ELEMENT_TYPE_GENERICINST,       // GENERICINST
                ELEMENT_TYPE_CLASS,             // CLASS
                0x05,                           // TypeRef: 0x01000001(System.Func`1)
                1,                              // Generics Arguments Count: 1
                ELEMENT_TYPE_VALUETYPE,         // VALUETYPE
                0x0D                            // TypeRef: 0x01000003(System.DateTime)
            };                                  
            ULONG sigBlobSize = sizeof(pSigBlob) / sizeof(COR_SIGNATURE);
            hr = pEmtMSCorLibPrig->DefineField(mdtdNowGet, L"m_body", 
                                               fdPrivate | fdStatic, 
                                               pSigBlob, sigBlobSize, 
                                               ELEMENT_TYPE_VOID, NULL, 0, &mdfdNowGetm_body);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        }
            
        cout << format("Token of FieldDef for System.Prig.PDateTime.NowGet.m_body: 0x%|1$08X|") % mdfdNowGetm_body << endl;



        mdMethodDef mdmdNowGetget_Body = mdMethodDefNil;
        {
            COR_SIGNATURE pSigBlob[] = {
                IMAGE_CEE_CS_CALLCONV_DEFAULT,  // DEFAULT   
                0,                              // ParamCount
                ELEMENT_TYPE_GENERICINST,       // GENERICINST
                ELEMENT_TYPE_CLASS,             // CLASS
                0x05,                           // TypeRef: 0x01000001(System.Func`1)
                1,                              // Generics Arguments Count: 1
                ELEMENT_TYPE_VALUETYPE,         // VALUETYPE
                0x0D                            // TypeRef: 0x01000003(System.DateTime)
            };                                  
            ULONG sigBlobSize = sizeof(pSigBlob) / sizeof(COR_SIGNATURE);
            hr = pEmtMSCorLibPrig->DefineMethod(mdtdNowGet, L"get_Body", 
                                         fdPublic | mdHideBySig | mdSpecialName | mdStatic, 
                                         pSigBlob, sigBlobSize, 
                                         0, 0, &mdmdNowGetget_Body);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        }
            
        cout << format("Token of MethodDef for System.Prig.PDateTime.NowGet.get_Body: 0x%|1$08X|") % mdmdNowGetget_Body << endl;

        mdMethodDef mdmdNowGetset_Body = mdMethodDefNil;
        {
            COR_SIGNATURE pSigBlob[] = {
                IMAGE_CEE_CS_CALLCONV_DEFAULT,  // DEFAULT   
                1,                              // ParamCount
                ELEMENT_TYPE_VOID,              // RetType: void
                ELEMENT_TYPE_GENERICINST,       // GENERICINST
                ELEMENT_TYPE_CLASS,             // CLASS
                0x05,                           // TypeRef: 0x01000001(System.Func`1)
                1,                              // Generics Arguments Count: 1
                ELEMENT_TYPE_VALUETYPE,         // VALUETYPE
                0x0D                            // TypeRef: 0x01000003(System.DateTime)
            };                                  
            ULONG sigBlobSize = sizeof(pSigBlob) / sizeof(COR_SIGNATURE);
            hr = pEmtMSCorLibPrig->DefineMethod(mdtdNowGet, L"set_Body", 
                                         fdPublic | mdHideBySig | mdSpecialName | mdStatic, 
                                         pSigBlob, sigBlobSize, 
                                         0, 0, &mdmdNowGetset_Body);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        }
            
        cout << format("Token of MethodDef for System.Prig.PDateTime.NowGet.set_Body: 0x%|1$08X|") % mdmdNowGetset_Body << endl;

        mdMethodDef mdmdNowGetcctor = mdMethodDefNil;
        {
            COR_SIGNATURE pSigBlob[] = {
                IMAGE_CEE_CS_CALLCONV_DEFAULT,  // DEFAULT   
                0,                              // ParamCount
                ELEMENT_TYPE_VOID               // RetType: void
            };                                  
            ULONG sigBlobSize = sizeof(pSigBlob) / sizeof(COR_SIGNATURE);
            hr = pEmtMSCorLibPrig->DefineMethod(mdtdNowGet, L".cctor", 
                                         fdPublic | mdHideBySig | mdSpecialName | mdStatic, 
                                         pSigBlob, sigBlobSize, 
                                         0, 0, &mdmdNowGetcctor);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        }
            
        cout << format("Token of MethodDef for System.Prig.PDateTime.NowGet..cctor: 0x%|1$08X|") % mdmdNowGetcctor << endl;



        mdParamDef mdpdNowGetset_Body0value = mdParamDefNil;
        hr = pEmtMSCorLibPrig->DefineParam(mdmdNowGetset_Body, 0, 
                                           L"value", 0, 
                                           ELEMENT_TYPE_VOID, NULL, 0, 
                                           &mdpdNowGetset_Body0value);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
            
        cout << format("Token of ParamDef for System.Prig.PDateTime.NowGet.set_Body, 0: value: 0x%|1$08X|") % mdpdNowGetset_Body0value << endl;



        mdProperty mdpNowGetBody = mdPropertyNil;
        {
            COR_SIGNATURE pSigBlob[] = {
                IMAGE_CEE_CS_CALLCONV_PROPERTY, // PROPERTY
                0,                              // ParamCount
                ELEMENT_TYPE_GENERICINST,       // GENERICINST
                ELEMENT_TYPE_CLASS,             // CLASS
                0x05,                           // TypeRef: 0x01000001(System.Func`1)
                1,                              // Generics Arguments Count: 1
                ELEMENT_TYPE_VALUETYPE,         // VALUETYPE
                0x0D                            // TypeRef: 0x01000003(System.DateTime)
            };                                  
            ULONG sigBlobSize = sizeof(pSigBlob) / sizeof(COR_SIGNATURE);
            hr = pEmtMSCorLibPrig->DefineProperty(mdtdNowGet, L"Body", 
                                                  0, 
                                                  pSigBlob, sigBlobSize, 
                                                  ELEMENT_TYPE_VOID, NULL, 0, 
                                                  mdmdNowGetset_Body, 
                                                  mdmdNowGetget_Body, 
                                                  NULL, &mdpNowGetBody);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        }
            
        cout << format("Token of Property for System.Prig.PDateTime.NowGet.Body: 0x%|1$08X|") % mdpNowGetBody << endl;



        hr = pEmtMSCorLibPrig->SetModuleProps(L"mscorlib.Prig.dll");
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));



        SimpleBlob mbNowGetget_Body;
        mbNowGetget_Body.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_LDSFLD].byte2);
        mbNowGetget_Body.Put<DWORD>(mdfdNowGetm_body);
        mbNowGetget_Body.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_RET].byte2);

        SimpleBlob mbNowGetset_Body;
        mbNowGetset_Body.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_LDARG_0].byte2);
        mbNowGetset_Body.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_STSFLD].byte2);
        mbNowGetset_Body.Put<DWORD>(mdfdNowGetm_body);
        mbNowGetset_Body.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_RET].byte2);

        SimpleBlob mbNowGetcctor;
        mbNowGetcctor.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_LDNULL].byte2);
        mbNowGetcctor.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_LDFTN].byte1);
        mbNowGetcctor.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_LDFTN].byte2);
        mbNowGetcctor.Put<DWORD>(mdmrDateTimeget_Now);
        mbNowGetcctor.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_NEWOBJ].byte2);
        mbNowGetcctor.Put<DWORD>(mdmrFunc1DateTimector);
        mbNowGetcctor.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_STSFLD].byte2);
        mbNowGetcctor.Put<DWORD>(mdfdNowGetm_body);
        mbNowGetcctor.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_RET].byte2);
        
        
        
        path msCorPEPath(corSystemDirectoryPath);
        msCorPEPath /= L"mscorpe.dll";
        HMODULE hmodCorPE = ::LoadLibraryW(msCorPEPath.c_str());
        if (!hmodCorPE)
            BOOST_THROW_EXCEPTION(CppAnonymSystemException(::GetLastError()));
        BOOST_SCOPE_EXIT((hmodCorPE))
        {
            ::FreeLibrary(hmodCorPE);
        }
        BOOST_SCOPE_EXIT_END

        {
            typedef HRESULT (__stdcall *CreateCeeFileGenPtr)(ICeeFileGen **ceeFileGen);
            typedef HRESULT (__stdcall *DestroyCeeFileGenPtr)(ICeeFileGen **ceeFileGen);
            
            CreateCeeFileGenPtr pfnCreateCeeFileGen = NULL;
            DestroyCeeFileGenPtr pfnDestroyCeeFileGen = NULL;

            pfnCreateCeeFileGen = reinterpret_cast<CreateCeeFileGenPtr>(
                                            ::GetProcAddress(hmodCorPE, "CreateICeeFileGen"));
            if (!pfnCreateCeeFileGen)
                BOOST_THROW_EXCEPTION(CppAnonymSystemException(::GetLastError()));
                
            pfnDestroyCeeFileGen = reinterpret_cast<DestroyCeeFileGenPtr>(
                                           ::GetProcAddress(hmodCorPE, "DestroyICeeFileGen"));
            if (!pfnDestroyCeeFileGen)
                BOOST_THROW_EXCEPTION(CppAnonymSystemException(::GetLastError()));

            ICeeFileGen* pCeeFileGen = NULL;
            hr = pfnCreateCeeFileGen(&pCeeFileGen);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
            BOOST_SCOPE_EXIT((pCeeFileGen)(pfnDestroyCeeFileGen))
            {
                pfnDestroyCeeFileGen(&pCeeFileGen);
            }
            BOOST_SCOPE_EXIT_END

            HCEEFILE ceeFile = NULL;
            hr = pCeeFileGen->CreateCeeFileEx(&ceeFile, ICEE_CREATE_FILE_PURE_IL);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
            BOOST_SCOPE_EXIT((ceeFile)(pCeeFileGen))
            {
                pCeeFileGen->DestroyCeeFile(&ceeFile);
            }
            BOOST_SCOPE_EXIT_END
            
            hr = pCeeFileGen->SetOutputFileName(ceeFile, L"mscorlib.Prig.dll");
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
            
            hr = pCeeFileGen->SetComImageFlags(ceeFile, 
                                 COMIMAGE_FLAGS_ILONLY | COMIMAGE_FLAGS_STRONGNAMESIGNED);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
            
            hr = pCeeFileGen->SetSubsystem(ceeFile, IMAGE_SUBSYSTEM_WINDOWS_CUI, 4, 0);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
            
            
            
            HCEESECTION textSection = NULL;
            hr = pCeeFileGen->GetIlSection(ceeFile, &textSection);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
            
            {
                COR_ILMETHOD_FAT fatHeader;
                ::ZeroMemory(&fatHeader, sizeof(COR_ILMETHOD_FAT));
                fatHeader.SetMaxStack(1);
                fatHeader.SetCodeSize(mbNowGetget_Body.Size());
                fatHeader.SetLocalVarSigTok(mdTokenNil);
                fatHeader.SetFlags(0);
                
                unsigned headerSize = COR_ILMETHOD::Size(&fatHeader, false);
                unsigned totalSize = headerSize + mbNowGetget_Body.Size();

                BYTE *pBuffer = NULL;
                hr = pCeeFileGen->GetSectionBlock(textSection, totalSize, 1, 
                                                  reinterpret_cast<void**>(&pBuffer));
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

                ULONG offset = 0;
                hr = pCeeFileGen->GetSectionDataLen(textSection, &offset);
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

                offset -= totalSize;
                ULONG codeRVA = 0;
                hr = pCeeFileGen->GetMethodRVA(ceeFile, offset, &codeRVA);
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
                
                hr = pEmtMSCorLibPrig->SetMethodProps(mdmdNowGetget_Body, -1, codeRVA, 0);
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

                pBuffer += COR_ILMETHOD::Emit(headerSize, &fatHeader, false, pBuffer);
                ::memcpy_s(pBuffer, totalSize - headerSize, mbNowGetget_Body.Ptr(), 
                           mbNowGetget_Body.Size());
            }
            
            {
                COR_ILMETHOD_FAT fatHeader;
                ::ZeroMemory(&fatHeader, sizeof(COR_ILMETHOD_FAT));
                fatHeader.SetMaxStack(1);
                fatHeader.SetCodeSize(mbNowGetset_Body.Size());
                fatHeader.SetLocalVarSigTok(mdTokenNil);
                fatHeader.SetFlags(0);
                
                unsigned headerSize = COR_ILMETHOD::Size(&fatHeader, false);
                unsigned totalSize = headerSize + mbNowGetset_Body.Size();

                BYTE *pBuffer = NULL;
                hr = pCeeFileGen->GetSectionBlock(textSection, totalSize, 1, 
                                                  reinterpret_cast<void**>(&pBuffer));
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

                ULONG offset = 0;
                hr = pCeeFileGen->GetSectionDataLen(textSection, &offset);
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

                offset -= totalSize;
                ULONG codeRVA = 0;
                hr = pCeeFileGen->GetMethodRVA(ceeFile, offset, &codeRVA);
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
                
                hr = pEmtMSCorLibPrig->SetMethodProps(mdmdNowGetset_Body, -1, codeRVA, 0);
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

                pBuffer += COR_ILMETHOD::Emit(headerSize, &fatHeader, false, pBuffer);
                ::memcpy_s(pBuffer, totalSize - headerSize, mbNowGetset_Body.Ptr(), 
                           mbNowGetset_Body.Size());
            }
            
            {
                COR_ILMETHOD_FAT fatHeader;
                ::ZeroMemory(&fatHeader, sizeof(COR_ILMETHOD_FAT));
                fatHeader.SetMaxStack(1);
                fatHeader.SetCodeSize(mbNowGetcctor.Size());
                fatHeader.SetLocalVarSigTok(mdTokenNil);
                fatHeader.SetFlags(0);
                
                unsigned headerSize = COR_ILMETHOD::Size(&fatHeader, false);
                unsigned totalSize = headerSize + mbNowGetcctor.Size();

                BYTE *pBuffer = NULL;
                hr = pCeeFileGen->GetSectionBlock(textSection, totalSize, 1, 
                                                  reinterpret_cast<void**>(&pBuffer));
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

                ULONG offset = 0;
                hr = pCeeFileGen->GetSectionDataLen(textSection, &offset);
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

                offset -= totalSize;
                ULONG codeRVA = 0;
                hr = pCeeFileGen->GetMethodRVA(ceeFile, offset, &codeRVA);
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
                
                hr = pEmtMSCorLibPrig->SetMethodProps(mdmdNowGetcctor, -1, codeRVA, 0);
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

                pBuffer += COR_ILMETHOD::Emit(headerSize, &fatHeader, false, pBuffer);
                ::memcpy_s(pBuffer, totalSize - headerSize, mbNowGetcctor.Ptr(), 
                           mbNowGetcctor.Size());
            }

            {
                DWORD msCorLibPrigSignReserveSize = 0;
                if (!::StrongNameSignatureSize(
                                    reinterpret_cast<PBYTE>(pMSCorLibPrigPubKey.get()), 
                                    msCorLibPrigPubKeySize, &msCorLibPrigSignReserveSize))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(::StrongNameErrorInfo()));

                BYTE *pBuffer = NULL;
                hr = pCeeFileGen->GetSectionBlock(textSection, 
                                                  msCorLibPrigSignReserveSize, 1, 
                                                  reinterpret_cast<void**>(&pBuffer));
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

                ULONG offset = 0;
                hr = pCeeFileGen->GetSectionDataLen(textSection, &offset);
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
                
                offset -= msCorLibPrigSignReserveSize;
                ULONG codeRVA = 0;
                hr = pCeeFileGen->GetMethodRVA(ceeFile, offset, &codeRVA);
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
                
                ::ZeroMemory(pBuffer, msCorLibPrigSignReserveSize);
                
                hr = pCeeFileGen->SetStrongNameEntry(ceeFile, msCorLibPrigSignReserveSize, codeRVA);
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
            }
            
            hr = pCeeFileGen->SetDllSwitch(ceeFile, true);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
            
            hr = pCeeFileGen->EmitMetaDataEx(ceeFile, pEmtMSCorLibPrig);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
            
            
            
            hr = pCeeFileGen->GenerateCeeFile(ceeFile);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
            
            
            
            if (!::StrongNameSignatureGenerationEx(L"mscorlib.Prig.dll", NULL, 
                                       pMSCorLibPrigKeyPair.get(), msCorLibPrigKeyPairSize, 
                                       NULL, NULL, 0))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(::StrongNameErrorInfo()));
        }
    }
    catch (CppAnonymException &e)
    {
        cout << diagnostic_information(e) << endl;
    }
    catch (...)
    {
        cout << diagnostic_information(current_exception()) << endl;
    }

    return 0;
}

