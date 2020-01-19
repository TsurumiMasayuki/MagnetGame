#include "Title_Cloud.h"
#include "WindowInstance.h"

Title_Cloud::Title_Cloud(IGameMediator * pMediator)
{
	this->pMediator = pMediator;
}

void Title_Cloud::Cleate( float speed, float duration, float shrinkRate, float amount)
{
	for (int i = 0; i < amount; i++) {
		
		angle = 180;
		int number = std::rand() % 2 + 1;;
		
		if (number == 1) name = "cloud1";
		else name = "cloud2";
		
		Vec3 pos[3] = 
		{
			Vec3(700,300,0),
			Vec3(700,250,0),
			Vec3(700,200,0),
		
		};

		int rnd = std::rand() %2;

		size_x = std::rand() % 100 + 100;
		size_y = size_x * 0.5f;

		particle = new Particle(name,pos[rnd], size_x, size_y, speed, angle, duration, shrinkRate, pMediator);
	}
}
