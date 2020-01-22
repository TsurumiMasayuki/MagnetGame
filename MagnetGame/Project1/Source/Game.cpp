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
#include"Scene/Road.h"
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
	TextureManager::loadTexture(L"Assets/Textures/A.png", "A");
	TextureManager::loadTexture(L"Assets/Textures/X.png", "X");
	TextureManager::loadTexture(L"Assets/Textures/N.png", "n");
	TextureManager::loadTexture(L"Assets/Textures/CircleFill.png", "CircleFill");
	TextureManager::loadTexture(L"Assets/Textures/CircleOutline.png", "CircleOutline");
	TextureManager::loadTexture(L"Assets/Textures/BoxFill.png", "BoxFill");
	TextureManager::loadTexture(L"Assets/Textures/BoxOutline.png", "BoxOutline");
	TextureManager::loadTexture(L"Assets/Textures/smoke.png", "smoke");
	TextureManager::loadTexture(L"Assets/Textures/white.png", "white");
	TextureManager::loadTexture(L"Assets/Textures/superjumpeffect.png", "superjumpeffect");
	TextureManager::loadTexture(L"Assets/Textures/mageffect.png", "mageffect");
	TextureManager::loadTexture(L"Assets/Textures/yagi.png", "yagi");
	TextureManager::loadTexture(L"Assets/Textures/Back.png", "Back");
	TextureManager::loadTexture(L"Assets/Textures/letter.png", "letter");
	TextureManager::loadTexture(L"Assets/Textures/PushA.png", "PushA");
	TextureManager::loadTexture(L"Assets/Textures/PushA_Ending.png", "PushA_E");
	TextureManager::loadTexture(L"Assets/Textures/rog_name.png", "Name");
	TextureManager::loadTexture(L"Assets/Textures/log_name_player.png", "lop");
	TextureManager::loadTexture(L"Assets/Textures/log_name_doctor.png", "beard");
	TextureManager::loadTexture(L"Assets/Textures/kanban.png", "kanban");

#pragma region 背景
	TextureManager::loadTexture(L"Assets/Textures/background/haikei1.png", "haikei1-0");
	TextureManager::loadTexture(L"Assets/Textures/background/haikei1-4.png", "haikei1-1");
	TextureManager::loadTexture(L"Assets/Textures/background/haikei1-2.png", "haikei1-2");
	TextureManager::loadTexture(L"Assets/Textures/background/haikei1-3.png", "haikei1-3");
	TextureManager::loadTexture(L"Assets/Textures/background/haikei2.png", "haikei2");
	TextureManager::loadTexture(L"Assets/Textures/background/haikei3.png", "haikei3");
	TextureManager::loadTexture(L"Assets/Textures/background/haikei4.png", "haikei4");
	TextureManager::loadTexture(L"Assets/Textures/background/haikei5.png", "haikei5");
	TextureManager::loadTexture(L"Assets/Textures/background/haikei6.png", "haikei6");
	TextureManager::loadTexture(L"Assets/Textures/background/ending.png", "ending");
	TextureManager::loadTexture(L"Assets/Textures/background/ending_open.png", "ending_open");
	TextureManager::loadTexture(L"Assets/Textures/background/fin.png", "fin");
#pragma endregion

#pragma region Opening
	TextureManager::loadTexture(L"Assets/Textures/opening/op_background.png", "op_background");
	TextureManager::loadTexture(L"Assets/Textures/opening/op_house.png", "op_house");
	TextureManager::loadTexture(L"Assets/Textures/opening/op_house_open.png", "op_house_open");
	TextureManager::loadTexture(L"Assets/Textures/opening/op_tree.png", "op_tree");
	TextureManager::loadTexture(L"Assets/Textures/opening/op_huusya.png", "op_huusya");
	TextureManager::loadTexture(L"Assets/Textures/opening/op_hane.png", "hane");
	TextureManager::loadTexture(L"Assets/Textures/opening/cloud1.png", "cloud1");
	TextureManager::loadTexture(L"Assets/Textures/opening/cloud2.png", "cloud2");
	TextureManager::loadTexture(L"Assets/Textures/opening/title.png", "title");
#pragma endregion

