
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

#ifndef INCLUDED_CCOMOBJECTSLIM_H
#include "CComObjectSlim.h"
#endif

namespace
{
    using std::vector;
    using boost::use_default;
    using My::CComEnumerator;
    using My::CComObjectSlim;
    using My::CComEnumerable;
    
    // NOTE: Give a interface declaration IN COM SERVER to CComEnumerable.
    //       In the following case, IMyEnumerable declared in the client happens to be same interface declared in the server.
    typedef vector<CAdapt<CComBSTR>> StrVector;
    typedef CComEnumerator<IEnumVARIANT, VARIANT, StrVector, use_default, use_default, use_default, CComObjectSlim> StrVectorEnumerator;
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
