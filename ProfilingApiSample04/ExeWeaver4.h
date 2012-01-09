// ExeWeaver4.h : CExeWeaver4 の宣言

#pragma once
#include "resource.h"       // メイン シンボル



#include "ProfilingApiSample04_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM の完全サポートを含んでいない Windows Mobile プラットフォームのような Windows CE プラットフォームでは、単一スレッド COM オブジェクトは正しくサポートされていません。ATL が単一スレッド COM オブジェクトの作成をサポートすること、およびその単一スレッド COM オブジェクトの実装の使用を許可することを強制するには、_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA を定義してください。ご使用の rgs ファイルのスレッド モデルは 'Free' に設定されており、DCOM Windows CE 以外のプラットフォームでサポートされる唯一のスレッド モデルと設定されていました。"
#endif

using namespace ATL;


// CExeWeaver4

class ATL_NO_VTABLE CExeWeaver4 :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CExeWeaver4, &CLSID_ExeWeaver4>,
	public IDispatchImpl<IExeWeaver4, &IID_IExeWeaver4, &LIBID_ProfilingApiSample04Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CExeWeaver4()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EXEWEAVER4)


BEGIN_COM_MAP(CExeWeaver4)
	COM_INTERFACE_ENTRY(IExeWeaver4)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



};

OBJECT_ENTRY_AUTO(__uuidof(ExeWeaver4), CExeWeaver4)
