#pragma once
#include "GameObject.h"

class Board
	:public GameObject
{
	public:
		Board(IGameMediator*pMediator);
		~Board();

		virtual void start()override;
		virtual void onCollisionStay(GameObject*pHit)override;
		virtual void onCollisionExit(GameObject*pHit)override;
};
