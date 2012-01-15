// ExeWeaver4.cpp : CExeWeaver4 ‚ÌŽÀ‘•

#include "stdafx.h"
#include "ExeWeaver4.h"

//#define OUTPUT_VERBOSE
//#define OUTPUT_DEBUG

#ifdef OUTPUT_VERBOSE
#define V_WCOUT(s) std::wcout << s << std::endl
#else
#define V_WCOUT(s)
#endif

#ifdef OUTPUT_VERBOSE
#define V_WCOUT1(fmt, arg) std::wcout << boost::wformat(fmt) % arg << std::endl
#else
#define V_WCOUT1(fmt, arg)
#endif

#ifdef OUTPUT_DEBUG
#define D_COUT1(fmt, arg) std::cout << boost::format(fmt) % arg << std::endl
#else
#define D_COUT1(fmt, arg) 
#endif

#ifdef OUTPUT_DEBUG
#define D_WCOUT1(fmt, arg) std::wcout << boost::wformat(fmt) % arg << std::endl
#else
#define D_WCOUT1(fmt, arg) 
#endif

std::wstring const CExeWeaver4::MODULE_NAME_OF_MS_COR_LIB = L"mscorlib.dll";
std::wstring const CExeWeaver4::TYPE_NAME_OF_SYSTEM_DATE_TIME_GET_NOW = L"System.DateTime.get_Now";

// CExeWeaver4
HRESULT CExeWeaver4::FinalConstruct()
{
    return S_OK;
}

void CExeWeaver4::FinalRelease()
{
}

HRESULT CExeWeaver4::InitializeCore(
    /* [in] */ IUnknown *pICorProfilerInfoUnk)
{
    using namespace std;
    using namespace Urasandesu::CppAnonym;
    HRESULT hr = E_FAIL;


    // Reset the timer.
    m_timer.restart();
    

    // Initialize the profiling API.
    hr = pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo2, 
                                              reinterpret_cast<void**>(&m_pInfo));
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));


    // Set a value that specifies the types of events for which the profiler 
    // wants to receive notification from CLR.
    // NOTE: If you want to profile core APIs such as types in mscorlib, 
    //       you should set COR_PRF_USE_PROFILE_IMAGES.
    DWORD event_ = COR_PRF_MONITOR_MODULE_LOADS | 
                   COR_PRF_MONITOR_JIT_COMPILATION | 
                   COR_PRF_USE_PROFILE_IMAGES;
    hr = m_pInfo->SetEventMask(event_);
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

    return S_OK;
}

HRESULT CExeWeaver4::ShutdownCore(void)
{ 
    using namespace std;
    using namespace boost;
    
    // Display the time elapsed.
    D_COUT1("Time Elapsed: %|1$f|s", m_timer.elapsed());

    return S_OK; 
}

