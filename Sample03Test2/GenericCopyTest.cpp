
#include "stdafx.h"

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#ifndef URASANDESU_NANONYM_CONCEPTS_ATLCOPY_H
#include "Urasandesu/NAnonym/Concepts/ATLCopy.h"
#endif

#ifndef URASANDESU_NANONYM_TRAITS_VARIANTTRAITS_H
#include "Urasandesu/NAnonym/Traits/VariantTraits.h"
#endif

#ifndef URASANDESU_NANONYM_UTILITIES_GENERICCOPY_H
#include "Urasandesu/NAnonym/Utilities/GenericCopy.h"
#endif

namespace
{
    using boost::is_base_of;
    using boost::addressof;
    using Urasandesu::NAnonym::Utilities::GenericCopy;
    using Urasandesu::NAnonym::Concepts::ATLCopy;

    BOOST_AUTO_TEST_SUITE(GenericCopyTestSuite)

    BOOST_AUTO_TEST_CASE(GenericCopyCComBSTRTest01)
    {
        CComBSTR s1(L"aiueo");
        CComBSTR s2;

        typedef GenericCopy<CComBSTR, CComBSTR> atl_copy;
        BOOST_CONCEPT_ASSERT((ATLCopy<atl_copy, CComBSTR, CComBSTR>));
        
        HRESULT hr = E_FAIL;
        GenericCopy<CComBSTR, CComBSTR>::init(addressof(s2));
        hr = GenericCopy<CComBSTR, CComBSTR>::copy(addressof(s2), addressof(s1));        
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(s1 == s2);
        BOOST_REQUIRE(static_cast<BSTR>(s1) != static_cast<BSTR>(s2));
    }

    BOOST_AUTO_TEST_CASE(GenericCopyCComBSTRTest02)
    {
        BSTR s1 = L"aiueo";
        CComBSTR s2;

        typedef GenericCopy<CComBSTR, BSTR> atl_copy;
        BOOST_CONCEPT_ASSERT((ATLCopy<atl_copy, CComBSTR, BSTR>));
        
        HRESULT hr = E_FAIL;
        atl_copy::init(addressof(s2));
        hr = atl_copy::copy(addressof(s2), addressof(s1));        
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(CComBSTR(s1) == s2);
        BOOST_REQUIRE(s1 != static_cast<BSTR>(s2));
    }

    BOOST_AUTO_TEST_CASE(GenericCopyCComBSTRTest03)
    {
        CComBSTR s1(L"aiueo");
        BSTR s2 = NULL;

        typedef GenericCopy<BSTR, CComBSTR> atl_copy;
        BOOST_CONCEPT_ASSERT((ATLCopy<atl_copy, BSTR, CComBSTR>));
        
        HRESULT hr = E_FAIL;
        atl_copy::init(addressof(s2));
        hr = atl_copy::copy(addressof(s2), addressof(s1));        
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(s1 == CComBSTR(s2));
        BOOST_REQUIRE(static_cast<BSTR>(s1) != s2);
    }

    BOOST_AUTO_TEST_CASE(GenericCopyCComBSTRTest04)
    {
        BSTR s1 = L"aiueo";
        BSTR s2 = NULL;

        typedef GenericCopy<BSTR, BSTR> atl_copy;
        BOOST_CONCEPT_ASSERT((ATLCopy<atl_copy, BSTR, BSTR>));
        
        HRESULT hr = E_FAIL;
        atl_copy::init(addressof(s2));
        hr = atl_copy::copy(addressof(s2), addressof(s1));        
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(CComBSTR(s1) == CComBSTR(s2));
        BOOST_REQUIRE(s1 != s2);
    }

    BOOST_AUTO_TEST_CASE(GenericCopyCComPtrTest01)
    {
        HRESULT hr = E_FAIL;
        
        CComPtr<IMyEnumerableGenerator> p1;
        hr = p1.CoCreateInstance(__uuidof(MyEnumerableGenerator));
        BOOST_REQUIRE(SUCCEEDED(hr));
        CComPtr<IMyEnumerableGenerator> p2;
 
        typedef GenericCopy<CComPtr<IMyEnumerableGenerator>, CComPtr<IMyEnumerableGenerator>> atl_copy;
        BOOST_CONCEPT_ASSERT((ATLCopy<atl_copy, CComPtr<IMyEnumerableGenerator>, CComPtr<IMyEnumerableGenerator>>));
        atl_copy::init(addressof(p2));
        hr = atl_copy::copy(addressof(p2), addressof(p1));
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(p1 == p2);
    }

    BOOST_AUTO_TEST_CASE(GenericCopyCComPtrTest02)
    {
        HRESULT hr = E_FAIL;
        
        IMyEnumerableGenerator* p1 = NULL;
        hr = ::CoCreateInstance(__uuidof(MyEnumerableGenerator), NULL, CLSCTX_ALL, __uuidof(IMyEnumerableGenerator), reinterpret_cast<void**>(&p1));
        BOOST_REQUIRE(SUCCEEDED(hr));
        CComPtr<IMyEnumerableGenerator> p2;
 
        typedef GenericCopy<CComPtr<IMyEnumerableGenerator>, IMyEnumerableGenerator*> atl_copy;
        BOOST_CONCEPT_ASSERT((ATLCopy<atl_copy, CComPtr<IMyEnumerableGenerator>, IMyEnumerableGenerator*>));
        atl_copy::init(addressof(p2));
        hr = atl_copy::copy(addressof(p2), addressof(p1));
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(p1 == p2);
        BOOST_REQUIRE(p1->Release() == 1);
    }

