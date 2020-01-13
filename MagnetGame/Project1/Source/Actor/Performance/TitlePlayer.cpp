#include "TitlePlayer.h"
#include "Device\GameTime.h"

#include "Component\Physics\BoxCollider2D.h"
#include "Component\Physics\Gravity.h"
#include "Actor\DetectHelper.h"
#include "Device\Input.h"

const float TitlePlayer::MOVE_SPEED = 64.0f;

TitlePlayer::TitlePlayer(IGameMediator * nMediator)
	:GameObject(nMediator)
{
}

TitlePlayer::~TitlePlayer()
{
}

void TitlePlayer::start()
{
	setSize(Vec3(64, 64, 0));

	a = 0.0f;

	sprite = new SpriteRenderer(this);
	sprite->setTextureName("BoxOutline");
	sprite->setColor(Color(0, 0, 0, a));

	auto collider = new BoxCollider2D(this);
	collider->isTrigger = false;
	collider->isMove = true;
	collider->setWidth(64);
	collider->setHeight(64);
	collider->layer = PhysicsLayer::Player;

	state = State::Alpha;

	isEndFlag = false;
	m_pMove = false;
}

void TitlePlayer::update()
{
	if (m_pMove) {
		Vec3 move(3.0f*MOVE_SPEED*GameTime::getDeltaTime(), 0, 0);
		setPosition(getPosition() + move);
	}

	Vec3 pos(getPosition());
	float distX = getSize().x*0.5f;

	switch (state)
	{
	case TitlePlayer::Alpha:
		a += 0.01f;
		sprite->setColor(Color(1, 1, 1, a));
		if (a >= 1.0f) {
			state = State::Idle;
		}
		break;
	case TitlePlayer::Idle:
		state = State::Move;
		if (Input::isKeyDown(VK_SPACE)) {
		}
		break;
	case TitlePlayer::Move:
		m_pMove = true;
		if (pos.x >= 640) {
			isEndFlag = true;
		}
		break;
	}
}

void TitlePlayer::onDestroy()
{
}

bool TitlePlayer::IsEnd()
{
	return isEndFlag;
}