HRESULT CExeWeaver4::ModuleLoadStartedCore( 
    /* [in] */ ModuleID moduleId)
{
    using namespace std;
    using namespace boost::filesystem;
    using namespace Urasandesu::CppAnonym;
    HRESULT hr = E_FAIL;
    

    // Convert ModuleID to the name.
    LPCBYTE pBaseLoadAddress = NULL;
    WCHAR modName[MAX_SYM_NAME] = { 0 };
    ULONG modNameSize = sizeof(modName);
    AssemblyID asmId = 0;
    
    hr = m_pInfo->GetModuleInfo(moduleId, &pBaseLoadAddress, 
                                modNameSize, &modNameSize, modName, &asmId);
    if (hr != CORPROF_E_DATAINCOMPLETE && FAILED(hr))
        BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
    

    // If target module is detected, the object implemented IMetaDataEmit is initialized 
    // to use the following process.
    path modPath(modName);

    V_WCOUT1(L"ModuleLoadStarted: %|1$s|", modName);
    if (modPath.filename().wstring() == MODULE_NAME_OF_MS_COR_LIB)
    {
        V_WCOUT(L"The target module is detected. Getting module meta data is started.");

        hr = m_pInfo->GetModuleMetaData(moduleId, ofRead | ofWrite, IID_IMetaDataEmit2, 
                                        reinterpret_cast<IUnknown **>(&m_pEmtMSCorLib));
        if (hr != CORPROF_E_DATAINCOMPLETE && FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
    }

    return S_OK;
}

HRESULT CExeWeaver4::JITCompilationStartedCore( 
    /* [in] */ FunctionID functionId,
    /* [in] */ BOOL fIsSafeToBlock)
{
    namespace OpCodes = Urasandesu::CppAnonym::MetaData::OpCodes;
    using namespace std;
    using namespace boost;
    using namespace boost::filesystem;
    using namespace Urasandesu::CppAnonym;
    HRESULT hr = E_FAIL;
    

    // Convert FunctionID to MethodDef token.
    mdMethodDef mdmd = mdMethodDefNil;
    CComPtr<IMetaDataImport2> pImport;
    hr = m_pInfo->GetTokenAndMetaDataFromFunction(functionId, IID_IMetaDataImport2, 
                                                  reinterpret_cast<IUnknown **>(&pImport), 
                                                  &mdmd);
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
    

    // Get the properties of this method.
    mdTypeDef mdtd = mdTypeDefNil;
    WCHAR methodName[MAX_SYM_NAME] = { 0 };
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
        BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
    

    // Get the properties of type that this method is declared.
    WCHAR typeName[MAX_SYM_NAME] = { 0 };
    ULONG typeNameSize = sizeof(typeName);
    DWORD typeAttr = 0;
    mdToken mdtTypeExtends = mdTokenNil;
    hr = pImport->GetTypeDefProps(mdtd, typeName, typeNameSize, &typeNameSize, 
                                  &typeAttr, &mdtTypeExtends);
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
    

    // If target type is detected, Replacing method body is started.
    wstring methodFullName(typeName);
    methodFullName += L".";
    methodFullName += methodName;

    V_WCOUT1(L"JITCompilationStarted: %|1$s|", methodFullName);

    if (methodFullName == TYPE_NAME_OF_SYSTEM_DATE_TIME_GET_NOW)
    {
        V_WCOUT(L"The target type is detected. Replacing method body is started.");
    

        // Prepare the 1st source assembly mscorlib.Prig that is delegated an actual process.
        // Get IMetaDataImport to manipulate the assembly.
        path msCorLibPrigPath(L"..\\Debug\\mscorlib.Prig.dll");
        
        CComPtr<IMetaDataDispenserEx> pDispMSCorLibPrig;
        hr = ::CoCreateInstance(CLSID_CorMetaDataDispenser, NULL, CLSCTX_INPROC_SERVER, 
                                IID_IMetaDataDispenserEx, 
                                reinterpret_cast<void **>(&pDispMSCorLibPrig));
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

        CComPtr<IMetaDataImport2> pImpMSCorLibPrig;
        hr = pDispMSCorLibPrig->OpenScope(msCorLibPrigPath.c_str(), ofRead, IID_IMetaDataImport2, 
                                      reinterpret_cast<IUnknown **>(&pImpMSCorLibPrig));
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        


        // Get TypeDef records to add to TypeRef table.
        mdTypeDef mdtdPDateTime = mdTypeDefNil;
        hr = pImpMSCorLibPrig->FindTypeDefByName(L"System.Prig.PDateTime", NULL, &mdtdPDateTime);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        D_COUT1("Token of TypeDef for System.Prig.PDateTime: 0x%|1$08X|", mdtdPDateTime);

        mdTypeDef mdtdNowGet = mdTypeDefNil;
        hr = pImpMSCorLibPrig->FindTypeDefByName(L"NowGet", mdtdPDateTime, &mdtdNowGet);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        D_COUT1("Token of TypeDef for System.Prig.PDateTime+NowGet: 0x%|1$08X|", mdtdNowGet);
        


        // Get MethodDef records to add to MethodRef table.
        mdMethodDef mdmdget_Body = mdMethodDefNil;
        {
            COR_SIGNATURE pSigBlob[] = { 
                IMAGE_CEE_CS_CALLCONV_DEFAULT,  // DEFAULT  
                0,                              // ParamCount: 0
                ELEMENT_TYPE_GENERICINST,       // RetType: GENERICINST
                ELEMENT_TYPE_CLASS,             //          CLASS
                0x05,                           //          TypeRef: 0x01000001(System.Func`1)
                1,                              //          Generics Arguments Count: 1
                ELEMENT_TYPE_VALUETYPE,         //          VALUETYPE
                0x0D                            //          TypeRef: 0x01000003(System.DateTime)
            };
            ULONG sigBlobSize = sizeof(pSigBlob) / sizeof(COR_SIGNATURE);
            hr = pImpMSCorLibPrig->FindMethod(mdtdNowGet, L"get_Body", 
                                              pSigBlob, sigBlobSize, &mdmdget_Body);            
            
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        }
        
        D_COUT1("Token of MethodDef for System.Prig.PDateTime+NowGet.get_Body: 0x%|1$08X|", mdmdget_Body);
        


        // Get MetaDataAssemblyImport and Assembly record to add to AssemblyRef table.
        CComPtr<IMetaDataAssemblyImport> pAsmImpMSCorLibPrig;
        hr = pImpMSCorLibPrig->QueryInterface(IID_IMetaDataAssemblyImport, 
                                       reinterpret_cast<void **>(&pAsmImpMSCorLibPrig));
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

        mdAssembly mdaMSCorLibPrig = mdAssemblyNil;
        hr = pAsmImpMSCorLibPrig->GetAssemblyFromScope(&mdaMSCorLibPrig);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        D_COUT1("Token of Assembly for mscorlib.Pring.dll: 0x%|1$08X|", mdaMSCorLibPrig);

        auto_ptr<PublicKeyBlob> pMSCorLibPrigPubKey;
        DWORD msCorLibPrigPubKeySize = 0;
        auto_ptr<WCHAR> msCorLibPrigAsmName;
        ASSEMBLYMETADATA amdMSCorLibPrig;
        ::ZeroMemory(&amdMSCorLibPrig, sizeof(ASSEMBLYMETADATA));
        DWORD msCorLibPrigAsmFlags = 0;
        {
            ULONG nameSize = 0;
            DWORD asmFlags = 0;
            hr = pAsmImpMSCorLibPrig->GetAssemblyProps(mdaMSCorLibPrig, NULL, NULL, NULL, NULL, 0, 
                                                       &nameSize, &amdMSCorLibPrig, 
                                                       &asmFlags);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

            msCorLibPrigAsmFlags |= (asmFlags & ~afPublicKey);
            msCorLibPrigAsmName = auto_ptr<WCHAR>(new WCHAR[nameSize]);
            amdMSCorLibPrig.szLocale = amdMSCorLibPrig.cbLocale ? new WCHAR[amdMSCorLibPrig.cbLocale] : NULL;
            amdMSCorLibPrig.rOS = amdMSCorLibPrig.ulOS ? new OSINFO[amdMSCorLibPrig.ulOS] : NULL;
            amdMSCorLibPrig.rProcessor = amdMSCorLibPrig.ulProcessor ? new ULONG[amdMSCorLibPrig.ulProcessor] : NULL;

            void *pPubKey = NULL;
            hr = pAsmImpMSCorLibPrig->GetAssemblyProps(mdaMSCorLibPrig, 
                                                const_cast<const void**>(&pPubKey), 
                                                &msCorLibPrigPubKeySize, NULL, 
                                                msCorLibPrigAsmName.get(), nameSize, NULL, 
                                                &amdMSCorLibPrig, NULL);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

            if (msCorLibPrigPubKeySize)
                if (!::StrongNameTokenFromPublicKey(reinterpret_cast<BYTE*>(pPubKey), 
                                                    msCorLibPrigPubKeySize, 
                                                    reinterpret_cast<BYTE**>(&pPubKey), 
                                                    &msCorLibPrigPubKeySize))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

            pMSCorLibPrigPubKey = auto_ptr<PublicKeyBlob>(
                            reinterpret_cast<PublicKeyBlob*>(new BYTE[msCorLibPrigPubKeySize]));
            ::memcpy_s(pMSCorLibPrigPubKey.get(), msCorLibPrigPubKeySize, pPubKey, 
                       msCorLibPrigPubKeySize);

            if (msCorLibPrigPubKeySize)
                ::StrongNameFreeBuffer(reinterpret_cast<BYTE*>(pPubKey));
        }

        D_WCOUT1(L"Assembly Name: %|1$s|", msCorLibPrigAsmName.get());
        
        

        // Prepare the 2nd source assembly System.Core to reference delegation types such as Func<TResult>.
        // NOTE: If you want to access GAC, you can use Fusion API.
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
        
        
        
        // Get IMetaDataImport to manipulate the assembly.
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
            
            D_WCOUT1(L"System.Core is here: %|1$s|", buffer);
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



        // Get TypeDef records to add to TypeRef table.
        mdTypeDef mdtdFunc1 = mdTypeDefNil;
        hr = pImpSystemCore->FindTypeDefByName(L"System.Func`1", NULL, &mdtdFunc1);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        D_COUT1("Token of TypeDef for System.Func<T>: 0x%|1$08X|", mdtdFunc1);



        // Get MethodDef records to add to MethodRef table.
        mdMethodDef mdmdFunc1Invoke = mdMethodDefNil;
        {
            COR_SIGNATURE pSigBlob[] = { 
                IMAGE_CEE_CS_CALLCONV_HASTHIS,  // HASTHIS 
                0,                              // ParamCount
                ELEMENT_TYPE_VAR,               // RetType: VAR
                0                               //          Generic Parameter Index: 0
            };
            ULONG sigBlobSize = sizeof(pSigBlob) / sizeof(COR_SIGNATURE);
            hr = pImpSystemCore->FindMethod(mdtdFunc1, L"Invoke", 
                                            pSigBlob, sigBlobSize, 
                                            &mdmdFunc1Invoke);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        }
        
        D_COUT1("Token of MethodDef for System.Func<T>.Invoke: 0x%|1$08X|", mdmdFunc1Invoke);



        // Get MetaDataAssemblyImport and Assembly record to add to AssemblyRef table.
        CComPtr<IMetaDataAssemblyImport> pAsmImpSystemCore;
        hr = pImpSystemCore->QueryInterface(IID_IMetaDataAssemblyImport, 
                                          reinterpret_cast<void **>(&pAsmImpSystemCore));
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

        mdAssembly mdaSystemCore = mdAssemblyNil;
        hr = pAsmImpSystemCore->GetAssemblyFromScope(&mdaSystemCore);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        D_COUT1("Token of Assembly for System.Core.dll: 0x%|1$08X|", mdaSystemCore);

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

        D_WCOUT1(L"Assembly Name: %|1$s|", systemCoreName.get());



        // Prepare the target assembly.
        // Get IMetaDataAssemblyEmit to add to AssemblyRef table. 
        CComPtr<IMetaDataAssemblyEmit> pAsmEmtMSCorLib;
        hr = m_pEmtMSCorLib->QueryInterface(IID_IMetaDataAssemblyEmit, 
                                            reinterpret_cast<void **>(&pAsmEmtMSCorLib));
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));



        // Add Assembly records retrieved in above to AssemblyRef table.
        mdAssemblyRef mdarMSCorLibPrig = mdAssemblyRefNil;
        hr = pAsmEmtMSCorLib->DefineAssemblyRef(pMSCorLibPrigPubKey.get(), msCorLibPrigPubKeySize, 
                                                msCorLibPrigAsmName.get(), &amdMSCorLibPrig, NULL, 0, 
                                                msCorLibPrigAsmFlags, &mdarMSCorLibPrig);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        D_COUT1("Token of AssemblyRef for mscorlib.Prig.dll: 0x%|1$08X|", mdarMSCorLibPrig);

        mdAssemblyRef mdarSystemCore = mdAssemblyRefNil;
        hr = pAsmEmtMSCorLib->DefineAssemblyRef(pSystemCorePubKey.get(), systemCorePubKeySize, 
                                                systemCoreName.get(), &amdSystemCore, 
                                                NULL, 0, 
                                                systemCoreAsmFlags, &mdarSystemCore);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        D_COUT1("Token of AssemblyRef for System.Core.dll: 0x%|1$08X|", mdarSystemCore);



        // Add to TypeRef table with the name.
        mdTypeRef mdtrFunc1 = mdTypeRefNil;
        hr = m_pEmtMSCorLib->DefineTypeRefByName(mdarSystemCore, L"System.Func`1", &mdtrFunc1);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        D_COUT1("Token of TypeRef for System.Func`1: 0x%|1$08X|", mdtrFunc1);

        mdTypeRef mdtrPDateTime = mdTypeRefNil;
        hr = m_pEmtMSCorLib->DefineTypeRefByName(mdarMSCorLibPrig, L"System.Prig.PDateTime", &mdtrPDateTime);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        D_COUT1("Token of TypeRef for System.Prig.PDateTime: 0x%|1$08X|", mdtrPDateTime);

        mdTypeRef mdtrPDateTimeNowGet = mdTypeRefNil;
        hr = m_pEmtMSCorLib->DefineTypeRefByName(mdtrPDateTime, L"NowGet", &mdtrPDateTimeNowGet);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        D_COUT1("Token of TypeRef for System.Prig.PDateTime+NowGet: 0x%|1$08X|", mdtrPDateTimeNowGet);



        // Add TypeRef records retrieved in above to TypeSpec table.
        mdTypeSpec mdtsSystemFunc1DateTime = mdTypeSpecNil;
        {
            COR_SIGNATURE pSigBlob[] = {
                ELEMENT_TYPE_GENERICINST,       // TYPE: GENERICINST
                ELEMENT_TYPE_CLASS,             //       CLASS
                0x05,                           //       TypeRef: 0x01000001(System.Func`1)
                1,                              //       Generics Arguments Count: 1
                ELEMENT_TYPE_VALUETYPE,         //       VALUETYPE
                0x80,                           //       TypeDef: 0x02000032(System.DateTime)
                0xC8                            // 
            };                                  
            ULONG sigBlobSize = sizeof(pSigBlob) / sizeof(COR_SIGNATURE);
            hr = m_pEmtMSCorLib->GetTokenFromTypeSpec(pSigBlob, sigBlobSize, 
                                                      &mdtsSystemFunc1DateTime);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        }
        
        D_COUT1("Token of TypeSpec for System.Func<DateTime>: 0x%|1$08X|", mdtsSystemFunc1DateTime);



        // Add MethodDef records retrieved in above to MemberRef table.
        mdMemberRef mdmrNowGetget_Body = mdMemberRefNil;
        hr = m_pEmtMSCorLib->DefineImportMember(pAsmImpMSCorLibPrig, NULL, 0, pImpMSCorLibPrig, 
                                                mdmdget_Body, 
                                                pAsmEmtMSCorLib, 
                                                mdtrPDateTimeNowGet, 
                                                &mdmrNowGetget_Body);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        D_COUT1("Token of MemberRef for System.Prig.PDateTime+NowGet.get_Body: 0x%|1$08X|", mdmrNowGetget_Body);

        mdMemberRef mdmrFunc1DateTimeInvoke = mdMemberRefNil;
        hr = m_pEmtMSCorLib->DefineImportMember(pAsmImpSystemCore, NULL, 0, pImpSystemCore, 
                                                mdmdFunc1Invoke, 
                                                pAsmEmtMSCorLib, 
                                                mdtsSystemFunc1DateTime, 
                                                &mdmrFunc1DateTimeInvoke);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        D_COUT1("Token of MemberRef for System.Func<DateTime>.Invoke: 0x%|1$08X|", mdmrFunc1DateTimeInvoke);



        // Get IMethodMalloc to allocate new method body area.
        ClassID classId = 0;
        ModuleID modId = 0;
        mdToken mdt = mdTokenNil;
        hr = m_pInfo->GetFunctionInfo(functionId, &classId, &modId, &mdt);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        CComPtr<IMethodMalloc> pMethodMalloc;
        hr = m_pInfo->GetILFunctionBodyAllocator(modId, &pMethodMalloc);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));



        // Emit the new method body to replace to a delegated process.
        SimpleBlob mbDateTimeget_Body;
        mbDateTimeget_Body.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_CALL].byte2);
        mbDateTimeget_Body.Put<DWORD>(mdmrNowGetget_Body);
        mbDateTimeget_Body.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_CALLVIRT].byte2);
        mbDateTimeget_Body.Put<DWORD>(mdmrFunc1DateTimeInvoke);
        mbDateTimeget_Body.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_RET].byte2);

        COR_ILMETHOD_FAT fatHeader;
        ::ZeroMemory(&fatHeader, sizeof(COR_ILMETHOD_FAT));
        fatHeader.SetMaxStack(1);
        fatHeader.SetCodeSize(mbDateTimeget_Body.Size());
        fatHeader.SetLocalVarSigTok(mdTokenNil);
        fatHeader.SetFlags(0);
        
        unsigned headerSize = COR_ILMETHOD::Size(&fatHeader, false);
        unsigned totalSize = headerSize + mbDateTimeget_Body.Size();


        BYTE *pNewILFunctionBody = reinterpret_cast<BYTE*>(pMethodMalloc->Alloc(totalSize));
        BYTE *pBuffer = pNewILFunctionBody;

        pBuffer += COR_ILMETHOD::Emit(headerSize, &fatHeader, false, pBuffer);
        ::memcpy_s(pBuffer, totalSize - headerSize, mbDateTimeget_Body.Ptr(), 
                   mbDateTimeget_Body.Size());



        // Set new method body!!
        hr = m_pInfo->SetILFunctionBody(modId, mdt, pNewILFunctionBody);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
    }

    return S_OK;
}
