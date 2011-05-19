// MyCachePrinter.h : CMyCachePrinter の宣言

#pragma once
#include "resource.h"       // メイン シンボル

#include "Sample02_i.h"
#include "dllmain.h"

#include "MyCache.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM の完全サポートを含んでいない Windows Mobile プラットフォームのような Windows CE プラットフォームでは、単一スレッド COM オブジェクトは正しくサポートされていません。ATL が単一スレッド COM オブジェクトの作成をサポートすること、およびその単一スレッド COM オブジェクトの実装の使用を許可することを強制するには、_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA を定義してください。ご使用の rgs ファイルのスレッド モデルは 'Free' に設定されており、DCOM Windows CE 以外のプラットフォームでサポートされる唯一のスレッド モデルと設定されていました。"
#endif



// CMyCachePrinter

class ATL_NO_VTABLE CMyCachePrinter :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMyCachePrinter, &CLSID_MyCachePrinter>,
	public ISupportErrorInfo,
	public IDispatchImpl<IMyCachePrinter, &IID_IMyCachePrinter, &LIBID_Sample02Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CMyCachePrinter()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MYCACHEPRINTER)


BEGIN_COM_MAP(CMyCachePrinter)
	COM_INTERFACE_ENTRY(IMyCachePrinter)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
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

    STDMETHOD(ToString)(const CComVariant& value, BSTR* pStr);

public:

    STDMETHOD(Print)(void);
};

OBJECT_ENTRY_AUTO(__uuidof(MyCachePrinter), CMyCachePrinter)
