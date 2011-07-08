
#include "stdafx.h"

#ifndef URASANDESU_NANONYM_TRAITS_ADDIMPLICITCONVERSION_H
#include "Urasandesu/NAnonym/Traits/AddImplicitConversion.h"
#endif

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include <string>

namespace
{
    using boost::is_convertible;
    using boost::mpl::not_;
    using std::string;
    using Urasandesu::NAnonym::Traits::AddImplicitConversion;
    using Urasandesu::NAnonym::Traits::IgnoreParam1;

    template<class T>
    struct MyClass1 { };

    BOOST_AUTO_TEST_SUITE(AddImplicitConversionTestSuite)

    BOOST_AUTO_TEST_CASE(AssignOperatorTest)
    {
        typedef MyClass1<INT> IntClass;
        typedef MyClass1<IUnknown*> UnkClass;
        typedef MyClass1<string> StrClass;
        
        BOOST_MPL_ASSERT((is_convertible<IntClass, AddImplicitConversion<IgnoreParam1<MyClass1>>>));
        BOOST_MPL_ASSERT((is_convertible<UnkClass, AddImplicitConversion<IgnoreParam1<MyClass1>>>));
        BOOST_MPL_ASSERT((is_convertible<StrClass, AddImplicitConversion<IgnoreParam1<MyClass1>>>));
        BOOST_MPL_ASSERT((not_<is_convertible<INT, AddImplicitConversion<IgnoreParam1<MyClass1>>>>));
        BOOST_MPL_ASSERT((not_<is_convertible<IUnknown*, AddImplicitConversion<IgnoreParam1<MyClass1>>>>));
        BOOST_MPL_ASSERT((not_<is_convertible<string, AddImplicitConversion<IgnoreParam1<MyClass1>>>>));
    }

    BOOST_AUTO_TEST_SUITE_END()
}