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

#include <io.h>
#include <iostream>
#include <boost/scope_exit.hpp>
#include <boost/exception/all.hpp>
#include <string>
#include <boost/system/windows_error.hpp>
#include <mscoree.h>
#include <boost/filesystem.hpp>
#include <cor.h>
#include <corhdr.h>
#include <iomanip>
#include <ICeeFileGen.h>
#include <comdef.h>
#include <memory>
#include <StrongName.h>
#include <corhlpr.h>
#include <boost/type_traits.hpp>
#include <boost/mpl/assert.hpp>
