// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。

#pragma once

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// 一部の CString コンストラクタは明示的です。

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>

using namespace ATL;

namespace Urasandesu { namespace NAnonym {

    template<class T>
    inline T max(T a, T b) { return a > b ? a : b; }
    
    template<class T>
    inline T min(T a, T b) { return a < b ? a : b; }
    
}}  // namespace Urasandesu { namespace NAnonym {

#ifndef URASANDESU_NANONYM_NANONYMDEPENDSON_H
#include "Urasandesu/NAnonym.h"
#endif

#include <boost/scope_exit.hpp>
#include <corprof.h>
#include <comdef.h>
#include <ios>
#include <iostream>
#include <iomanip>
#include <malloc.h>
#include <sstream>

