
#include "stdafx.h"

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#ifndef URASANDESU_NANONYM_COLLECTIONS_CCOMENUMERATOR_H
#include "Urasandesu/NAnonym/Collections/CComEnumerator.h"
#endif

#ifndef URASANDESU_NANONYM_UTILITIES_CCOMOBJECTSLIM_H
#include "Urasandesu/NAnonym/Utilities/CComObjectSlim.h"
#endif

#ifndef URASANDESU_NANONYM_UTILITIES_CCOMPAIR_H
#include "Urasandesu/NAnonym/Utilities/CComPair.h"
#endif

#ifndef URASANDESU_NANONYM_COLLECTIONS_IDICTIONARYIMPL_H
#include "Urasandesu/NAnonym/Collections/IDictionaryImpl.h"
#endif

namespace
{
    using std::map;
    using boost::use_default;
    using Urasandesu::NAnonym::Collections::CComEnumerator;
    using Urasandesu::NAnonym::Utilities::CComObjectSlim;
    using Urasandesu::NAnonym::Utilities::CComPair;
    using Urasandesu::NAnonym::Collections::IDictionaryImpl;    

    typedef CAdapt<CComBSTR> AdaptedStr;
    typedef map<AdaptedStr, CComVariant> StrVariantMap;
    typedef CComEnumerator<IEnumVARIANT, VARIANT, StrVariantMap, use_default, use_default, CComObjectSlim> StrVariantMapEnumerator;
    typedef CComObjectSlim<StrVariantMapEnumerator> StrVariantMapEnumeratorObject;
    
    MIDL_INTERFACE("971B749D-F0EF-4603-B49D-C8D6D915668A")
    IStrVariantPair : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_First( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_First( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Second( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Second( 
            /* [in] */ VARIANT newVal) = 0;
        
    };
    
    typedef CComPair<IStrVariantPair, BSTR, VARIANT> StrVariantPair;
    typedef CComObjectSlim<StrVariantPair> StrVariantPairObject;

    MIDL_INTERFACE("3987AEB7-32C0-47e5-90C0-1E31FAC89692")
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
    };

    MIDL_INTERFACE("D698701D-321F-460a-BA9E-CD9CD0BEAFF5")
    IVariantVectorCollection : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ VARIANT item) = 0;
        
        virtual /* [restricted][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Contains( 
            /* [in] */ VARIANT item,
            /* [retval][out] */ VARIANT_BOOL *exists) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CopyTo( 
            /* [out][in] */ SAFEARRAY * pArray,
            /* [in] */ LONG index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT item) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsReadOnly( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;        
    };
    
    MIDL_INTERFACE("47AD7F51-EA39-439e-979D-33D34F28107A")
    IStrVariantMapDictionary : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IStrVariantPair* item) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR first, VARIANT second) = 0;
        
        virtual /* [restricted][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Contains( 
            /* [in] */ IStrVariantPair* item,
            /* [retval][out] */ VARIANT_BOOL *exists) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ContainsKey( 
            /* [in] */ BSTR first,
            /* [retval][out] */ VARIANT_BOOL *exists) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CopyTo( 
            /* [out][in] */ SAFEARRAY * pArray,
            /* [in] */ LONG index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ IStrVariantPair* item) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TryGetValue( 
            /* [in] */ BSTR first, /* [out] */ VARIANT* pSecond, /* [retval][out] */ VARIANT_BOOL *exists) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsReadOnly( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;        
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ BSTR first,
            /* [retval][out] */ VARIANT *pSecond) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Item( 
            /* [in] */ BSTR first,
            /* [in] */ VARIANT second) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Keys( 
            /* [retval][out] */ IStrVectorCollection** ppFirstCollection) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Values( 
            /* [retval][out] */ IVariantVectorCollection** ppSecondCollection) = 0;
    };

    //// NOTE: ATL の奥のほうで型安全にするのを阻む輩がいる（CComSafeArray とか。）
    ////       get__NewEnum みたく、COM オブジェクトを返す場合は IUnknown にしたほうが良さげ。
    ////       そういう意味では、参考にすべきは System.Collections.Generic 名前空間のクラス群じゃなく、System.Collections 名前空間のクラス群か。
    ////       プリミティブな型のやりとりは可能にさせておいて、必ず COM オブジェクトじゃないとあかんぜよ、ってところは IUnkown でやりとりできる I/F にするとか。
    //typedef IDictionaryImpl<
    //            IStrVariantMapDictionary, 
    //            StrVariantPairObject, 
    //            IStrVectorCollection, 
    //            IVariantVectorCollection, 
    //            StrVariantMap, 
    //            StrVariantMapEnumeratorObject
    //        > StrVariantMapDictionaryImpl;
    //class ATL_NO_VTABLE CStrVariantMapDictionary;
    //typedef CComObjectSlim<CStrVariantMapDictionary> StrVariantMapDictionaryObject;

    //class ATL_NO_VTABLE CStrVariantMapDictionary : 
    //    public CComObjectRootEx<CComSingleThreadModel>,
    //    public StrVariantMapDictionaryImpl
    //{
    //public:
    //    CStrVariantMapDictionary() { }

    //BEGIN_COM_MAP(CStrVariantMapDictionary)
    //    COM_INTERFACE_ENTRY(IStrVariantMapDictionary)
    //END_COM_MAP()

    //    DECLARE_PROTECT_FINAL_CONSTRUCT()

    //    HRESULT FinalConstruct() { return S_OK; }
    //    void FinalRelease() { }
    //};
    
    BOOST_AUTO_TEST_SUITE(IDictionaryImplTestSuite)

    BOOST_AUTO_TEST_CASE(IDictionaryImplTest)
    {
    }

    BOOST_AUTO_TEST_SUITE_END()
}