#include "GoalObject.h"
#include "Component\SpriteRenderer.h"
#include "Component\Physics\BoxCollider2D.h"
#include "Actor\IGameMediator.h"
#include "Actor\Magnet\ObstacleMap.h"


GoalBlock::GoalBlock(IGameMediator * gGameMediator, std::string textureName, float width, float height)
	:GameObject(gGameMediator),
	m_TextureName(textureName),
	m_Width(width),
	m_Height(height)
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
	
	auto collider = new BoxCollider2D(this);
	collider->isTrigger = true;
	collider->isMove = false;
	collider->setWidth(m_Width);
	collider->setHeight(m_Height);
	collider->layer = PhysicsLayer::Block;

	setSize(Vec3(m_Width, m_Height, 0));
}

void GoalBlock::onCollisionEnter(GameObject * pHit)
{
	if (pHit->compareTag("Player"))
	{
		m_pGameMediator->gameEnd();
	}
}
