#include "TitlePlayer.h"
#include "Device\GameTime.h"
#include "Device\GameInput.h"
#include "Device\SoundManager.h"

#include "Component\Physics\BoxCollider2D.h"
#include "Component\Physics\Gravity.h"
#include "Component\SpriteRenderer.h"
#include "Component/SpriteAnimation.h"
#include "Component/AnimSpriteRenderer.h"
#include "Actor\DetectHelper.h"
#include "Device\Input.h"

const float TitlePlayer::MOVE_SPEED = 256.0f;

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
	eState = EndingState::eAlpha;

	seCnt = 0;

	isFlipX = false;
	isEndFlag = false;
	go = false;
	m_pMove = false;
	canMove = false;
	isGrobe = false;
}

void TitlePlayer::update()
{

	if (m_pMove) {
		Vec3 move(1.0f*MOVE_SPEED*GameTime::getDeltaTime(), 0, 0);
		setPosition(getPosition() + move);
		seCnt++;
		if (seCnt % 45 == 0) {
			seCnt = 0;
			SoundManager::playSE("walk");
		}
	}

	Vec3 pos(getPosition());
	float distX = getSize().x*0.5f;

	switch (Num)
	{
	case 0://Opening用
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
			anim->setAnimation("FirstRun");
			break;
		case TitlePlayer::Move:
			
			m_pMove = true;
			if (pos.x >= 95)
			{
				if (!isGrobe) {
					anim->setAnimation("FirstIdle");
				}
				else {
					anim->setAnimation("GrobeIdle");
				}
				
				m_pMove = false;
				state = State::Idle2;
			}
			break;
		case TitlePlayer::Idle2:
			if (go) {
				state = State::Move2;
				anim->setAnimation("FirstRun");
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
	case 1://Entrance用
		if (pos.x <= -410) {
			m_pMove = true;
			anim->setAnimation("FirstRun");
		}
		else if(pos.x>-410)
		{
			m_pMove = false;
			if (!isGrobe) {
				anim->setAnimation("FirstIdle");
			}
			else {
				anim->setAnimation("GrobeIdle");
			}
			Num = 2;
		}
		break;
	case 2://Entrance用
		if (canMove) {
			x = GameInput::getHorizontal();

			if (GameInput::getHorizontal() == 0) {

				if (!isGrobe) {
					anim->setAnimation("FirstIdle");
				}
				else {

					anim->setAnimation("GrobeIdle");
				}
			}
			else {
				if (!isGrobe) {
					anim->setAnimation("FirstRun");
				}
				else {
					anim->setAnimation("GrobeRun");
				}
				seCnt++;
				if (seCnt % 45 == 0) {
					seCnt = 0;
					SoundManager::playSE("walk");
				}
			}

			if (GameInput::getHorizontal() < 0)
				isFlipX = true;
			if (GameInput::getHorizontal() > 0)
				isFlipX = false;
			anim->setFlipX(isFlipX);

			if (pos.x <= -608) {
				setPosition(Vec3(-608, -283, 0));
			}
			else if (pos.x >= 608) {
				setPosition(Vec3(608, -283, 0));
			}
		}
		else {
			x = 0;
		}
		break;
	case 3://Roadシーンの時用
		if (pos.x >= 640) {
			m_pMove = false;
		}
		else{
			m_pMove = true;
		}
		anim->setAnimation("FirstRun");
		a = 0;
		break;
	case 4:
		switch (eState)
		{
		case EndingState::eAlpha:
			anim->setAnimation("Idle");
			a += 0.01f;
			anim->setColor(Color(1, 1, 1, a));
			if (a >= 1.5f) {
				eState=EndingState::eMove;
				anim->setAnimation("Run");
			}
			break;
		case EndingState::eMove:
			if (pos.x <= -300) {
				m_pMove = true;
			}
			else {
				eState = EndingState::eIdle;
				m_pMove = false;
			}
			if (pos.y <= -290) {
				y = 0;
			}
			else {
				y -= 0.1f;
			}
			setPosition(Vec3(getPosition().x, getPosition().y + y, 0));
			break;
		case eIdle:
			anim->setAnimation("FirstIdle");
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	Vec3 move(x * MOVE_SPEED * GameTime::getDeltaTime(), 0, 0);
	setPosition(getPosition() + move);
}

void TitlePlayer::onDestroy()
{
}

void TitlePlayer::initAnimations()
{
	anim = new AnimSpriteRenderer(this);
	anim->addAnimation("FirstIdle", new SpriteAnimation("FirstIdle", 160, 32, 0.1f, 5));
	anim->addAnimation("FirstRun", new SpriteAnimation("FirstRun", 256, 32, 0.08f, 8));
	anim->addAnimation("GrobeIdle", new SpriteAnimation("GloveIdle",160,32,0.1f,5));
	anim->addAnimation("GrobeRun", new SpriteAnimation("GloveRun", 256, 32, 0.08f, 8));
	anim->addAnimation("Idle", new SpriteAnimation("PlayerIdle", 160, 32, 0.1f, 5));
	anim->addAnimation("Run", new SpriteAnimation("PlayerRun", 256, 32, 0.08f, 8));
	anim->setAnimation("FirstIdle");
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

void TitlePlayer::setCanMove(bool value)
{
	canMove = value;
}

void TitlePlayer::setIsGrobe(bool value)
{
	isGrobe = value;
}
