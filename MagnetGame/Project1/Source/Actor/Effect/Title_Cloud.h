#pragma once
#include <d3d11.h>
#include "Particle.h"
#include "Actor/IGameMediator.h"
#include <string>

class Title_Cloud {
public:
	Title_Cloud(IGameMediator* pMediator);
	void Cleate(float speed, float duration, float shrinkRate, float amount);
	void Cleate2(Vec3 pos,float speed, float duration, float shrinkRate, float amount);

	Particle* particle;

	IGameMediator * pMediator;

	std::string name;

	float size_x, size_y, x, y;
	float angle, speed, duration, shrinkRate;
};