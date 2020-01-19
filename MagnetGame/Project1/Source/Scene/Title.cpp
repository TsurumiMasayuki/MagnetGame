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
#include "Actor/Performance/TitleHane.h"
#include "Actor/Performance/Title_Sprite.h"
#include"Actor/Performance/Letter.h"
#include "Actor/Effect/Title_Cloud.h"
#include"Device/SoundManager.h"
#include "Utility/Timer.h"
#include "Actor/Effect/SmokeEffect.h"

Title::Title()
{
}

Title::~Title()
{
	delete timer;
	delete smoketimer;
	delete title_cloud;
	delete smokeEffect;
}

void Title::init()
{
	sState = SceneState::Idle;
	m_pGameObjectManager = new GameObjectManager();
	m_pPhysicsWorld = new PhysicsWorld(this);

	m_pBackGround = new TitleBackGround(this, "op_house");

	m_pFade = new TitleFade(this);
	m_pFade->setActive(false);	
	
	m_pTitleLogo = new TitleLogo(this, "title");
	m_pTitleLogo->setSize(Vec3(620, 130, 0));
	m_pTitleLogo->setPosition(Vec3(-250, 240, 0));

	m_pDeliveryman = new Deliveryman(this);
	m_pDeliveryman->setPosition(Vec3(640, -135, 0));

	m_pTitlePlayer = new TitlePlayer(this);
	m_pTitlePlayer->setNum(0);
	m_pTitlePlayer->setPosition(Vec3(-160,  -135, 0));
	m_pTitlePlayer->setActive(false);

	m_pText = new EventText(this);
	m_pText->setActive(false);
	m_pText->setEventNum(0);

	hane = new TitleHane(this);
	hane->setPosition(Vec3(310,120, 0));

	title_sprite = new Title_Sprite(this);
	title_sprite->setPosition(Vec3(0, 0, 0));

	m_pTitleEndFlag = false;

	timer = new Timer(3);
	smoketimer = new Timer(1);
	
	title_cloud = new Title_Cloud(this);
	title_cloud->Cleate(0.1f, 30, 0, 2);

	smokeEffect = new SmokeEffect(this);
	smokeEffect->Cleate(Vec3(-310, 100, 0),3,0.5f,2);

	m_pLetter = new Letter(this);
	m_pLetter->setPosition(Vec3(105,-120,0));
	m_pLetter->setActive(false);

	Cnt = 0;
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
		if (m_pDeliveryman->getPosition().x <= 105) {
			m_pLetter->setActive(true);
		}
		if (m_pTitleLogo->getAlpha() <= 0.0f) {
			m_pTitleLogo->setActive(false);
		}
		if (m_pDeliveryman->isDestroy()) {
			SoundManager::playSE("door");
			m_pBackGround->setTextureName("op_house_open");
			sState = SceneState::Player;
		}
		break;
	case Title::Player:

		m_pTitlePlayer->setActive(true);

		if (m_pTitlePlayer->getPosition().x >= 90) {
			m_pLetter->setActive(false); 
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
		Cnt++;
		if (m_pTitlePlayer->IsEnd()&&Cnt<=120) {
			m_pTitleLogo->setFade(false);
		}

		if (m_pTitlePlayer->getPosition().x >= 550&&Cnt <= 240) {
			m_pTitleLogo->setActive(true);
			m_pTitleLogo->setFade(false);
			m_pFade->setActive(true);
		}

		if (m_pTitleLogo->isActive()) {
			if (m_pTitleLogo->getAlpha() >= 1.0f) {
				m_pTitleLogo->setFade(true);
			}
			if (m_pTitleLogo->getFade()) {
				if (m_pTitleLogo->getAlpha() <0.0f) {
					m_pTitleEndFlag = true;
				}
			}
		}

		if (m_pFade->isEnd()) {
			//m_pTitleEndFlag = true;
		}
		break;
	}

	m_pGameObjectManager->update();
	m_pPhysicsWorld->update();

	timer->update();
	smoketimer->update();
	if (timer->isTime()) {
		title_cloud->Cleate(0.1f, 30, 0, 2);
		timer->reset();
	}
	if (smoketimer->isTime()) {
		smokeEffect->Cleate(Vec3(-310, 100, 0), 3, 0.5f, 2);
		smoketimer->reset();
	}
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
