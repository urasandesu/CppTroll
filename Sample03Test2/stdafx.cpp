// stdafx.cpp : �W���C���N���[�h Sample03Test2.pch �݂̂�
// �܂ރ\�[�X �t�@�C���́A�v���R���p�C���ς݃w�b�_�[�ɂȂ�܂��B
// stdafx.obj �ɂ̓v���R���p�C���ς݌^��񂪊܂܂�܂��B

#include "stdafx.h"

// TODO: ���̃t�@�C���ł͂Ȃ��ASTDAFX.H �ŕK�v��
// �ǉ��w�b�_�[���Q�Ƃ��Ă��������B

#define BOOST_TEST_NO_LIB
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE Sample03Test2
#include <boost/test/included/unit_test.hpp>

struct OleCom 
{
    OleCom() { ::CoInitialize(NULL); }
    ~OleCom() { ::CoUninitialize(); }
} olecom;
