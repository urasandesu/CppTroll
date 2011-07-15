#pragma once
#ifndef URASANDESU_NANONYM_UTILITIES_IPAIRIMPL_H
#define URASANDESU_NANONYM_UTILITIES_IPAIRIMPL_H

#ifndef URASANDESU_NANONYM_CONCEPTS_COMPAIR_H
#include "Urasandesu/NAnonym/Concepts/ComPair.h"
#endif

#ifndef URASANDESU_NANONYM_TRAITS_WITHOUTADAPT_H
#include "Urasandesu/NAnonym/Traits/WithoutAdapt.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace Utilities {

    using namespace Urasandesu::NAnonym::Concepts;
    using namespace Urasandesu::NAnonym::Traits;

    template<
        class Base, 
        class FirstType, 
        class SecondType,
        class FirstCopy = use_default, 
        class SecondCopy = use_default
    >
    class ATL_NO_VTABLE IPairImpl : public Base
    {
        BOOST_CONCEPT_ASSERT((ComPair<Base, FirstType, SecondType>));

    public:
        typedef typename WithoutAdapt<FirstType>::type first_type;
        typedef GenericCopy<first_type> default_first_copy;
        typedef typename Replace<FirstCopy, use_default, default_first_copy>::type first_copy;
        typedef typename WithoutAdapt<SecondType>::type second_type;
        typedef GenericCopy<second_type> default_second_copy;
        typedef typename Replace<SecondCopy, use_default, default_second_copy>::type second_copy;

        typedef IPairImpl<Base, FirstType, SecondType, FirstCopy, SecondCopy> type;
        typedef Base base_type;
        typedef Base interface_type;

    private:
        BOOST_CONCEPT_ASSERT((ATLCopy<first_copy, first_type, first_type>));
        BOOST_CONCEPT_ASSERT((ATLCopy<second_copy, second_type, second_type>));
        
    public:
        STDMETHOD(get_First)(FirstType* pVal)
        {
            if (pVal == NULL) return E_POINTER;
            first_type& val = *pVal;
            return first_copy::copy(addressof(val), addressof(m_first));
        }

        STDMETHOD(put_First)(FirstType newVal)
        {
            first_type& val = newVal;
            return first_copy::copy(addressof(m_first), addressof(val));
        }

        STDMETHOD(get_Second)(SecondType* pVal)
        {
            if (pVal == NULL) return E_POINTER;
            second_type& val = *pVal;
            return second_copy::copy(addressof(val), addressof(m_second));
        }

        STDMETHOD(put_Second)(SecondType newVal)
        {
            second_type& val = newVal;
            return second_copy::copy(addressof(m_second), addressof(val));
        }

    private:
        first_type m_first;
        second_type m_second;

    };  // class ATL_NO_VTABLE IPairImpl

}}}   // namespace Urasandesu { namespace NAnonym { namespace Utilities {

#endif  // #ifndef URASANDESU_NANONYM_UTILITIES_IPAIRIMPL_H