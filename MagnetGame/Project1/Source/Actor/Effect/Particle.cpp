#include "Particle.h"
#include "Component/SpriteRenderer.h"

#define PI 3.141525

Particle::Particle(float angle)
{
	this->angle = angle;
	
}

void Particle::Init()
{
	angle = angle * (PI / 180);
	x = 200, y = 200;
	speed = 0.1f;
}

void Particle::Update()
{
	x += cos(angle)*speed;
	y += sin(angle)*speed;
}

void Particle::Draw()
{
}
