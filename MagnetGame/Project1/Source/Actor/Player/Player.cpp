#include "Player.h"
#include "Utility\State\StateManager.h"

#include "Component\SpriteRenderer.h"
#include "Component\AnimSpriteRenderer.h"
#include "Component\SpriteAnimation.h"
#include "Component\Physics\BoxCollider2D.h"
#include "Component\Physics\Gravity.h"
#include "Actor\DetectHelper.h"
#include "Actor\Player\PlayerState_Respawn.h"
#include "Actor\Effect\SpreadEffect.h"
#include <DirectXColors.h>

#include "PlayerState_Default.h"
#include "Device\GameInput.h"
#include "Device\GameTime.h"
#include "Device\File\CSVReader.h"

const float Player::MOVE_SPEED = 256.0;

Player::Player(IGameMediator * pMediator)
	: GameObject(pMediator), isSuperJump(false), isFlipX(false), m_IsRestart(false), isRespawn(false)
{
	m_pStateManager = new StateManager();
}

Player::~Player()
{
	delete m_pStateManager;
}

void Player::start()
{
	setTag("Player");
	setSize(Vec3(64, 64, 0));

	auto sprite = new SpriteRenderer(this);
	sprite->setTextureName("BoxOutline");

	auto collider = new BoxCollider2D(this);
	collider->isTrigger = false;
	collider->isMove = true;
	collider->setWidth(64);
	collider->setHeight(64);
	collider->layer = PhysicsLayer::Player;
	collider->isPlayer = true;

	m_pGravity = new Gravity(this, 80);
	m_pStateManager->setState(new PlayerState_Default(this));

	initDetectors();
	initMagChange();
	initAnimations();
}

void Player::update()
{
	m_pStateManager->update();

	float x = GameInput::getHorizontal();
	Vec3 move(x * MOVE_SPEED * GameTime::getDeltaTime(), 0, 0);
	setPosition(getPosition() + move);

	moveY();

	Vec3 pos(getPosition());
	float distX = getSize().x * 0.5f;
	float distY = getSize().y * 0.5f;
	m_pDetectUp->setPosition(pos + Vec3(0, 1, 0) * distY);
	m_pDetectDown->setPosition(pos + Vec3(0, -1.1f, 0) * distY);
	m_pDetectRight->setPosition(pos + Vec3(1, 0, 0) * distX);
	m_pDetectLeft->setPosition(pos + Vec3(-1, 0, 0) * distX);
	m_pDetectMid->setPosition(pos + Vec3(0, 0, 0));

	if (GameInput::getHorizontal() < 0)
		isFlipX = true;
	if (GameInput::getHorizontal() > 0)
		isFlipX = false;

	m_pAnimRenderer->setFlipX(isFlipX);


	setMagChange();

	if (isSandwich() && !m_IsRestart)
	{
		m_pStateManager->setState(new PlayerState_Respawn(this));
		m_IsRestart = true;
	}
}

void Player::onDestroy()
{
	m_pMagChange->destroy();

	m_pDetectUp->destroy();
	m_pDetectDown->destroy();
	m_pDetectRight->destroy();
	m_pDetectLeft->destroy();
	m_pDetectMid->destroy();
}

Gravity * Player::getGravity()
{
	return m_pGravity;
}

GameObject * Player::getMagChange()
{
	return m_pMagChange;
}

bool Player::isDetectUp()
{
	return m_pDetectUp->isDetect();
}

bool Player::isDetectDown()
{
	return  m_pDetectDown->isDetect();
}

bool Player::isDetectRight()
{
	return  m_pDetectRight->isDetect();
}

bool Player::isDetectLeft()
{
	return  m_pDetectLeft->isDetect();
}

bool Player::canSuperJump()
{
	return isSuperJump && m_pDetectDown->isDetect("MagnetS");
}

bool Player::isSandwich()
{
	if (m_pDetectMid == nullptr)return false;
	return m_pDetectMid->isDetect();
}

void Player::Respawn()
{
	setPosition(m_RespawnPoint);
	m_pStateManager->forceSetState(new PlayerState_Default(this));
	auto effect = new SpreadEffect(getGameMediator(), Color(DirectX::Colors::LightCyan));
	effect->setPosition(getPosition());

	m_IsRestart = false;

	if (m_pAnimRenderer != nullptr)
	{
		if (!isSuperJump)
			m_pAnimRenderer->setAnimation("Idle");
		else
			m_pAnimRenderer->setAnimation("GBIdle");
	}
}

void Player::SetRespawnPoint(Vec3 pos)
{
	m_RespawnPoint = pos;
}

float Player::GetJumpForce()
{
	return m_JumpForce;
}

void Player::setAnimation(std::string animName)
{
	m_pAnimRenderer->setAnimation(animName);
}

void Player::SetJumpForce(float jumpForce)
{
	m_JumpForce = jumpForce;
}

void Player::initMagChange()
{
	m_pMagChange = new GameObject(m_pGameMediator);
	m_pMagChange->setTag("MagChangeS");
	m_pMagChange->setActive(false);
	m_pMagChange->setSize(Vec3(64, 64, 0));

#ifdef _DEBUG
	//デバッグ用範囲描画
	auto sprite = new SpriteRenderer(m_pMagChange, 90);
	sprite->setTextureName("BoxFill");
	sprite->setColor(Color(0, 0, 1, 1.0f));
#endif

	m_pMagCollider = new BoxCollider2D(m_pMagChange);
	m_pMagCollider->isTrigger = true;
	m_pMagCollider->isMove = false;
	m_pMagCollider->setWidth(64);
	m_pMagCollider->setHeight(4);
	m_pMagCollider->layer = PhysicsLayer::None;
}

