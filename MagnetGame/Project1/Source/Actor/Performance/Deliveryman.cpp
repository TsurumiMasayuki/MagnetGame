#include "Deliveryman.h"

#include "Device\GameTime.h"
#include "Component\SpriteRenderer.h"
#include "Component\Physics\BoxCollider2D.h"
#include "Component\Physics\Gravity.h"
#include "Actor\DetectHelper.h"
#include "Device\Input.h"


const float Deliveryman::MOVE_SPEED = 64.0f;

Deliveryman::Deliveryman(IGameMediator * nMediator)
	:GameObject(nMediator)
{
}

Deliveryman::~Deliveryman()
{
}

void Deliveryman::start()
{

	setSize(Vec3(64, 64, 0));
	state = State::Idle;

	auto sprite = new SpriteRenderer(this);
	sprite->setTextureName("BoxOutline");
	sprite->setColor(Color(255, 255, 0, 1));

	auto col = new BoxCollider2D(this);
	col->isTrigger = false;
	col->isMove = true;
	col->setWidth(64);
	col->setHeight(64);
	col->layer = PhysicsLayer::Player;

	isEndFlag = false;
}

void Deliveryman::update()
{

	Vec3 move(1.5f*MOVE_SPEED*GameTime::getDeltaTime(), 0, 0);
	setPosition(getPosition() + move);
	Vec3 pos(getPosition());
	float distX = getSize().x*0.5f;

	switch (state)
	{
	case Deliveryman::Idle:
		if (Input::isKeyDown(VK_SPACE)) {
			state = State::Move;
		}
		break;
	case Deliveryman::Move:
		if (pos.x == 0) {
			state = State::Anim;
		}
		break;
	case Deliveryman::Anim:
		if (Input::isKeyDown(VK_SPACE)) {
			state = State::Move;
		}
		break;
	}

	if (pos.x < -640) {
		isEndFlag = true;
		destroy();
	}
}

void Deliveryman::onDestroy()
{
}


bool Deliveryman::IsEnd()
{
	return isEndFlag;
}
