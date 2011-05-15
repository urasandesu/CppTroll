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
    struct PairOf
    {
        BOOST_MPL_ASSERT((boost::is_base_of<IUnknown, X>));
            
        BOOST_CONCEPT_USAGE(PairOf)
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
    };  // struct PairOf

    template<class X, class SourceType, class DestinationType>
    struct ATLCopyPolicy
    {
        BOOST_CONCEPT_USAGE(ATLCopyPolicy)
        {
            HRESULT hr;
            const SourceType* pFrom;
            DestinationType* pTo;

            X::init(pTo);
            hr = X::copy(pTo, pFrom);
            X::destroy(pTo);
        }
    };  // struct ATLCopyPolicy

}   // namespace My
