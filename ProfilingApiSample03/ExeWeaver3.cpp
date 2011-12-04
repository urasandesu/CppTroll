// ExeWeaver3.cpp : CExeWeaver3 の実装

#include "stdafx.h"
#include "ExeWeaver3.h"

//#define OUTPUT_DEBUG_STRING

// CExeWeaver3
HRESULT CExeWeaver3::FinalConstruct()
{
    return S_OK;
}

void CExeWeaver3::FinalRelease()
{
}

HRESULT CExeWeaver3::InitializeCore(
    /* [in] */ IUnknown *pICorProfilerInfoUnk)
{
    using namespace std;
    using namespace Urasandesu::CppAnonym;
    HRESULT hr = E_FAIL;
    
    //::_CrtDbgBreak();
    m_timer.restart();

    hr = pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo2, 
                                              reinterpret_cast<void**>(&m_pInfo));
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

    DWORD event_ = COR_PRF_MONITOR_MODULE_LOADS | 
                   COR_PRF_MONITOR_JIT_COMPILATION | 
                   COR_PRF_USE_PROFILE_IMAGES;
    hr = m_pInfo->SetEventMask(event_);
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

    return S_OK;
}

HRESULT CExeWeaver3::ShutdownCore(void)
{ 
    using namespace std;
    using namespace boost;
    
    cout << format("Time Elapsed: %|1$f|s") % m_timer.elapsed() << endl;

    return S_OK; 
}

