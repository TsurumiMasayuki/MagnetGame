#include "GoalObject.h"
#include "Component\SpriteRenderer.h"
#include "Component\Physics\BoxCollider2D.h"
#include "Actor\IGameMediator.h"
#include "Actor\Magnet\ObstacleMap.h"


GoalBlock::GoalBlock(IGameMediator * gGameMediator, std::string textureName, float width, float height, bool hasCollider)
	:GameObject(gGameMediator),
	m_TextureName(textureName),
	m_Width(width),
	m_Height(height),
	m_HasColloder(hasCollider)
{
}

GoalBlock::~GoalBlock()
{
}

void GoalBlock::start()
{
	setTag("Goal");

	auto sprite = new SpriteRenderer(this);
	sprite->setTextureName(m_TextureName);
	sprite->setColor(Color(255,255,0, 1));

	if (m_HasColloder) {
		auto collider = new BoxCollider2D(this);
		collider->isTrigger = false;
		collider->isMove = false;
		collider->setWidth(m_Width);
		collider->setHeight(m_Height);
		collider->layer = PhysicsLayer::Block;

		//getGameMediator()->getObstacleMap()->writeStaticObstacle(getPosition().toVec2(), getSize().toVec2());
	}

	setSize(Vec3(m_Width, m_Height, 0));
}

bool GoalBlock::IsGoal()
{
	return m_goal;
}
