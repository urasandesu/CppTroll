﻿// MyEnumerableGenerator.h : CMyEnumerableGenerator の宣言

#pragma once
#include "resource.h"       // メイン シンボル

#include "Sample03_i.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM の完全サポートを含んでいない Windows Mobile プラットフォームのような Windows CE プラットフォームでは、単一スレッド COM オブジェクトは正しくサポートされていません。ATL が単一スレッド COM オブジェクトの作成をサポートすること、およびその単一スレッド COM オブジェクトの実装の使用を許可することを強制するには、_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA を定義してください。ご使用の rgs ファイルのスレッド モデルは 'Free' に設定されており、DCOM Windows CE 以外のプラットフォームでサポートされる唯一のスレッド モデルと設定されていました。"
#endif

using Urasandesu::NAnonym::Collections::CComEnumerator;
using Urasandesu::NAnonym::Collections::CComEnumerable;

typedef std::vector<CAdapt<CComBSTR>> StrVector;
typedef CComEnumerator<IEnumVARIANT, VARIANT, StrVector> StrEnumerator;
typedef CComObject<StrEnumerator> StrEnumeratorObject;
typedef CComEnumerable<IMyEnumerable, StrEnumeratorObject, StrVector> CMyEnumerable;
typedef CComObject<CMyEnumerable> CMyEnumerableObject;

// CMyEnumerableGenerator

class ATL_NO_VTABLE CMyEnumerableGenerator :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CMyEnumerableGenerator, &CLSID_MyEnumerableGenerator>,
    public IDispatchImpl<IMyEnumerableGenerator, &IID_IMyEnumerableGenerator, &LIBID_Sample03Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
    CMyEnumerableGenerator()
    {
    }

DECLARE_REGISTRY_RESOURCEID(IDR_MYENUMERABLEGENERATOR)


BEGIN_COM_MAP(CMyEnumerableGenerator)
    COM_INTERFACE_ENTRY(IMyEnumerableGenerator)
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

    STDMETHOD(CreateInstance)(IMyEnumerable** ppVal);
};

OBJECT_ENTRY_AUTO(__uuidof(MyEnumerableGenerator), CMyEnumerableGenerator)
