#pragma once
#include "Actor/GameObject.h"

class SpriteRenderer;

class NameTexture
	:public GameObject
{
public:
	NameTexture(IGameMediator*pMediator);
	~NameTexture();

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;

	void setEventNum(int num);
private:

	int EventNum;
	enum NameState
	{
		Hero,
		Doctor,
		Doctor_Black,
	};
	NameState nState;

	SpriteRenderer*sprite;
};
