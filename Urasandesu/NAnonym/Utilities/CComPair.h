#pragma once
#ifndef URASANDESU_NANONYM_UTILITIES_CCOMPAIR_H
#define URASANDESU_NANONYM_UTILITIES_CCOMPAIR_H

#ifndef URASANDESU_NANONYM_UTILITIES_IPAIRIMPL_H
#include "Urasandesu/NAnonym/Utilities/IPairImpl.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace Utilities {

    template<
        class Base, 
        class FirstType, 
        class SecondType,
        class FirstCopy = use_default, 
        class SecondCopy = use_default, 
        const GUID* plibid = &CAtlModule::m_libid,
        WORD wMajor = 1,
        WORD wMinor = 0, 
        class tihclass = use_default,
        class ThreadModel = use_default
    >
    class ATL_NO_VTABLE CComPair :
        public CComObjectRootEx<typename Replace<ThreadModel, use_default, CComObjectThreadModel>::type>,
        public IDispatchImpl<
            IPairImpl<Base, FirstType, SecondType, FirstCopy, SecondCopy>, 
            &__uuidof(Base), 
            plibid, 
            wMajor, 
            wMinor, 
            typename Replace<tihclass, use_default, CComTypeInfoHolder>::type
        >
    {
    public:
        typedef CComPair<
            Base, 
            FirstType, 
            SecondType, 
            FirstCopy, 
            SecondCopy, 
            plibid, 
            wMajor, 
            wMinor, 
            tihclass, 
            ThreadModel
        > type;
        
        typedef IPairImpl<Base, FirstType, SecondType, FirstCopy, SecondCopy> base_type;
        typedef typename base_type::interface_type interface_type;
        
        BEGIN_COM_MAP(type)
            COM_INTERFACE_ENTRY_IID(__uuidof(Base), base_type)
            COM_INTERFACE_ENTRY(IDispatch)
        END_COM_MAP()
    };  // class ATL_NO_VTABLE CComPair

}}}   // namespace Urasandesu { namespace NAnonym { namespace Utilities {

#endif  // #ifndef URASANDESU_NANONYM_UTILITIES_CCOMPAIR_H