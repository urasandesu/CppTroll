#pragma once
#ifndef URASANDESU_NANONYM_COLLECTIONS_ILISTIMPL_H
#define URASANDESU_NANONYM_COLLECTIONS_ILISTIMPL_H

#ifndef URASANDESU_NANONYM_CONCEPTS_COMLIST_H
#include "Urasandesu/NAnonym/Concepts/ComList.h"
#endif

#ifndef URASANDESU_NANONYM_COLLECTIONS_ICOLLECTIONIMPL_H
#include "Urasandesu/NAnonym/Collections/ICollectionImpl.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace Collections {
    
    using namespace Urasandesu::NAnonym::Concepts;
    
    template<
        class Base,
        class ItemType,
        class ListType,
        class ComEnumeratorObject, 
        class CopyItemFromList = use_default, 
        class CopyListFromItem = use_default
    >
    class ATL_NO_VTABLE IListImpl : 
        public ICollectionImpl<Base, ItemType, ListType, ComEnumeratorObject, CopyItemFromList, CopyListFromItem>
    {
        BOOST_CONCEPT_ASSERT((ComList<Base, ItemType>));
        BOOST_CONCEPT_ASSERT((Mutable_RandomAccessContainer<ListType>));
        BOOST_CONCEPT_ASSERT((Sequence<ListType>));

    public:
        typedef typename WithoutAdapt<typename ListType::value_type>::type list_value_type;
        typedef GenericCopy<ItemType, list_value_type> default_copy_item_from_list;
        typedef typename Replace<CopyItemFromList, use_default, default_copy_item_from_list>::type copy_item_from_list;
        typedef GenericCopy<list_value_type, ItemType> default_copy_list_from_item;
        typedef typename Replace<CopyListFromItem, use_default, default_copy_list_from_item>::type copy_list_from_item;
    
    private:
        BOOST_CONCEPT_ASSERT((ATLCopy<copy_item_from_list, ItemType, list_value_type>));
        BOOST_CONCEPT_ASSERT((ATLCopy<copy_list_from_item, list_value_type, ItemType>));

    public:    
        typedef ICollectionImpl<
            Base, 
            ItemType, 
            ListType, 
            ComEnumeratorObject, 
            CopyItemFromList, 
            CopyListFromItem> base_type;
        typedef IListImpl<
            Base, 
            ItemType, 
            ListType, 
            ComEnumeratorObject, 
            CopyItemFromList, 
            CopyListFromItem> type;
        typedef typename base_type::interface_type interface_type;

        typedef typename ListType::iterator list_iterator;

        STDMETHOD(IndexOf)(ItemType item, LONG* index)
        {
            if (index == NULL) return E_POINTER;

            LONG _index = 0;
            for (list_iterator i = m_container.begin(), i_end = m_container.end(); i != i_end; ++i, ++_index)
            {
                list_value_type& _i = *i;
                if (_i == item)
                {
                    *index = _index;
                    return S_OK;
                }
            }
            
            *index = -1;
            return S_FALSE;
        }

        STDMETHOD(Insert)(LONG index, ItemType item)
        {
            if (index < 0 || m_container.size() < static_cast<ULONG>(index)) return E_INVALIDARG;

            HRESULT hr = E_FAIL;
            list_value_type value;
            copy_list_from_item::init(addressof(value));
            hr = copy_list_from_item::copy(addressof(value), addressof(item));
            if (FAILED(hr)) return hr;

            m_container.insert(m_container.begin() + index, value);
            return S_OK;
        }

        STDMETHOD(RemoveAt)(LONG index)
        {
            if (index < 0 || m_container.size() < static_cast<ULONG>(index)) return E_INVALIDARG;

            m_container.erase(m_container.begin() + index);
            return S_OK;
        }

        STDMETHOD(get_Item)(LONG index, ItemType* pVal)
        {
            if (index < 0 || m_container.size() <= static_cast<ULONG>(index)) return E_INVALIDARG;

            list_value_type& value = m_container[index];
            return copy_item_from_list::copy(pVal, addressof(value));
        }

        STDMETHOD(put_Item)(LONG index, ItemType newVal)
        {
            if (index < 0 || m_container.size() <= static_cast<ULONG>(index)) return E_INVALIDARG;

            HRESULT hr = E_FAIL;
            list_value_type value;
            copy_list_from_item::init(addressof(value));
            hr = copy_list_from_item::copy(addressof(value), addressof(newVal));
            if (FAILED(hr)) return hr;

            m_container[index] = value;
            return S_OK;
        }

    };  // class ATL_NO_VTABLE IListImpl

}}}   // namespace Urasandesu { namespace NAnonym { namespace Collections {

#endif  // #ifndef URASANDESU_NANONYM_COLLECTIONS_ILISTIMPL_H