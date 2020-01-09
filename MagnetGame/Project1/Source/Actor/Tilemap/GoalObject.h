#pragma once
#include"Actor/GameObject.h"

class GoalBlock
	:public GameObject
{
public:
	GoalBlock(IGameMediator*gGameMediator, std::string textureName, float width, float height);
	~GoalBlock();

	virtual void start() override;
	virtual void onCollisionEnter(GameObject* pHit) override;

private:
	float m_Width;
	float m_Height;
	std::string m_TextureName;
};
