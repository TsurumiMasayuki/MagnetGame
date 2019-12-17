#pragma once
#include "Actor\GameObject.h"

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

	Magnet(IGameMediator* pGameMediator, MagnetOption magOption, bool isMove, float width, float height);

	virtual void start() override;
	virtual void update() override;

	void SetMagOption(MagnetOption magOption);

private:
	void writeMagMap();
	void readMagMap();

private:
	MagnetOption m_MagOption;
	ForceMap* m_pNMap;
	ForceMap* m_pSMap;
	bool m_IsMove;

	SpriteRenderer* m_pSprite;

	static const float MAG_MOVE_SPEED;
};