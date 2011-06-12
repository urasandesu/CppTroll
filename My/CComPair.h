#pragma once
#ifndef INCLUDED_CCOMPAIR_H
#define INCLUDED_CCOMPAIR_H

namespace My
{
    template<
        class Base, 
        class FirstType, 
        class SecondType,
        class FirstCopy, 
        class SecondCopy
    >
    class ATL_NO_VTABLE IPairImpl;

    template<
        class Base, 
        class FirstType, 
        class SecondType,
        class FirstCopy = _Copy<FirstType>, 
        class SecondCopy = _Copy<SecondType>, 
        const GUID* plibid = &CAtlModule::m_libid,
        WORD wMajor = 1,
        WORD wMinor = 0, 
        class tihclass = CComTypeInfoHolder,
        class ThreadModel = CComObjectThreadModel
    >
    class ATL_NO_VTABLE CComPair :
        public CComObjectRootEx<ThreadModel>,
        public IDispatchImpl<
            IPairImpl<
                Base, 
                FirstType, 
                SecondType, 
                FirstCopy, 
                SecondCopy
            >, 
            &__uuidof(Base), 
            plibid, 
            wMajor, 
            wMinor, 
            tihclass
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
        > _CComPair;
        
        typedef IPairImpl<Base, FirstType, SecondType, FirstCopy, SecondCopy> _CComPairBase;
        
        BEGIN_COM_MAP(_CComPair)
            COM_INTERFACE_ENTRY_IID(__uuidof(Base), _CComPairBase)
            COM_INTERFACE_ENTRY(IDispatch)
        END_COM_MAP()
    };  // class ATL_NO_VTABLE CComPair

}   // namespace My

#endif  // #ifndef INCLUDED_CCOMPAIR_H