#pragma once
#include <d3d11.h>
#include "Particle.h"
#include "Actor/IGameMediator.h"
#include <string>
class SuperJumpEffect {
public:
	SuperJumpEffect(IGameMediator* pMediator);
	void Cleate(Vec3 pos, float duration, float shrinkRate, float amount);

	Particle* particle;

	IGameMediator * pMediator;

	std::string name;

	float size_x, size_y, x, y;
	float angle, speed, duration, shrinkRate;
};