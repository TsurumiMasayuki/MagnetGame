#pragma once

#include "Actor\GameObjectManager.h"
#include "Scene\AbstractScene.h"
#include "Scene\SceneManager.h"
#include "Actor\IGameMediator.h"
#include "Physics\PhysicsWorld.h"

class ForceMap;

class Game :
	public IGameMediator
{
public:
	Game();
	~Game();

	void init();
	void update();
	void draw();
	void shutdown();

	virtual void addGameObject(GameObject* pAddObject) override;
	virtual void removeGameObject(GameObject * pRemoveObject) override;
	virtual PhysicsWorld * getPhysicsWorld() override;

	virtual ForceMap* getNMapRead() override;
	virtual ForceMap* getSMapRead() override;

	virtual ForceMap* getNMapWrite() override;
	virtual ForceMap* getSMapWrite() override;

private:
	GameObjectManager* m_pGameObjectManager;
	PhysicsWorld* m_pPhysicsWorld;
	SceneManager m_SceneManager;

	ForceMap* m_pNMapWrite;
	ForceMap* m_pSMapWrite;

	ForceMap* m_pNMapRead;
	ForceMap* m_pSMapRead;
};

