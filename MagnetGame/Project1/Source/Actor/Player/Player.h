#pragma once
#include "Actor\GameObject.h"

class StateManager;
class Gravity;
class DetectHelper;
class AnimSpriteRenderer;

class Player :
	public GameObject
{
public:
	Player(IGameMediator* pMediator);
	~Player();

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;

	Gravity* getGravity();
	GameObject* getMagChange();
	
	bool isDetectUp();
	bool isDetectDown();
	bool isDetectRight();
	bool isDetectLeft();
	bool canSuperJump();
	bool isSandwich();

	void Respawn();
	void SetRespawnPoint(Vec3 pos);
	void SetJumpForce(float jumpForce);
	float GetJumpForce();

	void setAnimation(std::string animName);

private:
	void initMagChange();
	void initDetectors();
	void initAnimations();
	void moveY();

public:
	bool isSuperJump;

private:
	StateManager* m_pStateManager;
	Gravity* m_pGravity;
	GameObject* m_pMagChange;

	DetectHelper* m_pDetectUp;
	DetectHelper* m_pDetectDown;
	DetectHelper* m_pDetectRight;
	DetectHelper* m_pDetectLeft;

	AnimSpriteRenderer* m_pAnimRenderer;

	Vec3 m_RespawnPoint;
	float m_JumpForce;

	static const float MOVE_SPEED;
};