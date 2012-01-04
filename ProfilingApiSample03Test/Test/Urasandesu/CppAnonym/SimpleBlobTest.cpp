#include "stdafx.h"

#ifndef URASANDESU_CPPANONYM_SIMPLEBLOB_H
#include <Urasandesu/CppAnonym/SimpleBlob.h>
#endif


namespace {

    // ProfilingApiSample03Test.exe --gtest_filter=SimpleBlobTestSuite.*

    struct MyPOD1
    {
        BYTE byte1;
        BYTE byte2;
        BYTE byte3;
        BYTE byte4;
        BYTE byte5;
        BYTE byte6;
        BYTE byte7;
        BYTE byte8;
    };
    
    struct MyPOD2
    {
        INT int1;
        MyPOD1 pod1;
        PVOID pv;
        
        MyPOD2 *prev;
        MyPOD2 *next;
    };

    
    TEST(SimpleBlobTestSuite, PutTTest01_SucceedPath)
    {
        using namespace Urasandesu::CppAnonym;
        
        SimpleBlob sb;
        sb.Put<BYTE>(0x01);
        sb.Put<DWORD>(0x23456789);
        
        BYTE *pb = sb.Ptr();
        ASSERT_EQ(0x01, *pb++);
        ASSERT_EQ(0x89, *pb++);
        ASSERT_EQ(0x67, *pb++);
        ASSERT_EQ(0x45, *pb++);
        ASSERT_EQ(0x23, *pb++);
    }


    TEST(SimpleBlobTestSuite, PutTTest02_Iteration)
    {
        using namespace Urasandesu::CppAnonym;
        
        SimpleBlob sb;
        sb.Put<BYTE>(0x01);
        sb.Put<DWORD>(0x23456789);

        BYTE expectedList[] = { 0x01, 0x89, 0x67, 0x45, 0x23 };
        INT n = 0;
        for (BYTE const *i = sb.Ptr(), *i_end = i + sb.Size(); i != i_end; ++i, ++n)
        {
            ASSERT_EQ(expectedList[n], *i);    
        }        
    }


    TEST(SimpleBlobTestSuite, PutTTest03_RandomAccess)
    {
        using namespace Urasandesu::CppAnonym;
        
        SimpleBlob sb;
        sb.Put<BYTE>(0x01);
        sb.Put<DWORD>(0x23456789);

        BYTE expectedList[] = { 0x01, 0x89, 0x67, 0x45, 0x23 };
        ASSERT_EQ(expectedList[0], sb[0]);
        ASSERT_EQ(expectedList[2], sb[2]);
        ASSERT_EQ(expectedList[4], sb[4]);
    }


    TEST(SimpleBlobTestSuite, PutTTest04_PutsPODObjects)
    {
        using namespace Urasandesu::CppAnonym;
        
        MyPOD1 pod1 = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
        MyPOD2 podPrev;
        MyPOD2 podNext;
        MyPOD2 pod2 = { 0x090A0B0C, pod1, NULL, &podPrev, &podNext };
        
        SimpleBlob sb;
        sb.Put<MyPOD2>(pod2);

        BYTE *pb = sb.Ptr();
        ASSERT_EQ(0x0C, *pb++);
        ASSERT_EQ(0x0B, *pb++);
        ASSERT_EQ(0x0A, *pb++);
        ASSERT_EQ(0x09, *pb++);
        ASSERT_EQ(0x01, *pb++);
        ASSERT_EQ(0x02, *pb++);
        ASSERT_EQ(0x03, *pb++);
        ASSERT_EQ(0x04, *pb++);
        ASSERT_EQ(0x05, *pb++);
        ASSERT_EQ(0x06, *pb++);
        ASSERT_EQ(0x07, *pb++);
        ASSERT_EQ(0x08, *pb++);
        ASSERT_EQ(0x00, *pb++);
        ASSERT_EQ(0x00, *pb++);
        ASSERT_EQ(0x00, *pb++);
        ASSERT_EQ(0x00, *pb++);
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<INT>(&podPrev) & 0xFF), *pb++);
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<INT>(&podPrev) >> 8 & 0xFF), *pb++);
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<INT>(&podPrev) >> 16 & 0xFF), *pb++);
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<INT>(&podPrev) >> 24 & 0xFF), *pb++);
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<INT>(&podNext) & 0xFF), *pb++);
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<INT>(&podNext) >> 8 & 0xFF), *pb++);
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<INT>(&podNext) >> 16 & 0xFF), *pb++);
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<INT>(&podNext) >> 24 & 0xFF), *pb++);
    }


    TEST(SimpleBlobTestSuite, PutTTest05_HigherPerformanceThanTypicalWay)
    {
        using namespace std;
        using namespace Urasandesu::CppAnonym;
        
        INT assignCount = 0;
        {
            SimpleBlob sb;
            assignCount = static_cast<INT>(sb.MaxSize() / sizeof(MyPOD2));
        }
        ASSERT_EQ(21, assignCount);
        

#ifdef _DEBUG
        INT const RETRY_COUNT = 1000;
#else
        INT const RETRY_COUNT = 100000;
#endif
        boost::timer t;
        t.restart();
        
        for (INT i = 0; i < RETRY_COUNT; ++i)
        {
            vector<MyPOD2> vec(assignCount);
            for (INT j = 0; j < assignCount; ++j)
            {
                vec.push_back(MyPOD2());
            }
        }
        
        double typicalElapsed = t.elapsed();
        
        t.restart();
        
        for (INT i = 0; i < RETRY_COUNT; ++i)
        {
            SimpleBlob sb;
            for (INT j = 0; j < assignCount; ++j)
            {
                sb.Put<MyPOD2>(MyPOD2());
            }
        }
        
        double sbElapsed = t.elapsed();
        
        cout << "Typical Way: " << typicalElapsed << endl;
        cout << "Simple Blob: " << sbElapsed << endl;
        ASSERT_LT(sbElapsed, typicalElapsed);
    }


    TEST(RapidVectorTestSuite, IterationTest01LessThan512)
    {
        using namespace std;
        using namespace Urasandesu::CppAnonym;
        
        RapidVector<BYTE> vec;
        for (INT i = 0; i < 512; ++i)
        {
            vec.push_back(static_cast<BYTE>(i & 0xFF));
        }
        ASSERT_EQ(512, vec.size());
        
        {
            RapidVector<BYTE>::iterator i = vec.begin();
            ASSERT_EQ(0x00, *i);
            ASSERT_EQ(0xFF, *(i += vec.size() - 1));
        }
    }
}
