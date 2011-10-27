// ProfilingApiSample02Test.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#ifndef URASANDESU_NANONYM_HEAPPROVIDER_H
#include <Urasandesu/NAnonym/HeapProvider.h>
#endif

namespace {

    template<class Key>
    class ATL_NO_VTABLE IHeapContent
    {
    public:
        IHeapContent() : 
            m_key(Key())
        { }
        
        Key GetKey()
        {
            return m_key;
        }
        
        void SetKey(Key key)
        {
            m_key = key;
        }
        
        bool IsPseudo()
        {
            return m_key == Key();
        }
        
    private:        
        Key m_key;
    }; 

    class A : public IHeapContent<UINT_PTR>
    {
    };
    
    class B : public IHeapContent<UINT_PTR>
    {
    };

    class Hoge
    {
        BEGIN_NANONYM_HEAP_PROVIDER()
            DECLARE_NANONYM_HEAP_PROVIDER(A, UINT_PTR, m_pAFactory)
            DECLARE_NANONYM_HEAP_PROVIDER(B, UINT_PTR, m_pBFactory)
        END_NANONYM_HEAP_PROVIDER()
    };

    // ProfilingApiSample02Test.exe --gtest_filter=ProfilingApiSample02TestSuite.TempTestTest
    TEST(ProfilingApiSample02TestSuite, TempTestTest)
    {
        using namespace std;
        using namespace boost;
        
        Hoge hoge;
        
        UINT_PTR a1Id = 1;
        UINT_PTR a2Id = 2;
        A *pA1 = hoge.New<A>(a1Id);
        A *pA2 = hoge.Get<A>(a1Id);
        
        cout << format("pA1: 0x%|1$08X|") % reinterpret_cast<void *>(pA1) << endl;
        cout << format("pA2: 0x%|1$08X|") % reinterpret_cast<void *>(pA2) << endl;
        
        ASSERT_TRUE(pA1 == pA2);
        ASSERT_EQ(1, pA1->GetKey());
        ASSERT_EQ(1, pA2->GetKey());

        
        
        pA2 = hoge.New<A>(a1Id);
        
        ASSERT_TRUE(pA1 != pA2);
        ASSERT_TRUE(pA1->IsPseudo());
        ASSERT_EQ(0, pA1->GetKey());

        
        
        pA2 = hoge.New<A>(a2Id);

        cout << format("pA1: 0x%|1$08X|") % reinterpret_cast<void *>(pA1) << endl;
        cout << format("pA2: 0x%|1$08X|") % reinterpret_cast<void *>(pA2) << endl;

        ASSERT_TRUE(pA1 != pA2);
        ASSERT_EQ(2, pA2->GetKey());
        
        
        
        UINT_PTR a3Id = 3;
        A *pA3 = hoge.NewPseudo<A>();
        hoge.SetToLast<A>(a3Id);
        A *pA4 = hoge.Get<A>(a3Id);

        cout << format("pA3: 0x%|1$08X|") % reinterpret_cast<void *>(pA3) << endl;
        cout << format("pA4: 0x%|1$08X|") % reinterpret_cast<void *>(pA4) << endl;
        
        ASSERT_TRUE(pA3 == pA4);
        ASSERT_EQ(3, pA3->GetKey());
        ASSERT_EQ(3, pA4->GetKey());

        
        
        A *pA5 = hoge.NewPseudo<A>();
        cout << format("pA5: 0x%|1$08X|") % reinterpret_cast<void *>(pA5) << endl;

        ASSERT_TRUE(pA5 != NULL);                


        
        cout << format("Size: %|1$d|") % hoge.Size<A>() << endl;

        ASSERT_EQ(5, hoge.Size<A>());


        
        A *pA6 = hoge.Peek<A>();         
        cout << format("pA6: 0x%|1$08X|") % reinterpret_cast<void *>(pA6) << endl;

        ASSERT_TRUE(pA5 == pA6);
        
        
        IHeapContent<UINT_PTR> piyo;

        ASSERT_TRUE(piyo.IsPseudo());
        
        piyo.SetKey(10);
        
        ASSERT_FALSE(piyo.IsPseudo());
    }
}
