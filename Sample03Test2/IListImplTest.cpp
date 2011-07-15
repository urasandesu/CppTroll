
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

#ifndef URASANDESU_NANONYM_COLLECTIONS_ILISTIMPL_H
#include "Urasandesu/NAnonym/Collections/IListImpl.h"
#endif

namespace
{
    using std::vector;
    using boost::use_default;
    using Urasandesu::NAnonym::Collections::CComEnumerator;
    using Urasandesu::NAnonym::Utilities::CComObjectSlim;
    using Urasandesu::NAnonym::Collections::IListImpl;

    typedef CAdapt<CComBSTR> AdaptedStr;
    typedef vector<AdaptedStr> StrVector;
    typedef CComEnumerator<IEnumVARIANT, VARIANT, StrVector, use_default, use_default, CComObjectSlim> StrVectorEnumerator;
    typedef CComObjectSlim<StrVectorEnumerator> StrVectorEnumeratorObject;

    MIDL_INTERFACE("AA62153A-ADB7-41B3-9176-2CC5D6FC5DA1")
    IStrVectorList : public IUnknown
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
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IndexOf( 
            /* [in] */ BSTR item,
            /* [retval][out] */ LONG *index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ LONG index,
            /* [in] */ BSTR item) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAt( 
            /* [in] */ LONG index) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ LONG index,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Item( 
            /* [in] */ LONG index,
            /* [in] */ BSTR newVal) = 0;
        
    };
    
    typedef IListImpl<IStrVectorList, BSTR, StrVector, StrVectorEnumeratorObject> StrVectorListImpl;
    class ATL_NO_VTABLE CStrVectorList;
    typedef CComObjectSlim<CStrVectorList> StrVectorListObject;

    class ATL_NO_VTABLE CStrVectorList : 
        public CComObjectRootEx<CComSingleThreadModel>,
        public StrVectorListImpl
    {
    public:
        CStrVectorList() { }

    BEGIN_COM_MAP(CStrVectorList)
        COM_INTERFACE_ENTRY(IStrVectorList)
    END_COM_MAP()

        DECLARE_PROTECT_FINAL_CONSTRUCT()

        HRESULT FinalConstruct() { return S_OK; }
        void FinalRelease() { }
    };

    BOOST_AUTO_TEST_SUITE(IListImplTestSuite)

    BOOST_AUTO_TEST_CASE(IndexOfTest)
    {
        HRESULT hr = E_FAIL;
        StrVectorListObject* pStrVectorList = NULL;
        hr = StrVectorListObject::CreateInstance(&pStrVectorList);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pStrVectorList);
        
        hr = pStrVectorList->Add(L"aiueo");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorList->Add(L"kakikukeko");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorList->Add(L"sasisuseso");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        LONG index = 0;
        hr = pStrVectorList->IndexOf(L"sasisuseso", &index);
        BOOST_REQUIRE(hr == S_OK);
        BOOST_REQUIRE(index == 2);

        hr = pStrVectorList->IndexOf(L"tatituteto", &index);
        BOOST_REQUIRE(hr == S_FALSE);
        BOOST_REQUIRE(index == -1);
    }

    BOOST_AUTO_TEST_CASE(InsertTest)
    {
        HRESULT hr = E_FAIL;
        StrVectorListObject* pStrVectorList = NULL;
        hr = StrVectorListObject::CreateInstance(&pStrVectorList);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pStrVectorList);
        
        hr = pStrVectorList->Add(L"aiueo");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorList->Add(L"kakikukeko");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorList->Add(L"sasisuseso");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorList->Insert(2, L"tatituteto");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        LONG index = 0;
        hr = pStrVectorList->IndexOf(L"sasisuseso", &index);
        BOOST_REQUIRE(hr == S_OK);
        BOOST_REQUIRE(index == 3);

        hr = pStrVectorList->IndexOf(L"tatituteto", &index);
        BOOST_REQUIRE(hr == S_OK);
        BOOST_REQUIRE(index == 2);
    }

    BOOST_AUTO_TEST_CASE(RemoveAtTest)
    {
        HRESULT hr = E_FAIL;
        StrVectorListObject* pStrVectorList = NULL;
        hr = StrVectorListObject::CreateInstance(&pStrVectorList);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pStrVectorList);
        
        hr = pStrVectorList->Add(L"aiueo");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorList->Add(L"kakikukeko");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorList->Add(L"sasisuseso");
        BOOST_REQUIRE(SUCCEEDED(hr));

        hr = pStrVectorList->RemoveAt(1);
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        LONG index = 0;
        hr = pStrVectorList->IndexOf(L"sasisuseso", &index);
        BOOST_REQUIRE(hr == S_OK);
        BOOST_REQUIRE(index == 1);

        hr = pStrVectorList->IndexOf(L"kakikukeko", &index);
        BOOST_REQUIRE(hr == S_FALSE);
        BOOST_REQUIRE(index == -1);
    }

    BOOST_AUTO_TEST_CASE(ItemTest)
    {
        HRESULT hr = E_FAIL;
        StrVectorListObject* pStrVectorList = NULL;
        hr = StrVectorListObject::CreateInstance(&pStrVectorList);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pStrVectorList);
        
        hr = pStrVectorList->Add(L"aiueo");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorList->Add(L"kakikukeko");
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        hr = pStrVectorList->Add(L"sasisuseso");
        BOOST_REQUIRE(SUCCEEDED(hr));

        // getter
        {        
            CComBSTR s;
            hr = pStrVectorList->get_Item(1, &s);
            BOOST_REQUIRE(s == L"kakikukeko");
        }

        // setter
        {        
            hr = pStrVectorList->put_Item(1, L"tatituteto");
            BOOST_REQUIRE(SUCCEEDED(hr));
            
            CComBSTR s;
            hr = pStrVectorList->get_Item(1, &s);
            BOOST_REQUIRE(s == L"tatituteto");
        }
    }

    BOOST_AUTO_TEST_SUITE_END()
}