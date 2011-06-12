#pragma once
#ifndef INCLUDED_CCOMEQUALITYCOMPARER_H
#define INCLUDED_CCOMEQUALITYCOMPARER_H

#ifndef INCLUDED_IEQUALITYCOMPARERIMPL_H
#include "IEqualityComparerImpl.h"
#endif  // #ifndef INCLUDED_IEQUALITYCOMPARERIMPL_H

namespace My
{
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
}   // namespace My

#endif  // #ifndef INCLUDED_CCOMEQUALITYCOMPARER_H