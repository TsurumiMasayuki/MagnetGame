#pragma once
#include "Actor/GameObject.h"

class SpriteRenderer;

class ExText
	:public GameObject
{
public:
	ExText(IGameMediator*pMediator, std::string TextureName);
	~ExText();

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;

private:

	SpriteRenderer*sprite;
	std::string name;

	int stateNum;

	void UpdateStateNum();

public:
	void setTextureName(std::string TextureName);
	void setStateNum(int value);
	void addStateNum();
	int getStateNum();
};
