// stdafx.cpp : 標準インクルード ProfilingApiSample02Test.pch のみを
// 含むソース ファイルは、プリコンパイル済みヘッダーになります。
// stdafx.obj にはプリコンパイル済み型情報が含まれます。

#include "stdafx.h"

// TODO: このファイルではなく、STDAFX.H で必要な
// 追加ヘッダーを参照してください。
#include <corhlpr.cpp>

struct OleCom 
{
    OleCom() { ::CoInitialize(NULL); }
    ~OleCom() { ::CoUninitialize(); }
} olecom;
