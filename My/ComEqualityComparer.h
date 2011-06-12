#pragma once
#ifndef INCLUDED_COMEQUALITYCOMPARER_H
#define INCLUDED_COMEQUALITYCOMPARER_H

namespace My
{
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
}   // namespace My

#endif  // #ifndef INCLUDED_COMEQUALITYCOMPARER_H