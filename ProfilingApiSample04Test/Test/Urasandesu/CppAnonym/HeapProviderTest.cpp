#include "stdafx.h"

#ifndef URASANDESU_CPPANONYM_HEAPPROVIDER_H
#include <Urasandesu/CppAnonym/HeapProvider.h>
#endif

#ifndef URASANDESU_CPPANONYM_IHEAPCONTENT_H
#include <Urasandesu/CppAnonym/IHeapContent.h>
#endif

namespace {

    struct A : 
        public Urasandesu::CppAnonym::IHeapContent<INT>
    {
        INT m_value;
    };

    struct B : 
        public Urasandesu::CppAnonym::IHeapContent<INT>
    {
        ULONG m_value;
    };

    //struct Manager
    //{
    //    CPPANONYM_BEGIN_HEAP_PROVIDER_DECLARATION()
    //        CPPANONYM_HEAP_PROVIDER(A, INT, m_pAFactory);
    //    CPPANONYM_END_HEAP_PROVIDER_DECLARATION()
    //};

    // ProfilingApiSample04Test.exe --gtest_filter=HeapProviderTestSuite.*
    TEST(HeapProviderTestSuite, HeapProviderTest01_DefineVariable)
    {
        using namespace Urasandesu::CppAnonym;

        typedef HeapProvider<int, boost::mpl::vector<A, B> > MyProvider;

        MyProvider provider;
        A *pa = provider.Of<A>().New(0);
        pa->m_value = 10;
        ASSERT_EQ(provider.Of<A>().Get(0), pa);
        ASSERT_EQ(10, provider.Of<A>().Get(0)->m_value);


        B *pb = provider.Of<B>().New(1);
        pb->m_value = 20;
        ASSERT_EQ(provider.Of<B>().Get(1), pb);
        ASSERT_EQ(20, provider.Of<B>().Get(1)->m_value);

        MyProvider const &const_provider = provider;
        A const *pca = const_provider.Of<A>().Get(0);
        ASSERT_EQ(const_provider.Of<A>().Get(0), pca);
        ASSERT_EQ(10, const_provider.Of<A>().Get(0)->m_value);
    }
}
