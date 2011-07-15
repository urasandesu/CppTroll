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
        class CollectionType,
        class ComEnumeratorObject, 
        class CopyItemFromCollection = use_default,
        class CopyCollectionFromItem = use_default,
        const GUID* plibid = &CAtlModule::m_libid,
        WORD wMajor = 1,
        WORD wMinor = 0, 
        class tihclass = use_default,
        class ThreadModel = use_default
    >
    class ATL_NO_VTABLE CComCollection :
        public CComObjectRootEx<typename Replace<ThreadModel, use_default, CComObjectThreadModel>::type>,
        public IDispatchImpl<
                    ICollectionImpl<
                        Base, 
                        ItemType, 
                        CollectionType, 
                        ComEnumeratorObject, 
                        CopyItemFromCollection, 
                        CopyCollectionFromItem
                    >, 
                    &__uuidof(Base), 
                    plibid, 
                    wMajor, 
                    wMinor, 
                    typename Replace<tihclass, use_default, CComTypeInfoHolder>::type
        >
    {
    public:
        typedef CComCollection<
                    Base, 
                    ItemType, 
                    CollectionType, 
                    ComEnumeratorObject, 
                    CopyItemFromCollection, 
                    CopyCollectionFromItem,
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
                    ComEnumeratorObject, 
                    CopyItemFromCollection,
                    CopyCollectionFromItem
        > base_type;

        typedef typename base_type::interface_type interface_type;
        
        BEGIN_COM_MAP(type)
            COM_INTERFACE_ENTRY_IID(__uuidof(Base), base_type)
            COM_INTERFACE_ENTRY(IDispatch)
        END_COM_MAP()
    };  // class ATL_NO_VTABLE CComCollection

}}}   // namespace Urasandesu { namespace NAnonym { namespace Collections {

#endif  // #ifndef URASANDESU_NANONYM_COLLECTIONS_CCOMCOLLECTION_H