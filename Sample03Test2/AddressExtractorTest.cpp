
#include "stdafx.h"

#ifndef URASANDESU_NANONYM_TRAITS_ADDRESSEXTRACTOR_H
#include "Urasandesu/NAnonym/Traits/AddressExtractor.h"
#endif

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

namespace
{
    using boost::is_same;
    using Urasandesu::NAnonym::Traits::AddressExtractor;

    struct MyClass 
    { 
        MyClass() : m_n(0) { }
        explicit MyClass(INT n) : m_n(n) { }
        bool operator==(const MyClass& that)
        {
            if (this == &that) return true;
            return false;
        }
        int m_n;
    };

    BOOST_AUTO_TEST_SUITE(AddressExtractorTestSuite)

    BOOST_AUTO_TEST_CASE(INTTest)
    {
        typedef AddressExtractor<INT> Extractor;
        
        BOOST_MPL_ASSERT((is_same<Extractor::source_type, INT>));    
        BOOST_MPL_ASSERT((is_same<Extractor::result_type, INT*>));    
        {
            INT value = 10;
            Extractor::result_type result = Extractor::Apply(value);
            BOOST_REQUIRE(result == &value);
            BOOST_REQUIRE(*result == value);
        }
    }

    BOOST_AUTO_TEST_CASE(MyClassTest)
    {
        typedef AddressExtractor<MyClass> Extractor;
        
        BOOST_MPL_ASSERT((is_same<Extractor::source_type, MyClass>));    
        BOOST_MPL_ASSERT((is_same<Extractor::result_type, MyClass*>));    
        {
            MyClass value(10);
            Extractor::result_type result = Extractor::Apply(value);
            BOOST_REQUIRE(result == &value);
            BOOST_REQUIRE(*result == value);
        }
    }

    BOOST_AUTO_TEST_CASE(CComBSTRTest)
    {
        typedef AddressExtractor<CComBSTR> Extractor;
        
        BOOST_MPL_ASSERT((is_same<Extractor::source_type, CComBSTR>));    
        BOOST_MPL_ASSERT((is_same<Extractor::result_type, BSTR*>));    
        {
            CComBSTR value(L"aiueo");
            Extractor::result_type result = Extractor::Apply(value);
            BOOST_REQUIRE(result == &value);
            BOOST_REQUIRE(*result == value);
        }
    }

    BOOST_AUTO_TEST_CASE(_com_ptr_tTest)
    {
        typedef AddressExtractor<IMyEnumerableGeneratorPtr> Extractor;
        
        BOOST_MPL_ASSERT((is_same<Extractor::source_type, IMyEnumerableGeneratorPtr>));    
        BOOST_MPL_ASSERT((is_same<Extractor::result_type, IMyEnumerableGenerator**>));    
        {
            HRESULT hr = E_FAIL;
            IMyEnumerableGeneratorPtr value;
            hr = value.CreateInstance(__uuidof(MyEnumerableGenerator));
            BOOST_REQUIRE(SUCCEEDED(hr));
            Extractor::result_type result = Extractor::Apply(value);
            BOOST_REQUIRE(result == &value);
            BOOST_REQUIRE(*result == value);
        }
    }

    BOOST_AUTO_TEST_CASE(CComPtrTest)
    {
        typedef AddressExtractor<CComPtr<IMyEnumerableGenerator>> Extractor;
        
        BOOST_MPL_ASSERT((is_same<Extractor::source_type, CComPtr<IMyEnumerableGenerator>>));    
        BOOST_MPL_ASSERT((is_same<Extractor::result_type, IMyEnumerableGenerator**>));
        {
            HRESULT hr = E_FAIL;
            CComPtr<IMyEnumerableGenerator> value;
            hr = value.CoCreateInstance(__uuidof(MyEnumerableGenerator));
            BOOST_REQUIRE(SUCCEEDED(hr));
            Extractor::result_type result = Extractor::Apply(value);
            BOOST_REQUIRE(result == &value.p);  // CComPtr<T> prohibits using the operator& by assert(p == 0).
            BOOST_REQUIRE(*result == value);
        }
    }

    BOOST_AUTO_TEST_SUITE_END()
}