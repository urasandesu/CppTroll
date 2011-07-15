﻿
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

#ifndef URASANDESU_NANONYM_COLLECTIONS_CCOMLIST_H
#include "Urasandesu/NAnonym/Collections/CComList.h"
#endif

namespace
{
    using std::vector;
    using boost::use_default;
    using Urasandesu::NAnonym::Collections::CComEnumerator;
    using Urasandesu::NAnonym::Utilities::CComObjectSlim;
    using Urasandesu::NAnonym::Collections::CComList;

    typedef CAdapt<CComBSTR> AdaptedStr;
    typedef vector<AdaptedStr> StrVector;
    typedef CComEnumerator<IEnumVARIANT, VARIANT, StrVector, use_default, use_default, CComObjectSlim> StrVectorEnumerator;
    typedef CComObjectSlim<StrVectorEnumerator> StrVectorEnumeratorObject;

    MIDL_INTERFACE("AA62153A-ADB7-41B3-9176-2CC5D6FC5DA1")
    IStrVectorList : public IDispatch
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

    typedef CComList<IStrVectorList, BSTR, StrVector, StrVectorEnumeratorObject> StrVectorList;
    typedef CComObjectSlim<StrVectorList> StrVectorListObject;

    BOOST_AUTO_TEST_SUITE(CComListTestSuite)

    BOOST_AUTO_TEST_CASE(CComListTest)
    {
        HRESULT hr = E_FAIL;
        StrVectorListObject* pStrVectorList = NULL;
        hr = StrVectorListObject::CreateInstance(&pStrVectorList);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pStrVectorList);
    }

    BOOST_AUTO_TEST_SUITE_END()
}
