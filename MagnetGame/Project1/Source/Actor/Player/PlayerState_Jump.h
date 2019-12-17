#pragma once
#include "Utility\State\IState.h"

class Player;
class Gravity;

class PlayerState_Jump
	: public IState
{
public:
	PlayerState_Jump(Player* pPlayer);

	virtual void update() override;
	virtual void onStateEnter() override;
	virtual void onStateExit() override;
	virtual IState * nextState() override;

private:
	Player* m_pPlayer;
	Gravity* m_pGravity;

	float m_JumpForce;
	static const float MAX_JUMP_FORCE;
	static const float MAX_SUPERJUMP_FORCE;
};