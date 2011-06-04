// MyCache.h : CMyCache �̐錾

#pragma once
#include "resource.h"       // ���C�� �V���{��

#include "Sample02_i.h"
#include "dllmain.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM �̊��S�T�|�[�g���܂�ł��Ȃ� Windows Mobile �v���b�g�t�H�[���̂悤�� Windows CE �v���b�g�t�H�[���ł́A�P��X���b�h COM �I�u�W�F�N�g�͐������T�|�[�g����Ă��܂���BATL ���P��X���b�h COM �I�u�W�F�N�g�̍쐬���T�|�[�g���邱�ƁA����т��̒P��X���b�h COM �I�u�W�F�N�g�̎����̎g�p�������邱�Ƃ���������ɂ́A_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ���`���Ă��������B���g�p�� rgs �t�@�C���̃X���b�h ���f���� 'Free' �ɐݒ肳��Ă���ADCOM Windows CE �ȊO�̃v���b�g�t�H�[���ŃT�|�[�g�����B��̃X���b�h ���f���Ɛݒ肳��Ă��܂����B"
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
