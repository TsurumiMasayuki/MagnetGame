#pragma once

#include "GameObject.h"

class Player;

class Boots : public GameObject {
public:
	Boots(IGameMediator* pGameMediator, Player* pPlayer);

	virtual void start() override;
	virtual void onCollisionEnter(GameObject* pHit) override;
private:
	Player* m_pPlayer;
};