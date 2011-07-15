// EmployeeList.h : CEmployeeList の宣言

#pragma once
#include "resource.h"       // メイン シンボル

#include "Sample01_i.h"
#include "dllmain.h"

#include "Employee.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM の完全サポートを含んでいない Windows Mobile プラットフォームのような Windows CE プラットフォームでは、単一スレッド COM オブジェクトは正しくサポートされていません。ATL が単一スレッド COM オブジェクトの作成をサポートすること、およびその単一スレッド COM オブジェクトの実装の使用を許可することを強制するには、_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA を定義してください。ご使用の rgs ファイルのスレッド モデルは 'Free' に設定されており、DCOM Windows CE 以外のプラットフォームでサポートされる唯一のスレッド モデルと設定されていました。"
#endif

using std::map;
using Urasandesu::NAnonym::Utilities::MapCopy2nd;
using Urasandesu::NAnonym::Collections::SinglePassCopyAnyRangeGenerator;
using Urasandesu::NAnonym::Collections::CComEnumerator;

typedef map<CComBSTR, EmployeePtr> EmployeeMap;
typedef EmployeeMap::iterator EmployeeMapItr;
typedef EmployeeMap::value_type EmployeePair;
typedef MapCopy2nd<EmployeeMap, VARIANT> CopyType;
typedef SinglePassCopyAnyRangeGenerator<EmployeeMap>::type EmployeeRange;
typedef CComEnumerator<IEnumVARIANT, VARIANT, EmployeeRange, CopyType> EmployeeEnumerator;
typedef CComObject<EmployeeEnumerator> EmployeeEnumeratorObject;


// CEmployeeList

class ATL_NO_VTABLE CEmployeeList :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CEmployeeList, &CLSID_EmployeeList>,
    public IDispatchImpl<IEmployeeList, &IID_IEmployeeList, &LIBID_Sample01Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
    CEmployeeList()
    {
    }

DECLARE_REGISTRY_RESOURCEID(IDR_EMPLOYEECOLLECTION)


BEGIN_COM_MAP(CEmployeeList)
    COM_INTERFACE_ENTRY(IEmployeeList)
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

    STDMETHOD(Add)(IEmployee* pVal);
    STDMETHOD(get_Count)(LONG* pVal);
    STDMETHOD(Item)(VARIANT index, IEmployee** ppItem);
    STDMETHOD(get__NewEnum)(IUnknown** ppVal);

private:
    EmployeeMap m_coll;
};

OBJECT_ENTRY_AUTO(__uuidof(EmployeeList), CEmployeeList)
