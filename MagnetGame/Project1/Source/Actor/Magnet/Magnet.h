#pragma once
#include "Actor\GameObject.h"
#include "Actor/Effect/MagEffect.h"

class ForceMap;
class SpriteRenderer;

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

	MagnetOption getMagOpition();
	void SetMagOption(MagnetOption magOption);

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

	MagEffect* magEffect;

	MagnetOption prevMagOption;

	static const float MAG_MOVE_SPEED;
};