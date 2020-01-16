#pragma once
#include "Actor/GameObject.h"

class SpriteRenderer;

class TitleFade
	:public GameObject
{
public:
	TitleFade(IGameMediator*pMediator);
	~TitleFade();

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;

	bool isEnd();
private:
	SpriteRenderer*sprite;
	float alpha;
	bool isEndFlag;
};
