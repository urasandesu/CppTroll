// BoostInvestigation01.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <vector>
#include <boost/static_assert.hpp>
#include <boost/concept_check.hpp>
#include <boost/concept/requires.hpp>

namespace std
{
    struct any
    {
    };

    template<>
    class vector<any>
    {
    public:
        template<class T>
        vector(vector<T>& other) { }

        template<class T>
        vector<any>& operator=(vector<T>& other) { return *this; } 
    };
}

template<class T>
BOOST_CONCEPT_REQUIRES(
                       ((boost::Convertible<T, std::vector<std::any>>)),
                       (void)
                       ) Hoge(T& t)
{
}

//template<class T>
//BOOST_CONCEPT_REQUIRES(
//                       ((boost::Convertible<T, std::vector<std::any>>)),
//                       (void)
//                       ) HogeHoge(void** ppObj)
//{
//}

template<class T>
void HogeHoge(void** ppObj)
{
}

int _tmain(int argc, _TCHAR* argv[])
{
    using namespace std;
    using namespace boost;

    vector<int> v1;
    Hoge(v1);
    vector<double> v2;
    Hoge(v2);
    int i = 0;
    //Hoge(i);      // コンパイルエラー
    struct Piyo { } piyo;
    //Hoge(piyo);   // コンパイルエラー
    BOOST_CONCEPT_ASSERT((Convertible<vector<int>, vector<any>>));
    BOOST_STATIC_ASSERT((is_convertible<vector<int>, vector<any>>::value));
    BOOST_STATIC_ASSERT((!is_convertible<vector<int>, vector<double>>::value));

    void* pObj = NULL;
    HogeHoge<int>(&pObj);

    return 0;
}

