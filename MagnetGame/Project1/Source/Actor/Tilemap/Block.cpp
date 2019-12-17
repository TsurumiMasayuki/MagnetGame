#include "Block.h"
#include "Component\SpriteRenderer.h"
#include "Component\Physics\BoxCollider2D.h"

Block::Block(IGameMediator* pGameMediator, std::string textureName, float width, float height)
	: GameObject(pGameMediator),
	m_TextureName(textureName),
	m_Width(width),
	m_Height(height)
{
}

Block::~Block()
{
}

void Block::start()
{
	auto sprite = new SpriteRenderer(this);
	sprite->setTextureName(m_TextureName);
	sprite->setColor(Color(0.25f, 0.25f, 0.25f, 1));

	auto collider = new BoxCollider2D(this);
	collider->isTrigger = false;
	collider->isMove = false;
	collider->setWidth(m_Width);
	collider->setHeight(m_Height);
	collider->layer = PhysicsLayer::Block;

	setSize(Vec3(m_Width, m_Height, 0));
}
