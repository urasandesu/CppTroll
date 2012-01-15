#include "stdafx.h"

#ifndef URASANDESU_CPPANONYM_HEAPPROVIDER_H
#include <Urasandesu/CppAnonym/HeapProvider.h>
#endif

#ifndef URASANDESU_CPPANONYM_IHEAPCONTENT_H
#include <Urasandesu/CppAnonym/IHeapContent.h>
#endif

namespace {

    struct A : 
        Urasandesu::CppAnonym::IHeapContent<INT>
    {
        INT m_value;
    };

    struct B : 
        Urasandesu::CppAnonym::IHeapContent<INT>
    {
        ULONG m_value;
    };

    // ProfilingApiSample04Test.exe --gtest_filter=HeapProviderTestSuite.*
    TEST(HeapProviderTestSuite, HeapProviderTestDefaultPath01)
    {
        namespace mpl = boost::mpl;
        using namespace Urasandesu::CppAnonym;

        typedef HeapProvider<INT, mpl::vector<A, B> > MyHeapProvider;

        MyHeapProvider heap;
        MyHeapProvider::type_decided_by<A>::type &aHeap = heap.Of<A>();
        A *pA = aHeap.New(0);
        pA->m_value = 10;
        ASSERT_EQ(aHeap.Get(0), pA);
        ASSERT_EQ(10, aHeap.Get(0)->m_value);
        ASSERT_EQ(1, aHeap.Size());
        ASSERT_TRUE(aHeap.Exists(0)); 
        ASSERT_FALSE(aHeap.Exists(1)); 

        MyHeapProvider::type_decided_by<B>::type &bHeap = heap.Of<B>();
        B *pB = bHeap.New(1);
        pB->m_value = 20;
        ASSERT_EQ(bHeap.Get(1), pB);
        ASSERT_EQ(20, bHeap.Get(1)->m_value);
        ASSERT_EQ(1, bHeap.Size());
        ASSERT_TRUE(bHeap.Exists(1)); 
        ASSERT_FALSE(bHeap.Exists(0)); 

        MyHeapProvider const &cHeap = heap;
        MyHeapProvider::type_decided_by<A>::type const &caHeap = cHeap.Of<A>();
        A const *pcA = caHeap.Get(0);
        ASSERT_EQ(caHeap.Get(0), pcA);
        ASSERT_EQ(10, caHeap.Get(0)->m_value);
        ASSERT_EQ(1, caHeap.Size());
        ASSERT_TRUE(caHeap.Exists(0)); 
        ASSERT_FALSE(caHeap.Exists(1)); 
    }


    TEST(HeapProviderTestSuite, HeapProviderTestTypeConcept01)
    {
        namespace mpl = boost::mpl;
        using namespace Urasandesu::CppAnonym;

        typedef HeapProvider<INT, mpl::vector<INT, DOUBLE> > MyHeapProvider;

        // This declaration doesn't work because contents of boost::mpl::vector don't 
        // implement necessary interface Urasandesu::CppAnonym::IHeapContent.
        //MyHeapProvider heap;  // error C2664
    }
}
