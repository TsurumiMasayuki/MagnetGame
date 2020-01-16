#pragma once

#include"Actor/GameObject.h"

class StateManager;
class Gravity;
class DetectHelper;
class AnimSpriteRenderer;

class TitlePlayer :
	public GameObject
{
public:
	TitlePlayer(IGameMediator* nMediator);
	~TitlePlayer();

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;

	void initAnimations();

	enum State
	{
		Alpha = 0,
		Idle = 1,
		Move = 2,
		Idle2,
		Move2,
	};
	State state;
	bool IsEnd();
	bool isFlipX;
private:
	AnimSpriteRenderer*anim;

	static const float MOVE_SPEED;
	bool isEndFlag;
	bool m_pMove;
	float a;
	bool go;
	int Num; 
	float x;

public:
	void setIsGo(bool value);
	void setNum(int value);
};
