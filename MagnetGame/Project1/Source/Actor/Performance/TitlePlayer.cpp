#include "TitlePlayer.h"
#include "Device\GameTime.h"
#include "Device\GameInput.h"

#include "Component\Physics\BoxCollider2D.h"
#include "Component\Physics\Gravity.h"
#include "Component\SpriteRenderer.h"
#include "Component/SpriteAnimation.h"
#include "Component/AnimSpriteRenderer.h"
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

	initAnimations();

	state = State::Alpha;

	isFlipX = false;
	isEndFlag = false;
	go = false;
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

	switch (Num)
	{
	case 0:
		switch (state)
		{
		case TitlePlayer::Alpha:
			a += 0.01f;
			anim->setColor(Color(1, 1, 1, a));
			if (a >= 1.5f) {
				state = State::Idle;
			}
			break;
		case TitlePlayer::Idle:
			state = State::Move;
			anim->setAnimation("Run");
			break;
		case TitlePlayer::Move:
			m_pMove = true;
			if (pos.x >= 210)
			{
				anim->setAnimation("Idle");
				m_pMove = false;
				state = State::Idle2;
			}
			break;
		case TitlePlayer::Idle2:
			if (go) {
				state = State::Move2;
				anim->setAnimation("Run");
				m_pMove = true;
			}
			break;
		case TitlePlayer::Move2:
			if (pos.x >= 600) {
				isEndFlag = true;
			}
			break;
		}
		break;
	case 1:
		if (pos.x <= -560) {
			m_pMove = true;
			anim->setAnimation("Run");
		}
		else if(pos.x>-560)
		{
			m_pMove = false;
			anim->setAnimation("Idle");
			Num = 2;
		}
		break;
	case 2:
		x = GameInput::getHorizontal(); 
		
		if (GameInput::getHorizontal() == 0) {
			anim->setAnimation("Idle");
		}
		else {
			anim->setAnimation("Run");
		}

		if (GameInput::getHorizontal() < 0)
			isFlipX = true;
		if (GameInput::getHorizontal() > 0)
			isFlipX = false;
		anim->setFlipX(isFlipX);

		if (pos.x <= -608) {
			setPosition(Vec3(-608,-283,0));
		}
		else if (pos.x>=608) {
			setPosition(Vec3(608, -283, 0));
		}
		break;
	default:
		break;
	}
	Vec3 move(x*3.0f * MOVE_SPEED * GameTime::getDeltaTime(), 0, 0);
	setPosition(getPosition() + move);
}

void TitlePlayer::onDestroy()
{
}

void TitlePlayer::initAnimations()
{
	anim = new AnimSpriteRenderer(this);
	anim->addAnimation("Idle", new SpriteAnimation("PlayerIdle", 160, 32, 0.1f, 5));
	anim->addAnimation("Run", new SpriteAnimation("PlayerRun", 256, 32, 0.08f, 8));

	anim->setAnimation("Idle");
}


bool TitlePlayer::IsEnd()
{
	return isEndFlag;
}

void TitlePlayer::setIsGo(bool value)
{
	go = value;
}

void TitlePlayer::setNum(int value)
{
	Num = value;
}
