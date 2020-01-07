#include "CircleEffect.h"
#include "Actor/IGameMediator.h"

CircleEffect::CircleEffect(IGameMediator* pMediator)
{
	this->pMediator = pMediator;
}

void CircleEffect::Cleate(Vec3 pos,float speed, float duration, float shrinkRate, float amount)
{
	for (int i = 0; i < amount; i++) 
	{
		name = "smoke";
		float angle = std::rand() * 360;
		
		particle = new Particle(name,pos,speed,angle, duration, shrinkRate,pMediator );
	}
}
