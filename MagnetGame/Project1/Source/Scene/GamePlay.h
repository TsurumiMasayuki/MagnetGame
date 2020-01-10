#pragma once
#include "AbstractScene.h"
#include "Actor\IGameMediator.h"
#include "Math\Vec2.h"

class GameObjectManager;
class Player;
class Stage;

class GamePlay :
	public AbstractScene, IGameMediator {
public:
	GamePlay();
	~GamePlay();
	virtual void init() override;
	virtual void update() override;
	virtual void draw() override;
	virtual void shutdown() override;
	virtual std::string nextScene() override;
	virtual bool isEnd() override;

	virtual void addGameObject(GameObject * pAddObject) override;
	virtual void removeGameObject(GameObject * pRemoveObject) override;
	virtual PhysicsWorld * getPhysicsWorld() override;
	virtual Tilemap * getTilemap() override;
	virtual ForceMap * getNMapRead() override;
	virtual ForceMap * getSMapRead() override;
	virtual ForceMap * getNMapWrite() override;
	virtual ForceMap * getSMapWrite() override;
	virtual ObstacleMap * getObstacleMap() override;
	virtual void gameEnd() override;

private:
	GameObjectManager* m_pGameObjectManager;
	PhysicsWorld* m_pPhysicsWorld;

	Player* m_pPlayer;

	bool m_GameEndFlag;
	Vec2 m_CurrentStage;

	Stage* m_pCurrentStage;
	Stage* m_pNextStage;
};