#pragma once
#ifndef INCLUDED_IENUMERATORIMPL_H
#define INCLUDED_IENUMERATORIMPL_H

#ifndef INCLUDED_COMENUMERATOR_H
#include "ComEnumerator.h"
#endif

#ifndef INCLUDED_ATLCOPY_H
#include "ATLCopy.h"
#endif

#ifndef INCLUDED_EXTRACTOR_H
#include "Extractor.h"
#endif

namespace My
{
    template <
        class Base, 
        class ItemType, 
        class RangeType, 
        class CopyItemFromRange,
        class RangeAddresser,
        class ThreadModel
    >
    class ATL_NO_VTABLE CComEnumerator;





    template <
        class Base,
        class ItemType, 
        class RangeType, 
        class CopyItemFromRange = GenericCopy<
                                    ItemType, 
                                    typename WithoutAdapt<
                                        typename range_value<RangeType>::type
                                    >::type
                                  >,
        class RangeAddresser = AddressExtractor<
                                    typename WithoutAdapt<
                                        typename range_value<RangeType>::type
                                    >::type
                               >,
        class ThreadModel = CComObjectThreadModel
    >
    class ATL_NO_VTABLE IEnumeratorImpl : 
        public Base
    {
        BOOST_CONCEPT_ASSERT((ComEnumerator<Base, ItemType>));
        BOOST_CONCEPT_ASSERT((SinglePassRangeConcept<RangeType>));
        BOOST_CONCEPT_ASSERT((ATLCopy<
                                CopyItemFromRange, 
                                ItemType, 
                                typename WithoutAdapt<
                                    typename range_value<RangeType>::type
                                >::type
                              >));
        BOOST_CONCEPT_ASSERT((Extractor<RangeAddresser>));

    public:
        typedef Base base_type;
        typedef IEnumeratorImpl<Base, ItemType, RangeType, CopyItemFromRange, RangeAddresser, ThreadModel> type;
        typedef Base interface_type;

        typedef typename WithoutAdapt<
                    typename range_value<RangeType>::type
                >::type range_value_type;
        typedef typename range_iterator<RangeType>::type range_iterator;

        IEnumeratorImpl() : m_pRange(NULL)
        {
        }

        HRESULT Init(IUnknown* pSource, RangeType& range)
        {
            m_pSource = pSource;
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
                HRESULT hr = CopyItemFromRange::copy(pelt, RangeAddresser::Apply(_i));
                if (FAILED(hr))
                {
                    if (pceltFetched != NULL)
                        *pceltFetched = 0;

                    for ( ; rgelt < pelt; ++rgelt)
                        CopyItemFromRange::destroy(rgelt);

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

        STDMETHOD(Clone)(Base** ppVal)
        {
            if (m_pRange == NULL) return E_FAIL;
            if (ppVal == NULL) return E_POINTER;

            typedef CComObject<CComEnumerator<Base, ItemType, RangeType, CopyItemFromRange, RangeAddresser, ThreadModel>> CComEnumeratorObject;

            HRESULT hr = S_OK;
            CComEnumeratorObject* pEnumerator = NULL;

            *ppVal = NULL;
            hr = CComEnumeratorObject::CreateInstance(&pEnumerator);
            if (FAILED(hr)) return hr;

            CComPtr<IUnknown> pUnkForRelease;
            pUnkForRelease.Attach(pEnumerator); 

            hr = pEnumerator->Init(m_pSource, *m_pRange);
            if (FAILED(hr)) goto RETURN_WITH_RELEASE;

            pEnumerator->m_i = m_i;
            hr = pEnumerator->QueryInterface(__uuidof(Base), (void**)ppVal);
            if (FAILED(hr)) goto RETURN_WITH_RELEASE;

            pUnkForRelease.Detach();
            return S_OK;

RETURN_WITH_RELEASE:
            return hr;
        }

    private:
        CComPtr<IUnknown> m_pSource;
        RangeType* m_pRange;
        range_iterator m_i, m_i_end;
    };  // class ATL_NO_VTABLE IEnumeratorImpl

}   // namespace My

#endif  // #ifndef INCLUDED_IENUMERATORIMPL_H