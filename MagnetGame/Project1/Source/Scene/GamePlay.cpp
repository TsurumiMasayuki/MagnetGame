#include "GamePlay.h"

#include "Actor\GameObjectManager.h"
#include "Actor\Player\Player.h"
#include "Actor\Tilemap\Tilemap.h"
#include "Actor\Magnet\ObstacleMap.h"
#include "Actor\Magnet\ForceMap.h"

#include "Component\Tilemap\Tile.h"

#include "Physics\PhysicsWorld.h"

#include "Device\Input.h"
#include"Device/GameTime.h"
#include "Def\Screen.h"
#include "Actor\Stage\Stage.h"
#include"Actor/PauseObject.h"
#include"Actor/Performance/TitleBackGround.h"

GamePlay::GamePlay()
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::init()
{
	m_CurrentStage = Vec2(1, 1);

	m_pGameObjectManager = new GameObjectManager();

	m_pPhysicsWorld = new PhysicsWorld(this);

	m_pPlayer = new Player(this);
	m_pPlayer->SetRespawnPoint(Vec3(-450, 250, 0));
	m_pPlayer->Respawn();

	m_pCurrentStage = new Stage(this, 32, 32);
	m_pCurrentStage->setPosition(Vec3(40 * 32 / -2, 23 * 32 / 2, 0));
	m_pCurrentStage->load("Assets/CSV/alpha" + std::to_string((int)m_CurrentStage.x) + "-" + std::to_string((int)m_CurrentStage.y) + ".csv");

	m_pBackGround = new TitleBackGround(this,"haikei6");
	m_pBackGround->setActive(true);

	m_pPause = new PauseObject(this);
	m_pPause->setActive(false);

	nScene = "Ending";

	m_GameEndFlag = false;
}

void GamePlay::update()
{
	if (Input::isKeyDown('R'))
	{
		m_pCurrentStage->clear();

		m_pGameObjectManager->update();

		delete m_pCurrentStage;

		m_pCurrentStage = new Stage(this, 32, 32);
		m_pCurrentStage->setPosition(Vec3(40 * 32 / -2, 23 * 32 / 2, 0));
		m_pCurrentStage->load("Assets/CSV/alpha" + std::to_string((int)m_CurrentStage.x) + "-" + std::to_string((int)m_CurrentStage.y) + ".csv");

		m_pPlayer->Respawn();
	}

	if (m_pPlayer->getPosition().x > Screen::getWindowWidth() / 2) {
		m_CurrentStage.y++;
		m_pCurrentStage->clear();

		m_pGameObjectManager->update();

		delete m_pCurrentStage;

		m_pCurrentStage = new Stage(this, 32, 32);
		m_pCurrentStage->setPosition(Vec3(40 * 32 / -2, 23 * 32 / 2, 0));
		m_pCurrentStage->load("Assets/CSV/alpha" + std::to_string((int)m_CurrentStage.x) + "-" + std::to_string((int)m_CurrentStage.y) + ".csv");

		m_pPlayer->setPosition(m_pPlayer->getPosition() - Vec3(Screen::getWindowWidth(), 0, 0));
		m_pPlayer->SetRespawnPoint(m_pPlayer->getPosition() + Vec3(50, 0, 0));
	}
	if (m_pPlayer->getPosition().x < -Screen::getWindowWidth() / 2) {
		m_CurrentStage.y--;
		m_pCurrentStage->clear();

		m_pGameObjectManager->update();

		delete m_pCurrentStage;

		m_pCurrentStage = new Stage(this, 32, 32);
		m_pCurrentStage->setPosition(Vec3(40 * 32 / -2, 23 * 32 / 2, 0));
		m_pCurrentStage->load("Assets/CSV/alpha" + std::to_string((int)m_CurrentStage.x) + "-" + std::to_string((int)m_CurrentStage.y) + ".csv");

		m_pPlayer->setPosition(m_pPlayer->getPosition() + Vec3(Screen::getWindowWidth(), 0, 0));
		m_pPlayer->SetRespawnPoint(m_pPlayer->getPosition() - Vec3(50, 0, 0));
	}

	//ポーズの処理
	Pause();

	//シーンの更新
	m_pGameObjectManager->update();

	m_pPhysicsWorld->update();

	m_pCurrentStage->update();
}

void GamePlay::draw()
{
}

void GamePlay::shutdown()
{
	delete m_pGameObjectManager;
	delete m_pCurrentStage;
	delete m_pPhysicsWorld;
}

std::string GamePlay::nextScene()
{
	return nScene;
}

bool GamePlay::isEnd()
{
	return m_GameEndFlag;
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

void GamePlay::Pause()
{
	if (!m_pPause->isActive()) {
		GameTime::timeScale = 1.0f;
		if (Input::isKeyDown(VK_ESCAPE) || Input::isPadButtonDown(Input::PAD_BUTTON_START)) {
			m_pPause->setActive(true);
			m_pPause->setReStart(false);
		}
	}
	else {

		if (m_pPause->getReStart()) {
			//↓リスタート時の処理を書いて

			m_pPause->setActive(false);
		}
	}

	if (m_pPause->IsEnd()) {
		nScene = "Title";
		m_GameEndFlag = true;
	}

}
