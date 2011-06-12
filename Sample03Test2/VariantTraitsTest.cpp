
#include "stdafx.h"

#ifndef INCLUDED_VARIANTTRAITS_H
#include "VariantTraits.h"
#endif

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

namespace
{
    using boost::is_same;
    using My::VariantTraits;

    struct MyClass { };

    BOOST_AUTO_TEST_SUITE(VariantTraitsTestSuite)

    BOOST_AUTO_TEST_CASE(VariantTraitsTest)
    {
        BOOST_MPL_ASSERT((is_same<VariantTraits<int>::param_type, const int>));
        BOOST_MPL_ASSERT((is_same<VariantTraits<int>::const_param_type, const int>));
        //BOOST_MPL_ASSERT((is_same<VariantTraits<int>::var_type, const int>));
        BOOST_MPL_ASSERT((is_same<VariantTraits<int>::return_type, int>));

        BOOST_MPL_ASSERT((is_same<VariantTraits<IUnknown*>::return_type, IUnknown*>));
        BOOST_MPL_ASSERT((is_same<VariantTraits<CY>::return_type, CY&>));
    }

    BOOST_AUTO_TEST_SUITE_END()
}