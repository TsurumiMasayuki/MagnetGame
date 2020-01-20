#pragma once
#include "AbstractScene.h"
#include "Actor\IGameMediator.h"

class GameObjectManager;
class TitleBackGround;
class EventText;
class TitlePlayer;

class Road:
	public AbstractScene,IGameMediator{
public:
	Road();
	~Road();

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
	TitlePlayer*m_pRoadPlayer;

	bool m_pRoadEndFlag;
};
