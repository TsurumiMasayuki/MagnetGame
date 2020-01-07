#pragma once
#include <d3d11.h>
#include <string>

class Particle {
public:
	Particle(float angle);
	void Init();
	void Update();
	void Draw();

	int grp;
	float x, y;
	float angle, speed;
};