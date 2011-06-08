#pragma once
#include "Concepts.h"
#include "AnyRanges.h"
#include "Traits.h"

namespace My
{
    template <
        class Base, 
        class ItemType, 
        class RangeType, 
        class CopyItemFromRange,
        class RangeExtractor,
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
                                        typename boost::range_value<RangeType>::type
                                    >::type
                                  >,
        class RangeExtractor = AddressExtractor<
                                    typename WithoutAdapt<
                                        typename boost::range_value<RangeType>::type
                                    >::type
                               >,
        class ThreadModel = CComObjectThreadModel
    >
    class ATL_NO_VTABLE IEnumeratorImpl : 
        public Base
    {
        BOOST_CONCEPT_ASSERT((ComEnumerator<Base, ItemType>));
        BOOST_CONCEPT_ASSERT((boost::SinglePassRangeConcept<RangeType>));
        BOOST_CONCEPT_ASSERT((ATLCopy<
                                CopyItemFromRange, 
                                ItemType, 
                                typename WithoutAdapt<
                                    typename boost::range_value<RangeType>::type
                                >::type
                              >));
        BOOST_CONCEPT_ASSERT((Extractor<RangeExtractor>));

    public:
        typedef Base base_type;
        typedef IEnumeratorImpl<Base, ItemType, RangeType, CopyItemFromRange, RangeExtractor, ThreadModel> type;
        typedef Base interface_type;

        typedef typename WithoutAdapt<
                    typename boost::range_value<RangeType>::type
                >::type range_value_type;
        typedef typename boost::range_iterator<RangeType>::type range_iterator;

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
                HRESULT hr = CopyItemFromRange::copy(pelt, RangeExtractor::Apply(_i));
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

            typedef CComObject<CComEnumerator<Base, ItemType, RangeType, CopyItemFromRange, RangeExtractor, ThreadModel>> CComEnumeratorObject;

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






    template <
        class Base, 
        class ItemType, 
        class RangeType, 
        class CopyItemFromRange = GenericCopy<
                                    ItemType, 
                                    typename WithoutAdapt<
                                        typename boost::range_value<RangeType>::type
                                    >::type
                                  >,
        class RangeExtractor = AddressExtractor<
                                    typename WithoutAdapt<
                                        typename boost::range_value<RangeType>::type
                                    >::type
                               >,
        class ThreadModel = CComObjectThreadModel
    >
    class ATL_NO_VTABLE CComEnumerator :
        public IEnumeratorImpl<Base, ItemType, RangeType, CopyItemFromRange, RangeExtractor, ThreadModel>,
        public CComObjectRootEx<ThreadModel>
    {
    public:
        typedef CComEnumerator<Base, ItemType, RangeType, CopyItemFromRange, RangeExtractor, ThreadModel> type;
        typedef IEnumeratorImpl<Base, ItemType, RangeType, CopyItemFromRange, RangeExtractor, ThreadModel> base_type;
        typedef typename base_type::interface_type interface_type;

        BEGIN_COM_MAP(type)
            COM_INTERFACE_ENTRY_IID(__uuidof(Base), base_type)
        END_COM_MAP()
    };  // class ATL_NO_VTABLE CComEnumerator






    template <class EnumeratorType, class RangeType>
    HRESULT CreateRangeEnumerator(IUnknown* pSource, RangeType& range, IUnknown** ppResult)
    {
        BOOST_MPL_ASSERT((boost::is_convertible<EnumeratorType, AddImplicitConversion<IgnoreParam6<CComEnumerator>>>));
        BOOST_CONCEPT_ASSERT((boost::SinglePassRangeConcept<RangeType>));

        if (ppResult == NULL) return E_POINTER;

        *ppResult = NULL;

        typedef CComObject<EnumeratorType> EnumeratorObject;
        EnumeratorObject* pEnumerator = NULL;
        HRESULT hr = EnumeratorObject::CreateInstance(&pEnumerator);
        if (FAILED(hr)) return hr;

        CComPtr<IUnknown> pUnkForRelease;
        pUnkForRelease.Attach(pEnumerator);

        hr = pEnumerator->Init(pSource, range);
        if (FAILED(hr)) goto RETURN_WITH_RELEASE;

        hr = pEnumerator->QueryInterface(ppResult);
        if (FAILED(hr)) goto RETURN_WITH_RELEASE;

        pUnkForRelease.Detach();
        return S_OK;

RETURN_WITH_RELEASE:
        return hr;
    } // HRESULT CreateRangeEnumerator(IUnknown* pSource, RangeType& range, IUnknown** ppResult)






    template<
        class Base,
        class EnumeratorType, 
        class RangeType
    >
    class ATL_NO_VTABLE IEnumerableImpl : 
        public Base
    {
        BOOST_CONCEPT_ASSERT((ComEnumerable<Base>));
        BOOST_MPL_ASSERT((boost::is_convertible<EnumeratorType, AddImplicitConversion<IgnoreParam6<CComEnumerator>>>));
        BOOST_CONCEPT_ASSERT((boost::SinglePassRangeConcept<RangeType>));

    public:
        typedef IEnumerableImpl<Base, EnumeratorType, RangeType> type;
        typedef Base base_type;
        typedef Base interface_type;

        STDMETHOD(get__NewEnum)(IUnknown** ppVal)
        {
            return CreateRangeEnumerator<EnumeratorType>(this, m_container, ppVal);
        }

        RangeType m_container;
    };  // class ATL_NO_VTABLE IEnumerableImpl






    template<
        class Base, 
        class EnumeratorType, 
        class RangeType,
        const GUID* plibid = &CAtlModule::m_libid,
        WORD wMajor = 1,
        WORD wMinor = 0, 
        class tihclass = CComTypeInfoHolder,
        class ThreadModel = CComObjectThreadModel
    >
    class ATL_NO_VTABLE CComEnumerable :
        public CComObjectRootEx<ThreadModel>,
        public IDispatchImpl<
            IEnumerableImpl<Base, EnumeratorType, RangeType>, 
            &__uuidof(Base), 
            plibid, 
            wMajor, 
            wMinor, 
            tihclass
        >
    {
    public:
        typedef CComEnumerable<
            Base, 
            EnumeratorType, 
            RangeType, 
            plibid, 
            wMajor, 
            wMinor, 
            tihclass, 
            ThreadModel
        > type;
        
        typedef IEnumerableImpl<Base, EnumeratorType, RangeType> base_type;
        typedef typename base_type::interface_type interface_type;
        
        BEGIN_COM_MAP(type)
            COM_INTERFACE_ENTRY_IID(__uuidof(Base), base_type)
            COM_INTERFACE_ENTRY(IDispatch)
        END_COM_MAP()
    };  // class ATL_NO_VTABLE CComEnumerable

    
    
    
    
    
    template<
        class Base,
        class ItemType,
        class EnumeratorType, 
        class CollectionType,
        class CopyItemFromCollection = GenericCopy<
                                            ItemType, 
                                            typename WithoutAdapt<
                                                typename CollectionType::value_type
                                            >::type
                                       >, 
        class ItemExtractor = AddressExtractor<ItemType>,
        class CopyCollectionFromItem = GenericCopy<
                                            typename WithoutAdapt<
                                                typename CollectionType::value_type
                                            >::type, 
                                            ItemType
                                       >,
        class CollectionExtractor = AddressExtractor<
                                        typename WithoutAdapt<
                                            typename CollectionType::value_type
                                        >::type
                                    >
    >
    class ATL_NO_VTABLE ICollectionImpl : 
        public IEnumerableImpl<Base, EnumeratorType, CollectionType>
    {
        BOOST_CONCEPT_ASSERT((ComCollection<Base, ItemType>));
        BOOST_CONCEPT_ASSERT((boost::Mutable_RandomAccessContainer<CollectionType>));
        BOOST_CONCEPT_ASSERT((boost::Sequence<CollectionType>));
        BOOST_CONCEPT_ASSERT((ATLCopy<
                                CopyItemFromCollection, 
                                ItemType, 
                                typename WithoutAdapt<
                                    typename CollectionType::value_type
                                >::type
                              >));
        BOOST_CONCEPT_ASSERT((Extractor<ItemExtractor>));
        BOOST_CONCEPT_ASSERT((ATLCopy<
                                CopyCollectionFromItem, 
                                typename WithoutAdapt<
                                    typename CollectionType::value_type
                                >::type, 
                                ItemType
                              >));
        BOOST_CONCEPT_ASSERT((Extractor<CollectionExtractor>));

    public:
        typedef IEnumerableImpl<Base, EnumeratorType, CollectionType> base_type;
        typedef ICollectionImpl<
            Base, 
            ItemType, 
            EnumeratorType, 
            CollectionType, 
            CopyItemFromCollection, 
            ItemExtractor, 
            CopyCollectionFromItem, 
            CollectionExtractor> type;
        typedef typename base_type::interface_type interface_type;

        typedef typename WithoutAdapt<typename CollectionType::value_type>::type collection_value_type;
        typedef typename CollectionType::iterator collection_iterator;

        STDMETHOD(Add)(ItemType item)
        {
            HRESULT hr = E_FAIL;
            collection_value_type value;
            CopyCollectionFromItem::init(CollectionExtractor::Apply(value));
            hr = CopyCollectionFromItem::copy(CollectionExtractor::Apply(value), ItemExtractor::Apply(item));
            if (FAILED(hr)) return hr;

            m_container.insert(m_container.end(), value);
            return S_OK;
        }

        STDMETHOD(Clear)(void)
        {
            m_container.erase(m_container.begin(), m_container.end());
            return S_OK;
        }

        STDMETHOD(Contains)(ItemType item, VARIANT_BOOL* exists)
        {
            if (exists == NULL) return E_POINTER;

            collection_iterator i = m_container.begin(), i_end = m_container.end();
            collection_iterator result = find(i, i_end, item);
            if (result != i_end)
            {
                *exists = VARIANT_TRUE;
                return S_OK;
            }
            else
            {
                *exists = VARIANT_FALSE;
                return S_FALSE;
            }
        }

        STDMETHOD(CopyTo)(SAFEARRAY* pArray, LONG index)
        {
            if (pArray == NULL) return E_POINTER;
            HRESULT hr;

            CComSafeArray<ItemType> arr;    // I could not use CComSafeArray<T, _vartype>::Attach(const SAFEARRAY*) because it is too sensitive.
            arr.m_psa = pArray;             // The method prohibits even the diferrence between VT_I4 and VT_INT.
            hr = SafeArrayLock(arr.m_psa);
            if (FAILED(hr)) return hr;

            for (collection_iterator i = m_container.begin(), i_end = m_container.end(); i != i_end; ++i, ++index)
            {
                collection_value_type& _i = *i;
                ItemType item;
                CopyItemFromCollection::init(ItemExtractor::Apply(item));
                hr = CopyItemFromCollection::copy(ItemExtractor::Apply(item), CollectionExtractor::Apply(_i));
                if (FAILED(hr)) return hr;

                hr = arr.SetAt(index, item);
                if (FAILED(hr)) return hr;
            }

            arr.Detach();
            return S_OK;
        }

        STDMETHOD(Remove)(ItemType item)
        {
            collection_iterator i = m_container.begin(), i_end = m_container.end();
            collection_iterator result = find(i, i_end, item);
            if (result != i_end)
            {
                m_container.erase(result);
            }

            return S_OK;
        }

        STDMETHOD(get_Count)(LONG* pVal)
        {
            if (pVal == NULL) return E_POINTER;

            *pVal = m_container.size();
            return S_OK;
        }

        STDMETHOD(get_IsReadOnly)(VARIANT_BOOL* pVal)
        {
            if (pVal == NULL) return E_POINTER;

            *pVal = VARIANT_FALSE;
            return S_OK;
        }

        STDMETHOD(get_Item)(LONG index, ItemType* pVal)
        {
            if (index < 0 || m_container.size() <= static_cast<ULONG>(index)) return E_INVALIDARG;

            collection_value_type& value = m_container[index];
            return CopyItemFromCollection::copy(pVal, CollectionExtractor::Apply(value));
        }

        STDMETHOD(put_Item)(LONG index, ItemType newVal)
        {
            if (index < 0 || m_container.size() <= static_cast<ULONG>(index)) return E_INVALIDARG;

            HRESULT hr = E_FAIL;
            collection_value_type value;
            CopyCollectionFromItem::init(CollectionExtractor::Apply(value));
            hr = CopyCollectionFromItem::copy(CollectionExtractor::Apply(value), ItemExtractor::Apply(newVal));
            if (FAILED(hr)) return hr;

            m_container[index] = value;
            return S_OK;
        }

    };  // class ATL_NO_VTABLE ICollectionImpl






    template<
        class Base, 
        class ItemType,
        class EnumeratorType, 
        class CollectionType,
        class CopyItemFromCollection = GenericCopy<
                                            ItemType, 
                                            typename WithoutAdapt<
                                                typename CollectionType::value_type
                                            >::type
                                       >,
        class ItemExtractor = AddressExtractor<ItemType>,
        class CopyCollectionFromItem = GenericCopy<
                                            typename WithoutAdapt<
                                                typename CollectionType::value_type
                                            >::type, 
                                            ItemType
                                       >,
        class CollectionExtractor = AddressExtractor<
                                        typename WithoutAdapt<
                                            typename CollectionType::value_type
                                        >::type
                                    >,
        const GUID* plibid = &CAtlModule::m_libid,
        WORD wMajor = 1,
        WORD wMinor = 0, 
        class tihclass = CComTypeInfoHolder,
        class ThreadModel = CComObjectThreadModel
    >
    class ATL_NO_VTABLE CComCollection :
        public CComObjectRootEx<ThreadModel>,
        public IDispatchImpl<
                    ICollectionImpl<
                        Base, 
                        ItemType, 
                        EnumeratorType, 
                        CollectionType, 
                        CopyItemFromCollection, 
                        ItemExtractor,
                        CopyCollectionFromItem,
                        CollectionExtractor
                    >, 
                    &__uuidof(Base), 
                    plibid, 
                    wMajor, 
                    wMinor, 
                    tihclass
        >
    {
    public:
        typedef CComCollection<
                    Base, 
                    ItemType, 
                    EnumeratorType, 
                    CollectionType, 
                    CopyItemFromCollection, 
                    ItemExtractor,
                    CopyCollectionFromItem,
                    CollectionExtractor,
                    plibid, 
                    wMajor, 
                    wMinor, 
                    tihclass, 
                    ThreadModel
        > type;
        
        typedef ICollectionImpl<
                    Base, 
                    ItemType, 
                    EnumeratorType, 
                    CollectionType, 
                    CopyItemFromCollection,
                    ItemExtractor,
                    CopyCollectionFromItem,
                    CollectionExtractor
        > base_type;

        typedef typename base_type::interface_type interface_type;
        
        BEGIN_COM_MAP(type)
            COM_INTERFACE_ENTRY_IID(__uuidof(Base), base_type)
            COM_INTERFACE_ENTRY(IDispatch)
        END_COM_MAP()
    };  // class ATL_NO_VTABLE CComCollection

}   // namespace My