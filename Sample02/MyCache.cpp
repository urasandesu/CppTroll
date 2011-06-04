// MyCache.cpp : CMyCache ‚ÌŽÀ‘•

#include "stdafx.h"
#include "MyCache.h"


// CMyCache

STDMETHODIMP CMyCache::get_Count(LONG* pVal)
{
    *pVal = m_values.size();
    return S_OK;
}

STDMETHODIMP CMyCache::get_Item(BSTR key, VARIANT* pVal)
{
    HRESULT hr;

    StrVariantConstIterator itr = m_values.find(CComBSTR(key));
    if (itr == m_values.end())
    {
        return S_FALSE;
    }

    CComVariant val = (*itr).second;
    hr = val.Detach(pVal);
    if (FAILED(hr))
    {
        return hr;
    }
    return S_OK;
}

STDMETHODIMP CMyCache::put_Item(BSTR key, VARIANT newVal)
{
    if (key == NULL)
    {
        return E_INVALIDARG;
    }

    m_values[CComBSTR(key)] = newVal;
    return S_OK;
}

STDMETHODIMP CMyCache::get__NewEnum(IUnknown** ppVal)
{
    return My::CreateRangeEnumerator<StrVariantEnumerator>(this, m_values, ppVal);
}
