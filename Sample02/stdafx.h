// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B

#pragma once

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// �ꕔ�� CString �R���X�g���N�^�͖����I�ł��B

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>

using namespace ATL;

#include <boost/unordered_map.hpp>
#include "ComUtilities.h"
#include "CComEnumOnRange.h"
#include "Copies.h"
#include <boost/format.hpp>
#include <iostream>
#include "Pairs.h"

#import "libid:BED7F4EA-1A96-11D2-8F08-00A0C9A6186D" version("2.0") // mscorlib.dll
