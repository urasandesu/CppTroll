
#include "stdafx.h"

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#ifndef INCLUDED_UTILITIES_H
#include "Utilities.h"
#endif

namespace
{
    using My::I_VT_INT;
    using My::I_VT_BYREF;
    using My::I_VT_BSTR;
    using My::I_VT_VARIANT;
    using My::I_VT_INT_REF;
    using My::I_VT_PTR;
    using My::I_VT_R4;
    using My::VariantEquals;
    using My::VariantGetHashCode;
    
    struct MyClass { };
    
    BOOST_AUTO_TEST_SUITE(UtilitiesTestSuite)

    BOOST_AUTO_TEST_CASE(VariantEqualsTest)
    {
        // VT_INT    
        {
            INT value1 = 10;
            INT value2 = 10;
            INT value3 = 20;
            BOOST_REQUIRE((VariantEquals(value1, value2, I_VT_INT())));
            BOOST_REQUIRE((!VariantEquals(value1, value3, I_VT_INT())));
        }
        
        // VT_BYREF | VT_INT    
        {
            INT n1 = 10;
            INT n2 = 10;
            INT* value1 = &n1;
            INT* value2 = &n1;
            INT* value3 = &n2;
            BOOST_REQUIRE((VariantEquals(value1, value2, I_VT_INT_REF())));
            BOOST_REQUIRE((!VariantEquals(value1, value3, I_VT_INT_REF())));
        }
        
        // VT_BYREF
        {
            MyClass myClass1;
            MyClass myClass2;
            MyClass& value1 = myClass1;
            MyClass& value2 = myClass1;
            MyClass& value3 = myClass2;
            BOOST_REQUIRE((VariantEquals<const MyClass&>(value1, value2, I_VT_BYREF())));
            BOOST_REQUIRE((!VariantEquals<const MyClass&>(value1, value3, I_VT_BYREF())));
        }
        
        // VT_BSTR
        {
            CComBSTR value1(L"aiueo");
            CComBSTR value2(L"aiueo");
            CComBSTR value3(L"kakikukeko");
            BOOST_REQUIRE((VariantEquals<const OLECHAR*>(value1, value2, I_VT_BSTR())));
            BOOST_REQUIRE((!VariantEquals<const OLECHAR*>(value1, value3, I_VT_BSTR())));
        }
        
        // VT_VARIANT
        {
            CComVariant value1(L"aiueo");
            CComVariant value2(L"aiueo");
            CComVariant value3(10);
            BOOST_REQUIRE((VariantEquals<const VARIANT&>(value1, value2, I_VT_VARIANT())));
            BOOST_REQUIRE((!VariantEquals<const VARIANT&>(value1, value3, I_VT_VARIANT())));
        }
    }

    BOOST_AUTO_TEST_CASE(VariantGetHashCodeTest)
    {
        // VT_INT    
        {
            INT value = 10;
            BOOST_REQUIRE((VariantGetHashCode(value, I_VT_INT()) == value));
        }
        
        // VT_PTR
        {
            MyClass myClass;
            MyClass* value = &myClass;
            BOOST_REQUIRE((VariantGetHashCode(value, I_VT_PTR()) == reinterpret_cast<LONG>(&myClass)));
        }
        
        // VT_BYREF
        {
            MyClass value;
            BOOST_REQUIRE((VariantGetHashCode<const MyClass&>(value, I_VT_BYREF()) == reinterpret_cast<LONG>(&value)));
        }
        
        // VT_BSTR
        {
            CComBSTR value(L"sasisuseso");
            BOOST_REQUIRE((VariantGetHashCode<const OLECHAR*>(value, I_VT_BSTR()) == -944633185L));
        }
        
        // VT_R4
        {
            FLOAT value = 10.f;
            BOOST_REQUIRE((VariantGetHashCode(value, I_VT_R4()) == 1092616192L));
        }
    }


    BOOST_AUTO_TEST_SUITE_END()
}