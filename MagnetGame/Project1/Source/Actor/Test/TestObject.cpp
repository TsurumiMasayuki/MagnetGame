#include "TestObject.h"
#include "Component\SpriteRenderer.h"
#include "Component\Physics\BoxCollider2D.h"
#include "Component\Physics\Gravity.h"
#include "Utility\Timer.h"
#include "Actor\IGameMediator.h"
#include "Def\Screen.h"
#include "Device\GameTime.h"

TestObject::TestObject(IGameMediator * pMediator)
	: GameObject(pMediator)
{
}

TestObject::~TestObject()
{
}

void TestObject::start()
{
	auto sprite = new SpriteRenderer(this);
	sprite->setTextureName("BoxOutline");

	auto collider = new BoxCollider2D(this);
	collider->isTrigger = false;
	collider->isMove = true;
	collider->setWidth(64);
	collider->setHeight(64);
	collider->layer = PhysicsLayer::Player;

	new Gravity(this, 100);

	setSize(Vec3(64, 64, 0));
}

void TestObject::update()
{
}
