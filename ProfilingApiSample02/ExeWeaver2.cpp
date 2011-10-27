// ExeWeaver2.cpp : CExeWeaver2 の実装

#include "stdafx.h"
#include "ExeWeaver2.h"

// CExeWeaver2
HRESULT CExeWeaver2::FinalConstruct()
{
    using namespace boost;
    using namespace Urasandesu::NAnonym::MetaData;
    using namespace Urasandesu::NAnonym::Profiling;
    using namespace Urasandesu::NAnonym::Utilities;
    
    m_pProfInfo = make_shared<ProfilingInfo>();
    m_pMetaInfo = make_shared<MetaDataInfo>();
    m_pConv = make_shared<ValueConverter<AssemblyMetaData *, ProcessProfile *>>();

    m_pTargetAssemblyProf = NULL;
    m_mdtdReplaceTypeFrom = mdTypeDefNil;
    m_mdmdReplaceMethodFrom = mdMethodDefNil;
    m_mdtdReplaceTypeTo = mdTypeDefNil;
    m_mdtdReplaceMethodTo = mdMethodDefNil;

	return S_OK;
}

void CExeWeaver2::FinalRelease()
{
}

HRESULT CExeWeaver2::COMError(HRESULT hr, LPCSTR filePath, INT line)
{
    using std::wostringstream;

    wostringstream msg;
    msg << _com_error(hr).ErrorMessage();
    msg << ", File: " << filePath;
    msg << ", Line: " << line;
    return Error(msg.str().c_str());
}

STDMETHODIMP CExeWeaver2::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IExeWeaver2
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}



HRESULT CExeWeaver2::InitializeCore( 
    /* [in] */ IUnknown *pICorProfilerInfoUnk)
{
    using namespace std;
    using namespace boost;
    using namespace Urasandesu::NAnonym;
    using namespace Urasandesu::NAnonym::MetaData;


    // Initialize the unmanaged profiling API.
    m_pProfInfo->Init(pICorProfilerInfoUnk);
    m_pProfInfo->SetEventMask(COR_PRF_MONITOR_ASSEMBLY_LOADS | 
                              COR_PRF_MONITOR_MODULE_LOADS | 
                              COR_PRF_MONITOR_APPDOMAIN_LOADS | 
                              COR_PRF_MONITOR_JIT_COMPILATION);


    // Get name of the target assembly.
    {
        m_targetAssemblyName = wstring(CA2W(Environment::GetEnvironmentVariable("NANONYM_TARGET_ASSEMBLY").c_str()));
        wcout << wformat(L"Target Assembly: %|1$s|") % m_targetAssemblyName << endl;
    }
    
    // Get token of the replaced type.
    {
        istringstream is(Environment::GetEnvironmentVariable("NANONYM_REPLACE_TYPE_FROM"));
        is >> hex >> m_mdtdReplaceTypeFrom;
        cout << format("Replaced Type Token: 0x%|1$08X|") % m_mdtdReplaceTypeFrom << endl;
    }
    
    // Get token of the replaced method.
    {
        istringstream is(Environment::GetEnvironmentVariable("NANONYM_REPLACE_METHOD_FROM"));
        is >> hex >> m_mdmdReplaceMethodFrom;
        cout << format("Replaced Method Token: 0x%|1$08X|") % m_mdmdReplaceMethodFrom << endl;
    }
    
    // Get token of the replacing type.
    {
        istringstream is(Environment::GetEnvironmentVariable("NANONYM_REPLACE_TYPE_TO"));
        is >> hex >> m_mdtdReplaceTypeTo;
        cout << format("Replacing Type Token: 0x%|1$08X|") % m_mdtdReplaceTypeTo << endl;
    }
    
    // Get token of the replacing method.
    {
        istringstream is(Environment::GetEnvironmentVariable("NANONYM_REPLACE_METHOD_TO"));
        is >> hex >> m_mdtdReplaceMethodTo;
        cout << format("Replacing Method Token: 0x%|1$08X|") % m_mdtdReplaceMethodTo << endl;
    }

    // Create pseudo AppDomain to load mscorlib.dll.
    m_pProfInfo->GetCurrentProcess()->GetPseudoDomain();

    return S_OK;
}

HRESULT CExeWeaver2::AppDomainCreationStartedCore( 
    /* [in] */ AppDomainID appDomainId)
{ 
    using namespace std;
    using namespace boost;
    using namespace Urasandesu::NAnonym;
    using namespace Urasandesu::NAnonym::MetaData;
    using namespace Urasandesu::NAnonym::Profiling;
    
    cout << format("AppDomain Creation Started(ID: 0x%|1$08X|)") % appDomainId << endl;
    m_pProfInfo->GetCurrentProcess()->CreateIfNecessary<AppDomainProfile>(appDomainId);

    return S_OK; 
}

