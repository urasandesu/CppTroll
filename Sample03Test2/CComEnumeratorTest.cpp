
#include "stdafx.h"

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include <vector>

#ifndef INCLUDED_CCOMENUMERATOR_H
#include "CComEnumerator.h"
#endif

namespace
{
    using std::vector;
    using My::CComEnumerator;
    
    // NOTE: Give a interface declaration IN COM SERVER to CComEnumerator.
    //       In the following case, IEnumVARIANT declared in the client happens to be same interface declared in the server.
    typedef vector<INT> CIntVector;
    typedef CComEnumerator<IEnumVARIANT, VARIANT, CIntVector> CIntEnumerator;
    typedef CComObjectCached<CIntEnumerator> CIntEnumeratorObject;

    BOOST_AUTO_TEST_SUITE(CComEnumeratorTestSuite)

    BOOST_AUTO_TEST_CASE(CComEnumeratorTest)
    {
        HRESULT hr = E_FAIL;
        CIntEnumeratorObject* pIntEnumerator = NULL;
        hr = CIntEnumeratorObject::CreateInstance(&pIntEnumerator);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pIntEnumerator);
    }

    BOOST_AUTO_TEST_SUITE_END()
}
