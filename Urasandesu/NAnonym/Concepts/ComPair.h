#pragma once
#ifndef URASANDESU_NANONYM_CONCEPTS_COMPAIR_H
#define URASANDESU_NANONYM_CONCEPTS_COMPAIR_H

namespace Urasandesu { namespace NAnonym { namespace Concepts {

    template<class X, class FirstType, class SecondType>
    struct ComPair
    {
        BOOST_MPL_ASSERT((is_base_of<IUnknown, X>));
            
        BOOST_CONCEPT_USAGE(ComPair)
        {
            HRESULT hr;
            X* pX1;

            FirstType* pFirst;
            hr = pX1->get_First(pFirst);
            hr = pX1->put_First(*pFirst);

            SecondType* pSecond;
            hr = pX1->get_Second(pSecond);
            hr = pX1->put_Second(*pSecond);
        }
    };  // struct ComPair

}}}   // namespace Urasandesu { namespace NAnonym { namespace Concepts {

#endif  // #ifndef URASANDESU_NANONYM_CONCEPTS_COMPAIR_H
