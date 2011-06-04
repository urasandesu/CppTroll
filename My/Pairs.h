#pragma once
#include "Concepts.h"

namespace My
{
    template<
        class Base, 
        class FirstType, 
        class SecondType,
        class FirstCopy = _Copy<FirstType>, 
        class SecondCopy = _Copy<SecondType>
    >
    class ATL_NO_VTABLE IPairImpl : public Base
    {
        BOOST_CONCEPT_ASSERT((ComPair<Base, FirstType, SecondType>));
        BOOST_CONCEPT_ASSERT((ATLCopy<FirstCopy, FirstType, FirstType>));
        BOOST_CONCEPT_ASSERT((ATLCopy<SecondCopy, SecondType, SecondType>));

    public:
        typedef IPairImpl<Base, FirstType, SecondType, FirstCopy, SecondCopy> type;
        typedef Base base_type;
        typedef FirstType first_type;
        typedef SecondType second_type;

        STDMETHOD(get_First)(FirstType* pVal)
        {
            return FirstCopy::copy(pVal, &m_first);
        }

        STDMETHOD(put_First)(FirstType newVal)
        {
            return FirstCopy::copy(&m_first, &newVal);
        }

        STDMETHOD(get_Second)(SecondType* pVal)
        {
            return SecondCopy::copy(pVal, &m_second);
        }

        STDMETHOD(put_Second)(SecondType newVal)
        {
            return SecondCopy::copy(&m_second, &newVal);
        }

    private:
        FirstType m_first;
        SecondType m_second;

    };  // class ATL_NO_VTABLE IPairImpl

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