#include "GamePlay.h"

#include "Actor\GameObjectManager.h"
#include "Actor\Player\Player.h"
#include "Actor\Tilemap\Tilemap.h"
#include "Actor\Magnet\ObstacleMap.h"
#include "Actor\Magnet\ForceMap.h"

#include "Component\Tilemap\Tile.h"

#include "Physics\PhysicsWorld.h"

#include "Device\Input.h"
#include "Def\Screen.h"
#include "Actor\Stage\Stage.h"

GamePlay::GamePlay()
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::init()
{
	m_pGameObjectManager = new GameObjectManager();

	m_pPhysicsWorld = new PhysicsWorld(this);

	m_pPlayer = new Player(this);
	m_pPlayer->SetRespawnPoint(Vec3(-450, -250, 0));
	m_pPlayer->Respawn();

	m_pCurrentStage = new Stage(this, 32, 32);
	m_pCurrentStage->setPosition(Vec3(40 * 32 / -2, 23 * 32 / 2, 0));
	m_pCurrentStage->load("Assets/CSV/alpha1-1.csv");
	m_GameEndFlag = false;
}

void GamePlay::update()
{
	if (Input::isKeyDown('R'))
	{
		//m_pCurrentStage->load("Assets/CSV/alpha1-1.csv");
	}

	/*if (Input::isKeyDown('R'))
	{
		delete m_pTilemap;

		m_pGameObjectManager->update();

		m_pTilemap = new Tilemap(this, 32, 32);
		m_pTilemap->setPosition(Vec3(40 * 32 / -2, 23 * 32 / 2, 0));
		m_pTilemap->load("Assets/CSV/alpha" + std::to_string((int)m_CurrentStage.x) + "-" + std::to_string((int)m_CurrentStage.y) + ".csv");

		m_pPlayer->Respawn();
	}*/

	//ゲームが終了していたらオブジェクトの更新を止める
	if (m_GameEndFlag)
		return;

	//if (m_pPlayer->getPosition().x > Screen::getWindowWidth() / 2) {
	//	delete m_pTilemap;
	//	m_CurrentStage.y++;

	//	m_pGameObjectManager->update();

	//	//障害物マップをクリア
	//	m_pObstacleMap->clear();

	//	m_pTilemap = new Tilemap(this, 32, 32);
	//	m_pTilemap->setPosition(Vec3(40 * 32 / -2, 23 * 32 / 2, 0));
	//	m_pTilemap->load("Assets/CSV/alpha" + std::to_string((int)m_CurrentStage.x) + "-" + std::to_string((int)m_CurrentStage.y) + ".csv");

	//	m_pPlayer->setPosition(m_pPlayer->getPosition() - Vec3(Screen::getWindowWidth(), 0, 0));
	//}
	//if (m_pPlayer->getPosition().x < -Screen::getWindowWidth() / 2) {
	//	delete m_pTilemap;
	//	m_CurrentStage.y--;

	//	m_pGameObjectManager->update();

	//	//障害物マップをクリア
	//	m_pObstacleMap->clear();

	//	m_pTilemap = new Tilemap(this, 32, 32);
	//	m_pTilemap->setPosition(Vec3(40 * 32 / -2, 23 * 32 / 2, 0));
	//	m_pTilemap->load("Assets/CSV/alpha" + std::to_string((int)m_CurrentStage.x) + "-" + std::to_string((int)m_CurrentStage.y) + ".csv");

	//	m_pPlayer->setPosition(m_pPlayer->getPosition() + Vec3(Screen::getWindowWidth(), 0, 0));
	//}
	//if (m_pPlayer->getPosition().y > Screen::getWindowHeight() / 2) {
	//	m_pPlayer->setPosition(m_pPlayer->getPosition() - Vec3(Screen::getWindowHeight(), 0, 0));
	//}
	//if (m_pPlayer->getPosition().y < -Screen::getWindowHeight() / 2) {
	//	m_pPlayer->setPosition(m_pPlayer->getPosition() + Vec3(Screen::getWindowHeight(), 0, 0));
	//}

	//シーンの更新
	m_pGameObjectManager->update();

	m_pPhysicsWorld->update();
}

void GamePlay::draw()
{
}

void GamePlay::shutdown()
{
	delete m_pGameObjectManager;
	delete m_pCurrentStage;
	//delete m_pNextStage;
	delete m_pPhysicsWorld;
}

std::string GamePlay::nextScene()
{
	return std::string();
}

bool GamePlay::isEnd()
{
	return false;
}

void GamePlay::addGameObject(GameObject * pAddObject)
{
	m_pGameObjectManager->add(pAddObject);
}

void GamePlay::removeGameObject(GameObject * pRemoveObject)
{
	m_pGameObjectManager->remove(pRemoveObject);
}

PhysicsWorld * GamePlay::getPhysicsWorld()
{
	return m_pPhysicsWorld;
}

Tilemap * GamePlay::getTilemap()
{
	return m_pCurrentStage->getTilemap();
}

ForceMap * GamePlay::getNMapRead()
{
	return m_pCurrentStage->getNMapRead();
}

ForceMap * GamePlay::getSMapRead()
{
	return m_pCurrentStage->getSMapRead();
}

ForceMap * GamePlay::getNMapWrite()
{
	return m_pCurrentStage->getNMapWrite();
}

ForceMap * GamePlay::getSMapWrite()
{
	return m_pCurrentStage->getSMapWrite();
}

ObstacleMap * GamePlay::getObstacleMap()
{
	return m_pCurrentStage->getObstacle();
}

void GamePlay::gameEnd()
{
	m_GameEndFlag = true;
}
