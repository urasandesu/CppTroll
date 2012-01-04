#include "stdafx.h"

#ifndef URASANDESU_CPPANONYM_RAPIDVECTOR_H
#include <Urasandesu/CppAnonym/RapidVector.h>
#endif

namespace {

    // ProfilingApiSample03Test.exe --gtest_filter=RapidVectorTestSuite.*

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


    TEST(RapidVectorTestSuite, IterationTest02EqualsOrGreaterThan512)
    {
        using namespace std;
        using namespace Urasandesu::CppAnonym;
        
        RapidVector<BYTE> vec;
        for (INT i = 0; i <= 512; ++i)
        {
            vec.push_back(static_cast<BYTE>(i & 0xFF));
        }
        ASSERT_EQ(513, vec.size());
        
        {
            //typedef RapidVector<BYTE>::reference ByteVectorRef;
            //BOOST_FOREACH (ByteVectorRef ref, vec)
            //{
            //    cout << static_cast<INT>(ref) << endl;
            //}

            //for (RapidVector<BYTE>::iterator i = vec.begin(), i_end = vec.end(); i != i_end; ++i)
            RapidVector<BYTE>::iterator i = vec.begin();
            ASSERT_EQ(0x00, *i);
            ASSERT_EQ(0xFF, i[vec.size() - 2]);
            ASSERT_EQ(0x00, i[vec.size() - 1]);
        }
    }


    TEST(RapidVectorTestSuite, RandomAccessOperatorTest01LessThan512)
    {
        using namespace std;
        using namespace Urasandesu::CppAnonym;
        
        RapidVector<BYTE> vec;
        for (INT i = 0; i < 512; ++i)
        {
            vec.push_back(static_cast<BYTE>(i & 0xFF));
        }
        ASSERT_EQ(512, vec.size());
        
        ASSERT_EQ(0x00, vec[0]);
        ASSERT_EQ(0xFF, vec[vec.size() - 1]);
    }


    TEST(RapidVectorTestSuite, RandomAccessOperatorTest02EqualsOrGreaterThan512)
    {
        using namespace std;
        using namespace Urasandesu::CppAnonym;
        
        RapidVector<BYTE> vec;
        for (INT i = 0; i <= 512; ++i)
        {
            vec.push_back(static_cast<BYTE>(i & 0xFF));
        }
        ASSERT_EQ(513, vec.size());
        
        ASSERT_EQ(0x00, vec[0]);
        ASSERT_EQ(0xFF, vec[vec.size() - 2]);
        ASSERT_EQ(0x00, vec[vec.size() - 1]);
    }
}
