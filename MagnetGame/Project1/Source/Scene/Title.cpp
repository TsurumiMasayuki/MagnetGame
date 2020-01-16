#include "Title.h"
#include "Device\Input.h"
#include"Actor/GameObjectManager.h"
#include"Actor/Performance/Deliveryman.h"
#include"Actor/Performance/TitlePlayer.h"
#include "Physics\PhysicsWorld.h"
#include "Actor\Performance\TitleBackGround.h"
#include "Actor\Performance\TitleLogo.h"
#include"Actor/Performance/TitleFade.h"
#include"Actor/Performance/EventText.h"
#include"Device/SoundManager.h"

Title::Title()
{
}

Title::~Title()
{
}

void Title::init()
{
	sState = SceneState::Idle;
	m_pGameObjectManager = new GameObjectManager();
	m_pPhysicsWorld = new PhysicsWorld(this);

	m_pBackGround = new TitleBackGround(this, "opening");

	m_pFade = new TitleFade(this);
	m_pFade->setActive(false);	
	
	m_pTitleLogo = new TitleLogo(this, "title");
	m_pTitleLogo->setSize(Vec3(500, 125, 0));
	m_pTitleLogo->setPosition(Vec3(0, 240, 0));

	m_pDeliveryman = new Deliveryman(this);
	m_pDeliveryman->setPosition(Vec3(640, -95, 0));

	m_pTitlePlayer = new TitlePlayer(this);
	m_pTitlePlayer->setNum(0);
	m_pTitlePlayer->setPosition(Vec3(40,  -95, 0));
	m_pTitlePlayer->setActive(false);

	m_pText = new EventText(this);
	m_pText->setActive(false);
	m_pText->setEventNum(0);

	m_pTitleEndFlag = false;

	SoundManager::playBGM("wind");
}

void Title::update()
{

	switch (sState)
	{
	case Title::Idle:
		if (Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A)) {
			sState = SceneState::Delivery;
			m_pTitleLogo->setFade(true);
		}
		break;
	case Title::Delivery:

		if (m_pDeliveryman->isDestroy()) {
			SoundManager::playSE("door");
			m_pBackGround->setTextureName("opening2");
			sState = SceneState::Player;
		}
		break;
	case Title::Player:

		m_pTitlePlayer->setActive(true);

		if (m_pTitlePlayer->getPosition().x >= 200) {

			if (m_pText->getEventNum() <= 4) {
				m_pText->setActive(true);
				if (Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A)) {
					m_pText->addEventNum();
				}
			}
			else if (m_pText->getEventNum() > 4) {
				m_pText->setActive(false);
				m_pTitlePlayer->setIsGo(true);
				sState = SceneState::Fade;
			}
		}
		break;
	case Title::Fade:
		if (m_pTitlePlayer->IsEnd()) {
			m_pTitleLogo->setFade(false);
			m_pFade->setActive(true);
		}
		if (m_pFade->isEnd()) {
			m_pTitleEndFlag = true;
		}
		break;
	}

	m_pGameObjectManager->update();
	m_pPhysicsWorld->update();
}

void Title::draw()
{
}

void Title::shutdown()
{
	m_pTitlePlayer->destroy();
	SoundManager::stopBGM();
	delete m_pGameObjectManager;
	delete m_pPhysicsWorld;
}

std::string Title::nextScene()
{
	return "Entrance";
}

bool Title::isEnd()
{
	return m_pTitleEndFlag;
}

void Title::addGameObject(GameObject * pAddObject)
{
	m_pGameObjectManager->add(pAddObject);
}

void Title::removeGameObject(GameObject * pRemoveObject)
{
	m_pGameObjectManager->remove(pRemoveObject);
}

PhysicsWorld * Title::getPhysicsWorld()
{
	return m_pPhysicsWorld;
}

Tilemap * Title::getTilemap()
{
	return nullptr;
}

ForceMap * Title::getNMapRead()
{
	return nullptr;
}

ForceMap * Title::getSMapRead()
{
	return nullptr;
}

ForceMap * Title::getNMapWrite()
{
	return nullptr;
}

ForceMap * Title::getSMapWrite()
{
	return nullptr;
}

ObstacleMap * Title::getObstacleMap()
{
	return nullptr;
}

void Title::gameEnd()
{
	m_pTitleEndFlag = true;
}
