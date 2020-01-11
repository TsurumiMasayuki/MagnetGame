#include "Title.h"
#include "Device\Input.h"
#include"Actor/GameObjectManager.h"
#include"Actor/Performance/Deliveryman.h"
#include "Physics\PhysicsWorld.h"

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

	m_pDeliveryman = new Deliveryman(this);
	m_pDeliveryman->setPosition(Vec3(0,0,0));

	m_TitleEndFlag = false;
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
		if (m_pDeliveryman == NULL) {
			sState = SceneState::Player;
		}
		break;
	case Title::Player:

		break;
	case Title::Fade:

		break;
	}
	m_pGameObjectManager->update();
}

void Title::draw()
{
}

void Title::shutdown()
{
	delete m_pGameObjectManager;
}

std::string Title::nextScene()
{
	return "GamePlay";
}

bool Title::isEnd()
{
	return m_TitleEndFlag;
}

void Title::addGameObject(GameObject * pAddObject)
{
}

void Title::removeGameObject(GameObject * pRemoveObject)
{
}

PhysicsWorld * Title::getPhysicsWorld()
{
	return nullptr;
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
	m_TitleEndFlag = true;
}
