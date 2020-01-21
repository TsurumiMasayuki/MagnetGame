#include "PlayerState_Default.h"
#include "Device\GameInput.h"
#include "Device\SoundManager.h"
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
	if (GameInput::getVertical() > 0 && GameInput::getHorizontal() == 0)
	{
		if (!m_pPlayer->isSuperJump)
			m_pPlayer->setAnimation("IdleUp");
		else
			m_pPlayer->setAnimation("GBIdleUp");
	}
	else if (GameInput::getVertical() < 0 && GameInput::getHorizontal() == 0)
	{
		if (!m_pPlayer->isSuperJump)
			m_pPlayer->setAnimation("IdleDown");
		else
			m_pPlayer->setAnimation("GBIdleDown");
	}
	else if (GameInput::getHorizontal() == 0)
	{
		if (!m_pPlayer->isSuperJump)
			m_pPlayer->setAnimation("Idle");
		else
			m_pPlayer->setAnimation("GBIdle");
	}
	else
	{
		if (!m_pPlayer->isSuperJump)
			m_pPlayer->setAnimation("Run");
		else
			m_pPlayer->setAnimation("GBRun");
	}
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
	if (GameInput::isJump() && m_pPlayer->isDetectDown())
	{
		if (m_pPlayer->canSuperJump())
			return new PlayerState_SuperJump(m_pPlayer);
		else
			SoundManager::playSE("jump", 0);
		return new PlayerState_Jump(m_pPlayer);
	}

	if (GameInput::isMagChange())
		return new PlayerState_MagChange(m_pPlayer);

	return nullptr;
}

