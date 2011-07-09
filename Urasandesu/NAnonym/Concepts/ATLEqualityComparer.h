#pragma once
#ifndef URASANDESU_NANONYM_CONCEPTS_ATLEQUALITYCOMPARER_H
#define URASANDESU_NANONYM_CONCEPTS_ATLEQUALITYCOMPARER_H

namespace Urasandesu { namespace NAnonym { namespace Concepts {

    template<class X, class Type>
    struct ATLEqualityComparer
    {
        BOOST_CONCEPT_USAGE(ATLEqualityComparer)
        {
            HRESULT hr;
            Type* pValue1;
            Type* pValue2;

            // For normal type.
            {
                VARIANT_BOOL equals;
                hr = X::Equals(*pValue1, *pValue2, &equals);

                LONG hashCode;
                hr = X::GetHashCode(*pValue1, &hashCode);
            }

            // For specialized type that overloads operator&.
            {
                VARIANT_BOOL equals;
                hr = X::Equals(*&*pValue1, *&*pValue2, &equals);

                LONG hashCode;
                hr = X::GetHashCode(*&*pValue1, &hashCode);
            }
        }
    };  // struct ATLEqualityComparer
}}}   // namespace Urasandesu { namespace NAnonym { namespace Concepts {

#endif // #ifndef URASANDESU_NANONYM_CONCEPTS_ATLEQUALITYCOMPARER_H
