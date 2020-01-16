#pragma once
#include <d3d11.h>
#include "Particle.h"
#include "Actor/IGameMediator.h"
#include <string>

class MagEffect {
public:
	MagEffect(IGameMediator* pMediator);
	void Cleate(Vec3 pos,float size_x,float size_y, float speed,float duration, float shrinkRate, float amount);

	Particle* particle;

	IGameMediator * pMediator;

	std::string name;

	float size_x, size_y, x, y;
	float angle, speed, duration, shrinkRate;
};