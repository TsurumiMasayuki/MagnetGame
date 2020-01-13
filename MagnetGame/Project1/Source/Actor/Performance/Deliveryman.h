#pragma once

#include"Actor/GameObject.h"

class StateManager;
class Gravity;
class DetectHelper;

class Deliveryman:
	public GameObject
{
public:
	Deliveryman(IGameMediator* nMediator);
	~Deliveryman();

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;


	bool IsEnd();
private:

	static const float MOVE_SPEED;
	bool isEndFlag;
	bool m_pMove;
	enum State
	{
		Idle,
		Move,
		Anim,
	};
	State state;
};