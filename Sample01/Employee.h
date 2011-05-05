// Employee.h : CEmployee の宣言

#pragma once
#include "resource.h"       // メイン シンボル

#include "Sample01_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM の完全サポートを含んでいない Windows Mobile プラットフォームのような Windows CE プラットフォームでは、単一スレッド COM オブジェクトは正しくサポートされていません。ATL が単一スレッド COM オブジェクトの作成をサポートすること、およびその単一スレッド COM オブジェクトの実装の使用を許可することを強制するには、_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA を定義してください。ご使用の rgs ファイルのスレッド モデルは 'Free' に設定されており、DCOM Windows CE 以外のプラットフォームでサポートされる唯一のスレッド モデルと設定されていました。"
#endif



// CEmployee

class ATL_NO_VTABLE CEmployee :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEmployee, &CLSID_Employee>,
	public IDispatchImpl<IEmployee, &IID_IEmployee, &LIBID_Sample01Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
    CEmployee() : m_lId(0)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EMPLOYEE)


BEGIN_COM_MAP(CEmployee)
	COM_INTERFACE_ENTRY(IEmployee)
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

    STDMETHOD(get_Name)(BSTR* pVal);
    STDMETHOD(put_Name)(BSTR newVal);
    STDMETHOD(get_Id)(LONG* pVal);
    STDMETHOD(put_Id)(LONG newVal);

private:
    CComBSTR m_name;
    LONG m_lId;
};

OBJECT_ENTRY_AUTO(__uuidof(Employee), CEmployee)
