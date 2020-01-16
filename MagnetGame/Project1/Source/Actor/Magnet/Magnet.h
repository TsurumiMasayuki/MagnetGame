#pragma once
#include "Actor\GameObject.h"
#include "Math\Vec2.h"

class ForceMap;
class SpriteRenderer;
class DetectHelper;

class Magnet
	: public GameObject
{
public:
	enum MagnetOption
	{
		MAGNET_N,
		MAGNET_S
	};

	Magnet(IGameMediator* pGameMediator, MagnetOption magOption, bool isMove, bool isMagChange, float width, float height);
	~Magnet();

	virtual void start() override;
	virtual void update() override;

	virtual void onCollisionEnter(GameObject* pHit) override;
	virtual void onCollisionStay(GameObject* pHit) override;
	virtual void onCollisionExit(GameObject* pHit) override;

	MagnetOption getMagOpition();
	void SetMagOption(MagnetOption magOption);
	Vec2 getVelocity();

private:
	void writeMagMap();
	void readMagMap();

private:

	MagnetOption m_MagOption;
	ForceMap* m_pNMapWrite;
	ForceMap* m_pSMapWrite;
	ForceMap* m_pNMapRead;
	ForceMap* m_pSMapRead;
	bool m_IsMove;
	bool m_IsMagChange;

	SpriteRenderer* m_pSprite;
	GameObject* m_pRider;

	MagnetOption prevMagOption;

	static const float MAG_MOVE_SPEED;
	Vec2 m_Velocity;
};