#pragma once

#include "GameObject.h"

class Player;

class CheckPoint  : public GameObject{
public:
	CheckPoint(IGameMediator* pGameMediator, Vec3 RespawnPoint);
	~CheckPoint();

	virtual void start() override;
	virtual void update() override;

	virtual void onCollisionEnter(GameObject* pHit) override;

	void WriteRespawnPoint(Player* pPlayer);

private:
	Vec3 m_RespawnPoint;
};