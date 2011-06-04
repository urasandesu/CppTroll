// MyEnumerableGenerator.cpp : CMyEnumerableGenerator ‚ÌŽÀ‘•

#include "stdafx.h"
#include "MyEnumerableGenerator.h"


// CMyEnumerableGenerator


STDMETHODIMP CMyEnumerableGenerator::CreateInstance(IMyEnumerable** ppVal)
{
    HRESULT hr;
    CMyEnumerableObject* pObj;
    hr = CMyEnumerableObject::CreateInstance(&pObj);
    if (FAILED(hr))
    {
        return hr;
    }
    CComPtr<IMyEnumerable> pMyEnumerable = pObj;

    pObj->m_container.push_back(CComBSTR(L"aiueo"));
    pObj->m_container.push_back(CComBSTR(L"kakikukeko"));
    pObj->m_container.push_back(CComBSTR(L"sasisuseso"));

    return pMyEnumerable.CopyTo(ppVal);
}
