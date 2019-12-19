#include "Game.h"
#include <Windows.h>

#include "Actor\GameObject.h"
#include "Actor\Player\Player.h"
#include "Actor\Tilemap\Block.h"
#include "Actor\Tilemap\Tilemap.h"
#include "Component\AbstractComponent.h"

#include "Device\DirectXManager.h"
#include "Device\GameDevice.h"
#include "Device\Renderer.h"

#include "Device\TextureManager.h"
#include "Device\SoundManager.h"

#include "Device\Input.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <DirectXColors.h>
#include "Device\Camera.h"
#include "Actor\Magnet\ForceMap.h"
#include "Actor\Magnet\ObstacleMap.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::init()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	m_pGameObjectManager = new GameObjectManager();

	m_pPhysicsWorld = new PhysicsWorld(this);

	auto player = new Player(this);
	//player->setPosition(Vec3(-640 + 96, -360 + 96, 0));

	auto tilemap = new Tilemap(this, 32, 32);
	tilemap->setPosition(Vec3(40 * 32 / -2, 23 * 32 / 2, 0));
	tilemap->load("Assets/CSV/test0.csv");

	m_pObstacleMap = new ObstacleMap(32, 32, tilemap->getColumn(), tilemap->getRow());
	m_pObstacleMap->setPosition(tilemap->getPosition().toVec2());

	m_pNMapRead = new ForceMap(32, 32, tilemap->getColumn(), tilemap->getRow(), m_pObstacleMap);
	m_pNMapRead->setPosition(tilemap->getPosition().toVec2());

	m_pNMapWrite = new ForceMap(32, 32, tilemap->getColumn(), tilemap->getRow(), m_pObstacleMap);
	m_pNMapWrite->setPosition(tilemap->getPosition().toVec2());

	m_pSMapRead = new ForceMap(32, 32, tilemap->getColumn(), tilemap->getRow(), m_pObstacleMap);
	m_pSMapRead->setPosition(tilemap->getPosition().toVec2());

	m_pSMapWrite = new ForceMap(32, 32, tilemap->getColumn(), tilemap->getRow(), m_pObstacleMap);
	m_pSMapWrite->setPosition(tilemap->getPosition().toVec2());

	TextureManager::loadTexture(L"Assets/Textures/CircleFill.png", "CircleFill");
	TextureManager::loadTexture(L"Assets/Textures/CircleOutline.png", "CircleOutline");
	TextureManager::loadTexture(L"Assets/Textures/BoxFill.png", "BoxFill");
	TextureManager::loadTexture(L"Assets/Textures/BoxOutline.png", "BoxOutline");

	GameDevice::initialize();
}

void Game::update()
{
	GameDevice::update();

	Input::update();
	SoundManager::update();

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

void Game::draw()
{
	GameDevice::getRenderer()->draw();
}

void Game::shutdown()
{
	delete m_pGameObjectManager;
	delete m_pPhysicsWorld;
	TextureManager::unLoadAll();
	GameDevice::shutdown();

	delete m_pNMapRead;
	delete m_pSMapRead;

	delete m_pNMapWrite;
	delete m_pSMapWrite;

	delete m_pObstacleMap;
}

void Game::addGameObject(GameObject * pAddObject)
{
	m_pGameObjectManager->add(pAddObject);
}

void Game::removeGameObject(GameObject * pRemoveObject)
{
	m_pGameObjectManager->remove(pRemoveObject);
}

PhysicsWorld * Game::getPhysicsWorld()
{
	return m_pPhysicsWorld;
}

ForceMap * Game::getNMapRead()
{
	return m_pNMapRead;
}

ForceMap * Game::getSMapRead()
{
	return m_pSMapRead;
}

ForceMap * Game::getNMapWrite()
{
	return m_pNMapWrite;
}

ForceMap * Game::getSMapWrite()
{
	return m_pSMapWrite;
}

ObstacleMap * Game::getObstacleMap()
{
	return m_pObstacleMap;
}
