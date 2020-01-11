#include "PlayerState_MagChange.h"
#include "Player.h"
#include "PlayerState_Default.h"
#include "Utility\Timer.h"
#include "Device\GameInput.h"
#include "Device\SoundManager.h"

PlayerState_MagChange::PlayerState_MagChange(Player * pPlayer)
	: m_pPlayer(pPlayer), m_pTimer(new Timer(0.5f))
{
}

PlayerState_MagChange::~PlayerState_MagChange()
{
	if (m_pTimer != nullptr)delete m_pTimer;
}

void PlayerState_MagChange::update()
{
	Vec3 magChangePos(m_pPlayer->getSize().x * m_MagChangeDir.x, m_pPlayer->getSize().y * m_MagChangeDir.y, 0);
	m_pMagChange->setPosition(m_pPlayer->getPosition() + magChangePos * 0.5f);

	m_pTimer->update();
}

void PlayerState_MagChange::onStateEnter()
{
	m_pTimer->reset();
	m_pMagChange = m_pPlayer->getMagChange();
	m_pMagChange->setActive(true);

	m_MagChangeDir = GameInput::getMagChangeDir().toVec3();

	if (m_MagChangeDir.y == 0)
		m_pPlayer->setAnimation("PunchLR");
	if (m_MagChangeDir.x == 0)
		if (m_MagChangeDir.y == 1)
			m_pPlayer->setAnimation("PunchUp");
		else if (m_MagChangeDir.y == -1)
			m_pPlayer->setAnimation("PunchDown");

	SoundManager::playSE("punch", 0);
}

void PlayerState_MagChange::onStateExit()
{
	m_pMagChange->setActive(false);
	delete m_pTimer;
	m_pTimer = nullptr;
}

IState * PlayerState_MagChange::nextState()
{
	if (m_pTimer->isTime())
		return new PlayerState_Default(m_pPlayer);
	return nullptr;
}
