// ExeWeaver3.cpp : CExeWeaver3 の実装

#include "stdafx.h"
#include "ExeWeaver3.h"


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

HRESULT CExeWeaver3::ModuleLoadStartedCore( 
    /* [in] */ ModuleID moduleId)
{
    using namespace std;
    using namespace Urasandesu::NAnonym;
    HRESULT hr = E_FAIL;

    LPCBYTE pBaseLoadAddress = NULL;
    WCHAR modName[MAX_SYM_NAME] = { 0 };
    ULONG modNameSize = sizeof(modName);
    AssemblyID asmId = 0;
    
    hr = m_pInfo->GetModuleInfo(moduleId, &pBaseLoadAddress, modNameSize, &modNameSize, modName, &asmId);
    if (hr != CORPROF_E_DATAINCOMPLETE && FAILED(hr))
        BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));

    wcout << L"ModuleLoadStarted: " << modName << endl;

    return S_OK;
}

HRESULT CExeWeaver3::JITCompilationStartedCore( 
    /* [in] */ FunctionID functionId,
    /* [in] */ BOOL fIsSafeToBlock)
{
    using namespace std;
    using namespace Urasandesu::NAnonym;
    HRESULT hr = E_FAIL;

    mdMethodDef mdmd = mdMethodDefNil;
    CComPtr<IMetaDataImport2> pImport;
    hr = m_pInfo->GetTokenAndMetaDataFromFunction(functionId, IID_IMetaDataImport2, 
                                                  reinterpret_cast<IUnknown**>(&pImport), 
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

    wcout << L"JITCompilationStarted: " << typeName << "." << methodName << endl;

    return S_OK;
}
