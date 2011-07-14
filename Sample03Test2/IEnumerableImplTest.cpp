
#include "stdafx.h"

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include <vector>

#ifndef URASANDESU_NANONYM_COLLECTIONS_CCOMENUMERATOR_H
#include "Urasandesu/NAnonym/Collections/CComEnumerator.h"
#endif

#ifndef URASANDESU_NANONYM_COLLECTIONS_IENUMERABLEIMPL_H
#include "Urasandesu/NAnonym/Collections/IEnumerableImpl.h"
#endif

#ifndef URASANDESU_NANONYM_UTILITIES_CCOMOBJECTSLIM_H
#include "Urasandesu/NAnonym/Utilities/CComObjectSlim.h"
#endif

namespace
{
    using std::vector;
    using boost::use_default;
    using boost::is_same;
    using boost::assign::operator +=;
    using Urasandesu::NAnonym::Collections::CComEnumerator;
    using Urasandesu::NAnonym::Utilities::CComObjectSlim;
    using Urasandesu::NAnonym::Collections::IEnumerableImpl;

    typedef vector<INT> IntVector;
    typedef CComEnumerator<IEnumVARIANT, VARIANT, IntVector, use_default, use_default, CComObjectSlim> IntVectorEnumerator;
    typedef CComObjectSlim<IntVectorEnumerator> IntVectorEnumeratorObject;
    
    MIDL_INTERFACE("26251BAE-B229-48DC-9B3E-7C9F77BF7D19")
    IMyEnumerable : public IUnknown
    {
    public:
        virtual /* [restricted][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppVal) = 0;
        
    };
    
    typedef IEnumerableImpl<IMyEnumerable, IntVector, IntVectorEnumeratorObject> IntVectorEnumerableImpl;
    class ATL_NO_VTABLE CIntVectorEnumerable;
    typedef CComObjectSlim<CIntVectorEnumerable> IntVectorEnumerableObject;

    class ATL_NO_VTABLE CIntVectorEnumerable : 
        public CComObjectRootEx<CComSingleThreadModel>,
        public IntVectorEnumerableImpl
    {
    public:
        CIntVectorEnumerable() { }

    BEGIN_COM_MAP(CIntVectorEnumerable)
        COM_INTERFACE_ENTRY(IMyEnumerable)
    END_COM_MAP()

        DECLARE_PROTECT_FINAL_CONSTRUCT()

        HRESULT FinalConstruct() { return S_OK; }
        void FinalRelease() { }
    };

    BOOST_AUTO_TEST_SUITE(IEnumerableImplTestSuite)

    BOOST_AUTO_TEST_CASE(TypedefTest)
    {
        BOOST_MPL_ASSERT((is_same<IntVectorEnumerableObject::base_type, IMyEnumerable>));
        BOOST_MPL_ASSERT((is_same<IntVectorEnumerableObject::type, IntVectorEnumerableImpl>));
        BOOST_MPL_ASSERT((is_same<IntVectorEnumerableObject::interface_type, IMyEnumerable>));
    }

    BOOST_AUTO_TEST_CASE(get__NewEnumTest)
    {
        HRESULT hr = E_FAIL;
        IntVectorEnumerableObject* pIntVectorEnumerable = NULL;
        hr = IntVectorEnumerableObject::CreateInstance(&pIntVectorEnumerable);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pIntVectorEnumerable);
        
        pIntVectorEnumerable->m_container += 1, 2, 3, 4, 5;
        
        IntVectorEnumeratorObject* pIntVectorEnumerator = NULL;
        hr = pIntVectorEnumerable->get__NewEnum(reinterpret_cast<IUnknown**>(&pIntVectorEnumerator));
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease2;
        pUnkForRelease2.Attach(pIntVectorEnumerator);
        
        ULONG celt = 1;
        CComVariant rgelt;
        ULONG celtFetched = 0;
        LONG n = 0;
        while ((hr = pIntVectorEnumerator->Next(celt, &rgelt, &celtFetched)) == S_OK)
        {
            BOOST_REQUIRE(rgelt.vt == VT_I4 && rgelt.lVal == ++n);
        }
        BOOST_REQUIRE(SUCCEEDED(hr));
    }

    BOOST_AUTO_TEST_SUITE_END()
}