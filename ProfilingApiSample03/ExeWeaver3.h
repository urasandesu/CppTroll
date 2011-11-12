// ExeWeaver3.h : CExeWeaver3 の宣言

#pragma once
#include "resource.h"       // メイン シンボル

#include "ProfilingApiSample03_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM の完全サポートを含んでいない Windows Mobile プラットフォームのような Windows CE プラットフォームでは、単一スレッド COM オブジェクトは正しくサポートされていません。ATL が単一スレッド COM オブジェクトの作成をサポートすること、およびその単一スレッド COM オブジェクトの実装の使用を許可することを強制するには、_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA を定義してください。ご使用の rgs ファイルのスレッド モデルは 'Free' に設定されており、DCOM Windows CE 以外のプラットフォームでサポートされる唯一のスレッド モデルと設定されていました。"
#endif



// CExeWeaver3
#ifdef UNP
#error This .h temporarily reserves the word "UNP" that means "Urasandesu::NAnonym::Profiling".
#else
#define UNP Urasandesu::NAnonym::Profiling

class ATL_NO_VTABLE CExeWeaver3 :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CExeWeaver3, &CLSID_ExeWeaver3>,
    public UNP::ICorProfilerCallback2Impl<ICorProfilerCallback2>,
	public IDispatchImpl<IExeWeaver3, &IID_IExeWeaver3, &LIBID_ProfilingApiSample03Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CExeWeaver3()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EXEWEAVER3)


BEGIN_COM_MAP(CExeWeaver3)
	COM_INTERFACE_ENTRY(IExeWeaver3)
	COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ICorProfilerCallback2)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();

	void FinalRelease();

protected:
    STDMETHOD(InitializeCore)(
        /* [in] */ IUnknown *pICorProfilerInfoUnk);

    STDMETHOD(ShutdownCore)(void);

    STDMETHOD(ModuleLoadStartedCore)( 
        /* [in] */ ModuleID moduleId);

    STDMETHOD(JITCompilationStartedCore)( 
        /* [in] */ FunctionID functionId,
        /* [in] */ BOOL fIsSafeToBlock);

private:
    boost::timer m_timer;

    CComPtr<ICorProfilerInfo2> m_pInfo;
    CComPtr<IMetaDataEmit2> m_pEmtMSCorLib;
};

OBJECT_ENTRY_AUTO(__uuidof(ExeWeaver3), CExeWeaver3)

#undef UNP
#endif
