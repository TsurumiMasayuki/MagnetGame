#include "Entrance.h"
#include "Device\Input.h"
#include"Actor/GameObjectManager.h"
#include "Physics\PhysicsWorld.h"
#include"Actor/Performance/TitleBackGround.h"
#include"Actor/Performance/TitleFade.h"
#include"Actor/Performance/EventText.h"
#include"Actor/Performance/TitlePlayer.h"
#include"Actor/Performance/ButtonTex.h"
#include"Actor/Performance/Item.h"
#include"Actor/Performance/ExText.h"
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
	m_pTitlePlayer->setPosition(Vec3(-660, -235, 0));
	m_pTitlePlayer->setNum(1);

	m_pButton = new ButtonTex(this);
	m_pButton->setActive(false);

	m_pItem = new Item(this,"grobe");
	m_pItem->setPosition(Vec3(10,-267,0));

	m_pExText = new ExText(this, "Mag_Ex");
	m_pExText->setActive(false);

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

	float size = 0.5f;

	switch (state)
	{
	case Entrance::Idle:
		m_pTitlePlayer->setSize(Vec3(160, 160, 0));
		if (m_pTitlePlayer->getPosition().x >= -410) {
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
		m_pTitlePlayer->setCanMove(true);
		if (m_pTitlePlayer->getPosition().x <= 76 && m_pTitlePlayer->getPosition().x >=-76) {
			m_pButton->setActive(true);
			m_pButton->setPosition(Vec3(m_pTitlePlayer->getPosition().x, -100, 0));
			if (Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A)) {
				m_pButton->setActive(false);
				state = State::Small;
				m_pTitlePlayer->setIsGrobe(true);
				m_pTitlePlayer->setCanMove(false);
				m_pItem->setActive(false);
			}
		}
		else {
			m_pButton->setActive(false);
		}
		break;
	case Entrance::Small:
		m_pTitlePlayer->setSize(Vec3(m_pTitlePlayer->getSize().x-size,
			                         m_pTitlePlayer->getSize().y-size,
			                         0));
		m_pTitlePlayer->setPosition(Vec3(m_pTitlePlayer->getPosition().x,m_pTitlePlayer->getPosition().y-(size/2),0));

		if (m_pTitlePlayer->getSize().x <= 64) {
			state = State::Talk2;
			
		}

		break;
	case Entrance::Talk2:
		if (m_pText->getEventNum() <= 21) {
			m_pText->setActive(true);
			if (Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A)) {
				if (m_pText->getEventNum() != 21) {
					m_pText->addEventNum();
				}
				else {
					SoundManager::playBGM("game2");
					m_pText->addEventNum();
				}
			}
		}
		else if (m_pText->getEventNum() > 21) {
			m_pText->setActive(false);
			state = State::Move2;
		}
		if (m_pText->getEventNum() ==21 ) {
			m_pBackGround->setTextureName("haikei1-2");
		}
		break;
	case Entrance::Move2:

		if (m_pExText->getStateNum() == 0) {
			m_pExText->setActive(true);
			if (Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A)) {
				m_pExText->addStateNum();
				m_pExText->setActive(false);
				m_pTitlePlayer->setCanMove(true);
			}
		}
		else {
			if (m_pTitlePlayer->getPosition().x <= 635 && m_pTitlePlayer->getPosition().x >= 440) {
				m_pButton->setActive(true);
				m_pButton->setPosition(Vec3(m_pTitlePlayer->getPosition().x, -120, 0));
				if (Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A)) {
					m_pEntranceEndFlag = true;
				}
			}
			else {
				m_pButton->setActive(false);
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
