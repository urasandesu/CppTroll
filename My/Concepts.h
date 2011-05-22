#pragma once
#include <atlbase.h>
#include <atlcom.h>
#include <boost/type_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/concept/assert.hpp>
#include <boost/concept/usage.hpp>
#include <boost/concept_check.hpp>

namespace My
{
    template<class X, class FirstType, class SecondType>
    struct ComPair
    {
        BOOST_MPL_ASSERT((boost::is_base_of<IUnknown, X>));
            
        BOOST_CONCEPT_USAGE(ComPair)
        {
            HRESULT hr;
            X* pX1;

            FirstType first;
            hr = pX1->get_First(&first);
            hr = pX1->put_First(first);

            SecondType second;
            hr = pX1->get_Second(&second);
            hr = pX1->put_Second(second);
        }
    };  // struct ComPair

    template<class X, class DestinationType, class SourceType>
    struct ATLCopy
    {
        BOOST_CONCEPT_USAGE(ATLCopy)
        {
            HRESULT hr;
            const SourceType* pFrom;
            DestinationType* pTo;

            X::init(pTo);
            hr = X::copy(pTo, pFrom);
            X::destroy(pTo);
        }
    };  // struct ATLCopy

    template<class X>
    struct ComEnumerable
    {
        BOOST_MPL_ASSERT((boost::is_base_of<IUnknown, X>));
            
        BOOST_CONCEPT_USAGE(ComEnumerable)
        {
            HRESULT hr;
            X* pX;
            IUnknown* pUnk;

            hr = pX->get__NewEnum(&pUnk);
        }
    };  // struct ComEnumerable

    //template<class X, class ItemType>
    //struct ComEnumerator
    //{
    //    BOOST_MPL_ASSERT((boost::is_base_of<IUnknown, X>));
    //        
    //    BOOST_CONCEPT_USAGE(ComEnumerator)
    //    {
    //        HRESULT hr;
    //        X* pX1;

    //        // Next
    //        {
    //            ULONG celt = 0;
    //            ItemType* pItem;
    //            ULONG celtFetched = 0;
    //            hr = pX1->Next(celt, pItem, &celtFetched);
    //        }

    //        // Skip
    //        {
    //            ULONG celt = 0;
    //            hr = pX1->Skip(celt);
    //        }

    //        // Reset
    //        {
    //            hr = pX1->Reset();
    //        }

    //        // Clone
    //        {
    //            X* pX2 = NULL;
    //            hr = pX1->Clone(&pX2);
    //        }
    //    }
    //};  // struct ComEnumerator

}   // namespace My
