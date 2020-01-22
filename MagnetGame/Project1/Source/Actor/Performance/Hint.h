#pragma once
#include "Actor/GameObject.h"

class SpriteRenderer;

class Hint
	:public GameObject {
public:
	Hint(IGameMediator *pMediator);
	~Hint();

	virtual void start() override;
	virtual void update() override;
private:
	SpriteRenderer*sprite;
	SpriteRenderer*text;
	int m_HintNum;
	std::string name;
public:
	void setHintNum(int value);
};
