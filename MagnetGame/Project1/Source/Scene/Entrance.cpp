#include "Entrance.h"
#include "Device\Input.h"
#include"Actor/GameObjectManager.h"
#include "Physics\PhysicsWorld.h"
#include"Actor/Performance/TitleBackGround.h"
#include"Actor/Performance/TitleFade.h"
#include"Actor/Performance/EventText.h"
#include"Actor/Performance/TitlePlayer.h"
#include"Device/SoundManager.h"


Entrance::Entrance()
{
}

Entrance::~Entrance()
{
}

void Entrance::init()
{
	m_pGameObjectManager = new GameObjectManager();
	m_pPhysicsWorld = new PhysicsWorld(this);
	m_pBackGround = new TitleBackGround(this, "haikei1-3");

	m_pText = new EventText(this);
	m_pText->setEventNum(5);
	m_pText->setActive(false);

	m_pTitlePlayer = new TitlePlayer(this);
	m_pTitlePlayer->setPosition(Vec3(-660, -283, 0));
	m_pTitlePlayer->setNum(1);

	state = State::Idle;

	m_pEntranceEndFlag = false;
}

void Entrance::update()
{
	if (Input::isKeyDown('Q') || Input::isPadButtonDown(Input::PAD_BUTTON_Y)) {
		//m_pEntranceEndFlag = true;
	}
	m_pGameObjectManager->update();
	m_pPhysicsWorld->update();

	switch (state)
	{
	case Entrance::Idle:
		if (Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A)) {
			state = State::Talk;
			m_pText->setEventNum(5);
		}
		break;
	case Entrance::Talk:
		if (m_pText->getEventNum() <= 9) {
			m_pText->setActive(true);
			if (Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A)) {
				m_pText->addEventNum();
			}
		}
		else if (m_pText->getEventNum() > 9) {
			m_pText->setActive(false);
			state = State::Move;
		}

		if (m_pText->getEventNum() == 7) {
			m_pBackGround->setTextureName("haikei1-1");
		}

		break;
	case Entrance::Move:
		m_pTitlePlayer->setNum(2);
		if (Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A)) {
			state = State::Talk2;
		}
		break;
	case Entrance::Talk2:
		if (m_pText->getEventNum() <= 18) {
			m_pText->setActive(true);
			if (Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A)) {
				if (m_pText->getEventNum() != 16) {
					m_pText->addEventNum();
				}
				else {
					SoundManager::playBGM("game2");
					m_pText->addEventNum();
				}
			}
		}
		else if (m_pText->getEventNum() > 18) {
			m_pText->setActive(false);
			state = State::Move2;
		}
		if (m_pText->getEventNum() ==18 ) {
			m_pBackGround->setTextureName("haikei1-2");
		}
		break;
	case Entrance::Move2:
		if (m_pTitlePlayer->getPosition().x <= 635 && m_pTitlePlayer->getPosition().x >= 585) {
			if (Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A)) {
				m_pEntranceEndFlag = true;
			}
		}
		break;
	default:
		break;
	}
}

void Entrance::draw()
{
}

void Entrance::shutdown()
{
	delete m_pGameObjectManager;
	delete m_pPhysicsWorld;
}

std::string Entrance::nextScene()
{
	return "GamePlay";
}

bool Entrance::isEnd()
{
	return m_pEntranceEndFlag;
}

void Entrance::addGameObject(GameObject * pAddObject)
{
	m_pGameObjectManager->add(pAddObject);
}

void Entrance::removeGameObject(GameObject * pRemoveObject)
{
	m_pGameObjectManager->remove(pRemoveObject);
}

PhysicsWorld * Entrance::getPhysicsWorld()
{
	return m_pPhysicsWorld;
}

Tilemap * Entrance::getTilemap()
{
	return nullptr;
}

ForceMap * Entrance::getNMapRead()
{
	return nullptr;
}

ForceMap * Entrance::getSMapRead()
{
	return nullptr;
}

ForceMap * Entrance::getNMapWrite()
{
	return nullptr;
}

ForceMap * Entrance::getSMapWrite()
{
	return nullptr;
}

ObstacleMap * Entrance::getObstacleMap()
{
	return nullptr;
}

void Entrance::gameEnd()
{
	m_pEntranceEndFlag = true;
}
