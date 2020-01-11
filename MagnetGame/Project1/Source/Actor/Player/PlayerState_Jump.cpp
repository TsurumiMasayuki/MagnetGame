#include "PlayerState_Jump.h"

#include "Device\GameTime.h"

#include "Actor\Player\Player.h"
#include "Component\Physics\Gravity.h"

#include "Device\GameInput.h"
#include "PlayerState_Default.h"
#include "PlayerState_MagChange.h"

const float PlayerState_Jump::MAX_JUMP_FORCE = 256.0f;

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
	m_pPlayer->setAnimation("Jump");
}

void PlayerState_Jump::onStateExit()
{
	m_pPlayer->setAnimation("Idle");
}

IState * PlayerState_Jump::nextState()
{
	if (MAX_JUMP_FORCE / 2 >= m_pPlayer->GetJumpForce() && m_pPlayer->isDetectDown())
		return new PlayerState_Default(m_pPlayer);
	if (m_pPlayer->GetJumpForce() <= 0 || m_pPlayer->isDetectUp())
		return new PlayerState_Default(m_pPlayer);
	if (GameInput::isMagChange())
		return new PlayerState_MagChange(m_pPlayer);

	return nullptr;
}
