
#include "stdafx.h"

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include <vector>

#ifndef INCLUDED_CCOMENUMERATOR_H
#include "CComEnumerator.h"
#endif

#ifndef INCLUDED_CCOMOBJECTSLIM_H
#include "CComObjectSlim.h"
#endif

namespace
{
    using std::vector;
    using boost::is_same;
    using boost::use_default;
    using My::IEnumeratorImpl;
    using My::CComEnumerator;
    using My::CComObjectSlim;
    
    // NOTE: Give a interface declaration IN COM SERVER to CComEnumerator.
    //       In the following case, IEnumVARIANT declared in the client happens to be same interface declared in the server.
    typedef vector<INT> IntVector;
    typedef IEnumeratorImpl<IEnumVARIANT, VARIANT, IntVector> IntVectorEnumeratorImpl;
    typedef CComEnumerator<IEnumVARIANT, VARIANT, IntVector, use_default, use_default, use_default, CComObjectSlim> IntVectorEnumerator;   // 仮想コピーコンストラクタ用の CComObject.* は、テンプレートの最後のほうがいいよね。
    typedef CComObjectSlim<IntVectorEnumerator> IntVectorEnumeratorObject;

    BOOST_AUTO_TEST_SUITE(CComEnumeratorTestSuite)

    BOOST_AUTO_TEST_CASE(TypedefTest)
    {
        BOOST_MPL_ASSERT((is_same<IntVectorEnumeratorObject::base_type, IntVectorEnumeratorImpl>));
        BOOST_MPL_ASSERT((is_same<IntVectorEnumeratorObject::type, IntVectorEnumerator>));
        BOOST_MPL_ASSERT((is_same<IntVectorEnumeratorObject::interface_type, IEnumVARIANT>));
    }

    BOOST_AUTO_TEST_CASE(CComEnumeratorTest)
    {
        HRESULT hr = E_FAIL;
        IntVectorEnumeratorObject* pIntEnumerator = NULL;
        hr = IntVectorEnumeratorObject::CreateInstance(&pIntEnumerator);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pIntEnumerator);
    }

    BOOST_AUTO_TEST_SUITE_END()
}
