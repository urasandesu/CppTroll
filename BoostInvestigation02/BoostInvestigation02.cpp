// BoostInvestigation02.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include <boost/type_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <vector>

template<template<class> class T>
struct scrape_param1
{
};

template<template<class, class> class T>
struct scrape_param2
{
};

template<class T>
struct to_convertible_from_any
{
    to_convertible_from_any(T& other) { }
    to_convertible_from_any& operator=(T& other) { return *this; }
};

template<template<class> class Container>
struct to_convertible_from_any<scrape_param1<Container>>
{
    template<class T0>
    to_convertible_from_any(Container<T0>& other) { }

    template<class T0>
    to_convertible_from_any& operator=(Container<T0>& other) { return *this; }
};

template<template<class, class> class Container>
struct to_convertible_from_any<scrape_param2<Container>>
{
    template<class T0, class T1>
    to_convertible_from_any(Container<T0, T1>& other) { }

    template<class T0, class T1>
    to_convertible_from_any& operator=(Container<T0, T1>& other) { return *this; }
};

template<class T0>
struct dummy_has_param1
{
};

template<class T0, class T1>
struct dummy_has_param2
{
};



int _tmain(int argc, _TCHAR* argv[])
{
    using namespace boost;


    BOOST_MPL_ASSERT((is_convertible<dummy_has_param1<int>, to_convertible_from_any<scrape_param1<dummy_has_param1>>>));
    //BOOST_MPL_ASSERT((is_convertible<int, to_convertible_from_any<scrape_param1<dummy_has_param1>>>));  // compile error

    BOOST_MPL_ASSERT((is_convertible<dummy_has_param2<int, int>, to_convertible_from_any<scrape_param2<dummy_has_param2>>>));
    //BOOST_MPL_ASSERT((is_convertible<int, to_convertible_from_any<scrape_param2<dummy_has_param2>>>));  // compile error

    using namespace std;
    BOOST_MPL_ASSERT((is_convertible<vector<int>, to_convertible_from_any<scrape_param2<vector>>>));
    //BOOST_MPL_ASSERT((is_convertible<int, to_convertible_from_any<scrape_param2<vector>>>));  // compile error

    return 0;
}

