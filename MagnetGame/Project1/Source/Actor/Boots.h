#pragma once

#include "GameObject.h"

class Boots : public GameObject {
public:
	Boots(IGameMediator* pGameMediator);

	virtual void start() override;
	virtual void onCollisionStay(GameObject* pHit) override;
};