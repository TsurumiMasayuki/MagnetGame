#include "PauseObject.h"
#include "Component\SpriteRenderer.h"
#include"Device/Input.h"
#include"Device/GameTime.h"
#include"Device/SoundManager.h"

PauseObject::PauseObject(IGameMediator * pMediator)
	:GameObject(pMediator)
{
	setSize(Vec3(1280, 720, 0));
	sprite = new SpriteRenderer(this, 148);
	sprite->setTextureName("pause");

	check = new SpriteRenderer(this, 149);
	check->setTextureName("check");

	back = new SpriteRenderer(this, 150);
	back->setTextureName("Back");
	
	pState = PauseState::Pause;

	checkNum = 0;
	pNum = 0;
	selectNum = 2;
	prevY = 0;
	currentY = Input::getLStickValue().y;
	isPause = true;
	isReStart = false;
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
			check->setActive(true);

			if (Input::isPadButtonDown(Input::PAD_BUTTON_X) || Input::isKeyDown(VK_SPACE)) {
				SoundManager::playSE("pause");
				switch (checkNum)
				{
				case 0:
					exit();
					break;
				case 1:
					//リスタート
					exit();
					isReStart = true;
					break;
				case 2://ルール
					pState = PauseState::HowTo;
					pNum = 1;
					checkNum = 0;
					selectNum = 2;
					break;
				case 3://ソウサ
					//sprite->setTextureName("");
					pNum = 6;
					break;
				case 4://タイトルへ
					setActive(false);
					isEndFlag = true;
					SoundManager::playSE("pause");
					break;
				default:
					break;
				}
			}

			if (Input::isPadButtonDown(Input::PAD_BUTTON_B) || Input::isKeyDown(VK_BACK)) {
				exit();
			}

			break;
		case 1:
			sprite->setTextureName("howto");
			check->setActive(true);
			if (selectNum > 5) {
				selectNum = 2;
			}
			else if (selectNum < 2) {
				selectNum = 5;
			}

			if (Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_X)) {
				SoundManager::playSE("pause");
				pNum = selectNum;
			}
			if (Input::isPadButtonDown(Input::PAD_BUTTON_B)||Input::isKeyDown(VK_BACK)) {
				SoundManager::playSE("cancel");
				pNum = 0;
				checkNum = 0;
				selectNum = 2;
				pState = PauseState::Pause;
			}
			break;
		case 2:
			sprite->setTextureName("Mag_Ex");
			check->setActive(false);
			if (Input::isPadButtonDown(Input::PAD_BUTTON_B) || Input::isKeyDown(VK_BACK)) {
				SoundManager::playSE("cancel");
				pNum = 1;
				checkNum = 0;
				selectNum = 2;
			}
			break;
		case 3:
			sprite->setTextureName("Punch_Ex");
			check->setActive(false);
			if (Input::isPadButtonDown(Input::PAD_BUTTON_B) || Input::isKeyDown(VK_BACK)) {
				SoundManager::playSE("cancel");
				pNum = 1;
				checkNum = 0;
				selectNum = 2;
			}
			break;
		case 4:
			sprite->setTextureName("N_Ex");
			check->setActive(false);
			if (Input::isPadButtonDown(Input::PAD_BUTTON_B) || Input::isKeyDown(VK_BACK)) {
				SoundManager::playSE("cancel");
				pNum = 1;
				checkNum = 0;
				selectNum = 2;
			}
			break;
		case 5:
			sprite->setTextureName("Jump_Ex");
			check->setActive(false);
			if (Input::isPadButtonDown(Input::PAD_BUTTON_B) || Input::isKeyDown(VK_BACK)) {
				SoundManager::playSE("cancel");
				pNum = 1;
				checkNum = 0;
				selectNum = 2;
			}
			break;
		case 6:
			sprite->setTextureName("sousa");
			check->setActive(false);
			if (Input::isPadButtonDown(Input::PAD_BUTTON_B) || Input::isKeyDown(VK_BACK)) {
				SoundManager::playSE("cancel");
				pNum = 0;
				checkNum = 0;
				selectNum = 2;
				pState = PauseState::Pause;
			}
			break;
		}
		if (pState == PauseState::Pause) {
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
			case 4:
				check->setTextureName("check5");
				break;
			default:
				break;
			}
		}
		if(pState==PauseState::HowTo){
			switch (checkNum)
			{
			case 0:
				check->setTextureName("check6");
				break;
			case 1:
				check->setTextureName("check7");
				break;
			case 2:
				check->setTextureName("check8");
				break;
			case 3:
				check->setTextureName("check9");
				break;
			default:
				break;
			}
		}
#pragma region パッド処理
		currentY = Input::getLStickValue().y;
		if (Input::getLStickValue().y > 0) {
			if (prevY == 0) {
				checkNum--;
				selectNum--;
				SoundManager::playSE("pause");
			}
		}
		else if (Input::getLStickValue().y < 0) {
			if (prevY == 0) {
				checkNum++;
				selectNum++;
				SoundManager::playSE("pause");
			}
		}
#pragma endregion

#pragma region キー入力
		if (Input::isKeyDown(VK_DOWN)) {
			checkNum++;
			selectNum++;
			SoundManager::playSE("pause");
		}
		else if (Input::isKeyDown(VK_UP)) {
			checkNum--;
			selectNum--;
			SoundManager::playSE("pause");
		}
#pragma endregion

		switch (pState)
		{
		case PauseObject::Pause:
			if (checkNum < 0) {
				checkNum = 4;
			}
			else if (checkNum > 4) {
				checkNum = 0;
			}
			break;
		case PauseObject::HowTo:
			if (checkNum < 0) {
				checkNum = 3;
			}
			else if (checkNum > 3) {
				checkNum = 0;
			}
			break;
		case PauseObject::None:
			break;
		default:
			break;
		}


		prevY = currentY;

	}
}

void PauseObject::onDestroy()
{
}

void PauseObject::exit()
{
	SoundManager::playSE("cancel");
	setActive(false);
	GameTime::timeScale = 1.0f;
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

bool PauseObject::getReStart()
{
	return isReStart;
}

void PauseObject::setReStart(bool value)
{
	isReStart = value;
}
