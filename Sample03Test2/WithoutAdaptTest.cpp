
#include "stdafx.h"

#ifndef URASANDESU_NANONYM_TRAITS_WITHOUTADAPT_H
#include "Urasandesu/NAnonym/Traits/WithoutAdapt.h"
#endif

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

namespace
{
    using boost::is_same;
    using Urasandesu::NAnonym::Traits::WithoutAdapt;

    BOOST_AUTO_TEST_SUITE(WithoutAdaptTestSuite)

    BOOST_AUTO_TEST_CASE(WithoutAdaptTest)
    {
        typedef CAdapt<CComBSTR> AdaptedBSTR;
        
        BOOST_MPL_ASSERT((is_same<WithoutAdapt<CComBSTR>::type, CComBSTR>));
        BOOST_MPL_ASSERT((is_same<WithoutAdapt<AdaptedBSTR>::type, CComBSTR>));
    }

    #ifdef _MY_PERFORMANCE_TEST
    BOOST_AUTO_TEST_CASE(PerformanceTest)
    {
        HRESULT hr = S_OK;

        unsigned int number = 0;
        errno_t err;

        boost::timer t;
        for (int n = 0; n < 1000000; ++n)
        {
            err = rand_s(&number);
            if (err)
            {
                std::cout << "rand_s error !!" << std::endl;
                break;
            }
            
            LONG hashCode = 0;
            CComVariant value(number);
            hr = My::GenericEqualityComparer<VARIANT>::GetHashCode(value, &hashCode);
            if (FAILED(hr) || hashCode != static_cast<LONG>(number))
            {
                std::cout << "GetHashCode error !!" << std::endl;
                break;
            }
        }
        std::cout << "Time: " << t.elapsed() << " sec." << std::endl;
    }

    BOOST_AUTO_TEST_CASE(PerformanceTest2)
    {
        HRESULT hr = S_OK;

        unsigned int number = 0;
        errno_t err;

        boost::timer t;
        for (int n = 0; n < 1000000; ++n)
        {
            err = rand_s(&number);
            if (err)
            {
                std::cout << "rand_s error !!" << std::endl;
                break;
            }
            
            CComVariant value(number);
            LONG hashCode = static_cast<LONG>(value.uintVal);
            if (hashCode != static_cast<LONG>(number))
            {
                std::cout << "GetHashCode error !!" << std::endl;
                break;
            }
        }
        std::cout << "Time: " << t.elapsed() << " sec." << std::endl;
    }
    #endif // _MY_PERFORMANCE_TEST

BOOST_AUTO_TEST_SUITE_END()

}