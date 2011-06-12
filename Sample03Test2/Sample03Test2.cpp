
#include "stdafx.h"

struct MyClass { };

#include "GenericEqualityComparer.h"

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

void Hoge(IUnknown* pUnk)
{
}

void Hoge(const IUnknown* pUnk)
{
}

BOOST_AUTO_TEST_SUITE(GenericEqualityComparerTestSuite)

BOOST_AUTO_TEST_CASE(IntTest)
{
    CComVariant v;

    Hoge(My::I_VT_UNKNOWN_TRAITS::Val(v));

    const VARIANT* p_v = &v;
    Hoge(My::I_VT_UNKNOWN_TRAITS::Val(*p_v));

    int i = 10;
    const int& iii = i;
    //iii = i;

    const int* p_i = &i;
    p_i = &i;

    int* const pp_i = &i;
    //pp_i = &i;

    // same
    {
        HRESULT hr = S_OK;

        INT value1 = 10;
        INT value2 = 10;

        VARIANT_BOOL equals = VARIANT_FALSE;
        hr = My::GenericEqualityComparer<INT>::Equals(value1, value2, &equals);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(equals == VARIANT_TRUE);

        LONG hashCode1 = 0;
        hr = My::GenericEqualityComparer<INT>::GetHashCode(value1, &hashCode1);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(hashCode1 == 10);

        LONG hashCode2 = 0;
        hr = My::GenericEqualityComparer<INT>::GetHashCode(value2, &hashCode2);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(hashCode2 == 10);
    }

    // different
    {
        HRESULT hr = S_OK;

        INT value1 = 10;
        INT value2 = 20;

        VARIANT_BOOL equals = VARIANT_FALSE;
        hr = My::GenericEqualityComparer<INT>::Equals(value1, value2, &equals);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(equals == VARIANT_FALSE);

        LONG hashCode1 = 0;
        hr = My::GenericEqualityComparer<INT>::GetHashCode(value1, &hashCode1);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(hashCode1 == 10);

        LONG hashCode2 = 0;
        hr = My::GenericEqualityComparer<INT>::GetHashCode(value2, &hashCode2);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(hashCode2 == 20);
    }
}

BOOST_AUTO_TEST_CASE(MyClassTest)
{
    //struct MyClass { };

    // same
    {
        HRESULT hr = S_OK;

        std::auto_ptr<MyClass> pValue1(new MyClass());
        MyClass* pValue2 = pValue1.get();

        VARIANT_BOOL equals = VARIANT_FALSE;
        hr = My::GenericEqualityComparer<MyClass>::Equals(*pValue1, *pValue2, &equals);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(equals == VARIANT_TRUE);

        LONG hashCode1 = 0;
        hr = My::GenericEqualityComparer<MyClass>::GetHashCode(*pValue1, &hashCode1);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(hashCode1 == reinterpret_cast<LONG>(&*pValue1));

        LONG hashCode2 = 0;
        hr = My::GenericEqualityComparer<MyClass>::GetHashCode(*pValue2, &hashCode2);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(hashCode2 == reinterpret_cast<LONG>(&*pValue2));
    }

    // different
    {
        HRESULT hr = S_OK;

        std::auto_ptr<MyClass> pValue1(new MyClass());
        std::auto_ptr<MyClass> pValue2(new MyClass());

        VARIANT_BOOL equals = VARIANT_FALSE;
        hr = My::GenericEqualityComparer<MyClass>::Equals(*pValue1, *pValue2, &equals);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(equals == VARIANT_FALSE);

        LONG hashCode1 = 0;
        hr = My::GenericEqualityComparer<MyClass>::GetHashCode(*pValue1, &hashCode1);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(hashCode1 == reinterpret_cast<LONG>(&*pValue1));

        LONG hashCode2 = 0;
        hr = My::GenericEqualityComparer<MyClass>::GetHashCode(*pValue2, &hashCode2);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(hashCode2 == reinterpret_cast<LONG>(&*pValue2));
    }
}

