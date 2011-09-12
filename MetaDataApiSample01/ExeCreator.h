// ExeCreator.h : CExeCreator の宣言

#pragma once
#include "resource.h"       // メイン シンボル

#include "MetaDataApiSample01_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM の完全サポートを含んでいない Windows Mobile プラットフォームのような Windows CE プラットフォームでは、単一スレッド COM オブジェクトは正しくサポートされていません。ATL が単一スレッド COM オブジェクトの作成をサポートすること、およびその単一スレッド COM オブジェクトの実装の使用を許可することを強制するには、_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA を定義してください。ご使用の rgs ファイルのスレッド モデルは 'Free' に設定されており、DCOM Windows CE 以外のプラットフォームでサポートされる唯一のスレッド モデルと設定されていました。"
#endif



// CExeCreator

class ATL_NO_VTABLE CExeCreator :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CExeCreator, &CLSID_ExeCreator>,
    public ISupportErrorInfo,
	public IDispatchImpl<IExeCreator, &IID_IExeCreator, &LIBID_MetaDataApiSample01Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CExeCreator()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EXECREATOR)


BEGIN_COM_MAP(CExeCreator)
	COM_INTERFACE_ENTRY(IExeCreator)
	COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

    typedef CComCoClass<CExeCreator, &CLSID_ExeCreator> BaseCoClass; 
	HRESULT SystemError(DWORD errorNo);
	HRESULT COMError(HRESULT hr);


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

    STDMETHOD(Create)(BSTR fileName);
};

OBJECT_ENTRY_AUTO(__uuidof(ExeCreator), CExeCreator)
