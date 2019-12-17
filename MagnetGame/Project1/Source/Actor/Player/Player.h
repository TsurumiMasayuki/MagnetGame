#pragma once
#include "Actor\GameObject.h"

class StateManager;
class Gravity;

class Player :
	public GameObject
{
public:
	Player(IGameMediator* pMediator);
	~Player();

	virtual void start() override;
	virtual void update() override;

	Gravity* getGravity();

private:
	StateManager* m_pStateManager;
	Gravity* m_pGravity;

	static const float MOVE_SPEED;
};