// stdafx.cpp : 標準インクルード MetaDataApiSample02Test.pch のみを
// 含むソース ファイルは、プリコンパイル済みヘッダーになります。
// stdafx.obj にはプリコンパイル済み型情報が含まれます。

#include "stdafx.h"

// TODO: このファイルではなく、STDAFX.H で必要な
// 追加ヘッダーを参照してください。

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE MetaDataApiSample02Test
#include <boost/test/included/unit_test.hpp>

struct OleCom 
{
    OleCom() { ::CoInitialize(NULL); }
    ~OleCom() { ::CoUninitialize(); }
} olecom;
