#include "Title.h"
#include "Device\Input.h"
#include"Actor/GameObjectManager.h"
#include"Actor/Performance/Deliveryman.h"
#include"Actor/Performance/TitlePlayer.h"
#include "Physics\PhysicsWorld.h"
#include "Component\SpriteRenderer.h"
#include "Actor\Performance\TitleBackGround.h"
#include"Actor/Performance/TitleFade.h"

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

	m_pBackGround = new TitleBackGround(this);
	m_pFade = new TitleFade(this);
	m_pFade->setActive(false);

	m_pDeliveryman = new Deliveryman(this);
	m_pDeliveryman->setPosition(Vec3(640, 0, 0));

	m_pTitlePlayer = new TitlePlayer(this);
	m_pTitlePlayer->setActive(false);



	m_pTitleEndFlag = false;
}

void Title::update()
{

	switch (sState)
	{
	case Title::Idle:
		if (Input::isKeyDown(VK_SPACE)) {
			sState = SceneState::Delivery;
		}
		break;
	case Title::Delivery:
		if (m_pDeliveryman->isDestroy()) {
			sState = SceneState::Player;
		}
		break;
	case Title::Player:
		m_pTitlePlayer->setActive(true);
		if (m_pTitlePlayer->IsEnd()) {
			sState = SceneState::Fade;
		}
		break;
	case Title::Fade:
		m_pFade->setActive(true);
		
		m_pTitleEndFlag = true;
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
	delete m_pGameObjectManager;
	delete m_pPhysicsWorld;
}

std::string Title::nextScene()
{
	return "GamePlay";
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
