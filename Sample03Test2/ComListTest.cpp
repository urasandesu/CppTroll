
#include "stdafx.h"

#ifndef URASANDESU_NANONYM_CONCEPTS_COMLIST_H
#include "Urasandesu/NAnonym/Concepts/ComList.h"
#endif

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

namespace
{
    using Urasandesu::NAnonym::Concepts::ComList;
    
    struct StrList : public IDispatch
    {
    public:
        STDMETHOD(Add)(BSTR item) { return S_OK; }
        STDMETHOD(get__NewEnum)(IUnknown **ppVal) { return S_OK; }
        STDMETHOD(Clear)(void) { return S_OK; }
        STDMETHOD(Contains)(BSTR item, VARIANT_BOOL *exists) { return S_OK; }
        STDMETHOD(CopyTo)(SAFEARRAY * pArray, LONG index) { return S_OK; }
        STDMETHOD(Remove)(BSTR item) { return S_OK; }
        STDMETHOD(get_Count)(LONG *pVal) { return S_OK; }
        STDMETHOD(get_IsReadOnly)(VARIANT_BOOL *pVal) { return S_OK; }
        STDMETHOD(IndexOf)(BSTR item, LONG *index) { return S_OK; }
        STDMETHOD(Insert)(LONG index, BSTR item) { return S_OK; }
        STDMETHOD(RemoveAt)(LONG index) { return S_OK; }
        STDMETHOD(get_Item)(LONG index, BSTR *pVal) { return S_OK; }
        STDMETHOD(put_Item)(LONG index, BSTR newVal) { return S_OK; }
    };

    BOOST_AUTO_TEST_SUITE(ComListTestSuite)

    BOOST_AUTO_TEST_CASE(ComListTest)
    {
        BOOST_CONCEPT_ASSERT((ComList<StrList, BSTR>));
    }

    BOOST_AUTO_TEST_SUITE_END()
}