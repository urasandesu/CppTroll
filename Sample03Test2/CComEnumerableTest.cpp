
#include "stdafx.h"

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include <vector>

#ifndef INCLUDED_CCOMENUMERATOR_H
#include "CComEnumerator.h"
#endif

#ifndef INCLUDED_CCOMENUMERABLE_H
#include "CComEnumerable.h"
#endif

namespace
{
    using std::vector;
    using My::CComEnumerator;
    using My::CComEnumerable;
    
    // NOTE: Give a interface declaration IN COM SERVER to CComEnumerable.
    //       In the following case, IMyEnumerable declared in the client happens to be same interface declared in the server.
    typedef vector<CAdapt<CComBSTR>> CStrVector;
    typedef CComEnumerator<IEnumVARIANT, VARIANT, CStrVector> CStrEnumerator;
    typedef CComEnumerable<IMyEnumerable, CStrEnumerator, CStrVector> CMyEnumerable;
    typedef CComObjectCached<CMyEnumerable> CMyEnumerableObject;

    BOOST_AUTO_TEST_SUITE(CComEnumerableTestSuite)

    BOOST_AUTO_TEST_CASE(CComEnumerableTest)
    {
        HRESULT hr = E_FAIL;
        CMyEnumerableObject* pMyEnumerable = NULL;
        hr = CMyEnumerableObject::CreateInstance(&pMyEnumerable);
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        CComPtr<IUnknown> pUnkForRelease(pMyEnumerable);
    }

    BOOST_AUTO_TEST_SUITE_END()
}
