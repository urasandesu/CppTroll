
#include "stdafx.h"

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

//#ifndef URASANDESU_NANONYM_COLLECTIONS_CCOMENUMERATOR_H
//#include "Urasandesu/NAnonym/Collections/CComEnumerator.h"
//#endif
//
//#ifndef URASANDESU_NANONYM_COLLECTIONS_CCOMCOLLECTION_H
//#include "CComCollection.h"
//#endif
//
//#include <vector>

namespace
{
    //using std::vector;
    //using My::CComEnumerator;
    //using My::CComCollection;

    // NOTE: Give a interface declaration IN COM SERVER to CComCollection. 
    MIDL_INTERFACE("5EC980D6-C48E-4840-B31D-3BB5121326F7")
    IStrVectorCollection : public IDispatch
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

    //typedef vector<CAdapt<CComBSTR>> StrVector;
    //typedef CComEnumerator<IEnumVARIANT, VARIANT, StrVector> StrEnumerator;
    //typedef CComCollection<IStrVectorCollection, BSTR, StrEnumerator, StrVector> CStrVectorCollection;
    //typedef CComObjectCached<CStrVectorCollection> CStrVectorCollectionObject;  // NOTE: CComObjectCached does not need the pointer to AtlModule, but CComObject needs it.

    BOOST_AUTO_TEST_SUITE(CComCollectionTestSuite)

    BOOST_AUTO_TEST_CASE(CComCollectionTest)
    {
        //HRESULT hr = E_FAIL;
        //CStrVectorCollectionObject* pStrVectorCollection = NULL;
        //hr = CStrVectorCollectionObject::CreateInstance(&pStrVectorCollection);
        //BOOST_REQUIRE(SUCCEEDED(hr));
        //
        //CComPtr<IUnknown> pUnkForRelease(pStrVectorCollection);
    }

    BOOST_AUTO_TEST_SUITE_END()
}