    BOOST_AUTO_TEST_CASE(GenericCopyCComPtrTest03)
    {
        HRESULT hr = E_FAIL;
        
        CComPtr<IMyEnumerableGenerator> p1;
        hr = p1.CoCreateInstance(__uuidof(MyEnumerableGenerator));
        BOOST_REQUIRE(SUCCEEDED(hr));
        IMyEnumerableGenerator* p2 = NULL;
 
        typedef GenericCopy<IMyEnumerableGenerator*, CComPtr<IMyEnumerableGenerator>> atl_copy;
        BOOST_CONCEPT_ASSERT((ATLCopy<atl_copy, IMyEnumerableGenerator*, CComPtr<IMyEnumerableGenerator>>));
        atl_copy::init(addressof(p2));
        hr = atl_copy::copy(addressof(p2), addressof(p1));
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(p1 == p2);
        BOOST_REQUIRE(p2->Release() == 1);
    }

    BOOST_AUTO_TEST_CASE(GenericCopyVARIANTTest01)
    {
        CComVariant v1(10);
        CComVariant v2;

        typedef GenericCopy<VARIANT, VARIANT> atl_copy;
        BOOST_CONCEPT_ASSERT((ATLCopy<atl_copy, VARIANT, VARIANT>));
        
        HRESULT hr = E_FAIL;
        atl_copy::init(addressof(v2));
        hr = atl_copy::copy(addressof(v2), addressof(v1));        
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(v2.vt == VT_I4);
        BOOST_REQUIRE(v2.lVal == 10);
    }

    BOOST_AUTO_TEST_CASE(GenericCopyVARIANTTest02)
    {
        LONG v1 = 10;
        VARIANT v2;

        typedef GenericCopy<VARIANT, LONG> atl_copy;
        BOOST_CONCEPT_ASSERT((ATLCopy<atl_copy, VARIANT, LONG>));
        
        HRESULT hr = E_FAIL;
        atl_copy::init(addressof(v2));
        hr = atl_copy::copy(addressof(v2), addressof(v1));        
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(v2.vt == VT_I4);
        BOOST_REQUIRE(v2.lVal == 10);
    }

    BOOST_AUTO_TEST_CASE(GenericCopyVARIANTTest02_1)
    {
        HRESULT hr = E_FAIL;
        
        CComPtr<IMyEnumerableGenerator> v1;
        hr = v1.CoCreateInstance(__uuidof(MyEnumerableGenerator));
        BOOST_REQUIRE(SUCCEEDED(hr));
        VARIANT v2;
 
        typedef GenericCopy<VARIANT, CComPtr<IMyEnumerableGenerator>> atl_copy;
        BOOST_CONCEPT_ASSERT((ATLCopy<atl_copy, VARIANT, CComPtr<IMyEnumerableGenerator>>));
        atl_copy::init(addressof(v2));
        hr = atl_copy::copy(addressof(v2), addressof(v1));
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(v2.vt == VT_DISPATCH);
        BOOST_REQUIRE(v2.pdispVal == static_cast<IMyEnumerableGenerator*>(v1));
        BOOST_REQUIRE(SUCCEEDED(::VariantClear(&v2)));
    }

    BOOST_AUTO_TEST_CASE(GenericCopyVARIANTTest02_2)
    {
        HRESULT hr = E_FAIL;

        CComBSTR v1(L"aiueo");
        VARIANT v2;
 
        typedef GenericCopy<VARIANT, CComBSTR> atl_copy;
        BOOST_CONCEPT_ASSERT((ATLCopy<atl_copy, VARIANT, CComBSTR>));
        atl_copy::init(addressof(v2));
        hr = atl_copy::copy(addressof(v2), addressof(v1));
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(v2.vt == VT_BSTR);
        BOOST_REQUIRE(CComBSTR(v2.bstrVal) == v1);
        BOOST_REQUIRE(v2.bstrVal != static_cast<BSTR>(v1));
        BOOST_REQUIRE(SUCCEEDED(::VariantClear(&v2)));
    }

    BOOST_AUTO_TEST_CASE(GenericCopyVARIANTTest03)
    {
        VARIANT v1;
        ::VariantInit(&v1);
        v1.vt = VT_I4;
        v1.lVal = 10;
        LONG v2;

        typedef GenericCopy<LONG, VARIANT> atl_copy;
        BOOST_CONCEPT_ASSERT((ATLCopy<atl_copy, LONG, VARIANT>));
        
        HRESULT hr = E_FAIL;
        atl_copy::init(addressof(v2));
        hr = atl_copy::copy(addressof(v2), addressof(v1));        
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(v2 == 10);
    }

    BOOST_AUTO_TEST_SUITE_END()
}