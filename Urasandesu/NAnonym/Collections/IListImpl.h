#pragma once
#ifndef URASANDESU_NANONYM_COLLECTIONS_ILISTIMPL_H
#define URASANDESU_NANONYM_COLLECTIONS_ILISTIMPL_H

namespace Urasandesu { namespace NAnonym { namespace Collections {

    template<
        class Base,
        class ItemType,
        class EnumeratorType, 
        class CollectionType,
        class CopyItemFromCollection, 
        class CopyCollectionFromItem
    >
    class ATL_NO_VTABLE ICollectionImpl;





    template<
        class Base,
        class ItemType,
        class EnumeratorType, 
        class ListType,
        class CopyItemFromList = GenericCopy<
                                    ItemType, 
                                    typename WithoutAdapt<
                                        typename ListType::value_type
                                    >::type
                                 >, 
        class CopyListFromItem = GenericCopy<
                                    typename WithoutAdapt<
                                        typename ListType::value_type
                                    >::type, 
                                    ItemType
                                 >
    >
    class ATL_NO_VTABLE IListImpl : 
        public ICollectionImpl<Base, ItemType, EnumeratorType, ListType, CopyItemFromList, CopyListFromItem>
    {
        BOOST_CONCEPT_ASSERT((ComList<Base, ItemType>));
        BOOST_CONCEPT_ASSERT((Mutable_RandomAccessContainer<ListType>));
        BOOST_CONCEPT_ASSERT((Sequence<ListType>));

    public:
        typedef ICollectionImpl<
            Base, 
            ItemType, 
            EnumeratorType, 
            ListType, 
            CopyItemFromList, 
            CopyListFromItem> base_type;
        typedef IListImpl<
            Base, 
            ItemType, 
            EnumeratorType, 
            ListType, 
            CopyItemFromList, 
            CopyListFromItem> type;
        typedef typename base_type::interface_type interface_type;

        typedef typename WithoutAdapt<typename ListType::value_type>::type list_value_type;
        typedef typename ListType::iterator list_iterator;

        STDMETHOD(IndexOf)(ItemType item, LONG* index)
        {
            if (index == NULL) return E_POINTER;

            // 文字列向けの特化版作れるように、Contains と同様、STL を利用する。
            // find_if には関数オブジェクトが渡せるので、そこで呼び出し回数を積算。

            struct Finder : 
                public std::unary_function<int, bool>   // Argument の type は call_traits あたりを使うと良さげ。
            {
            };

            return E_NOTIMPL;
        }

        STDMETHOD(Insert)(LONG index, ItemType item)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(RemoveAt)(LONG index)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(get_Item)(LONG index, ItemType* pVal)
        {
            //if (index < 0 || m_container.size() <= static_cast<ULONG>(index)) return E_INVALIDARG;

            //collection_value_type& value = m_container[index];
            //return CopyItemFromCollection::copy(pVal, CollectionAddresser::Apply(value));
            return E_NOTIMPL;
        }

        STDMETHOD(put_Item)(LONG index, ItemType newVal)
        {
            //if (index < 0 || m_container.size() <= static_cast<ULONG>(index)) return E_INVALIDARG;

            //HRESULT hr = E_FAIL;
            //collection_value_type value;
            //CopyCollectionFromItem::init(CollectionAddresser::Apply(value));
            //hr = CopyCollectionFromItem::copy(CollectionAddresser::Apply(value), ItemAddresser::Apply(newVal));
            //if (FAILED(hr)) return hr;

            //m_container[index] = value;
            //return S_OK;
            return E_NOTIMPL;
        }

    };  // class ATL_NO_VTABLE IListImpl

}}}   // namespace Urasandesu { namespace NAnonym { namespace Collections {

#endif  // #ifndef URASANDESU_NANONYM_COLLECTIONS_ILISTIMPL_H