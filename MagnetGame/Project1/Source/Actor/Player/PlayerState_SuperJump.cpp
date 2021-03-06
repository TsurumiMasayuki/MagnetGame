#include "PlayerState_SuperJump.h"

#include "Device\GameTime.h"

#include "Actor\Player\Player.h"
#include "Component\Physics\Gravity.h"
#include "Device\GameInput.h"
#include "Device\SoundManager.h"
#include "PlayerState_Default.h"
#include "PlayerState_MagChange.h"

const float PlayerState_SuperJump::MAX_JUMP_FORCE = 896.0f;

PlayerState_SuperJump::PlayerState_SuperJump(Player* pPlayer)
	: m_pPlayer(pPlayer), m_pGravity(pPlayer->getGravity())
{
	SoundManager::playSE("S_jump", 0);
	superJumpEffect = new SuperJumpEffect(pPlayer->getGameMediator());
	superJumpEffect->Cleate(pPlayer->getPosition(), 2, 3, 20);
	delete superJumpEffect;
}

void PlayerState_SuperJump::update()
{
}

void PlayerState_SuperJump::onStateEnter()
{
	m_pPlayer->SetJumpForce(MAX_JUMP_FORCE);
	m_pPlayer->setAnimation("GBSJump");
}

void PlayerState_SuperJump::onStateExit()
{
}

IState * PlayerState_SuperJump::nextState()
{
	if (MAX_JUMP_FORCE / 2 >= m_pPlayer->GetJumpForce() && m_pPlayer->isDetectDown())
		return new PlayerState_Default(m_pPlayer);
	if (m_pPlayer->GetJumpForce() <= 0)
		return new PlayerState_Default(m_pPlayer);
	if (MAX_JUMP_FORCE / 4 >= m_pPlayer->GetJumpForce() && m_pPlayer->isDetectUp())
		return new PlayerState_Default(m_pPlayer);
	if (m_pPlayer->isDetectUp() && m_pPlayer->isDetectDown())
		return new PlayerState_Default(m_pPlayer);
	if (GameInput::isMagChange())
		return new PlayerState_MagChange(m_pPlayer);

	return nullptr;
}
