
#include "stdafx.h"

#ifndef URASANDESU_NANONYM_CONCEPTS_ATLEQUALITYCOMPARER_H
#include "Urasandesu/NAnonym/Concepts/ATLEqualityComparer.h"
#endif

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

namespace
{
    using Urasandesu::NAnonym::Concepts::ATLEqualityComparer;
    using boost::is_same;
    using boost::mpl::not_;

    struct IntEqualityComparer
    {
        static HRESULT Equals(INT value1, INT value2, VARIANT_BOOL* equals) { *equals = VARIANT_TRUE; return S_OK; }
        static HRESULT GetHashCode(INT value, LONG* hashCode) { *hashCode = 0; return S_OK; }
    };

    struct BSTREqualityComparer
    {
        static HRESULT Equals(const BSTR value1, const BSTR value2, VARIANT_BOOL* equals) { *equals = VARIANT_TRUE; return S_OK; }
        static HRESULT GetHashCode(const BSTR value, LONG* hashCode) { *hashCode = 0; return S_OK; }
    };

    typedef CComPtr<IUnknown> UnkPtr;

    // MEMO: If you specialize the class with ATLEqualityComparer concept to manage the classes that overloads operator&, 
    //       let me suggest that you prepare the overload of the methods to manage them.
    struct UnkPtrEqualityComparer
    {
        static HRESULT Equals(const UnkPtr& value1, const UnkPtr& value2, VARIANT_BOOL* equals) { *equals = VARIANT_TRUE; return S_OK; }
        static HRESULT Equals(const IUnknown* value1, const IUnknown* value2, VARIANT_BOOL* equals) { *equals = VARIANT_TRUE; return S_OK; }
        static HRESULT GetHashCode(const UnkPtr& value, LONG* hashCode) { *hashCode = 0; return S_OK; }
        static HRESULT GetHashCode(const IUnknown* value, LONG* hashCode) { *hashCode = 0; return S_OK; }
    };

    BOOST_AUTO_TEST_SUITE(ATLEqualityComparerTestSuite)

    BOOST_AUTO_TEST_CASE(UsageTest)
    {
        BOOST_CONCEPT_ASSERT((ATLEqualityComparer<IntEqualityComparer, INT>));
        BOOST_CONCEPT_ASSERT((ATLEqualityComparer<BSTREqualityComparer, BSTR>));
        BOOST_CONCEPT_ASSERT((ATLEqualityComparer<UnkPtrEqualityComparer, IUnknown*>));
        BOOST_CONCEPT_ASSERT((ATLEqualityComparer<UnkPtrEqualityComparer, UnkPtr>));
    }

    BOOST_AUTO_TEST_SUITE_END()
}
