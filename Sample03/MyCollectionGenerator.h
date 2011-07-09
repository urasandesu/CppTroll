// MyCollectionGenerator.h : CMyCollectionGenerator の宣言

#pragma once
#include "resource.h"       // メイン シンボル

#include "Sample03_i.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM の完全サポートを含んでいない Windows Mobile プラットフォームのような Windows CE プラットフォームでは、単一スレッド COM オブジェクトは正しくサポートされていません。ATL が単一スレッド COM オブジェクトの作成をサポートすること、およびその単一スレッド COM オブジェクトの実装の使用を許可することを強制するには、_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA を定義してください。ご使用の rgs ファイルのスレッド モデルは 'Free' に設定されており、DCOM Windows CE 以外のプラットフォームでサポートされる唯一のスレッド モデルと設定されていました。"
#endif

using Urasandesu::NAnonym::Collections::CComEnumerator;
using Urasandesu::NAnonym::Collections::CComCollection;

typedef std::vector<CAdapt<CComBSTR>> StrVector;
typedef CComEnumerator<IEnumVARIANT, VARIANT, StrVector> StrEnumerator;
typedef CComObject<StrEnumerator> StrEnumeratorObject;
typedef CComCollection<IStrVectorCollection, BSTR, StrEnumeratorObject, StrVector> CStrVectorCollection;
typedef CComObject<CStrVectorCollection> CStrVectorCollectionObject;

typedef std::deque<INT> IntDeque;
typedef CComEnumerator<IEnumVARIANT, VARIANT, IntDeque> IntEnumerator;
typedef CComObject<IntEnumerator> IntEnumeratorObject;
typedef CComCollection<IIntDequeCollection, INT, IntEnumeratorObject, IntDeque> CIntDequeCollection;
typedef CComObject<CIntDequeCollection> CIntDequeCollectionObject;

typedef CComPtr<IUnknown> UnkPtr;
typedef CAdapt<UnkPtr> AdaptedUnkPtr;
typedef std::vector<AdaptedUnkPtr> UnkVector;
typedef CComEnumerator<IEnumVARIANT, VARIANT, UnkVector> UnkEnumerator;
typedef CComObject<UnkEnumerator> UnkEnumeratorObject;
typedef CComCollection<IUnkVectorCollection, IUnknown*, UnkEnumeratorObject, UnkVector> CUnkVectorCollection;
typedef CComObject<CUnkVectorCollection> CUnkVectorCollectionObject;

// CMyCollectionGenerator

class ATL_NO_VTABLE CMyCollectionGenerator :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CMyCollectionGenerator, &CLSID_MyCollectionGenerator>,
    public IDispatchImpl<IMyCollectionGenerator, &IID_IMyCollectionGenerator, &LIBID_Sample03Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
    CMyCollectionGenerator()
    {
    }

DECLARE_REGISTRY_RESOURCEID(IDR_MYCOLLECTIONGENERATOR)


BEGIN_COM_MAP(CMyCollectionGenerator)
    COM_INTERFACE_ENTRY(IMyCollectionGenerator)
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

    STDMETHOD(CreateStrVectorCollection)(IStrVectorCollection** ppVal);
    STDMETHOD(CreateIntDequeCollection)(IIntDequeCollection** ppVal);
    STDMETHOD(CreateUnkVectorCollection)(IUnkVectorCollection** ppVal);
};

OBJECT_ENTRY_AUTO(__uuidof(MyCollectionGenerator), CMyCollectionGenerator)
