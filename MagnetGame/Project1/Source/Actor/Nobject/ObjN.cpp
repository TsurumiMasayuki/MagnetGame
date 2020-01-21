#include "ObjN.h"
#include "Device\GameTime.h"
#include "Utility\State\StateManager.h"

#include "Component\SpriteRenderer.h"
#include "Component/SpriteAnimation.h"
#include "Component/AnimSpriteRenderer.h"
#include "Component\Physics\BoxCollider2D.h"
#include "Component\Physics\Gravity.h"
#include "Actor\DetectHelper.h"
#include "Device\Input.h"

const float ObjN::MOVE_SPEED = 64.0f;

ObjN::ObjN(IGameMediator * nMediator, int dir, float speedModifier)
	:GameObject(nMediator),
	m_SpeedModifier(speedModifier)
{
	//m_nStateManager = new StateManager();
	direction = dir;
}

ObjN::~ObjN()
{
	//delete m_nStateManager;
}

void ObjN::start()
{
	setSize(Vec3(64, 64, 0));

	anim= new AnimSpriteRenderer(this);
	anim->addAnimation("Walk", new SpriteAnimation("n", 128, 32, 0.08f, 4));
	anim->setAnimation("Walk");

	auto collider = new BoxCollider2D(this);
	collider->isTrigger = false;
	collider->isMove = true;
	collider->setWidth(64);
	collider->setHeight(64);
	collider->layer = PhysicsLayer::Player;

	m_nGravity = new Gravity(this, 20);



	setTag("ObjN");

	initMagChange();
	initDetectors();

}

void ObjN::update()
{

	//移動処理
	switch (direction)
	{
	case 0:
		x = 1.0f;
		break;
	case 1:
		x = -1.0f;
		break;
	}

	Vec3 move(x * MOVE_SPEED * m_SpeedModifier * GameTime::getDeltaTime(), 0, 0);
	setPosition(getPosition() + move);

	Vec3 pos(getPosition());
	float distX = getSize().x*0.5f;
	float distY = getSize().y*0.5f;


	m_nDetectLeft->setPosition(pos + Vec3(-1, 0, 0)*distX);
	m_nDetectRight->setPosition(pos + Vec3(1, 0, 0)*distX);

	if (isDetectLeft() && direction == 1) {
		direction = 0;
		anim->setFlipX(true);
	}

	if (isDetectRight() && direction == 0) {
		direction = 1;
		anim->setFlipX(false);
	}


	m_nMagChange->setPosition(getPosition());
}

void ObjN::onDestroy()
{
	m_nMagChange->destroy();

	m_nDetectLeft->destroy();
	m_nDetectRight->destroy();
}


void ObjN::onCollisionEnter(GameObject * nHit)
{
	
}

void ObjN::onCollisionStay(GameObject * nHit)
{

}

Gravity * ObjN::getGravity()
{
	return m_nGravity;
}

GameObject * ObjN::getMagChange()
{
	return m_nMagChange;
}

bool ObjN::isDetectLeft()
{
	return m_nDetectLeft->isDetect();
}

bool ObjN::isDetectRight()
{
	return m_nDetectRight->isDetect();
}

void ObjN::initMagChange()
{
	m_nMagChange = new GameObject(m_pGameMediator);
	m_nMagChange->setTag("MagChangeN");
	m_nMagChange->setSize(Vec3(96, 96, 0));

#ifdef _DEBUG
	//デバッグ用範囲描画
	/*auto sprite = new SpriteRenderer(m_nMagChange, 90);
	sprite->setTextureName("BoxFill");
	sprite->setColor(Color(0, 0, 1, 0.5f));*/
#endif // _DEBUG

	auto collider = new BoxCollider2D(m_nMagChange);
	collider->isTrigger = true;
	collider->isMove = false;
	collider->setWidth(96);
	collider->setHeight(96);
	collider->layer = PhysicsLayer::None;
}

void ObjN::initDetectors()
{
	float sizeX = getSize().x*0.8f;

	m_nDetectLeft = new DetectHelper(m_pGameMediator, this, { "Block","MagnetN" ,"MagnetS" });
	m_nDetectLeft->setSize(Vec3(6, sizeX, 0));

	m_nDetectRight = new DetectHelper(m_pGameMediator, this, { "Block","MagnetN" ,"MagnetS" });
	m_nDetectRight->setSize(Vec3(6, sizeX, 0));
}
