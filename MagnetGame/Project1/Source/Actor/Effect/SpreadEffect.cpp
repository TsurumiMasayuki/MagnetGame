#include "SpreadEffect.h"
#include "Math\MathUtility.h"
#include "Math\Vec2.h"
#include "Actor\Effect\Particle.h"

SpreadEffect::SpreadEffect(IGameMediator * pGameMediator, Color color)
	: GameObject(pGameMediator),
	m_Color(color)
{
}

SpreadEffect::~SpreadEffect()
{
}

void SpreadEffect::start()
{
	const int count = 8;
	const float angle = 360.0f / count;

	for (int i = 0; i < count; ++i)
	{
		new Particle("CircleFill", getPosition(), 32, 32, 64.0f, angle * i, 1.5f, 64.0f / 1.5f / 60.0f, m_Color, m_pGameMediator, true);
	}

	destroy();
}
