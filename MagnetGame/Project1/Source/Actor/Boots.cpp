#include "Boots.h"
#include "Player\Player.h"
#include "Component\Physics\BoxCollider2D.h"
#include "Component\SpriteRenderer.h"

Boots::Boots(IGameMediator * pGameMediator) :
	GameObject(pGameMediator)
{
}

void Boots::start()
{
	setSize(Vec3(32, 32, 0));

	auto sprite = new SpriteRenderer(this);
	sprite->setTextureName("boots");

	auto collider = new BoxCollider2D(this);
	collider->setWidth(getSize().x);
	collider->setHeight(getSize().y);
	collider->isMove = false;
	collider->isTrigger = true;
}

void Boots::onCollisionEnter(GameObject * pHit)
{
	if (pHit->getTag() != "Player")return;
	((Player*)pHit)->isSuperJump = true;
	this->setActive(false);
}
