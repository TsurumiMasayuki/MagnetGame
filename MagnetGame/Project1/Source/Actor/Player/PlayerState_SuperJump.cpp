#include "PlayerState_SuperJump.h"

#include "Device\GameTime.h"

#include "Actor\Player\Player.h"
#include "Component\Physics\Gravity.h"

#include "Device\Input.h"
#include "Device\SoundManager.h"
#include "PlayerState_Default.h"
#include "PlayerState_MagChange.h"

const float PlayerState_SuperJump::MAX_JUMP_FORCE = 500.0f;

PlayerState_SuperJump::PlayerState_SuperJump(Player* pPlayer)
	: m_pPlayer(pPlayer), m_pGravity(pPlayer->getGravity())
{
	SoundManager::playSE("S_jump",0);
}

void PlayerState_SuperJump::update()
{
}

void PlayerState_SuperJump::onStateEnter()
{
	m_pPlayer->SetJumpForce(MAX_JUMP_FORCE);
}

void PlayerState_SuperJump::onStateExit()
{
}

IState * PlayerState_SuperJump::nextState()
{
	if (MAX_JUMP_FORCE / 2 >= m_pPlayer->GetJumpForce() && m_pPlayer->isDetectDown())
		return new PlayerState_Default(m_pPlayer);
	if (m_pPlayer->GetJumpForce() <= 0 || m_pPlayer->isDetectUp())
		return new PlayerState_Default(m_pPlayer);
	if (Input::isKeyDown('Z'))
		return new PlayerState_MagChange(m_pPlayer);

	return nullptr;
}
