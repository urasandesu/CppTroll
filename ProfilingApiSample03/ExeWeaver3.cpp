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
    using namespace Urasandesu::NAnonym;
    HRESULT hr = E_FAIL;
    
    //::_CrtDbgBreak();
    m_timer.restart();

    hr = pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo2, 
                                              reinterpret_cast<void**>(&m_pInfo));
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));

    DWORD event_ = COR_PRF_MONITOR_MODULE_LOADS | 
                   COR_PRF_MONITOR_JIT_COMPILATION | 
                   COR_PRF_USE_PROFILE_IMAGES;
    hr = m_pInfo->SetEventMask(event_);
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));

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
    using namespace Urasandesu::NAnonym;
    HRESULT hr = E_FAIL;

    LPCBYTE pBaseLoadAddress = NULL;
    WCHAR modName[MAX_SYM_NAME] = { 0 };
    ULONG modNameSize = sizeof(modName);
    AssemblyID asmId = 0;
    
    hr = m_pInfo->GetModuleInfo(moduleId, &pBaseLoadAddress, modNameSize, &modNameSize, modName, &asmId);
    if (hr != CORPROF_E_DATAINCOMPLETE && FAILED(hr))
        BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));

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
            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
    }

    return S_OK;
}

HRESULT CExeWeaver3::JITCompilationStartedCore( 
    /* [in] */ FunctionID functionId,
    /* [in] */ BOOL fIsSafeToBlock)
{
#if 1
    namespace OpCodes = Urasandesu::NAnonym::MetaData::OpCodes;
    using namespace std;
    using namespace boost;
    using namespace boost::filesystem;
    using namespace Urasandesu::NAnonym;
    HRESULT hr = E_FAIL;

    mdMethodDef mdmd = mdMethodDefNil;
    CComPtr<IMetaDataImport2> pImport;
    hr = m_pInfo->GetTokenAndMetaDataFromFunction(functionId, IID_IMetaDataImport2, 
                                                  reinterpret_cast<IUnknown **>(&pImport), 
                                                  &mdmd);
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));

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
        BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));

    WCHAR typeName[MAX_SYM_NAME] = { 0 };
    ULONG typeNameSize = sizeof(typeName);
    DWORD typeAttr = 0;
    mdToken mdtTypeExtends = mdTokenNil;
    hr = pImport->GetTypeDefProps(mdtd, typeName, typeNameSize, &typeNameSize, 
                                  &typeAttr, &mdtTypeExtends);
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));

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
        
        path patch(L"C:\\Documents and Settings\\Administrator\\CppTroll\\Debug\\ProfilingApiSample03Patch.dll");
        
        CComPtr<IMetaDataDispenserEx> pDispPatch;
        hr = ::CoCreateInstance(CLSID_CorMetaDataDispenser, NULL, CLSCTX_INPROC_SERVER, 
                                IID_IMetaDataDispenserEx, 
                                reinterpret_cast<void **>(&pDispPatch));
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
        
        
        CComPtr<IMetaDataImport2> pImpPatch;
        hr = pDispPatch->OpenScope(patch.c_str(), ofRead, IID_IMetaDataImport2, 
                                      reinterpret_cast<IUnknown **>(&pImpPatch));
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
        


        mdTypeDef mdtdADateTime = mdTypeDefNil;
        hr = pImpPatch->FindTypeDefByName(L"Anonym.System.ADateTime", NULL, &mdtdADateTime);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));

        
        
        mdMethodDef mdmdget_Now = mdMethodDefNil;
        {
            COR_SIGNATURE pSigBlob[] = { 
                IMAGE_CEE_CS_CALLCONV_DEFAULT,  // DEFAULT  
                0,                              // ParamCount
                ELEMENT_TYPE_VALUETYPE,         // RetType
                0x09                            // RetTypeDetail(Encoded TypeRef Token: System.DateTime/*01000002*/)
            };
            ULONG sigBlobSize = sizeof(pSigBlob) / sizeof(COR_SIGNATURE);
            hr = pImpPatch->FindMethod(mdtdADateTime, L"get_Now", pSigBlob, sigBlobSize, &mdmdget_Now);            
            
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
        }
        
        
        
        
        CComPtr<IMetaDataAssemblyImport> pAsmImpPatch;
        hr = pImpPatch->QueryInterface(IID_IMetaDataAssemblyImport, 
                                       reinterpret_cast<void **>(&pAsmImpPatch));
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));

        mdAssembly mdaPatch = mdAssemblyNil;
        hr = pAsmImpPatch->GetAssemblyFromScope(&mdaPatch);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));

        auto_ptr<PublicKeyBlob> pPatchPubKey;
        DWORD patchPubKeySize = 0;
        auto_ptr<WCHAR> patchAsmName;
        ASSEMBLYMETADATA amdPatch;
        ::ZeroMemory(&amdPatch, sizeof(ASSEMBLYMETADATA));
        DWORD patchAsmFlags = 0;
        {
            ULONG nameSize = 0;
            DWORD asmFlags = 0;
            hr = pAsmImpPatch->GetAssemblyProps(mdaPatch, NULL, NULL, NULL, NULL, 0, 
                                                &nameSize, &amdPatch, 
                                                &asmFlags);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));

            patchAsmFlags |= (asmFlags & ~afPublicKey);
            patchAsmName = auto_ptr<WCHAR>(new WCHAR[nameSize]);
            amdPatch.szLocale = amdPatch.cbLocale ? new WCHAR[amdPatch.cbLocale] : NULL;
            amdPatch.rOS = amdPatch.ulOS ? new OSINFO[amdPatch.ulOS] : NULL;
            amdPatch.rProcessor = amdPatch.ulProcessor ? new ULONG[amdPatch.ulProcessor] : NULL;

            void *pPubKey = NULL;
            hr = pAsmImpPatch->GetAssemblyProps(mdaPatch, 
                                                const_cast<const void**>(&pPubKey), 
                                                &patchPubKeySize, NULL, 
                                                patchAsmName.get(), nameSize, NULL, 
                                                &amdPatch, NULL);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));

            if (patchPubKeySize)
                if (!::StrongNameTokenFromPublicKey(reinterpret_cast<BYTE*>(pPubKey), 
                                                    patchPubKeySize, 
                                                    reinterpret_cast<BYTE**>(&pPubKey), 
                                                    &patchPubKeySize))
                    BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));

            pPatchPubKey = auto_ptr<PublicKeyBlob>(
                            reinterpret_cast<PublicKeyBlob*>(new BYTE[patchPubKeySize]));
            ::memcpy_s(pPatchPubKey.get(), patchPubKeySize, pPubKey, 
                       patchPubKeySize);

            if (patchPubKeySize)
                ::StrongNameFreeBuffer(reinterpret_cast<BYTE*>(pPubKey));
        }

        CComPtr<IMetaDataAssemblyEmit> pAsmEmtMSCorLib;
        hr = m_pEmtMSCorLib->QueryInterface(IID_IMetaDataAssemblyEmit, 
                                            reinterpret_cast<void **>(&pAsmEmtMSCorLib));
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));

        mdAssemblyRef mdarPatch = mdAssemblyRefNil;
        hr = pAsmEmtMSCorLib->DefineAssemblyRef(pPatchPubKey.get(), patchPubKeySize, 
                                                patchAsmName.get(), &amdPatch, NULL, 0, 
                                                patchAsmFlags, &mdarPatch);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
        
        
        

        mdTypeRef mdtrADateTime = mdTypeRefNil;
        hr = m_pEmtMSCorLib->DefineTypeRefByName(mdarPatch, L"Anonym.System.ADateTime", &mdtrADateTime);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
        
        
        
        
        mdMemberRef mdmrget_Now = mdMemberRefNil;
        hr = m_pEmtMSCorLib->DefineImportMember(pAsmImpPatch, NULL, 0, pImpPatch,
                                                mdmdget_Now, 
                                                pAsmEmtMSCorLib, 
                                                mdtrADateTime, 
                                                &mdmrget_Now);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
        
