#pragma once
#include "Math\Vec2.h"

class GameInput
{
public:
	//�������̈ړ����͂�Ԃ��܂��B
	static float getHorizontal();
	//�c�����̈ړ����͂�Ԃ��܂��B
	static float getVertical();

	//S�Ƀp���`�̓��͂����ꂽ���ǂ����Ԃ��܂��B
	static bool isMagChange();
	//S�Ƀp���`�̕�����Ԃ��܂��B
	static Vec2 getMagChangeDir();

	//�W�����v���͂����ꂽ���ǂ����Ԃ��܂��B
	static bool isJump();

private:
	GameInput();	//�C���X�^���X�̐������֎~
};