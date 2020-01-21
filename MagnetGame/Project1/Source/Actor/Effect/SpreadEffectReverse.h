#pragma once
#include "Actor\GameObject.h"
#include "Utility\Color.h"

class SpreadEffectReverse
	: public GameObject
{
public:
	SpreadEffectReverse(IGameMediator* pGameMediator, Color color, float radius);
	~SpreadEffectReverse();

	virtual void start() override;

private:
	Color m_Color;
	float m_Radius;
};