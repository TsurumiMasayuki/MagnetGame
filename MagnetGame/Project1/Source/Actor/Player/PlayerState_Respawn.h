#pragma once
#include "Utility\State\IState.h"

class Player;

class PlayerState_Respawn
	: public IState
{
public:
	PlayerState_Respawn(Player* pPlayer);

	virtual void update() override;
	virtual void onStateEnter() override;
	virtual void onStateExit() override;
	virtual IState * nextState() override;

private:
	Player* m_pPlayer;

	float m_UnscaledTime;
};