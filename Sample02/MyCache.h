// MyCache.h : CMyCache の宣言

#pragma once
#include "resource.h"       // メイン シンボル

#include "Sample02_i.h"
#include "dllmain.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM の完全サポートを含んでいない Windows Mobile プラットフォームのような Windows CE プラットフォームでは、単一スレッド COM オブジェクトは正しくサポートされていません。ATL が単一スレッド COM オブジェクトの作成をサポートすること、およびその単一スレッド COM オブジェクトの実装の使用を許可することを強制するには、_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA を定義してください。ご使用の rgs ファイルのスレッド モデルは 'Free' に設定されており、DCOM Windows CE 以外のプラットフォームでサポートされる唯一のスレッド モデルと設定されていました。"
#endif


struct AdaptedComBSTREqualTo
    : std::binary_function<CAdapt<CComBSTR>, CAdapt<CComBSTR>, bool>
{
    bool operator()(CAdapt<CComBSTR> const& x, CAdapt<CComBSTR> const& y) const
    {
        return (CComBSTR&)x == (CComBSTR&)y;
    }
};

struct AdaptedComBSTRHash
    : std::unary_function<CAdapt<CComBSTR>, std::size_t>
{
    std::size_t operator()(CAdapt<CComBSTR> const& x) const
    {
        using namespace boost;

        std::size_t seed = 0;
        CComBSTR& _x = (CComBSTR&)x;
        for (BSTR itr = _x, end = _x + _x.Length(); itr != end; ++itr)
        {
            hash_combine(seed, *itr);
        }

        return seed;
    }
};

typedef std::pair<CAdapt<CComBSTR>, CComVariant> BStrVariantPair;
typedef boost::unordered_map<CAdapt<CComBSTR>, CComVariant, AdaptedComBSTRHash, AdaptedComBSTREqualTo> StrVariantMap;
typedef StrVariantMap::iterator StrVariantIterator;
typedef StrVariantMap::const_iterator StrVariantConstIterator;
typedef My::CComPair<IPairBStrVariant, BSTR, VARIANT, My::GenericCopy<BSTR, BSTR>> CPairBStrVariant;
typedef My::MapCopy<StrVariantMap, CPairBStrVariant> CopyType;
typedef My::CComEnumerator<IEnumVARIANT, VARIANT, StrVariantMap, CopyType> StrVariantEnumerator;

// CMyCache

class ATL_NO_VTABLE CMyCache :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CMyCache, &CLSID_MyCache>,
    public IDispatchImpl<IMyCache, &IID_IMyCache, &LIBID_Sample02Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
    CMyCache()
    {
    }

DECLARE_REGISTRY_RESOURCEID(IDR_MYCACHE)
DECLARE_CLASSFACTORY_SINGLETON(CMyCache)


BEGIN_COM_MAP(CMyCache)
    COM_INTERFACE_ENTRY(IMyCache)
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

private:
    StrVariantMap m_values;
    

public:

    STDMETHOD(get_Count)(LONG* pVal);
    STDMETHOD(get_Item)(BSTR key, VARIANT* pVal);
    STDMETHOD(put_Item)(BSTR key, VARIANT newVal);
    STDMETHOD(get__NewEnum)(IUnknown** ppVal);
};

OBJECT_ENTRY_AUTO(__uuidof(MyCache), CMyCache)
