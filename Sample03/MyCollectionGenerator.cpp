// MyCollectionGenerator.cpp : CMyCollectionGenerator の実装

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

STDMETHODIMP CMyCollectionGenerator::CreateUnkVectorCollection(IUnkVectorCollection** ppVal)
{
    using Urasandesu::NAnonym::Collections::CComEqualityComparer;

    // BSTR
    {
        typedef CComEqualityComparer<IStrEqualityComparer, BSTR> CStrEqualityComparer;
        typedef CComObject<CStrEqualityComparer> CStrEqualityComparerObject;

        HRESULT hr = S_OK;
        CStrEqualityComparerObject* pStrEqualityComparer = NULL;
        hr = CStrEqualityComparerObject::CreateInstance(&pStrEqualityComparer);
        if (FAILED(hr)) return hr;

        CComPtr<IUnknown> pUnkForRelease;
        pUnkForRelease.Attach(pStrEqualityComparer);

        CComBSTR value1 = L"aiueo";
        CComBSTR value2 = L"aiueo";
        VARIANT_BOOL equals = VARIANT_FALSE;
        LONG hashCode1 = 0;
        LONG hashCode2 = 0;

        hr = pStrEqualityComparer->Equals(value1, value2, &equals);
        ATLASSERT(equals);

        hr = pStrEqualityComparer->GetHashCode(value1, &hashCode1);
        hr = pStrEqualityComparer->GetHashCode(value2, &hashCode2);
        ATLASSERT(hashCode1 == hashCode2);
    }

    // IUnknown*
    {
        typedef CComEqualityComparer<IUnkEqualityComparer, IUnknown*> CUnkEqualityComparer;
        typedef CComObject<CUnkEqualityComparer> CUnkEqualityComparerObject;

        HRESULT hr = S_OK;
        CUnkEqualityComparerObject* pUnkEqualityComparer = NULL;
        hr = CUnkEqualityComparerObject::CreateInstance(&pUnkEqualityComparer);
        if (FAILED(hr)) return hr;

        CComPtr<IUnknown> pUnkForRelease;
        pUnkForRelease.Attach(pUnkEqualityComparer);

        IMyCollectionGenerator* value1 = this;
        IMyCollectionGenerator* value2 = value1;
        VARIANT_BOOL equals = VARIANT_FALSE;
        LONG hashCode1 = 0;
        LONG hashCode2 = 0;

        hr = pUnkEqualityComparer->Equals(value1, value2, &equals);
        ATLASSERT(equals);

        hr = pUnkEqualityComparer->GetHashCode(value1, &hashCode1);
        hr = pUnkEqualityComparer->GetHashCode(value2, &hashCode2);
        ATLASSERT(hashCode1 == hashCode2);
    }

    // VARIANT
    {
        typedef CComEqualityComparer<IVariantEqualityComparer, VARIANT> CVariantEqualityComparer;
        typedef CComObject<CVariantEqualityComparer> CVariantEqualityComparerObject;

        HRESULT hr = S_OK;
        CVariantEqualityComparerObject* pVariantEqualityComparer = NULL;
        hr = CVariantEqualityComparerObject::CreateInstance(&pVariantEqualityComparer);
        if (FAILED(hr)) return hr;

        CComPtr<IUnknown> pUnkForRelease;
        pUnkForRelease.Attach(pVariantEqualityComparer);

        CComVariant value1 = 10;
        CComVariant value2 = 10;
        VARIANT_BOOL equals = VARIANT_FALSE;
        LONG hashCode1 = 0;
        LONG hashCode2 = 0;

        hr = pVariantEqualityComparer->Equals(value1, value2, &equals);
        ATLASSERT(equals);

        //hr = pUnkEqualityComparer->GetHashCode(value1, &hashCode1);
        //hr = pUnkEqualityComparer->GetHashCode(value2, &hashCode2);
        //ATLASSERT(hashCode1 == hashCode2);
    }

    return E_NOTIMPL;
    //HRESULT hr;
    //CUnkVectorCollectionObject* pObj;
    //hr = CUnkVectorCollectionObject::CreateInstance(&pObj);
    //if (FAILED(hr))
    //{
    //    return hr;
    //}
    //CComPtr<IUnkVectorCollection> pUnkVectorCollection = pObj;

    //return pUnkVectorCollection.CopyTo(ppVal);
}
