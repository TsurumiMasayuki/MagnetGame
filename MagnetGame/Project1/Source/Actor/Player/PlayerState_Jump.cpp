#include "PlayerState_Jump.h"

#include "Device\GameTime.h"

#include "Actor\Player\Player.h"
#include "Component\Physics\Gravity.h"

#include "PlayerState_Default.h"

const float PlayerState_Jump::MAX_JUMP_FORCE = 64.0f;

PlayerState_Jump::PlayerState_Jump(Player* pPlayer)
	: m_pPlayer(pPlayer), m_pGravity(pPlayer->getGravity()), m_JumpForce(MAX_JUMP_FORCE)
{
}

void PlayerState_Jump::update()
{
	float deltaTime = GameTime::getDeltaTime();

	m_JumpForce -= m_pGravity->getGravSpeed() * deltaTime;

	Vec3 move(0, std::fmaxf(0, m_JumpForce * deltaTime), 0);
	m_pPlayer->setPosition(m_pPlayer->getPosition() + move);
}

void PlayerState_Jump::onStateEnter()
{
}

void PlayerState_Jump::onStateExit()
{
}

IState * PlayerState_Jump::nextState()
{
	if (m_JumpForce <= 0)
		return new PlayerState_Default(m_pPlayer);

	return nullptr;
}
