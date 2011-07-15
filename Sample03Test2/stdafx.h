// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "targetver.h"

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS    // 一部の CString コンストラクタは明示的です。

#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>

using namespace ATL;

#ifndef URASANDESU_NANONYM_NANONYMDEPENDSON_H
#include "Urasandesu/NAnonym/NAnonymDependsOn.h"
#endif

#ifndef URASANDESU_NANONYM_COLLECTIONS_COLLECTIONSDEPENDSON_H
#include "Urasandesu/NAnonym/Collections/CollectionsDependsOn.h"
#endif

#ifndef URASANDESU_NANONYM_CONCEPTS_CONCEPTSDEPENDSON_H
#include "Urasandesu/NAnonym/Concepts/ConceptsDependsOn.h"
#endif

#ifndef URASANDESU_NANONYM_TRAITS_TRAITSDEPENDSON_H
#include "Urasandesu/NAnonym/Traits/TraitsDependsOn.h"
#endif

#ifndef URASANDESU_NANONYM_UTILITIES_UTILITIESDEPENDSON_H
#include "Urasandesu/NAnonym/Utilities/UtilitiesDependsOn.h"
#endif


// TODO: プログラムに必要な追加ヘッダーをここで参照してください。
#import "libid:4F3639A6-BF3E-4D50-BEF2-A1AFF6C094DF" version("1.0") no_namespace // Sample03 1.0 タイプ ライブラリ

#include <stdlib.h>
#include <iostream> 
#include <vector>
#include <map>
#include <boost/timer.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/assert.hpp>
