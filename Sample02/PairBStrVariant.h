// PairBStrVariant.h : CPairBStrVariant の宣言

#pragma once
#include "resource.h"       // メイン シンボル

#include "Sample02_i.h"

#include "Copies.h"
#include "Pairs.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM の完全サポートを含んでいない Windows Mobile プラットフォームのような Windows CE プラットフォームでは、単一スレッド COM オブジェクトは正しくサポートされていません。ATL が単一スレッド COM オブジェクトの作成をサポートすること、およびその単一スレッド COM オブジェクトの実装の使用を許可することを強制するには、_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA を定義してください。ご使用の rgs ファイルのスレッド モデルは 'Free' に設定されており、DCOM Windows CE 以外のプラットフォームでサポートされる唯一のスレッド モデルと設定されていました。"
#endif


typedef My::IPairImpl<IPairBStrVariant, BSTR, VARIANT, My::GenericCopy<BSTR, BSTR>> IPairBStrVariantImpl;

// CPairBStrVariant

class ATL_NO_VTABLE CPairBStrVariant :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPairBStrVariant, &CLSID_PairBStrVariant>,
	public IDispatchImpl<IPairBStrVariantImpl, &IID_IPairBStrVariant, &LIBID_Sample02Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CPairBStrVariant()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PAIRBSTRVARIANT)


BEGIN_COM_MAP(CPairBStrVariant)
	COM_INTERFACE_ENTRY(IPairBStrVariant)
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

OBJECT_ENTRY_AUTO(__uuidof(PairBStrVariant), CPairBStrVariant)
typedef CComObject<CPairBStrVariant> CPairBStrVariantObject;
