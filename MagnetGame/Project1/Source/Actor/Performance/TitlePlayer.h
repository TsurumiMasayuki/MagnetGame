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

	
	bool IsEnd();
	bool isFlipX;
private:
	AnimSpriteRenderer*anim;
	
	enum State
	{
		Alpha = 0,
		Idle = 1,
		Move = 2,
		Idle2,
		Move2,
	};
	State state;

	enum EndingState {
		eAlpha,
		eMove,
		eIdle,

	};
	EndingState eState;

	static const float MOVE_SPEED;
	bool isEndFlag;
	bool m_pMove;
	bool canMove;
	bool isGrobe;
	float a;
	bool go;
	int Num;
	int seCnt;
	float x;
	float y;

public:
	void setIsGo(bool value);
	void setNum(int value);
	void setCanMove(bool value);
	void setIsGrobe(bool value);
};
