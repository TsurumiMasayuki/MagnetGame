#include "Board.h"
#include "Player\Player.h"
#include "Component\Physics\BoxCollider2D.h"
#include "Component\SpriteRenderer.h"
#include"Device/Input.h"

Board::Board(IGameMediator * pMediator)
	:GameObject(pMediator)
{

}

Board::~Board()
{
}

void Board::start()
{
	setSize(Vec3(64, 64, 0));

	auto sprite = new SpriteRenderer(this, 99);
	sprite->setTextureName("kanban");

	auto collider = new BoxCollider2D(this);
	collider->setWidth(getSize().x);
	collider->setHeight(getSize().y);
	collider->isMove = false;
	collider->isTrigger = true;

	setPosition(Vec3(getPosition().x, getPosition().y - 16, 0));
}

void Board::onCollisionStay(GameObject * pHit)
{
	if (pHit->getTag() != "Player") return;
		((Player*)pHit)->m_isHint = true;
}

void Board::onCollisionExit(GameObject * pHit)
{
	if (pHit->getTag() != "Player") return;
	((Player*)pHit)->m_isHint = false;
}
