
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
    using Urasandesu::NAnonym::Collections::CComEnumerator;
    using Urasandesu::NAnonym::Utilities::CComObjectSlim;
    using Urasandesu::NAnonym::Collections::IEnumerableImpl;

    typedef vector<INT> IntVector;
    typedef CComEnumerator<IEnumVARIANT, VARIANT, IntVector, use_default, use_default, use_default, CComObjectSlim> IntVectorEnumerator;
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

        //STDMETHOD(get__NewEnum)(IUnknown** ppVal)
        //{
        //    return IntVectorEnumerableImpl::get__NewEnum<IntVectorEnumeratorObject>(ppVal);
        //}
    };

    BOOST_AUTO_TEST_SUITE(IEnumerableImplTestSuite)

    BOOST_AUTO_TEST_CASE(IEnumerableImplTest)
    {
        HRESULT hr = E_FAIL;
        IntVectorEnumerableObject* pIntVectorEnumerable = NULL;
        hr = IntVectorEnumerableObject::CreateInstance(&pIntVectorEnumerable);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pIntVectorEnumerable);
    }

    BOOST_AUTO_TEST_SUITE_END()
}