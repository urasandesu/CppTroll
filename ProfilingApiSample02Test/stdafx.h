﻿// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
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
#import "libid:8B6C1B28-B4DA-4C92-8053-1B911458F597" version("1.0") no_namespace // ProfilingApiSample02 1.0 タイプ ライブラリ

#ifndef URASANDESU_NANONYM_NANONYMDEPENDSON_H
#include <Urasandesu/NAnonym/NAnonymDependsOn.h>
#endif

#include <corprof.h>
#include <gtest/gtest.h>
