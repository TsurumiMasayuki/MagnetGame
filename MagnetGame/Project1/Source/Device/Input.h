#pragma once
#include <Windows.h>
#include "Math\Vec3.h"
#include "Math\Vec2.h"

class Input
{
public:
	//�R���g���[���[�̃{�^���w��pEnum
	enum PAD_BUTTON
	{
		PAD_BUTTON_X = 0x0001,			//X�{�^��
		PAD_BUTTON_Y = 0x0002,			//Y�{�^��
		PAD_BUTTON_A = 0x0004,			//A�{�^��
		PAD_BUTTON_B = 0x0008,			//B�{�^��
		PAD_BUTTON_LB = 0x00000010l,	//L�{�^��
		PAD_BUTTON_RB = 0x00000020l,	//R�{�^��
		PAD_BUTTON_LT = 0x00000040l,	//L�g���K�[
		PAD_BUTTON_RT = 0x00000080l,	//R�g���K�[
		PAD_BUTTON_START = 0x00000800l,	//�X�^�[�g�{�^��
	};

	//�w�肳�ꂽ�L�[�������ꂽ����True��Ԃ��܂�
	static bool isKeyUp(UINT key);
	//�w�肳�ꂽ�L�[�������ꑱ���Ă��鎞��True��Ԃ��܂�
	static bool isKey(UINT key);
	//�w�肳�ꂽ�L�[�������ꂽ����True��Ԃ��܂�
	static bool isKeyDown(UINT key);

	//�}�E�X�̍��W��Ԃ��܂�
	static Vec3 getMousePosition();
	//�J������Ń}�E�X���W��Ԃ��܂�
	static Vec3 getWorldMousePosition();

	//�R���g���[���[�̃{�^���������ꂽ����True��Ԃ��܂�
	static bool isPadButtonUp(PAD_BUTTON button);
	//�R���g���[���[�̃{�^�������ꑱ���Ă��鎞��True��Ԃ��܂�
	static bool isPadButton(PAD_BUTTON button);
	//�R���g���[���[�̃{�^���������ꂽ����True��Ԃ��܂�
	static bool isPadButtonDown(PAD_BUTTON button);

	//�\���{�^��(���O���킩��Ȃ�)�̓��͂�(-1 ~ 1, -1 ~ 1)�͈̔͂Ŏ擾���܂�
	static Vec2 getDPadValue();
	//���X�e�B�b�N�̓��͂�(-1 ~ 1, -1 ~ 1)�͈̔͂Ŏ擾���܂�
	static Vec2 getLStickValue();
	//�E�X�e�B�b�N�̓��͂�(-1 ~ 1, -1 ~ 1)�͈̔͂Ŏ擾���܂�
	static Vec2 getRStickValue();

	static void update();

private:
	static BYTE m_CurKeys[256];
	static BYTE m_PreKeys[256];

	static JOYINFOEX m_CurPadInfo;
	static JOYINFOEX m_PrePadInfo;

	static bool m_isPadConnected;
};

