
#include "stdafx.h"

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include <list>

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
    using std::list;
    using boost::is_same;
    using boost::use_default;
    using Urasandesu::NAnonym::Collections::CComEnumerator;
    using Urasandesu::NAnonym::Utilities::CComObjectSlim;
    using Urasandesu::NAnonym::Collections::ICollectionImpl;
    using Urasandesu::NAnonym::Collections::IEnumerableImpl;
    using Urasandesu::NAnonym::Utilities::GenericCopy;
    
    typedef CAdapt<CComBSTR> AdaptedStr;
    typedef list<AdaptedStr> StrList;
    typedef CComEnumerator<IEnumVARIANT, VARIANT, StrList, use_default, use_default, CComObjectSlim> StrListEnumerator;
    typedef CComObjectSlim<StrListEnumerator> StrListEnumeratorObject;
    
    MIDL_INTERFACE("5EC980D6-C48E-4840-B31D-3BB5121326F8")
    IStrListCollection : public IUnknown
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
        
    };
    
    typedef ICollectionImpl<IStrListCollection, BSTR, StrList, StrListEnumeratorObject> StrListCollectionImpl;
    class ATL_NO_VTABLE CStrListCollection;
    typedef CComObjectSlim<CStrListCollection> StrListCollectionObject;

    class ATL_NO_VTABLE CStrListCollection : 
        public CComObjectRootEx<CComSingleThreadModel>,
        public StrListCollectionImpl
    {
    public:
        CStrListCollection() { }

    BEGIN_COM_MAP(CStrListCollection)
        COM_INTERFACE_ENTRY(IStrListCollection)
    END_COM_MAP()

        DECLARE_PROTECT_FINAL_CONSTRUCT()

        HRESULT FinalConstruct() { return S_OK; }
        void FinalRelease() { }
    };

    BOOST_AUTO_TEST_SUITE(ICollectionImplTestSuite)

    BOOST_AUTO_TEST_CASE(TypedefTest)
    {
        typedef IEnumerableImpl<IStrListCollection, StrList, StrListEnumeratorObject> StrListEnumerableImpl;
        BOOST_MPL_ASSERT((is_same<StrListCollectionObject::base_type, StrListEnumerableImpl>));
        BOOST_MPL_ASSERT((is_same<StrListCollectionObject::type, StrListCollectionImpl>));
        BOOST_MPL_ASSERT((is_same<StrListCollectionObject::interface_type, IStrListCollection>));
        BOOST_MPL_ASSERT((is_same<StrListCollectionObject::collection_value_type, CComBSTR>));
        typedef GenericCopy<BSTR, CComBSTR> DefaultCopyItemFromCollection;
        BOOST_MPL_ASSERT((is_same<StrListCollectionObject::default_copy_item_from_collection, DefaultCopyItemFromCollection>));
        BOOST_MPL_ASSERT((is_same<StrListCollectionObject::copy_item_from_collection, DefaultCopyItemFromCollection>));
        typedef GenericCopy<CComBSTR, BSTR> DefaultCopyCollectionFromItem;
        BOOST_MPL_ASSERT((is_same<StrListCollectionObject::default_copy_collection_from_item, DefaultCopyCollectionFromItem>));
        BOOST_MPL_ASSERT((is_same<StrListCollectionObject::copy_collection_from_item, DefaultCopyCollectionFromItem>));
    }

    BOOST_AUTO_TEST_CASE(AddTest)
    {
        HRESULT hr = E_FAIL;
        StrListCollectionObject* pStrListCollection = NULL;
        hr = StrListCollectionObject::CreateInstance(&pStrListCollection);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pStrListCollection);
        
        hr = pStrListCollection->Add(L"aiueo");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrListCollection->Add(L"kakikukeko");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrListCollection->Add(L"sasisuseso");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        StrListEnumeratorObject* pStrListEnumerator = NULL;
        hr = pStrListCollection->get__NewEnum(reinterpret_cast<IUnknown**>(&pStrListEnumerator));
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease2;
        pUnkForRelease2.Attach(pStrListEnumerator);
        
        ULONG celt = 1;
        CComVariant rgelt;
        ULONG celtFetched = 0;
        LONG n = 0;
        while ((hr = pStrListEnumerator->Next(celt, &rgelt, &celtFetched)) == S_OK)
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
        StrListCollectionObject* pStrListCollection = NULL;
        hr = StrListCollectionObject::CreateInstance(&pStrListCollection);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pStrListCollection);
        
        hr = pStrListCollection->Add(L"aiueo");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrListCollection->Add(L"kakikukeko");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrListCollection->Add(L"sasisuseso");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrListCollection->Clear();
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        StrListEnumeratorObject* pStrListEnumerator = NULL;
        hr = pStrListCollection->get__NewEnum(reinterpret_cast<IUnknown**>(&pStrListEnumerator));
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease2;
        pUnkForRelease2.Attach(pStrListEnumerator);
        
        ULONG celt = 1;
        CComVariant rgelt;
        ULONG celtFetched = 0;
        LONG n = 0;
        while ((hr = pStrListEnumerator->Next(celt, &rgelt, &celtFetched)) == S_OK)
        {
            BOOST_REQUIRE(false);
        }
        BOOST_REQUIRE(SUCCEEDED(hr));
    }

    BOOST_AUTO_TEST_CASE(ContainsTest)
    {
        HRESULT hr = E_FAIL;
        StrListCollectionObject* pStrListCollection = NULL;
        hr = StrListCollectionObject::CreateInstance(&pStrListCollection);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pStrListCollection);
        
        hr = pStrListCollection->Add(L"aiueo");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrListCollection->Add(L"kakikukeko");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrListCollection->Add(L"sasisuseso");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        VARIANT_BOOL exists = VARIANT_FALSE;
        hr = pStrListCollection->Contains(L"kakikukeko", &exists);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(exists == VARIANT_TRUE);
        
        hr = pStrListCollection->Contains(L"tatituteto", &exists);
        BOOST_REQUIRE(SUCCEEDED(hr));
        BOOST_REQUIRE(exists == VARIANT_FALSE);
    }

    BOOST_AUTO_TEST_CASE(CopyToTest)
    {
        HRESULT hr = E_FAIL;
        StrListCollectionObject* pStrListCollection = NULL;
        hr = StrListCollectionObject::CreateInstance(&pStrListCollection);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pStrListCollection);
        
        hr = pStrListCollection->Add(L"aiueo");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrListCollection->Add(L"kakikukeko");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrListCollection->Add(L"sasisuseso");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        CComSafeArray<BSTR> arr(4);
        hr = pStrListCollection->CopyTo(arr.m_psa, 1);
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        BOOST_REQUIRE(CComBSTR(arr[0]) == NULL);
        BOOST_REQUIRE(CComBSTR(arr[1]) == L"aiueo");
        BOOST_REQUIRE(CComBSTR(arr[2]) == L"kakikukeko");
        BOOST_REQUIRE(CComBSTR(arr[3]) == L"sasisuseso");
    }

    BOOST_AUTO_TEST_CASE(RemoveTest)
    {
        HRESULT hr = E_FAIL;
        StrListCollectionObject* pStrListCollection = NULL;
        hr = StrListCollectionObject::CreateInstance(&pStrListCollection);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pStrListCollection);
        
        hr = pStrListCollection->Add(L"aiueo");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrListCollection->Add(L"kakikukeko");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrListCollection->Add(L"sasisuseso");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrListCollection->Remove(L"kakikukeko");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        StrListEnumeratorObject* pStrListEnumerator = NULL;
        hr = pStrListCollection->get__NewEnum(reinterpret_cast<IUnknown**>(&pStrListEnumerator));
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease2;
        pUnkForRelease2.Attach(pStrListEnumerator);
        
        ULONG celt = 1;
        CComVariant rgelt;
        ULONG celtFetched = 0;
        LONG n = 0;
        while ((hr = pStrListEnumerator->Next(celt, &rgelt, &celtFetched)) == S_OK)
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
        StrListCollectionObject* pStrListCollection = NULL;
        hr = StrListCollectionObject::CreateInstance(&pStrListCollection);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pStrListCollection);
        
        hr = pStrListCollection->Add(L"aiueo");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrListCollection->Add(L"kakikukeko");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrListCollection->Add(L"sasisuseso");
        BOOST_REQUIRE(SUCCEEDED(hr));

        LONG count = 0;
        hr = pStrListCollection->get_Count(&count);        
        BOOST_REQUIRE(SUCCEEDED(hr));

        BOOST_REQUIRE(count == 3);
    }

    BOOST_AUTO_TEST_CASE(IsReadOnlyTest)
    {
        HRESULT hr = E_FAIL;
        StrListCollectionObject* pStrListCollection = NULL;
        hr = StrListCollectionObject::CreateInstance(&pStrListCollection);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pStrListCollection);

        VARIANT_BOOL isReadOnly = VARIANT_FALSE;
        hr = pStrListCollection->get_IsReadOnly(&isReadOnly);
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        BOOST_REQUIRE(isReadOnly == VARIANT_FALSE);
    }

    BOOST_AUTO_TEST_SUITE_END()
}