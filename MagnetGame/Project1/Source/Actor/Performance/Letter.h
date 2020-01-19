#pragma once
#include "Actor/GameObject.h"

class SpriteRenderer;

class Letter
	:public GameObject
{
public:
	Letter(IGameMediator *pMediator);
	~Letter();

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;

private:

	SpriteRenderer*sprite;
};
