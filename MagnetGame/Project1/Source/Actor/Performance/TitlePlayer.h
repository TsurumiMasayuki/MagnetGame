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
private:
	AnimSpriteRenderer*anim;

	static const float MOVE_SPEED;
	bool isEndFlag;
	bool m_pMove;
	float a;
	bool go;

public:
	void setIsGo(bool value);
};
