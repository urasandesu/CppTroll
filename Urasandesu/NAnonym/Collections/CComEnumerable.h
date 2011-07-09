#pragma once
#ifndef URASANDESU_NANONYM_COLLECTIONS_CCOMENUMERABLE_H
#define URASANDESU_NANONYM_COLLECTIONS_CCOMENUMERABLE_H

#ifndef URASANDESU_NANONYM_COLLECTIONS_IENUMERABLEIMPL_H
#include "Urasandesu/NAnonym/Collections/IEnumerableImpl.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace Collections {

    template<
        class Base, 
        class ComEnumeratorObject, 
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
            IEnumerableImpl<Base, RangeType, ComEnumeratorObject>, 
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
            ComEnumeratorObject, 
            RangeType, 
            plibid, 
            wMajor, 
            wMinor, 
            tihclass, 
            ThreadModel
        > type;
        
        typedef IEnumerableImpl<Base, RangeType, ComEnumeratorObject> base_type;
        typedef typename base_type::interface_type interface_type;
        
        BEGIN_COM_MAP(type)
            COM_INTERFACE_ENTRY_IID(__uuidof(Base), base_type)
            COM_INTERFACE_ENTRY(IDispatch)
        END_COM_MAP()
    };  // class ATL_NO_VTABLE CComEnumerable

}}}   // namespace Urasandesu { namespace NAnonym { namespace Collections {

#endif  // #ifndef URASANDESU_NANONYM_COLLECTIONS_CCOMENUMERABLE_H