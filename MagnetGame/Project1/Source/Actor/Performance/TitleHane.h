#pragma once
#include "Component/SpriteRenderer.h"
#include "Actor/GameObject.h"
#include "Actor/IGameMediator.h"

class TitleHane:public GameObject {
public:
	TitleHane(IGameMediator*pMediator);
	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;


private:
	SpriteRenderer*sprite;
	Vec3 pos;
	float angle;
};