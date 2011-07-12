// MyCachePrinter.cpp : CMyCachePrinter の実装

#include "stdafx.h"
#include "MyCachePrinter.h"

// CMyCachePrinter

STDMETHODIMP CMyCachePrinter::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* arr[] = 
    {
        &IID_IMyCachePrinter
    };

    for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (InlineIsEqualGUID(*arr[i],riid))
            return S_OK;
    }
    return S_FALSE;
}

HRESULT CMyCachePrinter::ToString(const CComVariant& value, BSTR* pStr)
{
    HRESULT hr;

    CComVariant _value = value;
    switch (_value.vt)
    {
    case VT_UNKNOWN:
        {
            mscorlib::_ObjectPtr pObject;
            hr = _value.punkVal->QueryInterface(__uuidof(mscorlib::_Object), (void**)&pObject);
            if (FAILED(hr))
            {
                CComBSTR str(L"IUnknown");
                hr = str.CopyTo(pStr);
                if (FAILED(hr))
                {
                    return hr;
                }
            }
            else
            {
                hr = pObject->get_ToString(pStr);
                if (FAILED(hr))
                {
                    return Error(L"Error, World !!", GUID_NULL, hr);
                }
            }
            break;
        }
    case VT_DISPATCH:
        {
            CComBSTR str(L"IDispatch");
            hr = str.CopyTo(pStr);
            if (FAILED(hr))
            {
                return hr;
            }
            break;
        }
    case VT_BSTR:
        {
            hr = _value.CopyTo(pStr);
            if (FAILED(hr))
            {
                return hr;
            }
            break;
        }
    case VT_UI1:
    case VT_I1:
    case VT_I2:
    case VT_UI2:
    case VT_BOOL:
    case VT_I4:
    case VT_UI4:
    case VT_R4:
    case VT_INT:
    case VT_UINT:
    case VT_ERROR:
    case VT_I8:
    case VT_UI8:
    case VT_R8:
    case VT_CY:
    case VT_DATE:
        {
            _value.ChangeType(VT_BSTR);
            hr = _value.CopyTo(pStr);
            if (FAILED(hr))
            {
                return hr;
            }
            break;
        }
    default:
        return E_INVALIDARG;
    }   // switch (_value.vt)

    return S_OK;
}

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

    static int i = 0;
    ULONG celt = 1;
    CComVariant rgVar;
    ULONG celtFetched = 0;
    while ((hr = pEnum->Next(celt, &rgVar, &celtFetched)) != S_FALSE)
    {
        if (FAILED(hr))
        {
            return hr;
        }

        CComQIPtr<IPairStrVariant> pair = rgVar.punkVal;
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

        BSTR str;
        hr = ToString(second, &str);
        if (FAILED(hr))
        {
            return hr;
        }

        cout << format("MyCache[%|1|]:  %|2|") % CW2A(first) % CW2A(str) << endl;
    }

    return S_OK;
}
