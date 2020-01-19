#pragma once
#include "Actor\GameObject.h"
#include "Utility\Color.h"
#include "Math\Vec2.h"

class ForceMap;
class SpriteRenderer;
class MultiSpriteRenderer;
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
	void setMagOption(GameObject* pHit);
	Vec2 getVelocity();

private:
	void writeMagMap();
	void readMagMap();
	void magForceEffect(const Vec2& currentForce, const Vec2& previousForce, Color effectColor);

private:

	MagnetOption m_MagOption;
	ForceMap* m_pNMapWrite;
	ForceMap* m_pSMapWrite;
	ForceMap* m_pNMapRead;
	ForceMap* m_pSMapRead;
	bool m_IsMove;
	bool m_IsMagChange;

	SpriteRenderer* m_pNoMagChange;
	MultiSpriteRenderer* m_pSprite;
	GameObject* m_pRider;

	MagnetOption prevMagOption;

	static const float MAG_MOVE_SPEED;
	Vec2 m_Velocity;
	Vec3 m_PrePosition;
	Vec2 m_Movement;

	Vec2 m_PreNForce;
	Vec2 m_PreSForce;
};