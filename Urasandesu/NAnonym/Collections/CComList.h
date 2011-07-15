#pragma once
#ifndef URASANDESU_NANONYM_COLLECTIONS_CCOMLIST_H
#define URASANDESU_NANONYM_COLLECTIONS_CCOMLIST_H

#ifndef URASANDESU_NANONYM_COLLECTIONS_ILISTIMPL_H
#include "Urasandesu/NAnonym/Collections/IListImpl.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace Collections {

    template<
        class Base, 
        class ItemType,
        class ListType,
        class ComEnumeratorObject, 
        class CopyItemFromList = use_default,
        class CopyListFromItem = use_default,
        const GUID* plibid = &CAtlModule::m_libid,
        WORD wMajor = 1,
        WORD wMinor = 0, 
        class tihclass = use_default,
        class ThreadModel = use_default
    >
    class ATL_NO_VTABLE CComList :
        public CComObjectRootEx<typename Replace<ThreadModel, use_default, CComObjectThreadModel>::type>,
        public IDispatchImpl<
                    IListImpl<
                        Base, 
                        ItemType, 
                        ListType, 
                        ComEnumeratorObject, 
                        CopyItemFromList, 
                        CopyListFromItem
                    >, 
                    &__uuidof(Base), 
                    plibid, 
                    wMajor, 
                    wMinor, 
                    typename Replace<tihclass, use_default, CComTypeInfoHolder>::type
        >
    {
    public:
        typedef CComList<
                    Base, 
                    ItemType, 
                    ListType, 
                    ComEnumeratorObject, 
                    CopyItemFromList, 
                    CopyListFromItem,
                    plibid, 
                    wMajor, 
                    wMinor, 
                    tihclass, 
                    ThreadModel
        > type;
        
        typedef IListImpl<
                    Base, 
                    ItemType, 
                    ListType, 
                    ComEnumeratorObject, 
                    CopyItemFromList,
                    CopyListFromItem
        > base_type;

        typedef typename base_type::interface_type interface_type;
        
        BEGIN_COM_MAP(type)
            COM_INTERFACE_ENTRY_IID(__uuidof(Base), base_type)
            COM_INTERFACE_ENTRY(IDispatch)
        END_COM_MAP()
    };  // class ATL_NO_VTABLE CComList

}}}   // namespace Urasandesu { namespace NAnonym { namespace Collections {

#endif  // #ifndef URASANDESU_NANONYM_COLLECTIONS_CCOMLIST_H