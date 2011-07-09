
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
    using Urasandesu::NAnonym::Collections::CComEnumerator;
    using Urasandesu::NAnonym::Utilities::CComObjectSlim;
    using Urasandesu::NAnonym::Collections::ICollectionImpl;
    
    typedef vector<CAdapt<CComBSTR>> StrVector;
    typedef CComEnumerator<IEnumVARIANT, VARIANT, StrVector> StrVectorEnumerator;
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

    BOOST_AUTO_TEST_CASE(ICollectionImplTest)
    {
        HRESULT hr = E_FAIL;
        StrVectorCollectionObject* pStrVectorCollection = NULL;
        hr = StrVectorCollectionObject::CreateInstance(&pStrVectorCollection);
        BOOST_REQUIRE(SUCCEEDED(hr));

        CComPtr<IUnknown> pUnkForRelease(pStrVectorCollection);
    }

    BOOST_AUTO_TEST_SUITE_END()
}