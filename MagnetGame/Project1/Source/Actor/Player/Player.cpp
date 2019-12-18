#include "Player.h"
#include "Utility\State\StateManager.h"

#include "Component\SpriteRenderer.h"
#include "Component\Physics\BoxCollider2D.h"
#include "Component\Physics\Gravity.h"
#include "Actor\DetectHelper.h"

#include "PlayerState_Default.h"
#include "Device\Input.h"
#include "Device\GameTime.h"

const float Player::MOVE_SPEED = 64.0f;

Player::Player(IGameMediator * pMediator)
	: GameObject(pMediator), isSuperJump(true)
{
	m_pStateManager = new StateManager();
}

Player::~Player()
{
	delete m_pStateManager;
}

void Player::start()
{
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

	m_pGravity = new Gravity(this, 1);
	m_pStateManager->setState(new PlayerState_Default(this));

	initMagChange();
	initDetectors();
}

void Player::update()
{
	m_pStateManager->update();

	float x = 0.0f;

	if (Input::isKey(VK_LEFT))
		x -= 1.0f;

	if (Input::isKey(VK_RIGHT))
		x += 1.0f;

	Vec3 move(x * MOVE_SPEED * GameTime::getDeltaTime(), 0, 0);
	setPosition(getPosition() + move);

	Vec3 pos(getPosition());
	float distX = getSize().x * 0.5f;
	float distY = getSize().y * 0.5f;
	m_pDetectUp->setPosition(pos + Vec3(0, 1, 0) * distY);
	m_pDetectDown->setPosition(pos + Vec3(0, -1, 0) * distY);
	m_pDetectRight->setPosition(pos + Vec3(1, 0, 0) * distX);
	m_pDetectLeft->setPosition(pos + Vec3(-1, 0, 0) * distX);
}

void Player::onDestroy()
{
	m_pMagChange->destroy();

	m_pDetectUp->destroy();
	m_pDetectDown->destroy();
	m_pDetectRight->destroy();
	m_pDetectLeft->destroy();
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

void Player::initMagChange()
{
	m_pMagChange = new GameObject(m_pGameMediator);
	m_pMagChange->setTag("MagChangeS");
	//m_pMagChange->setActive(false);
	m_pMagChange->setSize(Vec3(64, 64, 0));

#ifdef _DEBUG
	//�f�o�b�O�p�͈͕`��
	auto sprite = new SpriteRenderer(m_pMagChange, 90);
	sprite->setTextureName("BoxFill");
	sprite->setColor(Color(0, 0, 1, 0.5f));
#endif

	auto collider = new BoxCollider2D(m_pMagChange);
	collider->isTrigger = true;
	collider->isMove = false;
	collider->setWidth(64);
	collider->setHeight(64);
	collider->layer = PhysicsLayer::None;
}

void Player::initDetectors()
{
	float sizeX = getSize().x * 0.8f;

	m_pDetectUp = new DetectHelper(m_pGameMediator, this, { "Block", "Magnet" });
	m_pDetectUp->setSize(Vec3(sizeX, 6, 0));

	m_pDetectDown = new DetectHelper(m_pGameMediator, this, { "Block", "Magnet" });
	m_pDetectDown->setSize(Vec3(sizeX, 6, 0));

	m_pDetectRight = new DetectHelper(m_pGameMediator, this, { "Block", "Magnet" });
	m_pDetectRight->setSize(Vec3(6, sizeX, 0));

	m_pDetectLeft = new DetectHelper(m_pGameMediator, this, { "Block", "Magnet" });
	m_pDetectLeft->setSize(Vec3(6, sizeX, 0));
}
