#pragma once
#include "Actor/GameObject.h"

class SpriteRenderer;

class Item
	:public GameObject
{
public:
	Item(IGameMediator*pMediator, std::string TextureName);
	~Item();

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;

private:

	SpriteRenderer*sprite;
	std::string name;

public:
	void setTextureName(std::string TextureName);
};
