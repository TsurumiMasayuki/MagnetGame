#pragma once
#include "Actor/GameObject.h"

class SpriteRenderer;

class EndTex
	:public GameObject
{
public:
	EndTex(IGameMediator*pMediator);
	~EndTex();

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
