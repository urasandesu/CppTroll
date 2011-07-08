#pragma once
#ifndef URASANDESU_NANONYM_CONCEPTS_COMEQUALITYCOMPARER_H
#define URASANDESU_NANONYM_CONCEPTS_COMEQUALITYCOMPARER_H

namespace Urasandesu { namespace NAnonym { namespace Concepts {

    template<class X, class Type>
    struct ComEqualityComparer
    {
        BOOST_MPL_ASSERT((is_base_of<IUnknown, X>));
            
        BOOST_CONCEPT_USAGE(ComEqualityComparer)
        {
            HRESULT hr;
            X* pX;
            Type* pValue1;
            Type* pValue2;

            // Equals
            {
                VARIANT_BOOL equals;
                hr = pX->Equals(*pValue1, *pValue2, &equals);
            }

            // GetHashCode
            {
                LONG hashCode;
                hr = pX->GetHashCode(*pValue1, &hashCode);
            }
        }
    };  // struct ComEqualityComparer
    
}}}   // namespace Urasandesu { namespace NAnonym { namespace Concepts {

#endif  // #ifndef URASANDESU_NANONYM_CONCEPTS_COMEQUALITYCOMPARER_H