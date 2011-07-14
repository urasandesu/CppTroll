
#include "stdafx.h"

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include <vector>

#ifndef URASANDESU_NANONYM_COLLECTIONS_CCOMENUMERATOR_H
#include "Urasandesu/NAnonym/Collections/CComEnumerator.h"
#endif

#ifndef URASANDESU_NANONYM_UTILITIES_CCOMOBJECTSLIM_H
#include "Urasandesu/NAnonym/Utilities/CComObjectSlim.h"
#endif

#ifndef URASANDESU_NANONYM_COLLECTIONS_ICOLLECTIONIMPL_H
#include "Urasandesu/NAnonym/Collections/ICollectionImpl.h"
#endif

namespace
{
    using std::vector;
    using boost::is_same;
    using boost::use_default;
    using Urasandesu::NAnonym::Collections::CComEnumerator;
    using Urasandesu::NAnonym::Utilities::CComObjectSlim;
    using Urasandesu::NAnonym::Collections::ICollectionImpl;
    using Urasandesu::NAnonym::Collections::IEnumerableImpl;
    
    typedef CAdapt<CComBSTR> AdaptedStr;
    typedef vector<AdaptedStr> StrVector;
    typedef CComEnumerator<IEnumVARIANT, VARIANT, StrVector, use_default, use_default, CComObjectSlim> StrVectorEnumerator;
    typedef CComObjectSlim<StrVectorEnumerator> StrVectorEnumeratorObject;
    
