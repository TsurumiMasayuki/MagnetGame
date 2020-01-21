#pragma once
#include"Actor/GameObject.h"

class StateManager;
class Gravity;
class DetectHelper;
class AnimSpriteRenderer;

class ObjN :
	public GameObject
{
public:
	ObjN(IGameMediator* nMediator, int dir, float speedModifier);
	~ObjN();

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;

	virtual void onCollisionEnter(GameObject*nHit)override;
	virtual void onCollisionStay(GameObject*nHit)override;

	Gravity * getGravity();
	GameObject*getMagChange();

	bool isDetectLeft();
	bool isDetectRight();

private:
	void initMagChange();
	void initDetectors();
private:
	//StateManager*m_nStateManager;
	Gravity * m_nGravity;
	GameObject*m_nMagChange;

	DetectHelper*m_nDetectRight;
	DetectHelper*m_nDetectLeft;

	AnimSpriteRenderer* anim;

	static const float MOVE_SPEED;

	float m_SpeedModifier;
	int direction;
	float x;
};
