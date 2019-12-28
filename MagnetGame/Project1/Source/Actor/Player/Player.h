#pragma once
#include "Actor\GameObject.h"

class StateManager;
class Gravity;
class DetectHelper;

class Player :
	public GameObject
{
public:
	Player(IGameMediator* pMediator);
	~Player();

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;

	Gravity* getGravity();
	GameObject* getMagChange();
	
	bool isDetectUp();
	bool isDetectDown();
	bool isDetectRight();
	bool isDetectLeft();
	bool canSuperJump();

private:
	void initMagChange();
	void initDetectors();

public:
	bool isSuperJump;

private:
	StateManager* m_pStateManager;
	Gravity* m_pGravity;
	GameObject* m_pMagChange;

	DetectHelper* m_pDetectUp;
	DetectHelper* m_pDetectDown;
	DetectHelper* m_pDetectRight;
	DetectHelper* m_pDetectLeft;

	static const float MOVE_SPEED;
};