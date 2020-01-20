#pragma once
#include "AbstractScene.h"
#include "Actor\IGameMediator.h"

class GameObjectManager;
class TitleBackGround;
class EventText;
class TitlePlayer;
class TitleFade;

class Ending :
	public AbstractScene, IGameMediator {
public:
	Ending();
	~Ending();
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
	GameObjectManager*m_pGameObjectManager;
	PhysicsWorld* m_pPhysicsWorld;

	TitleBackGround*m_pBackGround;
	EventText*m_pText;
	TitlePlayer*m_pPlayer;
	TitleFade*m_pFade;

	enum EndingState
	{
		Open,
		Idle,
		Talk,
		Big,
		Talk2,
		Move,
	};

	EndingState eState;

	bool m_pTitleEndFlag;
	int Cnt;
};
