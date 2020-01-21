#pragma once
#include "Actor/GameObject.h"

class SpriteRenderer;

class FadeOut
	:public GameObject
{
public:
	FadeOut(IGameMediator*pMediator);
	~FadeOut();

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;
private:
	SpriteRenderer*sprite;
	float alpha;
	bool isEndFlag;
public:

	float getAlpha();

};