#pragma region マップ系
	TextureManager::loadTexture(L"Assets/Textures/n_mag_block.png", "NBlock");
	TextureManager::loadTexture(L"Assets/Textures/n_block_stop.png", "NBlockStop");
	TextureManager::loadTexture(L"Assets/Textures/s_mag_block.png", "SBlock");
	TextureManager::loadTexture(L"Assets/Textures/s_block_stop.png", "SBlockStop");
	TextureManager::loadTexture(L"Assets/Textures/Cross.png", "Cross");
	TextureManager::loadTexture(L"Assets/Textures/fieldblock.png", "BlockTest");
#pragma endregion

#pragma region テキスト
	TextureManager::loadTexture(L"Assets/Textures/log_arrow.png", "log_arrow");
	TextureManager::loadTexture(L"Assets/Textures/log_arrow_A.png", "log_arrow_A");
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
	TextureManager::loadTexture(L"Assets/Textures/Performance/text19.png", "text19");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text20.png", "text20");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text21.png", "text21");

	TextureManager::loadTexture(L"Assets/Textures/Performance/text30.png", "text30");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text31.png", "text31");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text32.png", "text32");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text33.png", "text33");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text34.png", "text34");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text35.png", "text35");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text36.png", "text36");

	TextureManager::loadTexture(L"Assets/Textures/Performance/text50.png", "text50");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text51.png", "text51");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text52.png", "text52");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text53.png", "text53");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text54.png", "text54");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text55.png", "text55");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text56.png", "text56");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text57.png", "text57");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text58.png", "text58");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text59.png", "text59");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text60.png", "text60");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text61.png", "text61");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text62.png", "text62");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text63.png", "text63");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text64.png", "text64");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text65.png", "text65");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text66.png", "text66");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text67.png", "text67");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text68.png", "text68");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text69.png", "text69");
	TextureManager::loadTexture(L"Assets/Textures/Performance/text70.png", "text70");
#pragma endregion

#pragma region Pause
	TextureManager::loadTexture(L"Assets/Textures/Pause/howto.png", "howto");
	TextureManager::loadTexture(L"Assets/Textures/Pause/pause.png", "pause");
	TextureManager::loadTexture(L"Assets/Textures/Pause/sousa.png", "sousa");
	TextureManager::loadTexture(L"Assets/Textures/Pause/sousa_Text.png", "sousa_Text");
	TextureManager::loadTexture(L"Assets/Textures/Pause/Punch_Ex.png", "Punch_Ex");
	TextureManager::loadTexture(L"Assets/Textures/Pause/Punch_Ex_Text.png", "Punch_Ex_Text");
	TextureManager::loadTexture(L"Assets/Textures/Pause/Mag_Ex.png", "Mag_Ex");
	TextureManager::loadTexture(L"Assets/Textures/Pause/Mag_Ex_Text.png", "Mag_Ex_Text");
	TextureManager::loadTexture(L"Assets/Textures/Pause/N_Ex.png", "N_Ex");
	TextureManager::loadTexture(L"Assets/Textures/Pause/N_Ex_Text.png", "N_Ex_Text");
	TextureManager::loadTexture(L"Assets/Textures/Pause/Jump_Ex.png", "Jump_Ex");
	TextureManager::loadTexture(L"Assets/Textures/Pause/Jump_Ex_Text.png", "Jump_Ex_Text");
	TextureManager::loadTexture(L"Assets/Textures/Pause/check.png", "check");
	TextureManager::loadTexture(L"Assets/Textures/Pause/check2.png", "check2");
	TextureManager::loadTexture(L"Assets/Textures/Pause/check3.png", "check3");
	TextureManager::loadTexture(L"Assets/Textures/Pause/check4.png", "check4");
	TextureManager::loadTexture(L"Assets/Textures/Pause/check5.png", "check5");
	TextureManager::loadTexture(L"Assets/Textures/Pause/check6.png", "check6");
	TextureManager::loadTexture(L"Assets/Textures/Pause/check7.png", "check7");
	TextureManager::loadTexture(L"Assets/Textures/Pause/check8.png", "check8");
	TextureManager::loadTexture(L"Assets/Textures/Pause/check9.png", "check9");
#pragma endregion

