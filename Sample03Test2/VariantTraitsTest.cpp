
#include "stdafx.h"

#ifndef URASANDESU_NANONYM_TRAITS_VARIANTTRAITS_H
#include "Urasandesu/NAnonym/Traits/VariantTraits.h"
#endif

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

namespace
{
    using boost::is_same;
    using Urasandesu::NAnonym::Traits::VariantTraits;
    using Urasandesu::NAnonym::Traits::I_VT_INT;

    struct MyClass { };

    BOOST_AUTO_TEST_SUITE(VariantTraitsTestSuite)

    BOOST_AUTO_TEST_CASE(VariantTraitsTest)
    {
        BOOST_MPL_ASSERT((is_same<VariantTraits<int>::param_type, int>));
        BOOST_MPL_ASSERT((is_same<VariantTraits<int>::const_param_type, int>));
        BOOST_MPL_ASSERT((is_same<VariantTraits<int>::var_type, I_VT_INT>));
        BOOST_MPL_ASSERT((is_same<VariantTraits<int>::return_type, int>));

        BOOST_MPL_ASSERT((is_same<VariantTraits<IUnknown*>::return_type, IUnknown*>));
        BOOST_MPL_ASSERT((is_same<VariantTraits<CY>::return_type, CY&>));
    }

    BOOST_AUTO_TEST_SUITE_END()
}