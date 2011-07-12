// MyCache.h : CMyCache の宣言

#pragma once
#include "resource.h"       // メイン シンボル

#include "Sample02_i.h"
#include "dllmain.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM の完全サポートを含んでいない Windows Mobile プラットフォームのような Windows CE プラットフォームでは、単一スレッド COM オブジェクトは正しくサポートされていません。ATL が単一スレッド COM オブジェクトの作成をサポートすること、およびその単一スレッド COM オブジェクトの実装の使用を許可することを強制するには、_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA を定義してください。ご使用の rgs ファイルのスレッド モデルは 'Free' に設定されており、DCOM Windows CE 以外のプラットフォームでサポートされる唯一のスレッド モデルと設定されていました。"
#endif

using std::binary_function;
using std::unary_function;
using std::pair;
using std::size_t;
using boost::unordered_map;
using Urasandesu::NAnonym::Utilities::CComPair;
using Urasandesu::NAnonym::Utilities::GenericCopy;
using Urasandesu::NAnonym::Utilities::MapCopy;
using Urasandesu::NAnonym::Collections::CComEnumerator;

typedef CAdapt<CComBSTR> AdaptedStr;

struct AdaptedStrEqualTo
    : binary_function<AdaptedStr, AdaptedStr, bool>
{
    bool operator()(AdaptedStr const& x, AdaptedStr const& y) const
    {
        const CComBSTR& _x = x;
        const CComBSTR& _y = y;
        return _x == _y;
    }
};

struct AdaptedStrHash
    : unary_function<AdaptedStr, size_t>
{
    size_t operator()(AdaptedStr const& x) const
    {
        using namespace boost;

        size_t seed = 0;
        const CComBSTR& _x = x;
        for (BSTR i = _x, i_end = _x + _x.Length(); i != i_end; ++i)
        {
            hash_combine(seed, *i);
        }

        return seed;
    }
};

typedef unordered_map<AdaptedStr, CComVariant, AdaptedStrHash, AdaptedStrEqualTo> StrVariantMap;
typedef StrVariantMap::iterator StrVariantIterator;
typedef StrVariantMap::const_iterator StrVariantConstIterator;
typedef CComPair<IPairStrVariant, BSTR, VARIANT, GenericCopy<BSTR, BSTR>> StrVariantPair;
typedef MapCopy<StrVariantMap, StrVariantPair> StrVariantMapCopy;
typedef CComEnumerator<IEnumVARIANT, VARIANT, StrVariantMap, StrVariantMapCopy> StrVariantEnumerator;
typedef CComObject<StrVariantEnumerator> StrVariantEnumeratorObject;

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
