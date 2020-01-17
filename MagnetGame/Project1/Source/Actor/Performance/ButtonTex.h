#pragma once
#include"Actor/GameObject.h"

class SpriteRenderer;

class ButtonTex
	:public GameObject
{
public:
	ButtonTex(IGameMediator *pMediator);
	~ButtonTex();

	virtual void start()override;
	virtual void update()override;
	virtual void onDestroy()override;

private:
	SpriteRenderer*sprite;

};