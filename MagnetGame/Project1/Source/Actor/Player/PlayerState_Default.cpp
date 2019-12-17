#include "PlayerState_Default.h"
#include "Device\Input.h"
#include "Actor\Player\Player.h"
#include "Actor\Player\PlayerState_Jump.h"
#include "Component\Physics\Gravity.h"

PlayerState_Default::PlayerState_Default(Player * pPlayer)
	: m_pPlayer(pPlayer), m_pGravity(pPlayer->getGravity())
{
}

void PlayerState_Default::update()
{
}

void PlayerState_Default::onStateEnter()
{
}

void PlayerState_Default::onStateExit()
{
}

IState * PlayerState_Default::nextState()
{
	if (Input::isKeyDown(VK_SPACE) && m_pGravity->isGround())
		return new PlayerState_Jump(m_pPlayer);

	return nullptr;
}

