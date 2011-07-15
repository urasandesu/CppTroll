
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

#ifndef URASANDESU_NANONYM_COLLECTIONS_CCOMCOLLECTION_H
#include "Urasandesu/NAnonym/Collections/CComCollection.h"
#endif

namespace
{
    using std::list;
    using boost::use_default;
    using Urasandesu::NAnonym::Collections::CComEnumerator;
    using Urasandesu::NAnonym::Collections::CComCollection;
    using Urasandesu::NAnonym::Utilities::CComObjectSlim;

    typedef CAdapt<CComBSTR> AdaptedStr;
    typedef list<AdaptedStr> StrList;
    typedef CComEnumerator<IEnumVARIANT, VARIANT, StrList, use_default, use_default, CComObjectSlim> StrListEnumerator;
    typedef CComObjectSlim<StrListEnumerator> StrListEnumeratorObject;

    // NOTE: Give a interface declaration IN COM SERVER to CComCollection. 
    MIDL_INTERFACE("5EC980D6-C48E-4840-B31D-3BB5121326F9")
    IStrListCollection : public IDispatch
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

    typedef CComCollection<IStrListCollection, BSTR, StrList, StrListEnumeratorObject> StrListCollection;
    typedef CComObjectSlim<StrListCollection> StrListCollectionObject;

    BOOST_AUTO_TEST_SUITE(CComCollectionTestSuite)

    BOOST_AUTO_TEST_CASE(CComCollectionTest)
    {
        HRESULT hr = E_FAIL;
        StrListCollectionObject* pStrListCollection = NULL;
        hr = StrListCollectionObject::CreateInstance(&pStrListCollection);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pStrListCollection);
    }

    BOOST_AUTO_TEST_SUITE_END()
}
