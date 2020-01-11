#include "GameInput.h"
#include "Device\Input.h"
#include <cmath>
#include "Math\MathUtility.h"

float GameInput::getHorizontal()
{
	float move = 0;
	if (Input::isKey(VK_LEFT))
	{
		move -= 1;
	}

	if (Input::isKey(VK_RIGHT))
	{
		move += 1;
	}

	//�L�[�{�[�h�œ��͂�����Ă��Ȃ�������
	if (move == 0)
	{
		move = Input::getLStickValue().x;
	}


	return move;
}

float GameInput::getVertical()
{
	float move = 0;
	if (Input::isKey(VK_DOWN))
	{
		move -= 1;
	}

	if (Input::isKey(VK_UP))
	{
		move += 1;
	}

	//�L�[�{�[�h�œ��͂�����Ă��Ȃ�������
	if (move == 0)
	{
		move = Input::getLStickValue().y;
	}

	return move;
}

bool GameInput::isMagChange()
{
	//�{�^�����͂�����Ă�����true
	bool isButtonPressed = (Input::isKey('Z')) || Input::isPadButton(Input::PAD_BUTTON_B);
	//�������͂�����Ă�����true
	bool isDirInput = getHorizontal() != 0 || getVertical() != 0;

	return isButtonPressed && isDirInput;
}

Vec2 GameInput::getMagChangeDir()
{
	float horizontal = getHorizontal();
	float vertical = getVertical();

	//�X�e�B�b�N�̌X�����傫������Ԃ�
	if (std::fabsf(horizontal) > std::fabsf(vertical))
		return Vec2(MathUtility::sign(horizontal), 0);
	else
		return Vec2(0, MathUtility::sign(vertical));
}

bool GameInput::isJump()
{
	return Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A);
}
