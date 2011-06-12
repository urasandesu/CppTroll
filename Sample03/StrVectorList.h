// StrVectorList.h : CStrVectorList の宣言

#pragma once
#include "resource.h"       // メイン シンボル

#include "Sample03_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM の完全サポートを含んでいない Windows Mobile プラットフォームのような Windows CE プラットフォームでは、単一スレッド COM オブジェクトは正しくサポートされていません。ATL が単一スレッド COM オブジェクトの作成をサポートすること、およびその単一スレッド COM オブジェクトの実装の使用を許可することを強制するには、_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA を定義してください。ご使用の rgs ファイルのスレッド モデルは 'Free' に設定されており、DCOM Windows CE 以外のプラットフォームでサポートされる唯一のスレッド モデルと設定されていました。"
#endif


typedef std::vector<CAdapt<CComBSTR>> StrVector;
typedef My::CComEnumerator<IEnumVARIANT, VARIANT, StrVector> StrEnumerator;
typedef My::IListImpl<IStrVectorList, BSTR, StrEnumerator, StrVector> IStrVectorListImpl;


// CStrVectorList

class ATL_NO_VTABLE CStrVectorList :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStrVectorList, &CLSID_StrVectorList>,
	public IDispatchImpl<IStrVectorListImpl, &IID_IStrVectorList, &LIBID_Sample03Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CStrVectorList()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STRVECTORLIST)


BEGIN_COM_MAP(CStrVectorList)
	COM_INTERFACE_ENTRY(IStrVectorList)
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

OBJECT_ENTRY_AUTO(__uuidof(StrVectorList), CStrVectorList)
