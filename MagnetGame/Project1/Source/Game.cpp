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
	TextureManager::loadTexture(L"Assets/Textures/white.png", "white");
	TextureManager::loadTexture(L"Assets/Textures/N.png", "n");
	TextureManager::loadTexture(L"Assets/Textures/superjumpeffect.png", "superjumpeffect");
	TextureManager::loadTexture(L"Assets/Textures/mageffect.png", "mageffect");
	TextureManager::loadTexture(L"Assets/Textures/yagi.png", "yagi");
	TextureManager::loadTexture(L"Assets/Textures/op.png", "opening");

	//マップ系
	TextureManager::loadTexture(L"Assets/Textures/n_mag_block.png", "NBlock");
	TextureManager::loadTexture(L"Assets/Textures/n_block_stop.png", "NBlockStop");
	TextureManager::loadTexture(L"Assets/Textures/s_mag_block.png", "SBlock");
	TextureManager::loadTexture(L"Assets/Textures/s_block_stop.png", "SBlockStop");

	TextureManager::loadTexture(L"Assets/Textures/Cross.png", "Cross");

	TextureManager::loadTexture(L"Assets/Textures/BlockTest.png", "BlockTest");
	TextureManager::loadTexture(L"Assets/Textures/op2.png", "opening2");
	TextureManager::loadTexture(L"Assets/Textures/haikei1.png", "haikei1-1");
	TextureManager::loadTexture(L"Assets/Textures/haikei1-2.png", "haikei1-2");
	TextureManager::loadTexture(L"Assets/Textures/haikei1-3.png", "haikei1-3");
	TextureManager::loadTexture(L"Assets/Textures/haikei2.png", "haikei2");
	TextureManager::loadTexture(L"Assets/Textures/haikei3.png", "haikei3");
	TextureManager::loadTexture(L"Assets/Textures/title.png", "title");

	//画像テキスト
	TextureManager::loadTexture(L"Assets/Textures/log_arrow.png", "log_arrow");
	TextureManager::loadTexture(L"Assets/Textures/log_hakase.png", "log_hakase");
	TextureManager::loadTexture(L"Assets/Textures/log_hakase_black.png", "log_hakase_black");
	TextureManager::loadTexture(L"Assets/Textures/log_player.png", "log_player");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text0.png", "text0");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text1.png", "text1");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text2.png", "text2");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text3.png", "text3");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text4.png", "text4");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text5.png", "text5");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text6.png", "text6");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text7.png", "text7");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text8.png", "text8");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text9.png", "text9");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text10.png", "text10");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text11.png", "text11");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text12.png", "text12");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text13.png", "text13");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text14.png", "text14");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text15.png", "text15");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text16.png", "text16");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text17.png", "text17");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text18.png", "text18");

	//Pause
	TextureManager::loadTexture(L"Assets/Textures/Pause/howto.png", "howto");
	TextureManager::loadTexture(L"Assets/Textures/Pause/pause.png", "pause");
	TextureManager::loadTexture(L"Assets/Textures/Pause/Punch_Ex.png", "Punch_Ex");
	TextureManager::loadTexture(L"Assets/Textures/Pause/Mag_Ex.png", "Mag_Ex");
	TextureManager::loadTexture(L"Assets/Textures/Pause/N_Ex.png", "N_Ex");
	TextureManager::loadTexture(L"Assets/Textures/Pause/Jump_Ex.png", "Jump_Ex");
	TextureManager::loadTexture(L"Assets/Textures/Pause/check.png", "check");
	TextureManager::loadTexture(L"Assets/Textures/Pause/check2.png", "check2");
	TextureManager::loadTexture(L"Assets/Textures/Pause/check3.png", "check3");
	TextureManager::loadTexture(L"Assets/Textures/Pause/check4.png", "check4");

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
	SoundManager::loadWavFile(L"Assets/Sound/BGM/wind.wav", "wind");

	//SE追加
	SoundManager::loadWavFile(L"Assets/Sound/SE/Jump.wav", "jump");
	SoundManager::loadWavFile(L"Assets/Sound/SE/S_Jump.wav", "S_jump");
	SoundManager::loadWavFile(L"Assets/Sound/SE/punch.wav", "punch");
	SoundManager::loadWavFile(L"Assets/Sound/SE/MagChange.wav", "MagChange");
	SoundManager::loadWavFile(L"Assets/Sound/SE/bike.wav", "bike");
	SoundManager::loadWavFile(L"Assets/Sound/SE/kettei.wav", "kettei");
	SoundManager::loadWavFile(L"Assets/Sound/SE/door.wav", "door");

	GameDevice::initialize();
	m_GameEndFlag = false;

	m_pSceneManager = new SceneManager();
	m_pSceneManager->addScene("Title", new Title());
	m_pSceneManager->addScene("Entrance", new Entrance());
	m_pSceneManager->addScene("GamePlay", new GamePlay());
	m_pSceneManager->addScene("Ending", new Ending());

	m_pSceneManager->changeScene("Ending");

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
