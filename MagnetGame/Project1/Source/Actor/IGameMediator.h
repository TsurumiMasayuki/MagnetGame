#pragma once

class GameObject;
class Tilemap;
class PhysicsWorld;
class ForceMap;
class ObstacleMap;

class IGameMediator
{
public:
	virtual void addGameObject(GameObject* pAddObject) = 0;
	virtual void removeGameObject(GameObject* pRemoveObject) = 0;

	virtual PhysicsWorld* getPhysicsWorld() = 0;

	virtual Tilemap* getTilemap() = 0;

	virtual ForceMap* getNMapRead() = 0;
	virtual ForceMap* getSMapRead() = 0;

	virtual ForceMap* getNMapWrite() = 0;
	virtual ForceMap* getSMapWrite() = 0;

	virtual ObstacleMap* getObstacleMap() = 0;

protected:
	IGameMediator() {};
	virtual ~IGameMediator() {};
};