#include "Deliveryman.h"

#include "Device\GameTime.h"
#include "Component\SpriteRenderer.h"
#include "Component/SpriteAnimation.h"
#include "Component/AnimSpriteRenderer.h"
#include "Component\Physics\BoxCollider2D.h"
#include "Component\Physics\Gravity.h"
#include "Actor\DetectHelper.h"
#include "Device\Input.h"
#include"Device/SoundManager.h"


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

	anim = new AnimSpriteRenderer(this);
	anim->addAnimation("Move", new SpriteAnimation("yagi", 128, 32, 0.12f, 4));
	anim->setAnimation("Move");
	anim->setFlipX(true);

	auto col = new BoxCollider2D(this);
	col->isTrigger = false;
	col->isMove = true;
	col->setWidth(64);
	col->setHeight(64);
	col->layer = PhysicsLayer::Player;

	isEndFlag = false;
	m_pMove = false;
}

void Deliveryman::update()
{
	if (m_pMove) {
		Vec3 move(-3.0f*MOVE_SPEED*GameTime::getDeltaTime(), 0, 0);
		setPosition(getPosition() + move);
	}
	Vec3 pos(getPosition());
	float distX = getSize().x*0.5f;
	switch (state)
	{
	case Deliveryman::Idle:
		if (Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A)) {
			state = State::Move;
			SoundManager::playSE("bike");
		}
		break;
	case Deliveryman::Move:
		m_pMove = true;
		if (pos.x <= 270) {
			state = State::Anim;
		}
		break;
	case Deliveryman::Anim:
		m_pMove = false;
		if (Input::isKeyDown(VK_SPACE) || Input::isPadButtonDown(Input::PAD_BUTTON_A)) {
			state = State::Move2;
			SoundManager::playSE("bike",1);
		}
		break;
	case Deliveryman::Move2:
		m_pMove = true;
		if (pos.x <= -670) {
			destroy();
		}
		break;
	}

}

void Deliveryman::onDestroy()
{
}


bool Deliveryman::IsEnd()
{
	return isEndFlag;
}
