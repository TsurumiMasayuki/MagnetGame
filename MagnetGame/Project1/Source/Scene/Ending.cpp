#include "Ending.h"
#include "Device\Input.h"
#include "Device\GameTime.h"
#include"Actor/GameObjectManager.h"
#include"Actor/PauseObject.h"
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

	m_pPause = new PauseObject(this);
	m_pPause->setActive(false);

	m_pTitleEndFlag = false;
}

void Ending::update()
{
	/*if (Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A)) {
		m_pTitleEndFlag = true;
	}*/
	if (Input::isKeyDown(VK_ESCAPE) || Input::isPadButtonDown(Input::PAD_BUTTON_START)) {
		m_pPause->setActive(true);
	}

	if (!m_pPause->isActive()) {
		GameTime::timeScale = 1.0f;
	}
	if (m_pPause->IsEnd()) {
		m_pTitleEndFlag = true;
	}

	m_pGameObjectManager->update();
	m_pPhysicsWorld->update();
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
