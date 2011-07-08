
#include "stdafx.h"

#ifndef URASANDESU_NANONYM_TRAITS_INSERTCONST_H
#include "Urasandesu/NAnonym/Traits/InsertConst.h"
#endif

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

namespace
{
    using Urasandesu::NAnonym::Traits::InsertConst;
    using boost::is_same;

    struct MyClass { };

    BOOST_AUTO_TEST_SUITE(InsertConstTestSuite)

    BOOST_AUTO_TEST_CASE(InsertConstTest)
    {
        BOOST_MPL_ASSERT((is_same<InsertConst<INT>::type, const INT>));
        BOOST_MPL_ASSERT((is_same<InsertConst<INT*>::type, const INT*>));
        BOOST_MPL_ASSERT((is_same<InsertConst<const INT*>::type, const INT*>));
        BOOST_MPL_ASSERT((is_same<InsertConst<INT* const>::type, const INT* const>));
        BOOST_MPL_ASSERT((is_same<InsertConst<const INT* const>::type, const INT* const>));
        BOOST_MPL_ASSERT((is_same<InsertConst<MyClass>::type, const MyClass>));
        BOOST_MPL_ASSERT((is_same<InsertConst<MyClass&>::type, const MyClass&>));
    }

    BOOST_AUTO_TEST_SUITE_END()
}