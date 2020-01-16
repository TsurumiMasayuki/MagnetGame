#pragma once
#include "Utility\State\IState.h"
#include "Actor/Effect/SuperJumpEffect.h"

class Player;
class Gravity;

class PlayerState_SuperJump
	: public IState
{
public:
	PlayerState_SuperJump(Player* pPlayer);

	virtual void update() override;
	virtual void onStateEnter() override;
	virtual void onStateExit() override;
	virtual IState * nextState() override;

private:
	Player* m_pPlayer;
	Gravity* m_pGravity;

	SuperJumpEffect* superJumpEffect;

	float m_JumpForce;
	static const float MAX_JUMP_FORCE;
};