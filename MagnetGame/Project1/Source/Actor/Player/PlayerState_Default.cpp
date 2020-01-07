#include "PlayerState_Default.h"
#include "Device\Input.h"
#include "Actor\Player\Player.h"
#include "Actor\Player\PlayerState_Jump.h"
#include "Actor\Player\PlayerState_SuperJump.h"
#include "Actor\Player\PlayerState_MagChange.h"
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
	m_pPlayer->SetJumpForce(0);
}

void PlayerState_Default::onStateExit()
{
}

IState * PlayerState_Default::nextState()
{
	if (Input::isKeyDown(VK_SPACE) && m_pPlayer->isDetectDown())
	{
		if (m_pPlayer->canSuperJump())
			return new PlayerState_SuperJump(m_pPlayer);
		else
			return new PlayerState_Jump(m_pPlayer);
	}

	if (Input::isKeyDown('Z'))
		return new PlayerState_MagChange(m_pPlayer);

	return nullptr;
}