void Player::initDetectors()
{
	float sizeX = getSize().x * 0.8f;

	m_pDetectUp = new DetectHelper(m_pGameMediator, this, { "Block", "MagnetN", "MagnetS" });
	m_pDetectUp->setSize(Vec3(sizeX, 6, 0));

	m_pDetectDown = new DetectHelper(m_pGameMediator, this, { "Block", "MagnetN", "MagnetS" });
	m_pDetectDown->setSize(Vec3(sizeX, 6, 0));
	m_pDetectDown->setTag("LandDetector");

	m_pDetectRight = new DetectHelper(m_pGameMediator, this, { "Block", "MagnetN", "MagnetS" });
	m_pDetectRight->setSize(Vec3(6, sizeX, 0));

	m_pDetectLeft = new DetectHelper(m_pGameMediator, this, { "Block", "MagnetN", "MagnetS" });
	m_pDetectLeft->setSize(Vec3(6, sizeX, 0));

	m_pDetectMid = new DetectHelper(m_pGameMediator, this, { "Block", "MagnetN", "MagnetS" });
	m_pDetectMid->setSize(Vec3(16, 16, 0));
}

void Player::initAnimations()
{
	m_pAnimRenderer = new AnimSpriteRenderer(this);
	m_pAnimRenderer->addAnimation("GBIdle", new SpriteAnimation("PlayerIdle", 160, 32, 0.1f, 5));
	m_pAnimRenderer->addAnimation("GBIdleUp", new SpriteAnimation("PlayerIdleUp", 160, 32, 0.1f, 1));
	m_pAnimRenderer->addAnimation("GBIdleDown", new SpriteAnimation("PlayerIdleDown", 160, 32, 0.1f, 1));
	m_pAnimRenderer->addAnimation("GBRun", new SpriteAnimation("PlayerRun", 256, 32, 0.08f, 8));
	m_pAnimRenderer->addAnimation("GBJump", new SpriteAnimation("PlayerJump", 224, 32, 0.1f, 7));
	m_pAnimRenderer->addAnimation("GBSJump", new SpriteAnimation("PlayerSJump", 224, 40, 0.3f, 7));
	m_pAnimRenderer->addAnimation("GBPunchLR", new SpriteAnimation("PlayerPunch", 160, 32, 0.1f, 3));
	m_pAnimRenderer->addAnimation("GBPunchUp", new SpriteAnimation("PlayerPunch_Up", 128, 32, 0.2f, 2));
	m_pAnimRenderer->addAnimation("GBPunchDown", new SpriteAnimation("PlayerPunch_Down", 128, 32, 0.2f, 2));

	m_pAnimRenderer->addAnimation("Idle", new SpriteAnimation("GloveIdle", 160, 32, 0.1f, 5));
	m_pAnimRenderer->addAnimation("IdleUp", new SpriteAnimation("GloveIdleUp", 160, 32, 0.1f, 1));
	m_pAnimRenderer->addAnimation("IdleDown", new SpriteAnimation("GloveIdleDown", 160, 32, 0.1f, 1));
	m_pAnimRenderer->addAnimation("Run", new SpriteAnimation("GloveRun", 256, 32, 0.08f, 8));
	m_pAnimRenderer->addAnimation("Jump", new SpriteAnimation("GloveJump", 224, 32, 0.1f, 7));
	m_pAnimRenderer->addAnimation("PunchLR", new SpriteAnimation("GlovePunch", 160, 32, 0.1f, 3));
	m_pAnimRenderer->addAnimation("PunchUp", new SpriteAnimation("GlovePunch_Up", 128, 32, 0.2f, 2));
	m_pAnimRenderer->addAnimation("PunchDown", new SpriteAnimation("GlovePunch_Down", 128, 32, 0.2f, 2));

	m_pAnimRenderer->setAnimation("Idle");
}

void Player::moveY()
{
	float deltaTime = GameTime::getDeltaTime();

	m_JumpForce -= m_pGravity->getGravSpeed() * deltaTime *  m_pGravity->getGravSpeed() * deltaTime;

	Vec3 move(0, std::fmaxf(0, m_JumpForce * deltaTime), 0);
	setPosition(getPosition() + move);
}

void Player::setMagChange()
{
	Vec3 MagChangeDir = GameInput::getMagChangeDir().toVec3();
	if (MagChangeDir.x == 0 && MagChangeDir.y == 0)
		MagChangeDir = isFlipX ? Vec3(-1, 0, 0) : Vec3(1, 0, 0);
	Vec3 MagChangePos = Vec3(getSize().x * MagChangeDir.x, getSize().y * MagChangeDir.y, 0) / 2;
	m_pMagChange->setPosition(getPosition() + MagChangePos);

	float size = getSize().x * 0.9f;

	Vec3 MagChangeSize = MagChangeDir.y != 0 ? Vec3(size, 32, 0) : Vec3(4, size, 0);
	m_pMagChange->setSize(MagChangeSize);

	m_pMagCollider->setWidth(MagChangeSize.x);
	m_pMagCollider->setHeight(MagChangeSize.y);
}
