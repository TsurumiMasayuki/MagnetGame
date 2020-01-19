#include "SmokeEffect.h"

SmokeEffect::SmokeEffect(IGameMediator * pMediator)
{
	this->pMediator = pMediator;
}

void SmokeEffect::Cleate(Vec3 pos, float speed, float shrinkRate, float amount)
{
	for (int i = 0; i < amount; i++) {

		name = "smoke";

		angle = std::rand() % 10 + 85;

		duration = std::rand() % 3 + 2;

		particle = new Particle(name, pos, 32, 32, speed, angle, duration, shrinkRate, pMediator);
	}
}
