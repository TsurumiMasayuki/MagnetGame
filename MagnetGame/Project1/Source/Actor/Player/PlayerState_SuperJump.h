#pragma once
#include "Utility\State\IState.h"

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

	static const float MAX_SUPERJUMP_FORCE;
};