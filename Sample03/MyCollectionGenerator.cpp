// MyCollectionGenerator.cpp : CMyCollectionGenerator ‚ÌŽÀ‘•

#include "stdafx.h"
#include "MyCollectionGenerator.h"

// CMyCollectionGenerator

STDMETHODIMP CMyCollectionGenerator::CreateStrVectorCollection(IStrVectorCollection** ppVal)
{
    HRESULT hr;
    CStrVectorCollectionObject* pObj;
    hr = CStrVectorCollectionObject::CreateInstance(&pObj);
    if (FAILED(hr))
    {
        return hr;
    }
    CComPtr<IStrVectorCollection> pStrVectorCollection = pObj;

    return pStrVectorCollection.CopyTo(ppVal);
}

STDMETHODIMP CMyCollectionGenerator::CreateIntDequeCollection(IIntDequeCollection** ppVal)
{
    HRESULT hr;
    CIntDequeCollectionObject* pObj;
    hr = CIntDequeCollectionObject::CreateInstance(&pObj);
    if (FAILED(hr))
    {
        return hr;
    }
    CComPtr<IIntDequeCollection> pIntDequeCollection = pObj;

    return pIntDequeCollection.CopyTo(ppVal);
}
