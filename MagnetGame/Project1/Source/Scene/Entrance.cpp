#include "Entrance.h"
#include "Device\Input.h"
#include"Actor/GameObjectManager.h"
#include "Physics\PhysicsWorld.h"
#include"Actor/Performance/TitleBackGround.h"

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
	m_pEntranceEndFlag = false;
}

void Entrance::update()
{
	if (Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A)) {
		m_pEntranceEndFlag = true;
	}
	m_pGameObjectManager->update();
	m_pPhysicsWorld->update();
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
