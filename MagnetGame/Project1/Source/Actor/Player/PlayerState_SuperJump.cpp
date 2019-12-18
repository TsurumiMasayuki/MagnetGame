#include "PlayerState_SuperJump.h"

const float PlayerState_SuperJump::MAX_SUPERJUMP_FORCE = 192.0f;

PlayerState_SuperJump::PlayerState_SuperJump(Player * pPlayer)
	: m_pPlayer(pPlayer)
{
}

void PlayerState_SuperJump::update()
{
}

void PlayerState_SuperJump::onStateEnter()
{

}

void PlayerState_SuperJump::onStateExit()
{
}

IState * PlayerState_SuperJump::nextState()
{
	return nullptr;
}
