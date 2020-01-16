#pragma once
#include"Actor/GameObject.h"

class SpriteRenderer;

class EventText
	:public GameObject {
public:
	EventText(IGameMediator*pMediator);
	~EventText();

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;

	void setEventNum(int num);
	int getEventNum();
	void addEventNum();

private:
	SpriteRenderer*text;
	SpriteRenderer*frame;
	SpriteRenderer*arrow;
	int EventNum;
	std::string eventText;

	enum State
	{
		Hero,
		Doctor,
		Doctor_Black,
	};
	State state;

	float alpha;
	float a;
};
