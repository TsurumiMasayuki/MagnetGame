#include "Particle.h"
#include "Component/SpriteRenderer.h"
#include "Device/GameTime.h"
#include "Utility/Timer.h"

#define PI 3.141525

Particle::Particle(float speed,float angle, float duration,float shrinkRate, IGameMediator * pMediator) : GameObject(pMediator)
{
	this->speed = speed;
	this->angle = angle;
	this->duration = duration;
	this->shrinkRate = shrinkRate;
}

Particle::~Particle()
{
}

void Particle::start()
{
	size_x = 32,size_y=32;
	setSize(Vec3(size_x,size_y, 0));

	auto sprite = new SpriteRenderer(this);
	sprite->setTextureName("smoke");

	timer.setMaxTime(duration);

	angle = angle * (PI / 180);
	x = 0, y = 0;

	
}

void Particle::update()
{
	x += cos(angle)*speed;
	y += sin(angle)*speed;
	Vec3 move(x* GameTime::getDeltaTime(), y* GameTime::getDeltaTime(), 0);
	setPosition(getPosition() + move);

	size_x -= shrinkRate;
	size_y -= shrinkRate;

	setSize(Vec3(size_x, size_y, 0));
	timer.update();
	if (timer.isTime()||size_x<=0||size_y<=0) 
	{
		destroy();
	}
}

void Particle::onDestroy()
{

}
