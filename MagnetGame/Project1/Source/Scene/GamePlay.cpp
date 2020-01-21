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
#include"Device/SoundManager.h"
#include "Device\File\CSVReader.h"
#include "Def\Screen.h"
#include "Actor\Stage\Stage.h"
#include"Actor/PauseObject.h"
#include"Actor/Performance/TitleBackGround.h"
#include"Actor/Performance/EventText.h"
#include"Actor/Performance/FadeOut.h"
#include"Actor/Performance/TitleFade.h"

GamePlay::GamePlay()
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::init()
{
	m_CurrentStage = Vec2(1, 18);


	m_pGameObjectManager = new GameObjectManager();

	m_pPhysicsWorld = new PhysicsWorld(this);

	m_pPlayer = new Player(this);
	ReadRespawnData();
	m_pPlayer->Respawn();

	m_pCurrentStage = new Stage(this, 32, 32);
	m_pCurrentStage->setPosition(Vec3(40 * 32 / -2, 23 * 32 / 2, 0));
	m_pCurrentStage->load("Assets/CSV/alpha" + std::to_string((int)m_CurrentStage.x) + "-" + std::to_string((int)m_CurrentStage.y) + ".csv");

	m_pBackGround = new TitleBackGround(this, "haikei6");
	m_pBackGround->setActive(true);

	m_pPause = new PauseObject(this);
	m_pPause->setActive(false);

	m_pText = new EventText(this);
	m_pText->setEventNum(30);
	m_pText->setActive(false);

	m_pFadeIn = new TitleFade(this);
	m_pFadeIn->setActive(false);
	
	m_pFadeOut = new FadeOut(this);

	nScene = "Ending";

	NowStageNum = 0;
	m_GameEndFlag = false;
}

void GamePlay::update()
{
	if (Input::isKeyDown('R') || Input::isPadButtonDown(Input::PAD_BUTTON_Y) || m_pPause->getReStart() || m_pPlayer->isSandwich())
	{
		//ポーズの処理
		m_pPause->setReStart(false);
		m_pPause->setActive(false);

		m_pCurrentStage->clear();

		m_pGameObjectManager->update();

		delete m_pCurrentStage;

		m_pCurrentStage = new Stage(this, 32, 32);
		m_pCurrentStage->setPosition(Vec3(40 * 32 / -2, 23 * 32 / 2, 0));
		m_pCurrentStage->load("Assets/CSV/alpha" + std::to_string((int)m_CurrentStage.x) + "-" + std::to_string((int)m_CurrentStage.y) + ".csv");

		ReadRespawnData();
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

	if (m_CurrentStage.y == 18) {
		if (m_pPlayer->getPosition().x <= 350 && m_pPlayer->getPosition().x >= 280) {
			if (Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A)) {
				m_pFadeIn->setActive(true);
			}
		}
	}

	//ポーズの更新処理
	Pause();
	//テキストの更新処理
	TextUpdate();

	//フェード
	Fade();

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
	SoundManager::stopBGM();
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
		if (Input::isKeyDown(VK_ESCAPE) || Input::isPadButtonDown(Input::PAD_BUTTON_START)) {
			m_pPause->setActive(true);
			m_pPause->setReStart(false);
		}
	}

	if (m_pPause->IsEnd()) {
		nScene = "Title";
		m_GameEndFlag = true;
	}

}

void GamePlay::ReadRespawnData()
{
	CSVReader reader;
	reader.open("Assets/CSV/respawn.csv");

	for (unsigned int y = 0; y < reader.getRowCount(); y++)
	{
		for (unsigned int x = 0; x < reader.getColumnCount(y); x++)
		{
			int num = atoi(reader.getData(0, y).c_str());
			if (m_CurrentStage.y == num)
				m_pPlayer->SetRespawnPoint(Vec3(atoi(reader.getData(1, y).c_str()), atoi(reader.getData(2, y).c_str()), 0) * 32);
		}
	}

}

void GamePlay::Fade()
{
	if (m_pFadeOut->getAlpha() <= -2.0f) {
		m_pFadeOut->setActive(false);
	}

	if (m_pFadeIn->getAlpha() >= 2.0f) {
		m_GameEndFlag = true;
	}
}

void GamePlay::TextUpdate()
{
	NowStageNum = (int)m_CurrentStage.y;
	if (m_pPlayer->getPosition().x >= -600) {
		switch (NowStageNum)
		{
		case 4:
			if (m_pText->getEventNum() <= 33) {
				GameTime::timeScale = 0.0f;
				m_pText->setActive(true);
				if (Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A)) {
					m_pText->addEventNum();
				}
			}
			else if (m_pText->getEventNum() > 33) {
				m_pText->setActive(false);
				GameTime::timeScale = 1.0f;
			}
			break;
		case 6:
			if (m_pPlayer->isSuperJump) {
				if (m_pText->getEventNum() <= 36) {
					GameTime::timeScale = 0.0f;
					m_pText->setActive(true);
					if (Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A)) {
						m_pText->addEventNum();
					}
				}
				else if (m_pText->getEventNum() > 36) {
					m_pText->setActive(false);
					GameTime::timeScale = 1.0f;
				}
			}
			break;
		default:
			m_pText->setActive(false);
			break;
		}
	}
}


