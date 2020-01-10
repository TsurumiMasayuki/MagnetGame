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

	m_CurrentStage = Vec2(1, 1);

	m_pTilemap = new Tilemap(this, 32, 32);
	m_pTilemap->setPosition(Vec3(40 * 32 / -2, 23 * 32 / 2, 0));
	m_pTilemap->load("Assets/CSV/alpha" + std::to_string((int)m_CurrentStage.x) + "-" + std::to_string((int)m_CurrentStage.y) + ".csv");

	m_pObstacleMap = new ObstacleMap(32, 32, m_pTilemap->getColumn(), m_pTilemap->getRow());
	m_pObstacleMap->setPosition(m_pTilemap->getPosition().toVec2());

	m_pNMapRead = new ForceMap(32, 32, m_pTilemap->getColumn(), m_pTilemap->getRow(), m_pObstacleMap);
	m_pNMapRead->setPosition(m_pTilemap->getPosition().toVec2());

	m_pNMapWrite = new ForceMap(32, 32, m_pTilemap->getColumn(), m_pTilemap->getRow(), m_pObstacleMap);
	m_pNMapWrite->setPosition(m_pTilemap->getPosition().toVec2());

	m_pSMapRead = new ForceMap(32, 32, m_pTilemap->getColumn(), m_pTilemap->getRow(), m_pObstacleMap);
	m_pSMapRead->setPosition(m_pTilemap->getPosition().toVec2());

	m_pSMapWrite = new ForceMap(32, 32, m_pTilemap->getColumn(), m_pTilemap->getRow(), m_pObstacleMap);
	m_pSMapWrite->setPosition(m_pTilemap->getPosition().toVec2());

	m_GameEndFlag = false;
}

void GamePlay::update()
{
	if (Input::isKeyDown('R'))
	{
		delete m_pTilemap;

		m_pGameObjectManager->update();

		m_pTilemap = new Tilemap(this, 32, 32);
		m_pTilemap->setPosition(Vec3(40 * 32 / -2, 23 * 32 / 2, 0));
		m_pTilemap->load("Assets/CSV/alpha" + std::to_string((int)m_CurrentStage.x) + "-" + std::to_string((int)m_CurrentStage.y) + ".csv");

		m_pPlayer->Respawn();
	}

	//ゲームが終了していたらオブジェクトの更新を止める
	if (m_GameEndFlag)
		return;

	if (m_pPlayer->getPosition().x > Screen::getWindowWidth() / 2) {
		delete m_pTilemap;
		m_CurrentStage.y++;

		m_pGameObjectManager->update();

		//障害物マップをクリア
		m_pObstacleMap->clear();

		m_pTilemap = new Tilemap(this, 32, 32);
		m_pTilemap->setPosition(Vec3(40 * 32 / -2, 23 * 32 / 2, 0));
		m_pTilemap->load("Assets/CSV/alpha" + std::to_string((int)m_CurrentStage.x) + "-" + std::to_string((int)m_CurrentStage.y) + ".csv");

		m_pPlayer->setPosition(m_pPlayer->getPosition() - Vec3(Screen::getWindowWidth(), 0, 0));
	}
	if (m_pPlayer->getPosition().x < -Screen::getWindowWidth() / 2) {
		delete m_pTilemap;
		m_CurrentStage.y--;

		m_pGameObjectManager->update();

		//障害物マップをクリア
		m_pObstacleMap->clear();

		m_pTilemap = new Tilemap(this, 32, 32);
		m_pTilemap->setPosition(Vec3(40 * 32 / -2, 23 * 32 / 2, 0));
		m_pTilemap->load("Assets/CSV/alpha" + std::to_string((int)m_CurrentStage.x) + "-" + std::to_string((int)m_CurrentStage.y) + ".csv");

		m_pPlayer->setPosition(m_pPlayer->getPosition() + Vec3(Screen::getWindowWidth(), 0, 0));
	}
	if (m_pPlayer->getPosition().y > Screen::getWindowHeight() / 2) {
		m_pPlayer->setPosition(m_pPlayer->getPosition() - Vec3(Screen::getWindowHeight(), 0, 0));
	}
	if (m_pPlayer->getPosition().y < -Screen::getWindowHeight() / 2) {
		m_pPlayer->setPosition(m_pPlayer->getPosition() + Vec3(Screen::getWindowHeight(), 0, 0));
	}

	//シーンの更新
	m_pGameObjectManager->update();

	m_pPhysicsWorld->update();

	m_pNMapRead->clear();
	m_pSMapRead->clear();

	m_pNMapWrite->copyTo(*m_pNMapRead);
	m_pSMapWrite->copyTo(*m_pSMapRead);

	m_pNMapWrite->clear();
	m_pSMapWrite->clear();
}

void GamePlay::draw()
{
}

void GamePlay::shutdown()
{
	delete m_pTilemap;

	delete m_pNMapRead;
	delete m_pSMapRead;

	delete m_pNMapWrite;
	delete m_pSMapWrite;

	delete m_pObstacleMap;

	delete m_pGameObjectManager;
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
	return m_pTilemap;
}

ForceMap * GamePlay::getNMapRead()
{
	return m_pNMapRead;
}

ForceMap * GamePlay::getSMapRead()
{
	return m_pSMapRead;
}

ForceMap * GamePlay::getNMapWrite()
{
	return m_pNMapWrite;
}

ForceMap * GamePlay::getSMapWrite()
{
	return m_pSMapWrite;
}

ObstacleMap * GamePlay::getObstacleMap()
{
	return m_pObstacleMap;
}

void GamePlay::gameEnd()
{
	m_GameEndFlag = true;
}
