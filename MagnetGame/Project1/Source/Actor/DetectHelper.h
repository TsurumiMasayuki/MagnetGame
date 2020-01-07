#pragma once
#include "Actor\GameObject.h"
#include <string>
#include <vector>
#include <initializer_list>

class DetectHelper
	: public GameObject
{
public:
	DetectHelper(IGameMediator* pGameMediator, GameObject* pUser, std::initializer_list<std::string> detectTags);

	bool isDetect();
	bool isDetect(std::string tag);

	virtual void start() override;
	virtual void update() override;

	virtual void onCollisionEnter(GameObject* pHit) override;
	virtual void onCollisionStay(GameObject* pHit) override;

private:
	bool compareTags(std::string tag);

private:
	bool m_DetectFlag;
	std::vector<std::string> m_DetectTags;
	std::vector<std::string> m_CollisionTags;
	GameObject* m_pUser;
};