#include "MagEffect.h"

MagEffect::MagEffect(IGameMediator * pMediator)
{
	this->pMediator = pMediator;
}

void MagEffect::Cleate(Vec3 pos,float size_x,float size_y,float speed, float duration, float shrinkRate, float amount)
{
	for (int i = 0; i < amount; i++) {

		name = "mageffect";

		angle = std::rand() / 360;

		particle = new Particle(name, pos+ Vec3(-size_x / 2, -size_y / 2, 0),16,16, speed,angle, duration, shrinkRate, pMediator);
		particle = new Particle(name, pos+ Vec3(size_x / 2, -size_y / 2, 0),16,16, speed,angle, duration, shrinkRate, pMediator);
		particle = new Particle(name, pos+ Vec3(size_x / 2, size_y / 2, 0),16,16, speed,angle, duration, shrinkRate, pMediator);
		particle = new Particle(name, pos+ Vec3(-size_x / 2, size_y / 2, 0),16,16, speed,angle, duration, shrinkRate, pMediator);
	}
}
