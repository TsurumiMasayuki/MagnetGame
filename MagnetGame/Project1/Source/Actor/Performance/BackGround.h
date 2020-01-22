#pragma once
#include "Actor/GameObject.h"

class SpriteRenderer;

class BackGround
	:public GameObject
{
public:
	BackGround(IGameMediator*pMediator, std::string TextureName);
	~BackGround();

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;

	bool isFade;
private:
	SpriteRenderer*sprite;
	std::string name;

public:
	void setTextureName(std::string TextureName);
};
