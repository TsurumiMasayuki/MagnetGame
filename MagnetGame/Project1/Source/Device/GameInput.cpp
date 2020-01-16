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

	//キーボードで入力がされていなかったら
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

	//キーボードで入力がされていなかったら
	if (move == 0)
	{
		move = Input::getLStickValue().y;
	}

	return move;
}

bool GameInput::isMagChange()
{
	//ボタン入力がされていたらtrue
	bool isButtonPressed = (Input::isKeyDown('Z')) || Input::isPadButtonDown(Input::PAD_BUTTON_B);

	return isButtonPressed;
}

Vec2 GameInput::getMagChangeDir()
{
	float horizontal = getHorizontal();
	float vertical = getVertical();

	//スティックの傾きが大きい方を返す
	if (std::fabsf(horizontal) > std::fabsf(vertical))
		return Vec2(MathUtility::sign(horizontal), 0);
	else
		return Vec2(0, MathUtility::sign(vertical));
}

bool GameInput::isJump()
{
	return Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A);
}

bool GameInput::isPause()
{
	return Input::isKeyDown(VK_ESCAPE) || Input::isPadButtonDown(Input::PAD_BUTTON_START);
}
