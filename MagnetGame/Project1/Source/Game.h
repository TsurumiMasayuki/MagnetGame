#pragma once

#include "Actor\GameObjectManager.h"
#include "Actor/Effect/CircleEffect.h"
#include "Scene\AbstractScene.h"
#include "Actor\IGameMediator.h"
#include "Physics\PhysicsWorld.h"
#include "Math\Vec2.h"

class Tilemap;
class Player;
class SceneManager;

class Game
{
public:
	Game();
	~Game();

	void init();
	void update();
	void draw();
	void shutdown();

private:
	GameObjectManager* m_pGameObjectManager;
	PhysicsWorld* m_pPhysicsWorld;
	SceneManager* m_pSceneManager;

	Tilemap* m_pTilemap;

	ForceMap* m_pNMapWrite;
	ForceMap* m_pSMapWrite;

	ForceMap* m_pNMapRead;
	ForceMap* m_pSMapRead;

	ObstacleMap* m_pObstacleMap;
	Player* m_pPlayer;
  
	CircleEffect* circleEffect;
	bool m_GameEndFlag;
	Vec2 m_CurrentStage;
};

