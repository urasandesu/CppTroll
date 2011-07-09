#pragma once
#ifndef URASANDESU_NANONYM_UTILITIES_IPAIRIMPL_H
#define URASANDESU_NANONYM_UTILITIES_IPAIRIMPL_H

namespace Urasandesu { namespace NAnonym { namespace Utilities {

    using namespace Urasandesu::NAnonym::Concepts;

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

}}}   // namespace Urasandesu { namespace NAnonym { namespace Utilities {

#endif  // #ifndef URASANDESU_NANONYM_UTILITIES_IPAIRIMPL_H