#pragma region プレイヤー
	TextureManager::loadTexture(L"Assets/Textures/Player/player_idle_right.png", "PlayerIdle");
	TextureManager::loadTexture(L"Assets/Textures/Player/player_run_right.png", "PlayerRun");
	TextureManager::loadTexture(L"Assets/Textures/Player/player_jamp_right.png", "PlayerJump");
	TextureManager::loadTexture(L"Assets/Textures/Player/player_sjamp_right.png", "PlayerSJump");
	TextureManager::loadTexture(L"Assets/Textures/Player/player_panti_right.png", "PlayerPunch");
	TextureManager::loadTexture(L"Assets/Textures/Player/player_panti_up.png", "PlayerPunch_Up");
	TextureManager::loadTexture(L"Assets/Textures/Player/player_panti_down.png", "PlayerPunch_Down");
	TextureManager::loadTexture(L"Assets/Textures/Player/player_idle_up.png", "PlayerIdleUp");
	TextureManager::loadTexture(L"Assets/Textures/Player/player_idle_down.png", "PlayerIdleDown");
	//プレイヤー(何もない状態)
	TextureManager::loadTexture(L"Assets/Textures/FirstPlayer/player_idle_first_right.png", "FirstIdle");
	TextureManager::loadTexture(L"Assets/Textures/FirstPlayer/player_run_first_right.png", "FirstRun");
	//プレイヤー(グローブのみ)
	TextureManager::loadTexture(L"Assets/Textures/GlovePlayer/player_idle_glove.png", "GloveIdle");
	TextureManager::loadTexture(L"Assets/Textures/GlovePlayer/player_idle_up_glove.png", "GloveIdleUp");
	TextureManager::loadTexture(L"Assets/Textures/GlovePlayer/player_idle_down_glove.png", "GloveIdleDown");
	TextureManager::loadTexture(L"Assets/Textures/GlovePlayer/player_run_glove.png", "GloveRun");
	TextureManager::loadTexture(L"Assets/Textures/GlovePlayer/player_jump_glove.png", "GloveJump");
	TextureManager::loadTexture(L"Assets/Textures/GlovePlayer/player_punch_glove.png", "GlovePunch");
	TextureManager::loadTexture(L"Assets/Textures/GlovePlayer/player_punch_up_glove.png", "GlovePunch_Up");
	TextureManager::loadTexture(L"Assets/Textures/GlovePlayer/player_punch_down_glove.png", "GlovePunch_Down");
#pragma endregion

#pragma region アイテム
	TextureManager::loadTexture(L"Assets/Textures/glove.png", "grobe");
	TextureManager::loadTexture(L"Assets/Textures/boots.png", "boots");
#pragma endregion

#pragma region BGM
	SoundManager::loadWavFile(L"Assets/Sound/BGM/game.wav", "game");
	SoundManager::loadWavFile(L"Assets/Sound/BGM/game2.wav", "game2");
	SoundManager::loadWavFile(L"Assets/Sound/BGM/wind.wav", "wind");
	SoundManager::loadWavFile(L"Assets/Sound/BGM/ending.wav", "ending");
#pragma endregion

#pragma region SE
	SoundManager::loadWavFile(L"Assets/Sound/SE/Jump.wav", "jump");
	SoundManager::loadWavFile(L"Assets/Sound/SE/S_Jump.wav", "S_jump");
	SoundManager::loadWavFile(L"Assets/Sound/SE/punch.wav", "punch");
	SoundManager::loadWavFile(L"Assets/Sound/SE/MagChange.wav", "MagChange");
	SoundManager::loadWavFile(L"Assets/Sound/SE/bike.wav", "bike");
	SoundManager::loadWavFile(L"Assets/Sound/SE/kettei.wav", "kettei");
	SoundManager::loadWavFile(L"Assets/Sound/SE/door.wav", "door");
	SoundManager::loadWavFile(L"Assets/Sound/SE/open.wav", "open");
	SoundManager::loadWavFile(L"Assets/Sound/SE/walk.wav", "walk");
#pragma endregion

	GameDevice::initialize();
	m_GameEndFlag = false;

	m_pSceneManager = new SceneManager();
	m_pSceneManager->addScene("Title", new Title());
	m_pSceneManager->addScene("Road", new Road());
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
