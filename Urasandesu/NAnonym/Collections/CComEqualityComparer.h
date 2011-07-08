#pragma once
#ifndef URASANDESU_NANONYM_COLLECTIONS_CCOMEQUALITYCOMPARER_H
#define URASANDESU_NANONYM_COLLECTIONS_CCOMEQUALITYCOMPARER_H

#ifndef URASANDESU_NANONYM_COLLECTIONS_IEQUALITYCOMPARERIMPL_H
#include "Urasandesu/NAnonym/Collections/IEqualityComparerImpl.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace Collections {

    template<
        class Base, 
        class Type,
        class EqualityComparer = GenericEqualityComparer<Type>,
        const GUID* plibid = &CAtlModule::m_libid,
        WORD wMajor = 1,
        WORD wMinor = 0, 
        class tihclass = CComTypeInfoHolder,
        class ThreadModel = CComObjectThreadModel
    >
    class ATL_NO_VTABLE CComEqualityComparer :
        public CComObjectRootEx<ThreadModel>,
        public IDispatchImpl<
            IEqualityComparerImpl<Base, Type, EqualityComparer>, 
            &__uuidof(Base), 
            plibid, 
            wMajor, 
            wMinor, 
            tihclass
        >
    {
    public:
        typedef CComEqualityComparer<
            Base, 
            Type, 
            EqualityComparer,
            plibid, 
            wMajor, 
            wMinor, 
            tihclass, 
            ThreadModel
        > type;
        
        typedef IEqualityComparerImpl<Base, Type, EqualityComparer> base_type;
        typedef Base interface_type;
        
        BEGIN_COM_MAP(type)
            COM_INTERFACE_ENTRY_IID(__uuidof(Base), base_type)
            COM_INTERFACE_ENTRY(IDispatch)
        END_COM_MAP()
    };  // class ATL_NO_VTABLE CComEqualityComparer

}}}   // namespace Urasandesu { namespace NAnonym { namespace Collections {

#endif  // #ifndef URASANDESU_NANONYM_COLLECTIONS_CCOMEQUALITYCOMPARER_H