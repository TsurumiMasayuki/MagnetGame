#include "GameInput.h"
#include "Device\Input.h"

float GameInput::getHorizontal()
{
	float move = 0;
	if (Input::isKey(VK_LEFT) || Input::getLStickValue().x < 0)
	{
		move -= 1;
	}

	if (Input::isKey(VK_RIGHT) || Input::getLStickValue().x > 0)
	{
		move += 1;
	}

	return move;
}

float GameInput::getVertical()
{
	float move = 0;
	if (Input::isKey(VK_DOWN) || Input::getLStickValue().y < 0)
	{
		move -= 1;
	}

	if (Input::isKey(VK_UP) || Input::getLStickValue().y > 0)
	{
		move += 1;
	}

	return move;
}

bool GameInput::isMagChange()
{
	//S極パンチの方向入力がされていて、かつボタンも押されていたらTrue
	return (getHorizontal() != 0 || getVertical() != 0) &&
		((Input::isKey('Z')) || Input::isPadButton(Input::PAD_BUTTON_B));
}

Vec2 GameInput::getMagChangeDir()
{
	return Vec2(getHorizontal(), getVertical());
}

bool GameInput::isJump()
{
	return Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A);
}