#ifdef OUTPUT_DEBUG_STRING
        cout << format("MemberRef Token in MSCorLib: %|1$08X|") % mdmrget_Now << endl;
#endif

        
        
        ClassID classId = 0;
        ModuleID modId = 0;
        mdToken mdt = mdTokenNil;
        hr = m_pInfo->GetFunctionInfo(functionId, &classId, &modId, &mdt);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
        
        CComPtr<IMethodMalloc> pMethodMalloc;
        hr = m_pInfo->GetILFunctionBodyAllocator(modId, &pMethodMalloc);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));



        SimpleBlob mbDateTimeget_Now;
        mbDateTimeget_Now.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_CALL].byte2);
        mbDateTimeget_Now.Put<DWORD>(mdmrget_Now);
        mbDateTimeget_Now.Put<BYTE>(OpCodes::Encodings[OpCodes::CEE_RET].byte2);

        COR_ILMETHOD_FAT fatHeader;
        ::ZeroMemory(&fatHeader, sizeof(COR_ILMETHOD_FAT));
        fatHeader.SetMaxStack(1);
        fatHeader.SetCodeSize(mbDateTimeget_Now.Size());
        fatHeader.SetLocalVarSigTok(mdTokenNil);
        fatHeader.SetFlags(0);
        
        unsigned headerSize = COR_ILMETHOD::Size(&fatHeader, false);
        unsigned totalSize = headerSize + mbDateTimeget_Now.Size();


        BYTE *pNewILFunctionBody = reinterpret_cast<BYTE*>(pMethodMalloc->Alloc(totalSize));
        BYTE *pBuffer = pNewILFunctionBody;

        pBuffer += COR_ILMETHOD::Emit(headerSize, &fatHeader, false, pBuffer);
        ::memcpy_s(pBuffer, totalSize - headerSize, mbDateTimeget_Now.Ptr(), 
                   mbDateTimeget_Now.Size());
        
        // When this process is enabled, the count of JIT compilation increases 2-fold :(
        // It seems that the validation of added assembly is performed...
#if 1
        hr = m_pInfo->SetILFunctionBody(modId, mdt, pNewILFunctionBody);
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
#endif
    }
#endif
#endif
    return S_OK;
}
