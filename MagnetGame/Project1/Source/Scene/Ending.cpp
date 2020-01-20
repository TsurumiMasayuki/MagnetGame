#include "Ending.h"
#include "Device\Input.h"
#include "Device\GameTime.h"
#include"Device/SoundManager.h"
#include"Actor/GameObjectManager.h"
#include"Actor/Performance/TitleBackGround.h"
#include"Actor/Performance/EventText.h"
#include"Actor/Performance/TitlePlayer.h"
#include"Actor/Performance/TitleFade.h"
#include "Physics\PhysicsWorld.h"

Ending::Ending()
{
}

Ending::~Ending()
{
}

void Ending::init()
{
	m_pGameObjectManager = new GameObjectManager();
	m_pPhysicsWorld = new PhysicsWorld(this);

	m_pBackGround = new TitleBackGround(this, "ending");

	m_pText = new EventText(this);
	m_pText->setEventNum(50);
	m_pText->setActive(false);

	m_pPlayer = new TitlePlayer(this);
	m_pPlayer->setPosition(Vec3(-530,-260,0));
	m_pPlayer->setNum(4);
	m_pPlayer->setActive(false);

	m_pFade = new TitleFade(this);
	m_pFade->setActive(false);

	eState = EndingState::Open;
	Cnt = 0;
	m_pTitleEndFlag = false;
}

void Ending::update()
{
	m_pGameObjectManager->update();
	m_pPhysicsWorld->update();

	float size = 0.5f;

	
	switch (eState)
	{
	case Ending::Open:
		Cnt++;
		if (Cnt == 120) {
			SoundManager::playSE("open");
			m_pBackGround->setTextureName("ending_open");
		}
		if (Cnt >= 180) {
			eState = EndingState::Idle;
		}
		
		break;
	case Ending::Idle:
		m_pPlayer->setActive(true);
		if (m_pPlayer->getPosition().x >= -300) {
			eState = EndingState::Talk;
		}
		break;
	case Ending::Talk:
		m_pText->setActive(true);
		if (m_pText->getEventNum() <= 55) {
			m_pText->setActive(true);
			if (Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A)) {
				m_pText->addEventNum();
			}
		}
		else if (m_pText->getEventNum() > 55) {
			m_pText->setActive(false);
			eState = EndingState::Big;
		}
		break;
	case Ending::Big:
		m_pPlayer->setSize(Vec3(m_pPlayer->getSize().x + size,
			m_pPlayer->getSize().y + size,
			0));
		m_pPlayer->setPosition(Vec3(m_pPlayer->getPosition().x, m_pPlayer->getPosition().y + size / 2, 0));

		if (m_pPlayer->getSize().x>=160) {
			eState = EndingState::Talk2;
		}
		break;
	case Ending::Talk2:
		m_pText->setActive(true);
		if (m_pText->getEventNum() <= 60) {
			m_pText->setActive(true);
			if (Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A)) {
				m_pText->addEventNum();
			}
		}
		else if (m_pText->getEventNum() > 60) {
			m_pText->setActive(false);
			eState = EndingState::Move;
		}
		break;
	case Ending::Move:
		m_pFade->setActive(true);
		if (m_pFade->getAlpha() >= 5.0f) {
			m_pTitleEndFlag = true;
		}
		break;
	default:
		break;
	}
}

void Ending::draw()
{
}

void Ending::shutdown()
{
	GameTime::timeScale = 1.0f;
	delete m_pGameObjectManager;
	delete m_pPhysicsWorld;
}

std::string Ending::nextScene()
{
	return "Title";
}

bool Ending::isEnd()
{
	return m_pTitleEndFlag;
}

void Ending::addGameObject(GameObject * pAddObject)
{
	m_pGameObjectManager->add(pAddObject);
}

void Ending::removeGameObject(GameObject * pRemoveObject)
{
	m_pGameObjectManager->remove(pRemoveObject);
}

PhysicsWorld * Ending::getPhysicsWorld()
{
	return m_pPhysicsWorld;
}

Tilemap * Ending::getTilemap()
{
	return nullptr;
}

ForceMap * Ending::getNMapRead()
{
	return nullptr;
}

ForceMap * Ending::getSMapRead()
{
	return nullptr;
}

ForceMap * Ending::getNMapWrite()
{
	return nullptr;
}

ForceMap * Ending::getSMapWrite()
{
	return nullptr;
}

ObstacleMap * Ending::getObstacleMap()
{
	return nullptr;
}

void Ending::gameEnd()
{
	m_pTitleEndFlag = true;
}
