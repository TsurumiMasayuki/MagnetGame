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
		new Particle("CircleFill", getPosition(), 32, 32, 10.0f, angle * i, 0.25f, 16.0f / 0.25f / 60.0f, m_Color, m_pGameMediator);
	}

	destroy();
}
