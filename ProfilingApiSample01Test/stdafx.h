// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 一部の CString コンストラクタは明示的です。

#include <atlbase.h>
#include <atlstr.h>

// TODO: プログラムに必要な追加ヘッダーをここで参照してください。
#import "libid:27AD8864-4640-4757-BA89-AE75C3614EAF" version("1.0") no_namespace // ProfilingApiSample01 1.0 タイプ ライブラリ

#include <cor.h>
#include <corprof.h>
#include <comdef.h>
#include <ios>
#include <iostream>
#include <iomanip>