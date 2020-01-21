#include "Road.h"
#include "Device\Input.h"
#include "Device\GameTime.h"
#include"Actor/GameObjectManager.h"
#include "Physics\PhysicsWorld.h"
#include"Actor/Performance/EventText.h"
#include"Actor/Performance/TitleBackGround.h"
#include"Actor/Performance/TitlePlayer.h"

Road::Road()
{
}

Road::~Road()
{
}

void Road::init()
{
	m_pGameObjectManager = new GameObjectManager();
	m_pPhysicsWorld = new PhysicsWorld(this);

	m_pBackGround = new TitleBackGround(this, "haikei5");

	m_pRoadPlayer = new TitlePlayer(this);
	m_pRoadPlayer->setPosition(Vec3(-660, -280, 0));
	m_pRoadPlayer->setNum(3);

	m_pRoadEndFlag = false;
}

void Road::update()
{
	m_pRoadPlayer->setSize(Vec3(160, 160, 0));
	if (m_pRoadPlayer->getPosition().x >= 640) {
		m_pRoadEndFlag = true;
	}
	m_pGameObjectManager->update();
	m_pPhysicsWorld->update();
}

void Road::draw()
{
}

void Road::shutdown()
{
	delete m_pGameObjectManager;
	delete m_pPhysicsWorld;
}

std::string Road::nextScene()
{
	return "Entrance";
}

bool Road::isEnd()
{
	return m_pRoadEndFlag;
}

void Road::addGameObject(GameObject * pAddObject)
{
	m_pGameObjectManager->add(pAddObject);
}

void Road::removeGameObject(GameObject * pRemoveObject)
{
	m_pGameObjectManager->remove(pRemoveObject);
}

PhysicsWorld * Road::getPhysicsWorld()
{
	return nullptr;
}

Tilemap * Road::getTilemap()
{
	return nullptr;
}

ForceMap * Road::getNMapRead()
{
	return nullptr;
}

ForceMap * Road::getSMapRead()
{
	return nullptr;
}

ForceMap * Road::getNMapWrite()
{
	return nullptr;
}

ForceMap * Road::getSMapWrite()
{
	return nullptr;
}

ObstacleMap * Road::getObstacleMap()
{
	return nullptr;
}

void Road::gameEnd()
{
	m_pRoadEndFlag = true;
}
