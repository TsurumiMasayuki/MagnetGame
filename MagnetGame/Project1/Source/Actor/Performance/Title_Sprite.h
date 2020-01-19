#pragma once
#include "Component/SpriteRenderer.h"
#include "Actor/IGameMediator.h"
#include "Actor/GameObject.h"

class Title_Sprite :public GameObject {
public:
	Title_Sprite(IGameMediator*pMediator);
	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;

private:
	SpriteRenderer*tree;
	SpriteRenderer*background;
	SpriteRenderer*huusya;
};