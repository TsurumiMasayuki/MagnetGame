#pragma once
#include "Actor/GameObject.h"

class SpriteRenderer;

class PauseObject
	:public GameObject
{
public:
	PauseObject(IGameMediator*pMediator);
	~PauseObject();

	virtual void start()override;
	virtual void update()override;
	virtual void onDestroy()override;

private:
	void exit();

private:
	SpriteRenderer*sprite;
	SpriteRenderer*back;
	SpriteRenderer*check;
	bool isPause;
	bool isReStart;
	int pNum;
	int selectNum;
	int checkNum;

	float prevY,currentY;

	bool isEndFlag;
	enum PauseState
	{
		Pause,
		HowTo,
		None
	};
	PauseState pState;
public:
	void setNum(int value);
	void setPause(bool value);
	bool IsEnd();
	bool getReStart();
	void setReStart(bool value);
};
