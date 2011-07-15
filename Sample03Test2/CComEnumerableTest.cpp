
#include "stdafx.h"

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#ifndef URASANDESU_NANONYM_COLLECTIONS_CCOMENUMERATOR_H
#include "Urasandesu/NAnonym/Collections/CComEnumerator.h"
#endif

#ifndef URASANDESU_NANONYM_COLLECTIONS_CCOMENUMERABLE_H
#include "Urasandesu/NAnonym/Collections/CComEnumerable.h"
#endif

#ifndef URASANDESU_NANONYM_UTILITIES_CCOMOBJECTSLIM_H
#include "Urasandesu/NAnonym/Utilities/CComObjectSlim.h"
#endif

namespace
{
    using std::vector;
    using boost::use_default;
    using Urasandesu::NAnonym::Collections::CComEnumerator;
    using Urasandesu::NAnonym::Utilities::CComObjectSlim;
    using Urasandesu::NAnonym::Collections::CComEnumerable;
    
    // NOTE: Give a interface declaration IN COM SERVER to CComEnumerable.
    //       In the following case, IMyEnumerable declared in the client happens to be same interface declared in the server.
    typedef vector<CAdapt<CComBSTR>> StrVector;
    typedef CComEnumerator<IEnumVARIANT, VARIANT, StrVector, use_default, use_default, CComObjectSlim> StrVectorEnumerator;
    typedef CComObjectSlim<StrVectorEnumerator> StrVectorEnumeratorObject;
    typedef CComEnumerable<IMyEnumerable, StrVectorEnumeratorObject, StrVector> MyEnumerable;
    typedef CComObjectSlim<MyEnumerable> MyEnumerableObject;

    BOOST_AUTO_TEST_SUITE(CComEnumerableTestSuite)

    BOOST_AUTO_TEST_CASE(CComEnumerableTest)
    {
        HRESULT hr = E_FAIL;
        MyEnumerableObject* pMyEnumerable = NULL;
        hr = MyEnumerableObject::CreateInstance(&pMyEnumerable);
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        CComPtr<IUnknown> pUnkForRelease(pMyEnumerable);
    }

    BOOST_AUTO_TEST_SUITE_END()
}
