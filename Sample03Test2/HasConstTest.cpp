
#include "stdafx.h"

#ifndef URASANDESU_NANONYM_TRAITS_HASCONST_H
#include "Urasandesu/NAnonym/Traits/HasConst.h"
#endif

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

namespace
{
    using Urasandesu::NAnonym::Traits::HasConst;
    using boost::mpl::not_;

    struct MyClass { };

    BOOST_AUTO_TEST_SUITE(HasConstTestSuite)

    BOOST_AUTO_TEST_CASE(HasConstTest)
    {
        BOOST_MPL_ASSERT((HasConst<const MyClass*>));
        BOOST_MPL_ASSERT((HasConst<MyClass* const>));
        BOOST_MPL_ASSERT((HasConst<const MyClass* const>));
        BOOST_MPL_ASSERT((HasConst<const MyClass&>));
        BOOST_MPL_ASSERT((HasConst<MyClass const&>));
        BOOST_MPL_ASSERT((not_<HasConst<MyClass&>>));
        BOOST_MPL_ASSERT((not_<HasConst<MyClass*>>));
        BOOST_MPL_ASSERT((not_<HasConst<MyClass>>));
    }

    BOOST_AUTO_TEST_SUITE_END()
}