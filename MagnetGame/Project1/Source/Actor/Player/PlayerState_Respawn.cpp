#include "PlayerState_Respawn.h"
#include "PlayerState_Default.h"
#include "Device\GameTime.h"
#include "Actor\Player\Player.h"
#include "Actor\Effect\SpreadEffect.h"
#include <DirectXColors.h>

PlayerState_Respawn::PlayerState_Respawn(Player * pPlayer)
	: m_pPlayer(pPlayer)
{
}

PlayerState_Respawn::~PlayerState_Respawn()
{
	GameTime::timeScale = 1.0f;
	m_pPlayer->isRespawn = true;
}

void PlayerState_Respawn::update()
{
	m_UnscaledTime += GameTime::getUnscaledDeltaTime();
}

void PlayerState_Respawn::onStateEnter()
{
	GameTime::timeScale = 0.0f;
	auto effect = new SpreadEffect(m_pPlayer->getGameMediator(), Color(DirectX::Colors::LightCyan));
	effect->setPosition(m_pPlayer->getPosition());
}

void PlayerState_Respawn::onStateExit()
{
	GameTime::timeScale = 1.0f;
}

IState * PlayerState_Respawn::nextState()
{
	if (m_UnscaledTime >= 1.5f)
		return new PlayerState_Default(m_pPlayer);
	
	return nullptr;
}
