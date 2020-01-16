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
#include "Scene\Entrance.h"
#include "Scene\GamePlay.h"
#include "Scene\Ending.h"
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

	//画像のロード
	TextureManager::loadTexture(L"Assets/Textures/CircleFill.png", "CircleFill");
	TextureManager::loadTexture(L"Assets/Textures/CircleOutline.png", "CircleOutline");
	TextureManager::loadTexture(L"Assets/Textures/BoxFill.png", "BoxFill");
	TextureManager::loadTexture(L"Assets/Textures/BoxOutline.png", "BoxOutline");
	TextureManager::loadTexture(L"Assets/Textures/smoke.png", "smoke");
	TextureManager::loadTexture(L"Assets/Textures/title.png", "title");
	TextureManager::loadTexture(L"Assets/Textures/white.png", "white");
	TextureManager::loadTexture(L"Assets/Textures/N.png", "n");
	TextureManager::loadTexture(L"Assets/Textures/yagi.png", "yagi");
	TextureManager::loadTexture(L"Assets/Textures/op.png", "opening");

	//画像テキスト
	TextureManager::loadTexture(L"Assets/Textures/log_arrow.png", "log_arrow");
	TextureManager::loadTexture(L"Assets/Textures/log_hakase.png", "log_hakase");
	TextureManager::loadTexture(L"Assets/Textures/log_hakase_black.png", "log_hakase_black");
	TextureManager::loadTexture(L"Assets/Textures/log_player.png", "log_player");
	TextureManager::loadTexture(L"Assets/Textures/text0.png", "text0");
	TextureManager::loadTexture(L"Assets/Textures/text1.png", "text1");
	TextureManager::loadTexture(L"Assets/Textures/text2.png", "text2");
	TextureManager::loadTexture(L"Assets/Textures/text3.png", "text3");
	TextureManager::loadTexture(L"Assets/Textures/text4.png", "text4");

	//プレイヤー
	TextureManager::loadTexture(L"Assets/Textures/player_idle_right.png", "PlayerIdle");
	TextureManager::loadTexture(L"Assets/Textures/player_run_right.png", "PlayerRun");
	TextureManager::loadTexture(L"Assets/Textures/player_jamp_right.png", "PlayerJump");
	TextureManager::loadTexture(L"Assets/Textures/player_sjamp_right.png", "PlayerSJump");
	TextureManager::loadTexture(L"Assets/Textures/player_panti_right.png", "PlayerPunch");
	TextureManager::loadTexture(L"Assets/Textures/player_panti_up.png", "PlayerPunch_Up");
	TextureManager::loadTexture(L"Assets/Textures/player_panti_down.png", "PlayerPunch_Down");

	//BGM追加
	SoundManager::loadWavFile(L"Assets/Sound/BGM/game.wav", "game");
	SoundManager::loadWavFile(L"Assets/Sound/BGM/game2.wav", "game2");

	//SE追加
	SoundManager::loadWavFile(L"Assets/Sound/SE/Jump.wav", "jump");
	SoundManager::loadWavFile(L"Assets/Sound/SE/S_Jump.wav", "S_jump");
	SoundManager::loadWavFile(L"Assets/Sound/SE/punch.wav", "punch");
	SoundManager::loadWavFile(L"Assets/Sound/SE/MagChange.wav", "MagChange");

	GameDevice::initialize();
	m_GameEndFlag = false;

	m_pSceneManager = new SceneManager();
	m_pSceneManager->addScene("Title", new Title());
	m_pSceneManager->addScene("Entrance", new Entrance());
	m_pSceneManager->addScene("GamePlay", new GamePlay());
	m_pSceneManager->addScene("Ending", new Ending());
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
