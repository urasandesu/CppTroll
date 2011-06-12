#pragma once
#ifndef INCLUDED_CCOMENUMERABLE_H
#define INCLUDED_CCOMENUMERABLE_H

#ifndef INCLUDED_IENUMERABLEIMPL_H
#include "IEnumerableImpl.h"
#endif

namespace My
{
    template<
        class Base, 
        class EnumeratorType, 
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
            IEnumerableImpl<Base, EnumeratorType, RangeType>, 
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
            EnumeratorType, 
            RangeType, 
            plibid, 
            wMajor, 
            wMinor, 
            tihclass, 
            ThreadModel
        > type;
        
        typedef IEnumerableImpl<Base, EnumeratorType, RangeType> base_type;
        typedef typename base_type::interface_type interface_type;
        
        BEGIN_COM_MAP(type)
            COM_INTERFACE_ENTRY_IID(__uuidof(Base), base_type)
            COM_INTERFACE_ENTRY(IDispatch)
        END_COM_MAP()
    };  // class ATL_NO_VTABLE CComEnumerable

}   // namespace My

#endif  // #ifndef INCLUDED_CCOMENUMERABLE_H