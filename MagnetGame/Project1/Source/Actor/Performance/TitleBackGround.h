#pragma once
#include "Actor/GameObject.h"

class SpriteRenderer;

class TitleBackGround
	:public GameObject
{
public:
	TitleBackGround(IGameMediator*pMediator);
	~TitleBackGround();

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;

	bool isFade;
private:
	SpriteRenderer*sprite;
};
