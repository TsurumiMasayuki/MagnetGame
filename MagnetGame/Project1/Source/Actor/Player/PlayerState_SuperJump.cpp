#include "PlayerState_SuperJump.h"

#include "Device\GameTime.h"

#include "Actor\Player\Player.h"
#include "Component\Physics\Gravity.h"

#include "Device\Input.h"
#include "PlayerState_Default.h"
#include "PlayerState_MagChange.h"

const float PlayerState_SuperJump::MAX_JUMP_FORCE = 384.0f;

PlayerState_SuperJump::PlayerState_SuperJump(Player* pPlayer)
	: m_pPlayer(pPlayer), m_pGravity(pPlayer->getGravity())
{
}

void PlayerState_SuperJump::update()
{
	float deltaTime = GameTime::getDeltaTime();

	m_JumpForce -= m_pGravity->getGravSpeed() * deltaTime;

	Vec3 move(0, std::fmaxf(0, m_JumpForce * deltaTime), 0);
	m_pPlayer->setPosition(m_pPlayer->getPosition() + move);
}

void PlayerState_SuperJump::onStateEnter()
{
	m_JumpForce = MAX_JUMP_FORCE;
}

void PlayerState_SuperJump::onStateExit()
{
}

IState * PlayerState_SuperJump::nextState()
{
	if (MAX_JUMP_FORCE / 2 >= m_JumpForce && m_pPlayer->isDetectDown())
		return new PlayerState_Default(m_pPlayer);
	if (m_JumpForce <= 0 || m_pPlayer->isDetectUp())
		return new PlayerState_Default(m_pPlayer);
	if (Input::isKeyDown('Z'))
		return new PlayerState_MagChange(m_pPlayer);

	return nullptr;
}
