#include "PlayerState_Jump.h"

#include "Device\GameTime.h"

#include "Actor\Player\Player.h"
#include "Component\Physics\Gravity.h"

#include "Device\GameInput.h"
#include "PlayerState_Default.h"
#include "PlayerState_MagChange.h"

const float PlayerState_Jump::MAX_JUMP_FORCE = 384.0f;

PlayerState_Jump::PlayerState_Jump(Player* pPlayer)
	: m_pPlayer(pPlayer), m_pGravity(pPlayer->getGravity())
{
}

void PlayerState_Jump::update()
{
}

void PlayerState_Jump::onStateEnter()
{
	m_pPlayer->SetJumpForce(MAX_JUMP_FORCE);
	if (!m_pPlayer->isSuperJump)
		m_pPlayer->setAnimation("Jump");
	else
		m_pPlayer->setAnimation("GBJump");
}

void PlayerState_Jump::onStateExit()
{
	if (!m_pPlayer->isSuperJump)
		m_pPlayer->setAnimation("Idle");
	else
		m_pPlayer->setAnimation("GBIdle");
}

IState * PlayerState_Jump::nextState()
{
	if (MAX_JUMP_FORCE / 2 >= m_pPlayer->GetJumpForce() && m_pPlayer->isDetectDown())
		return new PlayerState_Default(m_pPlayer);
	if (m_pPlayer->GetJumpForce() <= 0)
		return new PlayerState_Default(m_pPlayer);
	if (MAX_JUMP_FORCE / 2 >= m_pPlayer->GetJumpForce() && m_pPlayer->isDetectUp())
		return new PlayerState_Default(m_pPlayer);
	if (GameInput::isMagChange())
		return new PlayerState_MagChange(m_pPlayer);

	return nullptr;
}
