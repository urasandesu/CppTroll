// MyCachePrinter.cpp : CMyCachePrinter ‚ÌŽÀ‘•

#include "stdafx.h"
#include "MyCachePrinter.h"


// CMyCachePrinter

STDMETHODIMP CMyCachePrinter::Print(void)
{
    using namespace std;
    using namespace boost;

    HRESULT hr;
    CComPtr<IClassFactory> pCf;
    hr = _AtlModule.DllGetClassObject(__uuidof(MyCache), IID_IClassFactory, (void**)&pCf);
    if (FAILED(hr))
    {
        return hr;
    }

    CComPtr<IMyCache> pMyCache;
    hr = pCf->CreateInstance(NULL, IID_IMyCache, (void**)&pMyCache);
    if (FAILED(hr))
    {
        return hr;
    }

    CComQIPtr<IEnumVARIANT> pEnum;
    hr = pMyCache->get__NewEnum((IUnknown**)&pEnum);
    if (FAILED(hr))
    {
        return hr;
    }

    ULONG celt = 1;
    CComVariant rgVar;
    ULONG celtFetched = 0;
    while ((hr = pEnum->Next(celt, &rgVar, &celtFetched)) != S_FALSE)
    {
        if (FAILED(hr))
        {
            return hr;
        }

        CComQIPtr<IPairBStrVariant> pair = rgVar.punkVal;
        CComBSTR first;
        hr = pair->get_First(&first);
        if (FAILED(hr))
        {
            return hr;
        }

        CComVariant second;
        hr = pair->get_Second(&second);
        if (FAILED(hr))
        {
            return hr;
        }

        second.ChangeType(VT_BSTR);
        if (FAILED(hr))
        {
            return hr;
        }

        cout << format("MyCache[%|1|]:  %|2|") % CW2A(first) % CW2A(second.bstrVal) << endl;
    }

    return S_OK;
}
