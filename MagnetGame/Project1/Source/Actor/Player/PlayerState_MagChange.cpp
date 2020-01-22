#include "PlayerState_MagChange.h"
#include "Player.h"
#include "PlayerState_Default.h"
#include "Utility\Timer.h"
#include "Device\GameInput.h"
#include "Device\SoundManager.h"

PlayerState_MagChange::PlayerState_MagChange(Player * pPlayer)
	: m_pPlayer(pPlayer), m_pTimer(new Timer(0.3f))
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
	if (m_pTimer->isTime())
		if (!m_pPlayer->isSuperJump)
			m_pPlayer->setAnimation("Idle");
		else
			m_pPlayer->setAnimation("GBIdle");
}

void PlayerState_MagChange::onStateEnter()
{
	m_pTimer->reset();
	m_pMagChange = m_pPlayer->getMagChange();
	m_pMagChange->setActive(true);

	m_MagChangeDir = GameInput::getMagChangeDir().toVec3();

	if (m_MagChangeDir.y == 0)
		if (!m_pPlayer->isSuperJump)
			m_pPlayer->setAnimation("PunchLR");
		else
			m_pPlayer->setAnimation("GBPunchLR");
	if (m_MagChangeDir.x == 0)
		if (m_MagChangeDir.y == 1)
			if (!m_pPlayer->isSuperJump)
				m_pPlayer->setAnimation("PunchUp");
			else
				m_pPlayer->setAnimation("GBPunchUp");
		else if (m_MagChangeDir.y == -1)
			if (!m_pPlayer->isSuperJump)
				m_pPlayer->setAnimation("PunchDown");
			else
				m_pPlayer->setAnimation("GBPunchDown");


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
	if (m_pTimer->isTime()) {
		if (m_pPlayer->isDetectDown())
			return new PlayerState_Default(m_pPlayer);
		if (m_pPlayer->GetJumpForce() <= 0)
			return new PlayerState_Default(m_pPlayer);
		if (m_pPlayer->isDetectUp() && m_pPlayer->isDetectDown())
			return new PlayerState_Default(m_pPlayer);
	}
	return nullptr;
}
