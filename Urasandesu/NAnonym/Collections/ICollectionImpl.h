#pragma once
#ifndef URASANDESU_NANONYM_COLLECTIONS_ICOLLECTIONIMPL_H
#define URASANDESU_NANONYM_COLLECTIONS_ICOLLECTIONIMPL_H

#ifndef URASANDESU_NANONYM_COLLECTIONS_IENUMERABLEIMPL_H
#include "Urasandesu/NAnonym/Collections/IEnumerableImpl.h"
#endif

#ifndef URASANDESU_NANONYM_CONCEPTS_COMCOLLECTION_H
#include "Urasandesu/NAnonym/Concepts/ComCollection.h"
#endif

#ifndef URASANDESU_NANONYM_TRAITS_WITHOUTADAPT_H
#include "Urasandesu/NAnonym/Traits/WithoutAdapt.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace Collections {

    template<
        class Base,
        class ItemType,
        class ComEnumeratorObject, 
        class CollectionType,
        //class ItemEqualityComparer,
        class CopyItemFromCollection = GenericCopy<
                                            ItemType, 
                                            typename WithoutAdapt<
                                                typename CollectionType::value_type
                                            >::type
                                       >, 
        class ItemAddresser = AddressExtractor<ItemType>,
        class CopyCollectionFromItem = GenericCopy<
                                            typename WithoutAdapt<
                                                typename CollectionType::value_type
                                            >::type, 
                                            ItemType
                                       >,
        class CollectionAddresser = AddressExtractor<
                                        typename WithoutAdapt<
                                            typename CollectionType::value_type
                                        >::type
                                    >
    >
    class ATL_NO_VTABLE ICollectionImpl : 
        public IEnumerableImpl<Base, CollectionType, ComEnumeratorObject>
    {
        BOOST_CONCEPT_ASSERT((ComCollection<Base, ItemType>));
        BOOST_CONCEPT_ASSERT((Mutable_RandomAccessContainer<CollectionType>));
        BOOST_CONCEPT_ASSERT((Sequence<CollectionType>));
        BOOST_CONCEPT_ASSERT((ATLCopy<
                                CopyItemFromCollection, 
                                ItemType, 
                                typename WithoutAdapt<
                                    typename CollectionType::value_type
                                >::type
                              >));
        BOOST_CONCEPT_ASSERT((Extractor<ItemAddresser>));
        BOOST_CONCEPT_ASSERT((ATLCopy<
                                CopyCollectionFromItem, 
                                typename WithoutAdapt<
                                    typename CollectionType::value_type
                                >::type, 
                                ItemType
                              >));
        BOOST_CONCEPT_ASSERT((Extractor<CollectionAddresser>));

    public:
        typedef IEnumerableImpl<Base, CollectionType, ComEnumeratorObject> base_type;
        typedef ICollectionImpl<
            Base, 
            ItemType, 
            ComEnumeratorObject, 
            CollectionType, 
            CopyItemFromCollection, 
            ItemAddresser, 
            CopyCollectionFromItem, 
            CollectionAddresser> type;
        typedef typename base_type::interface_type interface_type;

        typedef typename WithoutAdapt<typename CollectionType::value_type>::type collection_value_type;
        typedef typename CollectionType::iterator collection_iterator;

        STDMETHOD(Add)(ItemType item)
        {
            HRESULT hr = E_FAIL;
            collection_value_type value;
            CopyCollectionFromItem::init(CollectionAddresser::Apply(value));
            hr = CopyCollectionFromItem::copy(CollectionAddresser::Apply(value), ItemAddresser::Apply(item));
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
                CopyItemFromCollection::init(ItemAddresser::Apply(item));
                hr = CopyItemFromCollection::copy(ItemAddresser::Apply(item), CollectionAddresser::Apply(_i));
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
            return CopyItemFromCollection::copy(pVal, CollectionAddresser::Apply(value));
        }

        STDMETHOD(put_Item)(LONG index, ItemType newVal)
        {
            if (index < 0 || m_container.size() <= static_cast<ULONG>(index)) return E_INVALIDARG;

            HRESULT hr = E_FAIL;
            collection_value_type value;
            CopyCollectionFromItem::init(CollectionAddresser::Apply(value));
            hr = CopyCollectionFromItem::copy(CollectionAddresser::Apply(value), ItemAddresser::Apply(newVal));
            if (FAILED(hr)) return hr;

            m_container[index] = value;
            return S_OK;
        }

    private:


    };  // class ATL_NO_VTABLE ICollectionImpl

}}}   // namespace Urasandesu { namespace NAnonym { namespace Collections {

#endif  // #ifndef URASANDESU_NANONYM_COLLECTIONS_ICOLLECTIONIMPL_H