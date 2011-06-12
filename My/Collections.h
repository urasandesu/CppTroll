#pragma once
#ifndef INCLUDED_COLLECTIONS_H
#define INCLUDED_COLLECTIONS_H

namespace My
{
    template <class EnumeratorType, class RangeType>
    HRESULT CreateRangeEnumerator(IUnknown* pSource, RangeType& range, IUnknown** ppResult)
    {
        BOOST_MPL_ASSERT((is_convertible<EnumeratorType, AddImplicitConversion<IgnoreParam6<CComEnumerator>>>));
        BOOST_CONCEPT_ASSERT((SinglePassRangeConcept<RangeType>));

        if (ppResult == NULL) return E_POINTER;

        *ppResult = NULL;

        typedef CComObject<EnumeratorType> EnumeratorObject;
        EnumeratorObject* pEnumerator = NULL;
        HRESULT hr = EnumeratorObject::CreateInstance(&pEnumerator);
        if (FAILED(hr)) return hr;

        CComPtr<IUnknown> pUnkForRelease(pEnumerator);

        hr = pEnumerator->Init(pSource, range);
        if (FAILED(hr)) return hr;

        hr = pEnumerator->QueryInterface(ppResult);
        if (FAILED(hr)) return hr;

        return S_OK;
    } // HRESULT CreateRangeEnumerator(IUnknown* pSource, RangeType& range, IUnknown** ppResult)
}   // namespace My

#endif  // #ifndef INCLUDED_COLLECTIONS_H