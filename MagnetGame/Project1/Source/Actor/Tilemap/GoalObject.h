#pragma once
#include"Actor/GameObject.h"

class GoalBlock
	:public GameObject
{
public:
	GoalBlock(IGameMediator*gGameMediator,std::string textureName,float width,float height,bool hasCollider=true);
	~GoalBlock();

	virtual void start() override;

	bool IsGoal();
private:
	float m_Width;
	float m_Height;

	bool m_HasColloder;
	std::string m_TextureName;

	bool m_goal;

};
