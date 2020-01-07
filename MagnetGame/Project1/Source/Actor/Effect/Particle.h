#pragma once
#include <d3d11.h>
#include <string>
#include "Actor\GameObject.h"
#include "Utility/Timer.h"

class Particle:public GameObject {
public:
	Particle(float speed,float angle,float duration,float shrinkRate, IGameMediator * pMediator);
	~Particle();
	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;

	Timer timer;

	int grp;
	float x, y;
	float size_x, size_y;
	float angle, speed,duration,shrinkRate;
};