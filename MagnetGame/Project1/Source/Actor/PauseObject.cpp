#include "PauseObject.h"
#include "Component\SpriteRenderer.h"
#include"Device/Input.h"
#include"Device/GameTime.h"

PauseObject::PauseObject(IGameMediator * pMediator)
	:GameObject(pMediator)
{
	setSize(Vec3(1280, 720, 0));
	sprite = new SpriteRenderer(this, 101);
	sprite->setTextureName("pause");

	check = new SpriteRenderer(this, 102);
	check->setTextureName("check");


	checkNum = 0;
	pNum = 0;
	selectNum = 2;
	prevY = 0;
	currentY = Input::getLStickValue().y;
	isPause = true;
	isEndFlag = false;
}

PauseObject::~PauseObject()
{
}

void PauseObject::start()
{
}

void PauseObject::update()
{
	GameTime::timeScale = 0.0f;
	if (isPause) {
		switch (pNum)
		{
		case 0:
			sprite->setTextureName("pause");

			if (Input::isPadButtonDown(Input::PAD_BUTTON_A) || Input::isKeyDown(VK_SPACE)) {
				switch (checkNum)
				{
				case 0:
					setActive(false);
					break;
				case 1:
					//リスタート
					setActive(false);
					break;
				case 2:
					pNum = 1;
					checkNum = 0;
					selectNum = 2;
					break;
				case 3:
					setActive(false);
					isEndFlag = true;
					break;
				default:
					break;
				}
			}

			break;
		case 1:
			sprite->setTextureName("howto");
			if (selectNum > 5) {
				selectNum = 2;
			}
			else if (selectNum < 2) {
				selectNum = 5;
			}

			if (Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A)) {
				pNum = selectNum;
			}
			if (Input::isPadButtonDown(Input::PAD_BUTTON_B)||Input::isKeyDown(VK_BACK)) {
				pNum = 0;
				checkNum = 0;
				selectNum = 2;
			}
			break;
		case 2:
			sprite->setTextureName("Mag_Ex");
			if (Input::isPadButtonDown(Input::PAD_BUTTON_B) || Input::isKeyDown(VK_BACK)) {
				pNum = 1;
				checkNum = 0;
				selectNum = 2;
			}
			break;
		case 3:
			sprite->setTextureName("Punch_Ex");
			if (Input::isPadButtonDown(Input::PAD_BUTTON_B) || Input::isKeyDown(VK_BACK)) {
				pNum = 1;
				checkNum = 0;
				selectNum = 2;
			}
			break;
		case 4:
			sprite->setTextureName("N_Ex");
			if (Input::isPadButtonDown(Input::PAD_BUTTON_B) || Input::isKeyDown(VK_BACK)) {
				pNum = 1;
				checkNum = 0;
				selectNum = 2;
			}
			break;
		case 5:
			sprite->setTextureName("Jump_Ex");
			if (Input::isPadButtonDown(Input::PAD_BUTTON_B) || Input::isKeyDown(VK_BACK)) {
				pNum = 1;
				checkNum = 0;
				selectNum = 2;
			}
			break;
		}
		switch (checkNum)
		{
		case 0:
			check->setTextureName("check");
			break;
		case 1:
			check->setTextureName("check2");
			break;
		case 2:
			check->setTextureName("check3");
			break;
		case 3:
			check->setTextureName("check4");
			break;
		default:
			break;
		}
#pragma region パッド処理
		currentY = Input::getLStickValue().y;
		if (Input::getLStickValue().y > 0) {
			if (prevY == 0) {
				checkNum--;
				selectNum++;
			}
		}
		else if (Input::getLStickValue().y < 0) {
			if (prevY == 0) {
				checkNum++;
				selectNum--;
			}
		}
#pragma endregion

#pragma region キー入力
		if (Input::isKeyDown(VK_DOWN)) {
			checkNum++;
			selectNum++;
		}
		else if (Input::isKeyDown(VK_UP)) {
			checkNum--;
			selectNum--;
		}
#pragma endregion



		prevY = currentY;

		if (checkNum < 0) {
			checkNum = 3;
		}
		else if (checkNum > 3) {
			checkNum = 0;
		}
	}
}

void PauseObject::onDestroy()
{
}

void PauseObject::setNum(int value)
{
	pNum = value;
}

void PauseObject::setPause(bool value)
{
	isPause = value;
}

bool PauseObject::IsEnd()
{
	return isEndFlag;
}