BOOST_AUTO_TEST_CASE(BSTRTest)
{
    // same
    {
        HRESULT hr = S_OK;

        CComBSTR value1 = L"aiueo";
        CComBSTR value2 = L"aiueo";

        VARIANT_BOOL equals = VARIANT_FALSE;
        hr = My::GenericEqualityComparer<BSTR>::Equals(value1, value2, &equals);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(equals == VARIANT_TRUE);

        LONG hashCode1 = 0;
        hr = My::GenericEqualityComparer<BSTR>::GetHashCode(value1, &hashCode1);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(hashCode1 == 2122807606);

        LONG hashCode2 = 0;
        hr = My::GenericEqualityComparer<BSTR>::GetHashCode(value2, &hashCode2);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(hashCode2 == 2122807606);
    }

    // different
    {
        HRESULT hr = S_OK;

        CComBSTR value1 = L"aiueo";
        CComBSTR value2 = L"kakikukeko";

        VARIANT_BOOL equals = VARIANT_FALSE;
        hr = My::GenericEqualityComparer<BSTR>::Equals(value1, value2, &equals);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(equals == VARIANT_FALSE);

        LONG hashCode1 = 0;
        hr = My::GenericEqualityComparer<BSTR>::GetHashCode(value1, &hashCode1);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(hashCode1 == 2122807606);

        LONG hashCode2 = 0;
        hr = My::GenericEqualityComparer<BSTR>::GetHashCode(value2, &hashCode2);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(hashCode2 == -1284133397);
    }
}

BOOST_AUTO_TEST_CASE(IUnknownPtrTest)
{
    // same
    {
        HRESULT hr = S_OK;

        IMyEnumerableGeneratorPtr pValue1;
        hr = pValue1.CreateInstance(__uuidof(MyEnumerableGenerator));
        BOOST_REQUIRE(SUCCEEDED(hr));
        IMyEnumerableGeneratorPtr pValue2 = pValue1;

        VARIANT_BOOL equals = VARIANT_FALSE;
        hr = My::GenericEqualityComparer<IUnknown*>::Equals(pValue1, pValue2, &equals);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(equals == VARIANT_TRUE);

        LONG hashCode1 = 0;
        hr = My::GenericEqualityComparer<IUnknown*>::GetHashCode(pValue1, &hashCode1);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(hashCode1 == reinterpret_cast<LONG>(pValue1.GetInterfacePtr()));

        LONG hashCode2 = 0;
        hr = My::GenericEqualityComparer<IUnknown*>::GetHashCode(pValue2, &hashCode2);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(hashCode2 == reinterpret_cast<LONG>(pValue2.GetInterfacePtr()));
    }

    // different
    {
        HRESULT hr = S_OK;

        IMyEnumerableGeneratorPtr pValue1;
        hr = pValue1.CreateInstance(__uuidof(MyEnumerableGenerator));
        BOOST_REQUIRE(SUCCEEDED(hr));
        IMyEnumerableGeneratorPtr pValue2;
        hr = pValue2.CreateInstance(__uuidof(MyEnumerableGenerator));
        BOOST_REQUIRE(SUCCEEDED(hr));

        VARIANT_BOOL equals = VARIANT_FALSE;
        hr = My::GenericEqualityComparer<IUnknown*>::Equals(pValue1, pValue2, &equals);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(equals == VARIANT_FALSE);

        LONG hashCode1 = 0;
        hr = My::GenericEqualityComparer<IUnknown*>::GetHashCode(pValue1, &hashCode1);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(hashCode1 == reinterpret_cast<LONG>(pValue1.GetInterfacePtr()));

        LONG hashCode2 = 0;
        hr = My::GenericEqualityComparer<IUnknown*>::GetHashCode(pValue2, &hashCode2);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(hashCode2 == reinterpret_cast<LONG>(pValue2.GetInterfacePtr()));
    }
}