HRESULT CExeWeaver2::AppDomainCreationFinishedCore( 
    /* [in] */ AppDomainID appDomainId,
    /* [in] */ HRESULT hrStatus)
{ 
    using namespace std;
    using namespace boost;
    cout << format("AppDomain Creation Finished(ID: 0x%|1$08X|)") % appDomainId << endl;
    return S_OK;
}

HRESULT CExeWeaver2::AssemblyLoadStartedCore( 
    /* [in] */ AssemblyID assemblyId)
{
    using namespace std;
    using namespace boost;
    using namespace Urasandesu::NAnonym;
    using namespace Urasandesu::NAnonym::MetaData;
    using namespace Urasandesu::NAnonym::Profiling;
    
    AppDomainProfile *pDomainProf = m_pProfInfo->GetCurrentProcess()->GetCurrentDomain();
    AssemblyProfile *pAsmProf = pDomainProf->CreateIfNecessary<AssemblyProfile>(assemblyId);
    wcout << wformat(L"Assembly Load Started: %|1$s|") % pAsmProf->GetName() << endl;
    if (pAsmProf->GetName() != m_targetAssemblyName)
        return S_OK;
    
    cout << "Target Assembly Found" << endl;
    m_pTargetAssemblyProf = pAsmProf;

    return S_OK;
}

HRESULT CExeWeaver2::ModuleLoadStartedCore( 
    /* [in] */ ModuleID moduleId)
{
    using namespace std;
    using namespace boost;
    using namespace Urasandesu::NAnonym;
    using namespace Urasandesu::NAnonym::MetaData;
    using namespace Urasandesu::NAnonym::Profiling;
    
    cout << format("Module Load Started(ID: 0x%|1$08X|)") % moduleId << endl;
    if (m_pTargetAssemblyProf == NULL || m_pConv->HasInitialized())
        return S_OK;
    
    ModuleProfile *pModProf = m_pTargetAssemblyProf->CreateIfNecessary<ModuleProfile>(moduleId);
    wcout << wformat(L"Module Analysis Started: %|1$s|") % pModProf->GetName() << endl;
    AssemblyMetaData *pAsmMeta = m_pMetaInfo->CreatePseudo<AssemblyMetaData>();
    m_pConv->Initialize(pAsmMeta, m_pProfInfo->GetCurrentProcess(), pModProf);

    return S_OK;
}

HRESULT CExeWeaver2::ModuleLoadFinishedCore( 
    /* [in] */ ModuleID moduleId,
    /* [in] */ HRESULT hrStatus)
{
    using namespace std;
    using namespace boost;
    cout << format("Module Load Finished(ID: 0x%|1$08X|)") % moduleId << endl;
    return S_OK;
}

HRESULT CExeWeaver2::JITCompilationStartedCore( 
    /* [in] */ FunctionID functionId,
    /* [in] */ BOOL fIsSafeToBlock)
{
    using namespace std;
    using namespace boost;
    using namespace Urasandesu::NAnonym;
    using namespace Urasandesu::NAnonym::MetaData;
    using namespace Urasandesu::NAnonym::Profiling;
    
    if (!m_pConv->HasInitialized())
        return S_OK;

    MethodProfile *pMethodProfFrom = m_pProfInfo->GetCurrentProcess()->CreateIfNecessary<MethodProfile>(functionId);
    MethodMetaData *pMethodMetaFrom = m_pConv->Convert(pMethodProfFrom);
    cout << format("Current Method Token: 0x%|1$08X|") % pMethodMetaFrom->GetToken() << endl;
    if (pMethodMetaFrom->GetToken() != m_mdmdReplaceMethodFrom)
        return S_OK;


    TypeMetaData *pTypeMetaFrom = pMethodMetaFrom->GetDeclaringType();
    cout << format("Current Type Token: 0x%|1$08X|") % pTypeMetaFrom->GetToken() << endl;
    if (pTypeMetaFrom->GetToken() != m_mdtdReplaceTypeFrom)
        return S_OK;

    cout << "Conditions Right: Method Body Replace Started" << endl;

    ModuleMetaData *pModMetaFrom = pTypeMetaFrom->GetModule();
    TypeMetaData *pTypeMetaTo = pModMetaFrom->GetType(m_mdtdReplaceTypeTo);
    TypeProfile *pTypeProfTo = m_pConv->ConvertBack(pTypeMetaTo);   // NOTE: To resolve the type defined explicitly 
    MethodMetaData *pMethodMetaTo = pTypeMetaTo->GetMethod(m_mdtdReplaceMethodTo);
    MethodProfile *pMethodProfTo = m_pConv->ConvertBack(pMethodMetaTo);
    MethodBodyProfile *pBodyProfTo = pMethodProfTo->GetMethodBody();
    pMethodProfFrom->SetMethodBody(pBodyProfTo);

    return S_OK;
}
