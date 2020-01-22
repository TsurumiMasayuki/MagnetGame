#pragma once
#include <string>
#include "Actor\GameObject.h"
#include "Utility\Color.h"

class Timer;

class Particle :
	public GameObject
{
public:
	Particle(std::string name, Vec3 pos, float size_x, float size_y, float speed, float angle, float duration, float shrinkRate, IGameMediator * pMediator);
	Particle(std::string name, Vec3 pos, float size_x, float size_y, float speed, float angle, float duration, float shrinkRate, Color color, IGameMediator * pMediator, bool useUnscaledTime = false);
	~Particle();

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;

private:
	Timer* timer;
	Color color;
	bool m_UseUnscaledTime;

	std::string name;
	Vec3 pos;
	float x, y;
	float size_x, size_y;
	float angle, speed, duration, shrinkRate;
};