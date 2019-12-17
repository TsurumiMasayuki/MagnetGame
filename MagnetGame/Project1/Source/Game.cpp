#include "Game.h"
#include <Windows.h>

#include "Actor\GameObject.h"
#include "Actor\Test\TestObject.h"
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

	//auto testObj = new TestObject(this);

	new Player(this);

	//auto block = new Block(this, "BoxFill", 512.0f * 2, 64.0f);
	//block->setPosition(Vec3(256.0f, -120, 0));

	auto tilemap = new Tilemap(this, 32, 32);
	tilemap->setPosition(Vec3(40 * 32 / -2, 23 * 32 / 2, 0));
	tilemap->load("Assets/test.csv");

	m_pNMap = new ForceMap(32, 32, tilemap->getColumn(), tilemap->getRow());
	m_pNMap->setPosition(tilemap->getPosition().toVec2());

	m_pSMap = new ForceMap(32, 32, tilemap->getColumn(), tilemap->getRow());
	m_pSMap->setPosition(tilemap->getPosition().toVec2());

	TextureManager::loadTexture(L"Assets/Textures/CircleFill.png", "CircleFill");
	TextureManager::loadTexture(L"Assets/Textures/CircleOutline.png", "CircleOutline");
	TextureManager::loadTexture(L"Assets/Textures/BoxFill.png", "BoxFill");
	TextureManager::loadTexture(L"Assets/Textures/BoxOutline.png", "BoxOutline");

	GameDevice::initialize();
}

void Game::update()
{
	m_pNMap->clear();
	m_pSMap->clear();

	GameDevice::update();

	Input::update();
	SoundManager::update();

	//シーンの更新
	m_pGameObjectManager->update();

	m_pPhysicsWorld->update();
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

	delete m_pNMap;
	delete m_pSMap;
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

ForceMap * Game::getNMap()
{
	return m_pNMap;
}

ForceMap * Game::getSMap()
{
	return m_pSMap;
}
