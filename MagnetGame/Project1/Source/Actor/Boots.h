#pragma once

#include "GameObject.h"

class Boots : public GameObject {
public:
	Boots(IGameMediator* pGameMediator);

	virtual void start() override;
	virtual void onCollisionEnter(GameObject* pHit) override;
};