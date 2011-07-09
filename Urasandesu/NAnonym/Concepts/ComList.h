#pragma once
#ifndef URASANDESU_NANONYM_CONCEPTS_COMLIST_H
#define URASANDESU_NANONYM_CONCEPTS_COMLIST_H

#ifndef URASANDESU_NANONYM_CONCEPTS_COMCOLLECTION_H
#include "Urasandesu/NAnonym/Concepts/ComCollection.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace Concepts {

    template<class X, class ItemType>
    struct ComList
    {
        BOOST_CONCEPT_ASSERT((ComCollection<X, ItemType>));
        
        BOOST_CONCEPT_USAGE(ComList)
        {
            HRESULT hr;
            X* pX;

            // IndexOf
            {
                LONG index;
                ItemType* pItem;
                hr = pX->IndexOf(*pItem, &index);
            }

            // Insert
            {
                LONG index;
                ItemType* pItem;
                hr = pX->Insert(index, *pItem);
            }

            // RemoveAt
            {
                LONG index;
                hr = pX->RemoveAt(index);
            }

            // Item
            {
                LONG index;
                ItemType* pItem;
                hr = pX->get_Item(index, pItem);
                hr = pX->put_Item(index, *pItem);
            }
        }
    };  // struct ComCollection


}}}   // namespace Urasandesu { namespace NAnonym { namespace Concepts {

#endif // #ifndef URASANDESU_NANONYM_CONCEPTS_COMLIST_H