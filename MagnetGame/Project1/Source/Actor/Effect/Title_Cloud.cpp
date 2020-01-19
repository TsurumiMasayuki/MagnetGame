#include "Title_Cloud.h"
#include "WindowInstance.h"

Title_Cloud::Title_Cloud(IGameMediator * pMediator)
{
	this->pMediator = pMediator;
}

void Title_Cloud::Cleate( float speed, float duration, float shrinkRate, float amount)
{
	for (int i = 0; i < amount; i++) {
		
		angle = 90;
		name = "cloud"+std::rand()%2+1;
		Vec3 pos[3] = 
		{
			Vec3(10,300,0),
			Vec3(10,500,0),
			Vec3(10,700,0),
		
		};

		int rnd = std::rand() %2;

		size_x = std::rand() % 100 + 100;
		size_y = size_x * (3 / 2);

		particle = new Particle(name,pos[rnd], size_x, size_y, speed, angle, duration, shrinkRate, pMediator);
	}
}
