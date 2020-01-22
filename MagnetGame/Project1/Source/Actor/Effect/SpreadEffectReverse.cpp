#include "SpreadEffectReverse.h"
#include "Math\Vec2.h"
#include "Particle.h"

SpreadEffectReverse::SpreadEffectReverse(IGameMediator * pGameMediator, Color color, float radius)
	: GameObject(pGameMediator),
	m_Color(color),
	m_Radius(radius)
{
}

SpreadEffectReverse::~SpreadEffectReverse()
{
}

void SpreadEffectReverse::start()
{
	const int count = 8;
	const float angle = 360.0f / count;

	for (int i = 0; i < count; ++i)
	{
		Vec3 vector = Vec2::angleToVec(angle * i).toVec3();
		new Particle("CircleFill", getPosition() + vector * m_Radius, 32, 32, -64.0f, angle * i, 1.5f, 64.0f / 1.5f / 60.0f, m_Color, m_pGameMediator, true);
	}

	destroy();
}
