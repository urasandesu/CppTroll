#pragma once
#ifndef URASANDESU_NANONYM_COLLECTIONS_CCOMCOLLECTION_H
#define URASANDESU_NANONYM_COLLECTIONS_CCOMCOLLECTION_H

#ifndef URASANDESU_NANONYM_COLLECTIONS_ICOLLECTIONIMPL_H
#include "Urasandesu/NAnonym/Collections/ICollectionImpl.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace Collections {

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
                        CollectionType, 
                        EnumeratorType, 
                        CopyItemFromCollection, 
                        ItemAddresser,
                        CopyCollectionFromItem,
                        CollectionAddresser
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
                    ItemAddresser,
                    CopyCollectionFromItem,
                    CollectionAddresser,
                    plibid, 
                    wMajor, 
                    wMinor, 
                    tihclass, 
                    ThreadModel
        > type;
        
        typedef ICollectionImpl<
                    Base, 
                    ItemType, 
                    CollectionType, 
                    EnumeratorType, 
                    CopyItemFromCollection,
                    ItemAddresser,
                    CopyCollectionFromItem,
                    CollectionAddresser
        > base_type;

        typedef typename base_type::interface_type interface_type;
        
        BEGIN_COM_MAP(type)
            COM_INTERFACE_ENTRY_IID(__uuidof(Base), base_type)
            COM_INTERFACE_ENTRY(IDispatch)
        END_COM_MAP()
    };  // class ATL_NO_VTABLE CComCollection

}}}   // namespace Urasandesu { namespace NAnonym { namespace Collections {

#endif  // #ifndef URASANDESU_NANONYM_COLLECTIONS_CCOMCOLLECTION_H