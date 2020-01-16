#pragma once
#include "Actor/GameObject.h"

class SpriteRenderer;

class TitleBackGround
	:public GameObject
{
public:
	TitleBackGround(IGameMediator*pMediator, std::string TextureName);
	~TitleBackGround();

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
