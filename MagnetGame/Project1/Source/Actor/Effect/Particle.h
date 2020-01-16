#pragma once
#include <d3d11.h>
#include <string>
#include "Actor\GameObject.h"
#include "Utility/Timer.h"

class Particle:public GameObject {
public:
	Particle(std::string name,Vec3 pos,float size_x,float size_y,float speed,float angle,float duration,float shrinkRate, IGameMediator * pMediator);
	~Particle();
	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;


	Timer timer;

	std::string name;
	Vec3 pos;
	float x, y;
	float size_x, size_y;
	float angle, speed,duration,shrinkRate;
};