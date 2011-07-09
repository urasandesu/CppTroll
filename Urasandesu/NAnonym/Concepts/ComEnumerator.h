#pragma once
#ifndef URASANDESU_NANONYM_CONCEPTS_COMENUMERATOR_H
#define URASANDESU_NANONYM_CONCEPTS_COMENUMERATOR_H

namespace Urasandesu { namespace NAnonym { namespace Concepts {

    template<class X, class ItemType>
    struct ComEnumerator
    {
        BOOST_MPL_ASSERT((is_base_of<IUnknown, X>));
            
        BOOST_CONCEPT_USAGE(ComEnumerator)
        {
            HRESULT hr;
            X* pX1;

            // Next
            {
                ULONG celt;
                ItemType* rgelt;
                ULONG celtFetched;
                hr = pX1->Next(celt, rgelt, &celtFetched);
            }

            // Skip
            {
                ULONG celt;
                hr = pX1->Skip(celt);
            }

            // Reset
            {
                hr = pX1->Reset();
            }

            // Clone
            {
                X* pX2;
                hr = pX1->Clone(&pX2);
            }
        }
    };  // struct ComEnumerator

}}}   // namespace Urasandesu { namespace NAnonym { namespace Concepts {

#endif  // #ifndef URASANDESU_NANONYM_CONCEPTS_COMENUMERATOR_H