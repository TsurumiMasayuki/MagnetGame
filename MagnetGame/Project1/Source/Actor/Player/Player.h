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
	virtual void onDestroy() override;

	Gravity* getGravity();
	GameObject* getMagChange();
	
private:
	void initMagChange();

private:
	StateManager* m_pStateManager;
	Gravity* m_pGravity;
	GameObject* m_pMagChange;

	static const float MOVE_SPEED;
};