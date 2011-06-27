#pragma once
#ifndef INCLUDED_COMLIST_H
#define INCLUDED_COMLIST_H

#ifndef INCLUDED_COMCOLLECTION_H
#include "ComCollection.h"
#endif

namespace My
{
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


}   // namespace My

#endif // #ifndef INCLUDED_COMLIST_H