// stdafx.cpp : �W���C���N���[�h ProfilingApiSample04Test.pch �݂̂�
// �܂ރ\�[�X �t�@�C���́A�v���R���p�C���ς݃w�b�_�[�ɂȂ�܂��B
// stdafx.obj �ɂ̓v���R���p�C���ς݌^��񂪊܂܂�܂��B

#include "stdafx.h"

// TODO: ���̃t�@�C���ł͂Ȃ��ASTDAFX.H �ŕK�v��
// �ǉ��w�b�_�[���Q�Ƃ��Ă��������B
#include <corhlpr.cpp>

struct OleCom 
{
    OleCom() { ::CoInitialize(NULL); }
    ~OleCom() { ::CoUninitialize(); }
} olecom;