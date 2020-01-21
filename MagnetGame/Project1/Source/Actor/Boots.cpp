#include "Boots.h"
#include "Player\Player.h"
#include "Component\Physics\BoxCollider2D.h"
#include "Component\SpriteRenderer.h"

Boots::Boots(IGameMediator * pGameMediator, Player * pPlayer) :
	GameObject(pGameMediator),
	m_pPlayer(pPlayer)
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
	m_pPlayer->isSuperJump = true;
	this->setActive(false);
}
