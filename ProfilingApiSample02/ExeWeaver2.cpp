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
    using namespace Urasandesu::NAnonym;


    // Reset the timer.
    m_timer.restart();


    // Initialize the unmanaged profiling API.
    m_pProfInfo->Init(pICorProfilerInfoUnk);
    m_pProfInfo->SetEventMask(COR_PRF_MONITOR_ASSEMBLY_LOADS | 
                              COR_PRF_MONITOR_MODULE_LOADS | 
                              COR_PRF_MONITOR_APPDOMAIN_LOADS | 
                              COR_PRF_MONITOR_JIT_COMPILATION);


    // Get name of the target assembly, replaced method and its declaring type and 
    // replacing method and its declaring type.
    m_targetAssemblyName = wstring(CA2W(Environment::GetEnvironmentVariable("NANONYM_TARGET_ASSEMBLY").c_str()));
    {
        istringstream is(Environment::GetEnvironmentVariable("NANONYM_REPLACE_TYPE_FROM"));
        is >> hex >> m_mdtdReplaceTypeFrom;
    }
    {
        istringstream is(Environment::GetEnvironmentVariable("NANONYM_REPLACE_METHOD_FROM"));
        is >> hex >> m_mdmdReplaceMethodFrom;
    }
    {
        istringstream is(Environment::GetEnvironmentVariable("NANONYM_REPLACE_TYPE_TO"));
        is >> hex >> m_mdtdReplaceTypeTo;
    }
    {
        istringstream is(Environment::GetEnvironmentVariable("NANONYM_REPLACE_METHOD_TO"));
        is >> hex >> m_mdtdReplaceMethodTo;
    }


    // Create pseudo AppDomain to load mscorlib.dll.
    m_pProfInfo->GetCurrentProcess()->GetPseudoDomain();


    return S_OK;
}

HRESULT CExeWeaver2::ShutdownCore(void)
{ 
    using namespace std;
    using namespace boost;
    
    // Display the time elapsed.
    cout << format("Time Elapsed: %|1$f|s") % m_timer.elapsed() << endl;

    return S_OK; 
}

HRESULT CExeWeaver2::AppDomainCreationStartedCore( 
    /* [in] */ AppDomainID appDomainId)
{ 
    using namespace Urasandesu::NAnonym::Profiling;

    // Create the wrapper referring the AppDomainID.
    m_pProfInfo->GetCurrentProcess()->CreateIfNecessary<AppDomainProfile>(appDomainId);

    return S_OK; 
}

HRESULT CExeWeaver2::AssemblyLoadStartedCore( 
    /* [in] */ AssemblyID assemblyId)
{
    using namespace Urasandesu::NAnonym::Profiling;

    // Create the wrapper referring the AssemblyID through the current AppDoamin.    
    AppDomainProfile *pDomainProf = m_pProfInfo->GetCurrentProcess()->GetCurrentDomain();
    AssemblyProfile *pAsmProf = pDomainProf->CreateIfNecessary<AssemblyProfile>(assemblyId);
    if (pAsmProf->GetName() != m_targetAssemblyName)
        return S_OK;
    
    m_pTargetAssemblyProf = pAsmProf;

    return S_OK;
}

HRESULT CExeWeaver2::ModuleLoadStartedCore( 
    /* [in] */ ModuleID moduleId)
{
    using namespace Urasandesu::NAnonym::MetaData;
    using namespace Urasandesu::NAnonym::Profiling;

    if (m_pTargetAssemblyProf == NULL || m_pConv->HasInitialized())
        return S_OK;
    
    // Initialize the value converter to convert the wrapper of the profiling API 
    // to the wrapper of the meta data API.
    ModuleProfile *pModProf = m_pTargetAssemblyProf->CreateIfNecessary<ModuleProfile>(moduleId);
    AssemblyMetaData *pAsmMeta = m_pMetaInfo->CreatePseudo<AssemblyMetaData>();
    m_pConv->Initialize(pAsmMeta, m_pProfInfo->GetCurrentProcess(), pModProf);

    return S_OK;
}

HRESULT CExeWeaver2::JITCompilationStartedCore( 
    /* [in] */ FunctionID functionId,
    /* [in] */ BOOL fIsSafeToBlock)
{
    using namespace Urasandesu::NAnonym::MetaData;
    using namespace Urasandesu::NAnonym::Profiling;
    
    if (!m_pConv->HasInitialized())
        return S_OK;

    // Get the properties this method.
    MethodProfile *pMethodProfFrom = m_pProfInfo->GetCurrentProcess()->CreateIfNecessary<MethodProfile>(functionId);
    MethodMetaData *pMethodMetaFrom = m_pConv->Convert(pMethodProfFrom);
    if (pMethodMetaFrom->GetToken() != m_mdmdReplaceMethodFrom)
        return S_OK;

    
    // Get the properties of the type that this method is declared.
    TypeMetaData *pTypeMetaFrom = pMethodMetaFrom->GetDeclaringType();
    if (pTypeMetaFrom->GetToken() != m_mdtdReplaceTypeFrom)
        return S_OK;

    
    // Replace the IL method body of them that are set above.
    ModuleMetaData *pModMetaFrom = pTypeMetaFrom->GetModule();
    TypeMetaData *pTypeMetaTo = pModMetaFrom->GetType(m_mdtdReplaceTypeTo);
    TypeProfile *pTypeProfTo = m_pConv->ConvertBack(pTypeMetaTo);   // NOTE: To resolve the type defined explicitly 
    MethodMetaData *pMethodMetaTo = pTypeMetaTo->GetMethod(m_mdtdReplaceMethodTo);
    MethodProfile *pMethodProfTo = m_pConv->ConvertBack(pMethodMetaTo);
    MethodBodyProfile *pBodyProfTo = pMethodProfTo->GetMethodBody();
    pMethodProfFrom->SetMethodBody(pBodyProfTo);

    return S_OK;
}
