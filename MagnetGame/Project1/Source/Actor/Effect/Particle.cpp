#include "Particle.h"
#include "Component/SpriteRenderer.h"
#include "Device/GameTime.h"
#include "Utility/Timer.h"

#define PI 3.141525

Particle::Particle(std::string name, Vec3 pos, float size_x, float size_y, float speed, float angle, float duration, float shrinkRate, IGameMediator * pMediator)
	: Particle(name, pos, size_x, size_y, speed, angle, duration, shrinkRate, Color(1, 1, 1, 1), pMediator)
{
}

Particle::Particle(std::string name, Vec3 pos, float size_x, float size_y, float speed, float angle, float duration, float shrinkRate, Color color, IGameMediator * pMediator) : GameObject(pMediator)
{
	this->name = name;
	this->pos = pos;
	this->size_x = size_x;
	this->size_y = size_y;
	this->speed = speed;
	this->angle = angle;
	this->duration = duration;
	this->shrinkRate = shrinkRate;
	this->color = color;
}

Particle::~Particle()
{
	delete timer;
}

void Particle::start()
{
	setSize(Vec3(size_x, size_y, 0));

	auto sprite = new SpriteRenderer(this, 150);
	sprite->setTextureName(name);
	sprite->setColor(color);

	timer = new Timer(duration);

	angle = angle * (PI / 180);
	setPosition(Vec3(pos.x, pos.y, 0));
	x = 0;
	y = 0;
}

void Particle::update()
{
	x += cos(angle) * speed;
	y += sin(angle) * speed;
	Vec3 move(x, y, 0);
	setPosition(getPosition() + move * GameTime::getDeltaTime());

	size_x -= shrinkRate;
	size_y -= shrinkRate;

	setSize(Vec3(size_x, size_y, 0));
	timer->update();
	if (timer->isTime() || size_x <= 0 || size_y <= 0)
	{
		destroy();
	}
}

void Particle::onDestroy()
{

}