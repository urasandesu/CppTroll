
#include "stdafx.h"

#ifndef INCLUDED_ATLCOPY_H
#include "ATLCopy.h"
#endif

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

namespace
{
    using My::ATLCopy;

    template<class DestinationType, class SourceType>
    struct MyCopy
    {
        typedef DestinationType destination_type;
        typedef SourceType source_type;

        static void init(destination_type* p) { }
        static void destroy(destination_type* p) { }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom) { return S_OK; }
    }; 

    // MEMO: If you specialize the class with ATLCopy concept to manage the classes that overloads operator&, 
    //       let me suggest that you prepare the overload of the methods to manage them.
    template<class DestinationType, class SourceType>
    struct MyCopy<
                _com_ptr_t<_com_IIID<DestinationType, &__uuidof(DestinationType)>>, 
                _com_ptr_t<_com_IIID<SourceType, &__uuidof(SourceType)>>
           >
    {
        typedef DestinationType* destination_type;
        typedef SourceType* source_type;
        typedef _com_ptr_t<_com_IIID<DestinationType, &__uuidof(DestinationType)>> actual_destination_type;
        typedef _com_ptr_t<_com_IIID<SourceType, &__uuidof(SourceType)>> actual_source_type;

        static void init(destination_type* p) { }
        static void init(actual_destination_type* p) { }
        static void destroy(destination_type* p) { }
        static void destroy(actual_destination_type* p) { }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom) { return S_OK; }
        static HRESULT copy(actual_destination_type* pTo, const actual_source_type* pFrom) { return S_OK; }
    }; 

    BOOST_AUTO_TEST_SUITE(ATLCopyTestSuite)

    BOOST_AUTO_TEST_CASE(UsageTest)
    {
        BOOST_CONCEPT_ASSERT((ATLCopy<_Copy<INT>, INT, INT>));
        BOOST_CONCEPT_ASSERT((ATLCopy<_Copy<VARIANT>, VARIANT, VARIANT>));
        BOOST_CONCEPT_ASSERT((ATLCopy<_Copy<BSTR>, BSTR, BSTR>));
        BOOST_CONCEPT_ASSERT((ATLCopy<_CopyInterface<IUnknown>, IUnknown*, IUnknown*>));
        BOOST_CONCEPT_ASSERT((ATLCopy<MyCopy<VARIANT, BSTR>, VARIANT, BSTR>));
        BOOST_CONCEPT_ASSERT((ATLCopy<MyCopy<IMyEnumerableGeneratorPtr, IMyEnumerableGeneratorPtr>, 
                                      IMyEnumerableGenerator*, IMyEnumerableGenerator*>));
        BOOST_CONCEPT_ASSERT((ATLCopy<MyCopy<IMyEnumerableGeneratorPtr, IMyEnumerableGeneratorPtr>, 
                                      IMyEnumerableGeneratorPtr, IMyEnumerableGeneratorPtr>));
    }

    BOOST_AUTO_TEST_SUITE_END()
}