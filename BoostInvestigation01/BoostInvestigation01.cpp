// BoostInvestigation01.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
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

int _tmain(int argc, _TCHAR* argv[])
{
    using namespace std;
    using namespace boost;

    vector<int> v1;
    Hoge(v1);
    vector<double> v2;
    Hoge(v2);
    int i = 0;
    //Hoge(i);      // �R���p�C���G���[
    struct Piyo { } piyo;
    //Hoge(piyo);   // �R���p�C���G���[
    BOOST_CONCEPT_ASSERT((Convertible<vector<int>, vector<any>>));
    BOOST_STATIC_ASSERT((is_convertible<vector<int>, vector<any>>::value));
    BOOST_STATIC_ASSERT((!is_convertible<vector<int>, vector<double>>::value));

    return 0;
}

