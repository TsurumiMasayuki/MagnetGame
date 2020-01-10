#include "Game.h"
#include <Windows.h>

#include "Actor\GameObject.h"
#include "Actor\Player\Player.h"
#include "Actor/Nobject/ObjN.h"
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
#include "Actor\CheckPoint.h"
#include "Utility\Timer.h"
#include "Def\Screen.h"

#include "Scene\Title.h"
#include "Scene\GamePlay.h"
#include "Scene\SceneManager.h"

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

	TextureManager::loadTexture(L"Assets/Textures/CircleFill.png", "CircleFill");
	TextureManager::loadTexture(L"Assets/Textures/CircleOutline.png", "CircleOutline");
	TextureManager::loadTexture(L"Assets/Textures/BoxFill.png", "BoxFill");
	TextureManager::loadTexture(L"Assets/Textures/BoxOutline.png", "BoxOutline");
	TextureManager::loadTexture(L"Assets/Textures/smoke.png", "smoke");

	GameDevice::initialize();
	m_GameEndFlag = false;

	m_pSceneManager = new SceneManager();
	m_pSceneManager->addScene("Title", new Title());
	m_pSceneManager->addScene("GamePlay", new GamePlay());
	m_pSceneManager->changeScene("GamePlay");
}

void Game::update()
{
	GameDevice::update();

	Input::update();
	SoundManager::update();

	//ゲームが終了していたらオブジェクトの更新を止める
	if (m_GameEndFlag)
		return;

	m_pSceneManager->update();
}

void Game::draw()
{
	GameDevice::getRenderer()->draw();
}

void Game::shutdown()
{
	delete m_pSceneManager;
	TextureManager::unLoadAll();
	GameDevice::shutdown();
}
