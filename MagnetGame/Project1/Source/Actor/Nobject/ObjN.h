#pragma once
#include"Actor/GameObject.h"

class StateManager;
class Gravity;
class DetectHelper;

class ObjN:
	public GameObject
{
public:
	ObjN(IGameMediator* nMediator,int dir);
	~ObjN();

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;

	Gravity * getGravity();
	GameObject*getMagChange();

	bool isDetectLeft();
	bool isDetectRight();

private:
	void initMagChange();
	void initDetectors();
private:
	//StateManager*m_nStateManager;
	Gravity * m_nGravity;
	GameObject*m_nMagChange;

	DetectHelper*m_nDetectRight;
	DetectHelper*m_nDetectLeft;

	static const float MOVE_SPEED;

	int direction;
};
