#pragma once
#include "Utility\State\IState.h"
#include "Math\Vec3.h"

class GameObject;
class Player;
class Timer;

class PlayerState_MagChange
	: public IState
{
public:
	PlayerState_MagChange(Player* pPlayer);

	virtual void update() override;
	virtual void onStateEnter() override;
	virtual void onStateExit() override;
	virtual IState * nextState() override;

private:
	Player* m_pPlayer;
	GameObject* m_pMagChange;
	Vec3 m_MagChangeDir;
	Timer* m_pTimer;
};