    MIDL_INTERFACE("5EC980D6-C48E-4840-B31D-3BB5121326F8")
    IStrVectorCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR item) = 0;
        
        virtual /* [restricted][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Contains( 
            /* [in] */ BSTR item,
            /* [retval][out] */ VARIANT_BOOL *exists) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CopyTo( 
            /* [out][in] */ SAFEARRAY * pArray,
            /* [in] */ LONG index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ BSTR item) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsReadOnly( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ LONG index,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Item( 
            /* [in] */ LONG index,
            /* [in] */ BSTR newVal) = 0;
        
    };
    
    typedef ICollectionImpl<IStrVectorCollection, BSTR, StrVector, StrVectorEnumeratorObject> StrVectorCollectionImpl;
    class ATL_NO_VTABLE CStrVectorCollection;
    typedef CComObjectSlim<CStrVectorCollection> StrVectorCollectionObject;

    class ATL_NO_VTABLE CStrVectorCollection : 
        public CComObjectRootEx<CComSingleThreadModel>,
        public StrVectorCollectionImpl
    {
    public:
        CStrVectorCollection() { }

    BEGIN_COM_MAP(CStrVectorCollection)
        COM_INTERFACE_ENTRY(IStrVectorCollection)
    END_COM_MAP()

        DECLARE_PROTECT_FINAL_CONSTRUCT()

        HRESULT FinalConstruct() { return S_OK; }
        void FinalRelease() { }
    };

    BOOST_AUTO_TEST_SUITE(ICollectionImplTestSuite)

    BOOST_AUTO_TEST_CASE(TypedefTest)
    {
        typedef IEnumerableImpl<IStrVectorCollection, StrVector, StrVectorEnumeratorObject> StrVectorEnumerableImpl;
        BOOST_MPL_ASSERT((is_same<StrVectorCollectionObject::base_type, StrVectorEnumerableImpl>));
        BOOST_MPL_ASSERT((is_same<StrVectorCollectionObject::type, StrVectorCollectionImpl>));
        BOOST_MPL_ASSERT((is_same<StrVectorCollectionObject::interface_type, IStrVectorCollection>));
    }

    BOOST_AUTO_TEST_CASE(AddTest)
    {
        HRESULT hr = E_FAIL;
        StrVectorCollectionObject* pStrVectorCollection = NULL;
        hr = StrVectorCollectionObject::CreateInstance(&pStrVectorCollection);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pStrVectorCollection);
        
        hr = pStrVectorCollection->Add(L"aiueo");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorCollection->Add(L"kakikukeko");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorCollection->Add(L"sasisuseso");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        StrVectorEnumeratorObject* pStrVectorEnumerator = NULL;
        hr = pStrVectorCollection->get__NewEnum(reinterpret_cast<IUnknown**>(&pStrVectorEnumerator));
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease2;
        pUnkForRelease2.Attach(pStrVectorEnumerator);
        
        ULONG celt = 1;
        CComVariant rgelt;
        ULONG celtFetched = 0;
        LONG n = 0;
        while ((hr = pStrVectorEnumerator->Next(celt, &rgelt, &celtFetched)) == S_OK)
        {
            switch (n++)
            {
            case 0:
                BOOST_REQUIRE(rgelt.vt == VT_BSTR && CComBSTR(rgelt.bstrVal) == L"aiueo");
                break;
            case 1:
                BOOST_REQUIRE(rgelt.vt == VT_BSTR && CComBSTR(rgelt.bstrVal) == L"kakikukeko");
                break;
            case 2:
                BOOST_REQUIRE(rgelt.vt == VT_BSTR && CComBSTR(rgelt.bstrVal) == L"sasisuseso");
                break;
            default:
                BOOST_REQUIRE(false);
                break;
            }
        }
        BOOST_REQUIRE(SUCCEEDED(hr));
    }

    BOOST_AUTO_TEST_CASE(ClearTest)
    {
        HRESULT hr = E_FAIL;
        StrVectorCollectionObject* pStrVectorCollection = NULL;
        hr = StrVectorCollectionObject::CreateInstance(&pStrVectorCollection);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pStrVectorCollection);
        
        hr = pStrVectorCollection->Add(L"aiueo");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorCollection->Add(L"kakikukeko");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorCollection->Add(L"sasisuseso");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorCollection->Clear();
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        StrVectorEnumeratorObject* pStrVectorEnumerator = NULL;
        hr = pStrVectorCollection->get__NewEnum(reinterpret_cast<IUnknown**>(&pStrVectorEnumerator));
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease2;
        pUnkForRelease2.Attach(pStrVectorEnumerator);
        
        ULONG celt = 1;
        CComVariant rgelt;
        ULONG celtFetched = 0;
        LONG n = 0;
        while ((hr = pStrVectorEnumerator->Next(celt, &rgelt, &celtFetched)) == S_OK)
        {
            BOOST_REQUIRE(false);
        }
        BOOST_REQUIRE(SUCCEEDED(hr));
    }

    BOOST_AUTO_TEST_CASE(ContainsTest)
    {
        HRESULT hr = E_FAIL;
        StrVectorCollectionObject* pStrVectorCollection = NULL;
        hr = StrVectorCollectionObject::CreateInstance(&pStrVectorCollection);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pStrVectorCollection);
        
        hr = pStrVectorCollection->Add(L"aiueo");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorCollection->Add(L"kakikukeko");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorCollection->Add(L"sasisuseso");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        VARIANT_BOOL exists = VARIANT_FALSE;
        hr = pStrVectorCollection->Contains(L"kakikukeko", &exists);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(exists == VARIANT_TRUE);
        
        hr = pStrVectorCollection->Contains(L"tatituteto", &exists);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(exists == VARIANT_FALSE);
    }

    BOOST_AUTO_TEST_CASE(CopyToTest)
    {
        HRESULT hr = E_FAIL;
        StrVectorCollectionObject* pStrVectorCollection = NULL;
        hr = StrVectorCollectionObject::CreateInstance(&pStrVectorCollection);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pStrVectorCollection);
        
        hr = pStrVectorCollection->Add(L"aiueo");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorCollection->Add(L"kakikukeko");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorCollection->Add(L"sasisuseso");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        CComSafeArray<BSTR> arr(4);
        hr = pStrVectorCollection->CopyTo(arr.m_psa, 1);
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        BOOST_REQUIRE(CComBSTR(arr[0]) == NULL);
        BOOST_REQUIRE(CComBSTR(arr[1]) == L"aiueo");
        BOOST_REQUIRE(CComBSTR(arr[2]) == L"kakikukeko");
        BOOST_REQUIRE(CComBSTR(arr[3]) == L"sasisuseso");
    }

    BOOST_AUTO_TEST_CASE(RemoveTest)
    {
        HRESULT hr = E_FAIL;
        StrVectorCollectionObject* pStrVectorCollection = NULL;
        hr = StrVectorCollectionObject::CreateInstance(&pStrVectorCollection);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pStrVectorCollection);
        
        hr = pStrVectorCollection->Add(L"aiueo");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorCollection->Add(L"kakikukeko");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorCollection->Add(L"sasisuseso");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorCollection->Remove(L"kakikukeko");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        StrVectorEnumeratorObject* pStrVectorEnumerator = NULL;
        hr = pStrVectorCollection->get__NewEnum(reinterpret_cast<IUnknown**>(&pStrVectorEnumerator));
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease2;
        pUnkForRelease2.Attach(pStrVectorEnumerator);
        
        ULONG celt = 1;
        CComVariant rgelt;
        ULONG celtFetched = 0;
        LONG n = 0;
        while ((hr = pStrVectorEnumerator->Next(celt, &rgelt, &celtFetched)) == S_OK)
        {
            switch (n++)
            {
            case 0:
                BOOST_REQUIRE(rgelt.vt == VT_BSTR && CComBSTR(rgelt.bstrVal) == L"aiueo");
                break;
            case 1:
                BOOST_REQUIRE(rgelt.vt == VT_BSTR && CComBSTR(rgelt.bstrVal) == L"sasisuseso");
                break;
            default:
                BOOST_REQUIRE(false);
                break;
            }
        }
        BOOST_REQUIRE(SUCCEEDED(hr));
    }

    BOOST_AUTO_TEST_CASE(CountTest)
    {
        HRESULT hr = E_FAIL;
        StrVectorCollectionObject* pStrVectorCollection = NULL;
        hr = StrVectorCollectionObject::CreateInstance(&pStrVectorCollection);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pStrVectorCollection);
        
        hr = pStrVectorCollection->Add(L"aiueo");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorCollection->Add(L"kakikukeko");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorCollection->Add(L"sasisuseso");
        BOOST_REQUIRE(SUCCEEDED(hr));

        LONG count = 0;
        hr = pStrVectorCollection->get_Count(&count);        
        BOOST_REQUIRE(SUCCEEDED(hr));

        BOOST_REQUIRE(count == 3);
    }

    BOOST_AUTO_TEST_CASE(IsReadOnlyTest)
    {
        HRESULT hr = E_FAIL;
        StrVectorCollectionObject* pStrVectorCollection = NULL;
        hr = StrVectorCollectionObject::CreateInstance(&pStrVectorCollection);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pStrVectorCollection);

        VARIANT_BOOL isReadOnly = VARIANT_FALSE;
        hr = pStrVectorCollection->get_IsReadOnly(&isReadOnly);
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        BOOST_REQUIRE(isReadOnly == VARIANT_FALSE);
    }

    BOOST_AUTO_TEST_SUITE_END()
}