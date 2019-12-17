#include "Player.h"
#include "Utility\State\StateManager.h"

#include "Component\SpriteRenderer.h"
#include "Component\Physics\BoxCollider2D.h"
#include "Component\Physics\Gravity.h"

#include "PlayerState_Default.h"
#include "Device\Input.h"
#include "Device\GameTime.h"

const float Player::MOVE_SPEED = 64.0f;

Player::Player(IGameMediator * pMediator)
	: GameObject(pMediator)
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
}

void Player::update()
{
	m_pStateManager->update();

	float x = 0.0f;

	if (Input::isKey('A'))
		x -= 1.0f;

	if (Input::isKey('D'))
		x += 1.0f;

	Vec3 move(x * MOVE_SPEED * GameTime::getDeltaTime(), 0, 0);
	setPosition(getPosition() + move);
}

Gravity * Player::getGravity()
{
	return m_pGravity;
}