HRESULT CExeWeaver3::ModuleLoadStartedCore( 
    /* [in] */ ModuleID moduleId)
{
    using namespace std;
    using namespace boost::filesystem;
    using namespace Urasandesu::CppAnonym;
    HRESULT hr = E_FAIL;

    LPCBYTE pBaseLoadAddress = NULL;
    WCHAR modName[MAX_SYM_NAME] = { 0 };
    ULONG modNameSize = sizeof(modName);
    AssemblyID asmId = 0;
    
    hr = m_pInfo->GetModuleInfo(moduleId, &pBaseLoadAddress, modNameSize, &modNameSize, modName, &asmId);
    if (hr != CORPROF_E_DATAINCOMPLETE && FAILED(hr))
        BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

    path modPath(modName);

#ifdef OUTPUT_DEBUG_STRING
    wcout << L"ModuleLoadStarted: " << modName << endl;
#endif
    if (modPath.filename().wstring() == wstring(L"mscorlib.dll"))
    {
#ifdef OUTPUT_DEBUG_STRING
        wcout << L"YATTA!!" << endl;
#endif        
        hr = m_pInfo->GetModuleMetaData(moduleId, ofRead | ofWrite, IID_IMetaDataEmit2, reinterpret_cast<IUnknown **>(&m_pEmtMSCorLib));
        if (hr != CORPROF_E_DATAINCOMPLETE && FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
    }

    return S_OK;
}

HRESULT CExeWeaver3::JITCompilationStartedCore( 
    /* [in] */ FunctionID functionId,
    /* [in] */ BOOL fIsSafeToBlock)
{
#if 1
    namespace OpCodes = Urasandesu::CppAnonym::MetaData::OpCodes;
    using namespace std;
    using namespace boost;
    using namespace boost::filesystem;
    using namespace Urasandesu::CppAnonym;
    HRESULT hr = E_FAIL;

    mdMethodDef mdmd = mdMethodDefNil;
    CComPtr<IMetaDataImport2> pImport;
    hr = m_pInfo->GetTokenAndMetaDataFromFunction(functionId, IID_IMetaDataImport2, 
                                                  reinterpret_cast<IUnknown **>(&pImport), 
                                                  &mdmd);
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

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

    WCHAR typeName[MAX_SYM_NAME] = { 0 };
    ULONG typeNameSize = sizeof(typeName);
    DWORD typeAttr = 0;
    mdToken mdtTypeExtends = mdTokenNil;
    hr = pImport->GetTypeDefProps(mdtd, typeName, typeNameSize, &typeNameSize, 
                                  &typeAttr, &mdtTypeExtends);
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

#ifdef OUTPUT_DEBUG_STRING
    wcout << L"JITCompilationStarted: " << typeName << "." << methodName << endl;
#endif
    
    wstring methodFullName(typeName);
    methodFullName += L".";
    methodFullName += methodName;
#if 1
    if (methodFullName == wstring(L"System.DateTime.get_Now"))
    {
#ifdef OUTPUT_DEBUG_STRING
        wcout << L"YATTA!! YATTA!!" << endl;
#endif
        
        path msCorLibPrigPath(L"C:\\Documents and Settings\\Administrator\\CppTroll\\Debug\\mscorlib.Prig.dll");
        
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
        


        mdTypeDef mdtdPDateTime = mdTypeDefNil;
        hr = pImpMSCorLibPrig->FindTypeDefByName(L"System.Prig.PDateTime", NULL, &mdtdPDateTime);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of TypeDef for System.Prig.PDateTime: 0x%|1$08X|") % mdtdPDateTime << endl;

        mdTypeDef mdtdNowGet = mdTypeDefNil;
        hr = pImpMSCorLibPrig->FindTypeDefByName(L"NowGet", mdtdPDateTime, &mdtdNowGet);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        cout << format("Token of TypeDef for System.Prig.PDateTime+NowGet: 0x%|1$08X|") % mdtdNowGet << endl;
        


        mdMethodDef mdmdget_Body = mdMethodDefNil;
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
            hr = pImpMSCorLibPrig->FindMethod(mdtdNowGet, L"get_Body", pSigBlob, sigBlobSize, &mdmdget_Body);            
            
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        }
        
        cout << format("Token of MethodDef for System.Prig.PDateTime+NowGet.get_Body: 0x%|1$08X|") % mdmdget_Body << endl;
        
        

#if 0        
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
#endif
        
#if 0        
        CComPtr<IMetaDataAssemblyImport> pAsmImpMSCorLibPrig;
        hr = pImpMSCorLibPrig->QueryInterface(IID_IMetaDataAssemblyImport, 
                                       reinterpret_cast<void **>(&pAsmImpMSCorLibPrig));
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

        mdAssembly mdaMSCorLibPrig = mdAssemblyNil;
        hr = pAsmImpMSCorLibPrig->GetAssemblyFromScope(&mdaMSCorLibPrig);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

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

        CComPtr<IMetaDataAssemblyEmit> pAsmEmtMSCorLib;
        hr = m_pEmtMSCorLib->QueryInterface(IID_IMetaDataAssemblyEmit, 
                                            reinterpret_cast<void **>(&pAsmEmtMSCorLib));
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

        mdAssemblyRef mdarMSCorLibPrig = mdAssemblyRefNil;
        hr = pAsmEmtMSCorLib->DefineAssemblyRef(pMSCorLibPrigPubKey.get(), msCorLibPrigPubKeySize, 
                                                msCorLibPrigAsmName.get(), &amdMSCorLibPrig, NULL, 0, 
                                                msCorLibPrigAsmFlags, &mdarMSCorLibPrig);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        
        

        mdTypeRef mdtrADateTime = mdTypeRefNil;
        hr = m_pEmtMSCorLib->DefineTypeRefByName(mdarMSCorLibPrig, L"Anonym.System.ADateTime", &mdtrADateTime);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
        
        
        
        mdMemberRef mdmrget_Body = mdMemberRefNil;
        hr = m_pEmtMSCorLib->DefineImportMember(pAsmImpMSCorLibPrig, NULL, 0, pImpMSCorLibPrig,
                                                mdmdget_Body, 
                                                pAsmEmtMSCorLib, 
                                                mdtrADateTime, 
                                                &mdmrget_Body);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
        
#ifdef OUTPUT_DEBUG_STRING
        cout << format("MemberRef Token in MSCorLib: %|1$08X|") % mdmrget_Body << endl;
#endif

        
        
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



        SimpleBlob mbDateTimeget_Body;
        mbDateTimeget_Body.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_CALL].byte2);
        mbDateTimeget_Body.Put<DWORD>(mdmrget_Body);
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
        
        // When this process is enabled, the count of JIT compilation increases 2-fold :(
        // It seems that the validation of added assembly is performed...
#if 1
        hr = m_pInfo->SetILFunctionBody(modId, mdt, pNewILFunctionBody);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
#endif
#endif
    }
#endif
#endif
    return S_OK;
}
