#include "SuperJumpEffect.h"

SuperJumpEffect::SuperJumpEffect(IGameMediator * pMediator)
{
	this->pMediator = pMediator;
}

void SuperJumpEffect::Cleate(Vec3 pos, float duration, float shrinkRate, float amount)
{
	for (int i = 0; i < amount; i++) {
		name = "superjumpeffect";

		angle = std::rand()/360+230;
		speed = std::rand()/1000;

		float size = std::rand()/700;
		

		particle = new Particle(name, pos,size,size, speed, angle, duration, shrinkRate, pMediator);
	}
}
