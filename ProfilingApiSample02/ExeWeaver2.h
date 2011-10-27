// ExeWeaver2.h : CExeWeaver2 の宣言

#pragma once
#include "resource.h"       // メイン シンボル

#include "ProfilingApiSample02_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM の完全サポートを含んでいない Windows Mobile プラットフォームのような Windows CE プラットフォームでは、単一スレッド COM オブジェクトは正しくサポートされていません。ATL が単一スレッド COM オブジェクトの作成をサポートすること、およびその単一スレッド COM オブジェクトの実装の使用を許可することを強制するには、_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA を定義してください。ご使用の rgs ファイルのスレッド モデルは 'Free' に設定されており、DCOM Windows CE 以外のプラットフォームでサポートされる唯一のスレッド モデルと設定されていました。"
#endif

// CExeWeaver2

#ifdef UNM
#error This .h reserves the word "UNM" that means "Urasandesu::NAnonym::MetaData".
#endif
#define UNM Urasandesu::NAnonym::MetaData

#ifdef UNP
#error This .h reserves the word "UNP" that means "Urasandesu::NAnonym::Profiling".
#endif
#define UNP Urasandesu::NAnonym::Profiling

#ifdef UNT
#error This .h reserves the word "UNT" that means "Urasandesu::NAnonym::Traits".
#endif
#define UNT Urasandesu::NAnonym::Traits

#ifdef UNU
#error This .h reserves the word "UNU" that means "Urasandesu::NAnonym::Utilities".
#endif
#define UNU Urasandesu::NAnonym::Utilities

class ATL_NO_VTABLE CExeWeaver2 :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CExeWeaver2, &CLSID_ExeWeaver2>,
	public ISupportErrorInfo,
	public UNP::ICorProfilerCallback2Impl<ICorProfilerCallback2>,
	public IDispatchImpl<IExeWeaver2, &IID_IExeWeaver2, &LIBID_ProfilingApiSample02Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CExeWeaver2()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EXEWEAVER2)


BEGIN_COM_MAP(CExeWeaver2)
	COM_INTERFACE_ENTRY(IExeWeaver2)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(ICorProfilerCallback2)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();

	void FinalRelease();

	HRESULT COMError(HRESULT hr, LPCSTR filePath, INT line);

protected:
    STDMETHOD(InitializeCore)(
        /* [in] */ IUnknown *pICorProfilerInfoUnk);

    STDMETHOD(AppDomainCreationStartedCore)( 
        /* [in] */ AppDomainID appDomainId);

    STDMETHOD(AppDomainCreationFinishedCore)( 
        /* [in] */ AppDomainID appDomainId,
        /* [in] */ HRESULT hrStatus);

    STDMETHOD(AssemblyLoadStartedCore)( 
        /* [in] */ AssemblyID assemblyId);

    STDMETHOD(ModuleLoadStartedCore)( 
        /* [in] */ ModuleID moduleId);

    STDMETHOD(ModuleLoadFinishedCore)( 
        /* [in] */ ModuleID moduleId,
        /* [in] */ HRESULT hrStatus);

    STDMETHOD(JITCompilationStartedCore)( 
        /* [in] */ FunctionID functionId,
        /* [in] */ BOOL fIsSafeToBlock);

private:
    boost::shared_ptr<UNP::ProfilingInfo> m_pProfInfo;
    boost::shared_ptr<UNM::MetaDataInfo> m_pMetaInfo;
    boost::shared_ptr<UNU::ValueConverter<UNM::AssemblyMetaData *, UNP::ProcessProfile *>> m_pConv;

    UNP::AssemblyProfile *m_pTargetAssemblyProf;
    std::wstring m_targetAssemblyName;    
    mdTypeDef m_mdtdReplaceTypeFrom;
    mdMethodDef m_mdmdReplaceMethodFrom;
    mdTypeDef m_mdtdReplaceTypeTo;
    mdMethodDef m_mdtdReplaceMethodTo;
};

#undef UNU
#undef UNT
#undef UNM
#undef UNP

OBJECT_ENTRY_AUTO(__uuidof(ExeWeaver2), CExeWeaver2)
