#include "LineEffect.h"
#include "Particle.h"
#include "Math\MathUtility.h"
#include "Utility\Timer.h"
#include <DirectXColors.h>

LineEffect::LineEffect(IGameMediator * pGameMediator, float lineAngle, float particleAngle, float effectTime, float lineLength, int particleCount, Color color)
	: GameObject(pGameMediator),
	m_LineAngle(lineAngle),
	m_ParticleAngle(particleAngle),
	m_ParticleCount(2),
	m_MaxParticleCount(particleCount + 2),
	m_ParticleInterval(lineLength / particleCount / 2),
	m_pTimer(new Timer(effectTime / particleCount)),
	m_Color(color)
{
}

LineEffect::~LineEffect()
{
	delete m_pTimer;
}

void LineEffect::start()
{
	Vec3 particlePos = Vec2::angleToVec(m_LineAngle).toVec3() * m_ParticleCount * m_ParticleInterval;
	Vec3 linePosR = getPosition() + particlePos;
	Vec3 linePosL = getPosition() - particlePos;

	new Particle("BoxFill", linePosR, 8, 8, 64, m_ParticleAngle, 0.3f, 0, m_Color, m_pGameMediator);
	new Particle("BoxFill", linePosL, 8, 8, 64, m_ParticleAngle, 0.3f, 0, m_Color, m_pGameMediator);

	m_ParticleCount += 2;
}

void LineEffect::update()
{
	if (m_ParticleCount >= m_MaxParticleCount)
		destroy();

	m_pTimer->update();

	if (!m_pTimer->isTime()) return;

	m_pTimer->reset();

	Vec3 particlePos = Vec2::angleToVec(m_LineAngle).toVec3() * m_ParticleCount * m_ParticleInterval;
	Vec3 linePosR = getPosition() + particlePos;
	Vec3 linePosL = getPosition() - particlePos;

	new Particle("BoxFill", linePosR, 8, 8, 64, m_ParticleAngle, 0.3f, 0, m_Color, m_pGameMediator);
	new Particle("BoxFill", linePosL, 8, 8, 64, m_ParticleAngle, 0.3f, 0, m_Color, m_pGameMediator);

	m_ParticleCount += 2;
}
