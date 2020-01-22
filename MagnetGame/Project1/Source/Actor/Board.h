#pragma once
#include "GameObject.h"

class Board
	:public GameObject
{
	public:
		Board(IGameMediator*pMediator);

		virtual void start()override;
		virtual void onCollisionStay(GameObject*pHit)override;

private:
	bool isHint;
	int hintCnt;
public:
	bool getIsHint();
	void setIsHint(bool value);
	int getHintCnt();
	void setHintCnt(int value);
};
