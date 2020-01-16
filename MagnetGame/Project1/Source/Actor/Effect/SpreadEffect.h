#pragma once
#include "Actor\GameObject.h"
#include "Utility\Color.h"

class SpreadEffect
	: public GameObject
{
public:
	SpreadEffect(IGameMediator* pGameMediator, Color color);
	~SpreadEffect();

	virtual void start() override;

private:
	Color m_Color;
};