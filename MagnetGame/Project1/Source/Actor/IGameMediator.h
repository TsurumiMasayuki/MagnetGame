#pragma once

class GameObject;
class PhysicsWorld;
class ForceMap;

class IGameMediator
{
public:
	virtual void addGameObject(GameObject* pAddObject) = 0;
	virtual void removeGameObject(GameObject* pRemoveObject) = 0;

	virtual PhysicsWorld* getPhysicsWorld() = 0;

	virtual ForceMap* getNMap() = 0;
	virtual ForceMap* getSMap() = 0;

protected:
	IGameMediator() {};
	virtual ~IGameMediator() {};
};