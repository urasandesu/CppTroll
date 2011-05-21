#pragma once

#include "AddImplicitConversion.h"
#include "CComEnumOnRange.h"
#include "AnyRanges.h"

#include <atlbase.h>
#include <atlcom.h>
#include <boost/mpl/assert.hpp>
#include <boost/concept/requires.hpp>

namespace My
{
    template <class EnumType, class RangeType>
    HRESULT CreateRangeEnumerator(IUnknown** ppUnk, IUnknown* pUnkForRelease, RangeType& range)
    {
        using namespace boost;

        BOOST_MPL_ASSERT((is_convertible<EnumType, AddImplicitConversion<IgnoreParam5<CComEnumOnRange>>>));
        BOOST_CONCEPT_ASSERT((SinglePassRangeConcept<RangeType>));

        if (ppUnk == NULL)
            return E_POINTER;
        *ppUnk = NULL;

        CComObject<EnumType>* pEnum = NULL;
        HRESULT hr = CComObject<EnumType>::CreateInstance(&pEnum);

        if (FAILED(hr))
            return hr;

        hr = pEnum->Init(pUnkForRelease, range);

        if (SUCCEEDED(hr))
            hr = pEnum->QueryInterface(ppUnk);

        if (FAILED(hr))
            pEnum->Release();

        return hr;
    } // CreateRangeEnumerator

}   // namespace My
