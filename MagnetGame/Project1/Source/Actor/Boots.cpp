#include "Boots.h"
#include "Player\Player.h"
#include "Component\Physics\BoxCollider2D.h"
#include "Component\SpriteRenderer.h"
#include"Device/Input.h"

Boots::Boots(IGameMediator * pGameMediator) :
	GameObject(pGameMediator)
{
}

void Boots::start()
{
	setSize(Vec3(64, 64, 0));

	auto sprite = new SpriteRenderer(this,99);
	sprite->setTextureName("boots");

	auto collider = new BoxCollider2D(this);
	collider->setWidth(getSize().x);
	collider->setHeight(getSize().y);
	collider->isMove = false;
	collider->isTrigger = true;

	setPosition(Vec3(getPosition().x, getPosition().y - 16, 0));
}


void Boots::onCollisionStay(GameObject * pHit)
{
	if (pHit->getTag() != "Player")return;
	if (Input::isPadButtonDown(Input::PAD_BUTTON_X) || Input::isKeyDown(VK_SPACE)) {
		((Player*)pHit)->isSuperJump = true;
		this->setActive(false);
	}
}
