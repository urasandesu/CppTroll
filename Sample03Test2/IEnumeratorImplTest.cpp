
#include "stdafx.h"

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include <vector>

#ifndef URASANDESU_NANONYM_COLLECTIONS_IENUMERATORIMPL_H
#include "Urasandesu/NAnonym/Collections/IEnumeratorImpl.h"
#endif

#ifndef URASANDESU_NANONYM_UTILITIES_CCOMOBJECTSLIM_H
#include "Urasandesu/NAnonym/Utilities/CComObjectSlim.h"
#endif

namespace
{
    using std::vector;
    using boost::is_same;
    using Urasandesu::NAnonym::Collections::IEnumeratorImpl;
    using Urasandesu::NAnonym::Utilities::CComObjectSlim;
    using boost::assign::operator +=;
    using boost::is_convertible;

    
    
    typedef vector<INT> IntVector;
    typedef IEnumeratorImpl<IEnumVARIANT, VARIANT, IntVector> IntVectorEnumeratorImpl;
    class ATL_NO_VTABLE CIntVectorEnumerator;
    typedef CComObjectSlim<CIntVectorEnumerator> IntVectorEnumeratorObject;

    class ATL_NO_VTABLE CIntVectorEnumerator : 
        public CComObjectRootEx<CComSingleThreadModel>,
        public IntVectorEnumeratorImpl
    {
    public:
        CIntVectorEnumerator() { }

    BEGIN_COM_MAP(CIntVectorEnumerator)
        COM_INTERFACE_ENTRY(IEnumVARIANT)
    END_COM_MAP()

        DECLARE_PROTECT_FINAL_CONSTRUCT()

        HRESULT FinalConstruct() { return S_OK; }
        void FinalRelease() { }

        STDMETHOD(Clone)(IEnumVARIANT** ppVal)
        {
            return IntVectorEnumeratorImpl::Clone<IntVectorEnumeratorObject>(ppVal);
        }
    };


    BOOST_AUTO_TEST_SUITE(IEnumeratorImplTestSuite)

    BOOST_AUTO_TEST_CASE(TypedefTest)
    {
        BOOST_MPL_ASSERT((is_same<IntVectorEnumeratorObject::base_type, IEnumVARIANT>));
        BOOST_MPL_ASSERT((is_same<IntVectorEnumeratorObject::type, IntVectorEnumeratorImpl>));
        BOOST_MPL_ASSERT((is_same<IntVectorEnumeratorObject::interface_type, IEnumVARIANT>));
        BOOST_MPL_ASSERT((is_same<IntVectorEnumeratorObject::range_value_type, INT>));
        BOOST_MPL_ASSERT((is_same<IntVectorEnumeratorObject::range_iterator, IntVector::iterator>));
    }

    BOOST_AUTO_TEST_CASE(IEnumeratorImplTest01)
    {
        HRESULT hr = E_FAIL;
        IntVectorEnumeratorObject* pIntVectorEnumerator = NULL;
        hr = IntVectorEnumeratorObject::CreateInstance(&pIntVectorEnumerator);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pIntVectorEnumerator);
        
        IntVector iv;
        iv += 1, 2, 3, 4, 5;
        
        hr = pIntVectorEnumerator->Init(NULL, iv);
        BOOST_REQUIRE(SUCCEEDED(hr));
        
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

    BOOST_AUTO_TEST_CASE(IEnumeratorImplTest02)
    {
        HRESULT hr = E_FAIL;
        IntVectorEnumeratorObject* pIntVectorEnumerator = NULL;
        hr = IntVectorEnumeratorObject::CreateInstance(&pIntVectorEnumerator);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pIntVectorEnumerator);
        
        IntVector iv;
        iv += 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;
        
        hr = pIntVectorEnumerator->Init(NULL, iv);
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pIntVectorEnumerator->Skip(5);
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        ULONG celt = 1;
        CComVariant rgelt;
        ULONG celtFetched = 0;
        LONG n = 5;
        while ((hr = pIntVectorEnumerator->Next(celt, &rgelt, &celtFetched)) == S_OK)
        {
            BOOST_REQUIRE(rgelt.vt == VT_I4 && rgelt.lVal == ++n);
        }
        BOOST_REQUIRE(SUCCEEDED(hr));
    }

    BOOST_AUTO_TEST_CASE(IEnumeratorImplTest03)
    {
        HRESULT hr = E_FAIL;
        IntVectorEnumeratorObject* pIntVectorEnumerator = NULL;
        hr = IntVectorEnumeratorObject::CreateInstance(&pIntVectorEnumerator);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pIntVectorEnumerator);
        
        IntVector iv;
        iv += 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;
        
        hr = pIntVectorEnumerator->Init(NULL, iv);
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pIntVectorEnumerator->Skip(5);
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pIntVectorEnumerator->Reset();
        BOOST_REQUIRE(SUCCEEDED(hr));
        
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

    BOOST_AUTO_TEST_CASE(IEnumeratorImplTest04)
    {
        HRESULT hr = E_FAIL;
        IntVectorEnumeratorObject* pIntVectorEnumerator = NULL;
        hr = IntVectorEnumeratorObject::CreateInstance(&pIntVectorEnumerator);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pIntVectorEnumerator);
        
        IntVector iv;
        iv += 1, 2, 3, 4, 5;
        
        hr = pIntVectorEnumerator->Init(NULL, iv);
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        {
            ULONG celt = 1;
            CComVariant rgelt;
            ULONG celtFetched = 0;
            LONG n = 0;
            while (n < 2 && (hr = pIntVectorEnumerator->Next(celt, &rgelt, &celtFetched)) == S_OK)
            {
                BOOST_REQUIRE(rgelt.vt == VT_I4 && rgelt.lVal == ++n);
            }
        }
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        IEnumVARIANT* pIntVectorEnumerator2 = NULL;
        hr = pIntVectorEnumerator->Clone(&pIntVectorEnumerator2);   // Clone has already called AddRef() when returned from it.
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease2;
        pUnkForRelease2.Attach(pIntVectorEnumerator2);

        {
            ULONG celt = 1;
            CComVariant rgelt;
            ULONG celtFetched = 0;
            LONG n = 2;
            while ((hr = pIntVectorEnumerator2->Next(celt, &rgelt, &celtFetched)) == S_OK)
            {
                BOOST_REQUIRE(rgelt.vt == VT_I4 && rgelt.lVal == ++n);
            }
        }
        BOOST_REQUIRE(SUCCEEDED(hr));
    }

    BOOST_AUTO_TEST_CASE(IEnumeratorImplTest05)
    {
        HRESULT hr = E_FAIL;
        IEnumVARIANT* pEnum = NULL;
        
        IntVector iv;
        iv += 1, 2, 3, 4, 5;
        
        hr = IntVectorEnumeratorObject::New<IntVectorEnumeratorObject>(NULL, iv, (IUnknown**)&pEnum);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease;
        pUnkForRelease.Attach(pEnum);
        
        ULONG celt = 1;
        CComVariant rgelt;
        ULONG celtFetched = 0;
        LONG n = 0;
        while ((hr = pEnum->Next(celt, &rgelt, &celtFetched)) == S_OK)
        {
            BOOST_REQUIRE(rgelt.vt == VT_I4 && rgelt.lVal == ++n);
        }
        BOOST_REQUIRE(SUCCEEDED(hr));
    }

    BOOST_AUTO_TEST_SUITE_END()
}