BOOST_AUTO_TEST_CASE(VARIANTTest)
{
    // same
    {
        HRESULT hr = S_OK;

        //DECIMAL dec1;
        //::VarDecFromI4(10, &dec1);

        CComVariant value1 = 10;
        CComVariant value2 = 10;

        //hr = value1.ChangeType(VT_DECIMAL);
        //BOOST_REQUIRE(SUCCEEDED(hr));

        //DECIMAL& dec2 = reinterpret_cast<DECIMAL&>(value1);
        //BOOST_REQUIRE(::VarDecCmp(&dec1, &dec2) == static_cast<HRESULT>(VARCMP_EQ));

        INT n1 = 10;
        CComVariant value3;
        value3.SetByRef(&n1);

        //LONG hashCode3 = 0;
        //hr = My::GenericEqualityComparer<VARIANT>::GetHashCode(value3, &hashCode3);
        //BOOST_REQUIRE(SUCCEEDED(hr));
        //BOOST_REQUIRE(hashCode3 == reinterpret_cast<LONG>(value3.pintVal));
        //BOOST_REQUIRE(hashCode3 == reinterpret_cast<LONG>(&n1));

        VARIANT* pValue3 = &value3;
        VARTYPE* p_vt = reinterpret_cast<VARTYPE*>(pValue3);
        WORD* p_wReserved1 = reinterpret_cast<WORD*>(p_vt + 1);
        WORD* p_wReserved2 = p_wReserved1 + 1;
        WORD* p_wReserved3 = p_wReserved2 + 1;
        VOID** pp_v = reinterpret_cast<VOID**>(p_wReserved3 + 1);
        ATLTRACE("*pp_v: %d\n", *pp_v);
        ATLTRACE("value3.pintVal: %d\n", value3.pintVal);

        // ::memcpy_s égÇ¡ÇΩÇŸÇ§Ç™ÇÌÇ©ÇËÇ‚Ç∑Ç≠ÇÀÅH
        const size_t OFFSET = sizeof(VARTYPE) + sizeof(WORD) * 3;
        const size_t LENGTH = sizeof(VARIANT) - OFFSET;
        BYTE b[LENGTH];
        ::memcpy_s(b, LENGTH, (BYTE*)pValue3 + OFFSET, LENGTH); 
        ATLTRACE("b: %d\n", *(VOID**)&b);

        ATLTRACE("sizeof(LONGLONG): %d\n", sizeof(LONGLONG));
        ATLTRACE("sizeof(DOUBLE): %d\n", sizeof(DOUBLE));


        VARIANT_BOOL equals = VARIANT_FALSE;
        hr = My::GenericEqualityComparer<VARIANT>::Equals(value1, value2, &equals);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(equals == VARIANT_TRUE);

        LONG hashCode1 = 0;
        hr = My::GenericEqualityComparer<VARIANT>::GetHashCode(value1, &hashCode1);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(hashCode1 == value1.intVal);

        LONG hashCode2 = 0;
        hr = My::GenericEqualityComparer<VARIANT>::GetHashCode(value2, &hashCode2);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(hashCode2 == value2.intVal);

    }

    // different
    {
        HRESULT hr = S_OK;

        IMyEnumerableGeneratorPtr pValue1;
        hr = pValue1.CreateInstance(__uuidof(MyEnumerableGenerator));
        BOOST_REQUIRE(SUCCEEDED(hr));
        IMyEnumerableGeneratorPtr pValue2;
        hr = pValue2.CreateInstance(__uuidof(MyEnumerableGenerator));
        BOOST_REQUIRE(SUCCEEDED(hr));

        VARIANT_BOOL equals = VARIANT_FALSE;
        hr = My::GenericEqualityComparer<IUnknown*>::Equals(pValue1, pValue2, &equals);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(equals == VARIANT_FALSE);

        LONG hashCode1 = 0;
        hr = My::GenericEqualityComparer<IUnknown*>::GetHashCode(pValue1, &hashCode1);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(hashCode1 == reinterpret_cast<LONG>(pValue1.GetInterfacePtr()));

        LONG hashCode2 = 0;
        hr = My::GenericEqualityComparer<IUnknown*>::GetHashCode(pValue2, &hashCode2);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(hashCode2 == reinterpret_cast<LONG>(pValue2.GetInterfacePtr()));
    }

}

BOOST_AUTO_TEST_SUITE_END()