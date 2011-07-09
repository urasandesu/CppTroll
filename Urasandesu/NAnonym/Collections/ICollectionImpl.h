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

#ifndef URASANDESU_NANONYM_UTILITIES_GENERICCOPY_H
#include "Urasandesu/NAnonym/Utilities/GenericCopy.h"
#endif

#ifndef URASANDESU_NANONYM_TRAITS_REPLACE_H
#include "Urasandesu/NAnonym/Traits/Replace.h"
#endif

#ifndef URASANDESU_NANONYM_TRAITS_ADDRESSEXTRACTOR_H
#include "Urasandesu/NAnonym/Traits/AddressExtractor.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace Collections {

    using namespace Urasandesu::NAnonym::Utilities;
    using namespace Urasandesu::NAnonym::Traits;

    template<
        class Base,
        class ItemType,
        class CollectionType,
        class ComEnumeratorObject, 
        class CopyItemFromCollection = use_default, 
        class ItemAddresser = use_default,
        class CopyCollectionFromItem = use_default,
        class CollectionAddresser = use_default
    >
    class ATL_NO_VTABLE ICollectionImpl : 
        public IEnumerableImpl<Base, CollectionType, ComEnumeratorObject>
    {
        BOOST_CONCEPT_ASSERT((ComCollection<Base, ItemType>));
        BOOST_CONCEPT_ASSERT((Mutable_RandomAccessContainer<CollectionType>));
        BOOST_CONCEPT_ASSERT((Sequence<CollectionType>));
        
    public:
        typedef typename WithoutAdapt<typename CollectionType::value_type>::type collection_value_type;
        typedef GenericCopy<ItemType, collection_value_type> default_copy_item_from_collection;
        typedef typename Replace<CopyItemFromCollection, use_default, default_copy_item_from_collection>::type copy_item_from_collection;
        typedef AddressExtractor<ItemType> default_item_addresser;
        typedef typename Replace<ItemAddresser, use_default, default_item_addresser>::type item_addresser;
        typedef GenericCopy<collection_value_type, ItemType> default_copy_collection_from_item;
        typedef typename Replace<CopyCollectionFromItem, use_default, default_copy_collection_from_item>::type copy_collection_from_item;
        typedef AddressExtractor<collection_value_type> default_collection_addresser;
        typedef typename Replace<CollectionAddresser, use_default, default_collection_addresser>::type collection_addresser;
    
    private:
        BOOST_CONCEPT_ASSERT((ATLCopy<copy_item_from_collection, ItemType, collection_value_type>));
        BOOST_CONCEPT_ASSERT((Extractor<item_addresser>));
        BOOST_CONCEPT_ASSERT((ATLCopy<copy_collection_from_item, collection_value_type, ItemType>));
        BOOST_CONCEPT_ASSERT((Extractor<collection_addresser>));

    public:
        typedef IEnumerableImpl<Base, CollectionType, ComEnumeratorObject> base_type;
        typedef ICollectionImpl<
            Base, 
            ItemType, 
            CollectionType, 
            ComEnumeratorObject, 
            CopyItemFromCollection, 
            ItemAddresser, 
            CopyCollectionFromItem, 
            CollectionAddresser> type;
        typedef typename base_type::interface_type interface_type;

        //typedef typename WithoutAdapt<typename CollectionType::value_type>::type collection_value_type;
        typedef typename CollectionType::iterator collection_iterator;

        STDMETHOD(Add)(ItemType item)
        {
            HRESULT hr = E_FAIL;
            collection_value_type value;
            copy_collection_from_item::init(collection_addresser::Apply(value));
            hr = copy_collection_from_item::copy(collection_addresser::Apply(value), item_addresser::Apply(item));
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
                copy_item_from_collection::init(item_addresser::Apply(item));
                hr = copy_item_from_collection::copy(item_addresser::Apply(item), collection_addresser::Apply(_i));
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
            return copy_item_from_collection::copy(pVal, collection_addresser::Apply(value));
        }

        STDMETHOD(put_Item)(LONG index, ItemType newVal)
        {
            if (index < 0 || m_container.size() <= static_cast<ULONG>(index)) return E_INVALIDARG;

            HRESULT hr = E_FAIL;
            collection_value_type value;
            copy_collection_from_item::init(collection_addresser::Apply(value));
            hr = copy_collection_from_item::copy(collection_addresser::Apply(value), item_addresser::Apply(newVal));
            if (FAILED(hr)) return hr;

            m_container[index] = value;
            return S_OK;
        }

    private:


    };  // class ATL_NO_VTABLE ICollectionImpl

}}}   // namespace Urasandesu { namespace NAnonym { namespace Collections {

#endif  // #ifndef URASANDESU_NANONYM_COLLECTIONS_ICOLLECTIONIMPL_H