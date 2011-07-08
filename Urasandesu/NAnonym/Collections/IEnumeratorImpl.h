#pragma once
#ifndef URASANDESU_NANONYM_COLLECTIONS_IENUMERATORIMPL_H
#define URASANDESU_NANONYM_COLLECTIONS_IENUMERATORIMPL_H

#ifndef URASANDESU_NANONYM_CONCEPTS_COMENUMERATOR_H
#include "Urasandesu/NAnonym/Concepts/ComEnumerator.h"
#endif

#ifndef URASANDESU_NANONYM_CONCEPTS_ATLCOPY_H
#include "Urasandesu/NAnonym/Concepts/ATLCopy.h"
#endif

#ifndef URASANDESU_NANONYM_CONCEPTS_EXTRACTOR_H
#include "Urasandesu/NAnonym/Concepts/Extractor.h"
#endif

#ifndef URASANDESU_NANONYM_TRAITS_WITHOUTADAPT_H
#include "Urasandesu/NAnonym/Traits/WithoutAdapt.h"
#endif

#ifndef URASANDESU_NANONYM_UTILITIES_GENERICCOPY_H
#include "Urasandesu/NAnonym/Utilities/GenericCopy.h"
#endif

#ifndef URASANDESU_NANONYM_TRAITS_ADDRESSEXTRACTOR_H
#include "Urasandesu/NAnonym/Traits/AddressExtractor.h"
#endif

#ifndef URASANDESU_NANONYM_CONCEPTS_COMOBJECTWITHINSTANTIATION_H
#include "Urasandesu/NAnonym/Concepts/ComObjectWithInstantiation.h"
#endif

#ifndef URASANDESU_NANONYM_TRAITS_REPLACE_H
#include "Urasandesu/NAnonym/Traits/Replace.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace Collections {

    using namespace Urasandesu::NAnonym::Traits;
    using namespace Urasandesu::NAnonym::Concepts;
    using namespace Urasandesu::NAnonym::Utilities;

    template <
        class Base,
        class ItemType, 
        class RangeType, 
        class CopyItemFromRange = use_default,
        class RangeAddresser = use_default
    >
    class ATL_NO_VTABLE IEnumeratorImpl : 
        public Base
    {
    private:
        BOOST_CONCEPT_ASSERT((SinglePassRangeConcept<RangeType>));
        
    public:
        typedef typename RangeValueWithoutAdapt<RangeType>::type range_value_type;
        typedef GenericCopy<ItemType, range_value_type> default_copy_item_from_range;
        typedef typename Replace<CopyItemFromRange, use_default, default_copy_item_from_range>::type copy_item_from_range;
        typedef AddressExtractor<range_value_type> default_address_extractor;
        typedef typename Replace<RangeAddresser, use_default, default_address_extractor>::type range_addresser;

    private:
        BOOST_CONCEPT_ASSERT((ComEnumerator<Base, ItemType>));
        BOOST_CONCEPT_ASSERT((ATLCopy<copy_item_from_range, ItemType, range_value_type>));
        BOOST_CONCEPT_ASSERT((Extractor<range_addresser>));

    public:
        typedef Base base_type;
        typedef IEnumeratorImpl<Base, ItemType, RangeType, CopyItemFromRange, RangeAddresser> type;
        typedef Base interface_type;

        typedef ItemType item_type;
        typedef typename range_iterator<RangeType>::type range_iterator;

        IEnumeratorImpl() : m_pRange(NULL)
        {
        }

        HRESULT Init(IUnknown* pUnkForRelease, RangeType& range)
        {
            m_pUnkForRelease = pUnkForRelease;
            m_pRange = &range;
            m_i = range.begin();
            m_i_end = range.end();
            return S_OK;
        }

        STDMETHOD(Next)(ULONG celt, ItemType* rgelt, ULONG* pceltFetched)
        {
            if (m_pRange == NULL) return E_FAIL;
            if (rgelt == NULL || (celt != 1 && pceltFetched == NULL)) return E_POINTER;

            ULONG celtFetched = 0;
            for (ItemType* pelt = rgelt; m_i != m_i_end && celtFetched < celt; ++m_i, ++celtFetched, ++pelt)
            {
                range_value_type& _i = *m_i;
                HRESULT hr = copy_item_from_range::copy(pelt, range_addresser::Apply(_i));
                if (FAILED(hr))
                {
                    if (pceltFetched != NULL)
                        *pceltFetched = 0;

                    for ( ; rgelt < pelt; ++rgelt)
                        copy_item_from_range::destroy(rgelt);

                    return hr;
                }
            }

            if (pceltFetched != NULL)
                *pceltFetched = celtFetched;

            return celtFetched == 0 ? S_FALSE : S_OK;
        }

        STDMETHOD(Skip)(ULONG celt)
        {
            if (m_pRange == NULL) return E_FAIL;

            ULONG celtFetched = 0;
            for ( ; m_i != m_i_end && celtFetched < celt; ++m_i, ++celtFetched) ;

            return celtFetched == 0 ? S_FALSE : S_OK;
        }

        STDMETHOD(Reset)(void)
        {
            if (m_pRange == NULL) return E_FAIL;

            m_i = m_pRange->begin();
            m_i_end = m_pRange->end();
            return S_OK;
        }

        template<class ComEnumeratorObject>
        HRESULT Clone(Base** ppVal)
        {
            if (m_pRange == NULL) return E_FAIL;
            if (ppVal == NULL) return E_POINTER;
            *ppVal = NULL;

            HRESULT hr = S_OK;
            ComEnumeratorObject* pEnumerator = NULL;

            hr = ComEnumeratorObject::CreateInstance(&pEnumerator);
            if (FAILED(hr)) return hr;

            CComPtr<IUnknown> pUnkForRelease(pEnumerator);

            hr = pEnumerator->Init(m_pUnkForRelease, *m_pRange);
            if (FAILED(hr)) return hr;

            pEnumerator->m_i = m_i;
            hr = pEnumerator->QueryInterface(__uuidof(Base), reinterpret_cast<void**>(ppVal));
            if (FAILED(hr)) return hr;

            return S_OK;
        }
        
        template<class ComEnumeratorObject>
        static HRESULT New(IUnknown* pUnkForRelease, RangeType& range, IUnknown** ppResult)
        {
            BOOST_CONCEPT_ASSERT((ComObjectWithInstantiation<ComEnumeratorObject>));

            if (ppResult == NULL) return E_POINTER;
            *ppResult = NULL;

            HRESULT hr = E_FAIL;
            ComEnumeratorObject* pEnumerator = NULL;

            hr = ComEnumeratorObject::CreateInstance(&pEnumerator);
            if (FAILED(hr)) return hr;

            CComPtr<IUnknown> pUnkForRelease_(pEnumerator);

            hr = pEnumerator->Init(pUnkForRelease, range);
            if (FAILED(hr)) return hr;

            hr = pEnumerator->QueryInterface(__uuidof(Base), reinterpret_cast<void**>(ppResult));
            if (FAILED(hr)) return hr;

            return S_OK;
        }

    private:
        CComPtr<IUnknown> m_pUnkForRelease;
        RangeType* m_pRange;
        range_iterator m_i, m_i_end;
    };  // class ATL_NO_VTABLE IEnumeratorImpl

}}}   // namespace Urasandesu { namespace NAnonym { namespace Collections {

#endif  // #ifndef URASANDESU_NANONYM_COLLECTIONS_IENUMERATORIMPL_H