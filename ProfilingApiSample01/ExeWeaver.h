// ExeWeaver.h : CExeWeaver の宣言

#pragma once
#include "resource.h"       // メイン シンボル

#include "ProfilingApiSample01_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM の完全サポートを含んでいない Windows Mobile プラットフォームのような Windows CE プラットフォームでは、単一スレッド COM オブジェクトは正しくサポートされていません。ATL が単一スレッド COM オブジェクトの作成をサポートすること、およびその単一スレッド COM オブジェクトの実装の使用を許可することを強制するには、_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA を定義してください。ご使用の rgs ファイルのスレッド モデルは 'Free' に設定されており、DCOM Windows CE 以外のプラットフォームでサポートされる唯一のスレッド モデルと設定されていました。"
#endif



// CExeWeaver

#ifdef UNP
#error This .h reserves the word "UNP" that means "Urasandesu::NAnonym::Profiling".
#else
#define UNP Urasandesu::NAnonym::Profiling

class ATL_NO_VTABLE CExeWeaver :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CExeWeaver, &CLSID_ExeWeaver>,
    public ISupportErrorInfo,
    public UNP::ICorProfilerCallback2Impl<ICorProfilerCallback2>,
    public IDispatchImpl<IExeWeaver, &IID_IExeWeaver, &LIBID_ProfilingApiSample01Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
    CExeWeaver()
    {
    }

DECLARE_REGISTRY_RESOURCEID(IDR_EXEWEAVER)


BEGIN_COM_MAP(CExeWeaver)
    COM_INTERFACE_ENTRY(IExeWeaver)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
    COM_INTERFACE_ENTRY(ICorProfilerCallback2)
END_COM_MAP()

// ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    HRESULT FinalConstruct()
    {
        return S_OK;
    }

    void FinalRelease()
    {
    }

protected:
    STDMETHOD(InitializeCore)( 
        /* [in] */ IUnknown *pICorProfilerInfoUnk);

    STDMETHOD(ShutdownCore)(void);

    STDMETHOD(JITCompilationStartedCore)( 
        /* [in] */ FunctionID functionId,
        /* [in] */ BOOL fIsSafeToBlock);

private:
    boost::timer m_timer;
    CComPtr<ICorProfilerInfo2> m_pInfo;
    std::wstring m_targetMethodName;    
    std::wstring m_newMessage;
};

#undef UNP
#endif

OBJECT_ENTRY_AUTO(__uuidof(ExeWeaver), CExeWeaver)
