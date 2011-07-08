#pragma once
#ifndef URASANDESU_NANONYM_CONCEPTS_COMCOLLECTION_H
#define URASANDESU_NANONYM_CONCEPTS_COMCOLLECTION_H

#ifndef URASANDESU_NANONYM_CONCEPTS_COMENUMERABLE_H
#include "Urasandesu/NAnonym/Concepts/ComEnumerable.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace Concepts {

    template<class X, class ItemType>
    struct ComCollection
    {
        BOOST_CONCEPT_ASSERT((ComEnumerable<X>));
        
        BOOST_CONCEPT_USAGE(ComCollection)
        {
            HRESULT hr;
            X* pX;

            // Add
            {
                ItemType* pItem;
                hr = pX->Add(*pItem);
            }

            // Clear
            {
                hr = pX->Clear();
            }

            // Contains
            {
                ItemType* pItem;
                VARIANT_BOOL exists;
                hr = pX->Contains(*pItem, &exists);
            }

            // CopyTo 
            {
                SAFEARRAY* pArray;
                LONG index;
                hr = pX->CopyTo(pArray, index);
            }

            // Remove
            {
                ItemType* pItem;
                hr = pX->Remove(*pItem);
            }

            // Count
            {
                LONG count;
                hr = pX->get_Count(&count);
            }

            // IsReadOnly
            {
                VARIANT_BOOL isReadOnly;
                hr = pX->get_IsReadOnly(&isReadOnly);
            }
        }
    };  // struct ComCollection
}}}   // namespace Urasandesu { namespace NAnonym { namespace Concepts {

#endif  // #ifndef URASANDESU_NANONYM_CONCEPTS_COMCOLLECTION_H