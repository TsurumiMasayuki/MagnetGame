#include "Magnet.h"
#include "ForceMap.h"
#include "Component\SpriteRenderer.h"
#include "Component\Physics\BoxCollider2D.h"
#include "Device\GameTime.h"
#include "Actor\IGameMediator.h"

const float Magnet::MAG_MOVE_SPEED = 128.0f;

Magnet::Magnet(IGameMediator * pGameMediator, MagnetOption magOption, bool isMove, bool isMagChange, float width, float height)
	: GameObject(pGameMediator),
	m_MagOption(magOption),
	m_IsMove(isMove),
	m_IsMagChange(isMagChange)
{
	setSize(Vec3(width, height, 0));
}

void Magnet::start()
{
	m_pSprite = new SpriteRenderer(this);
	m_pSprite->setTextureName("BoxFill");
	if (m_MagOption == MAGNET_N)
		m_pSprite->setColor(Color(1, 0, 0, 1));
	else
		m_pSprite->setColor(Color(0, 0, 1, 1));

	auto collider = new BoxCollider2D(this);
	collider->isTrigger = false;
	collider->isMove = m_IsMove;
	collider->setWidth(getSize().x);
	collider->setHeight(getSize().y);
	collider->layer = PhysicsLayer::Magnet;

	m_pNMapRead = getGameMediator()->getNMapRead();
	m_pSMapRead = getGameMediator()->getSMapRead();

	m_pNMapWrite = getGameMediator()->getNMapWrite();
	m_pSMapWrite = getGameMediator()->getSMapWrite();

	setTag("Magnet");
}

void Magnet::update()
{
	writeMagMap();
	readMagMap();
}

void Magnet::onCollisionEnter(GameObject * pHit)
{
	if (pHit->compareTag("MagChangeS"))
		SetMagOption(MAGNET_S);

	if (pHit->compareTag("MagChangeN"))
		SetMagOption(MAGNET_N);
}

void Magnet::onCollisionStay(GameObject * pHit)
{
	if (pHit->compareTag("MagChangeS"))
		SetMagOption(MAGNET_S);

	if (pHit->compareTag("MagChangeN"))
		SetMagOption(MAGNET_N);
}

Magnet::MagnetOption Magnet::getMagOpition()
{
	return m_MagOption;
}

void Magnet::SetMagOption(MagnetOption magOption)
{
	if (!m_IsMagChange) return;

	m_MagOption = magOption;

	if (m_MagOption == MAGNET_N)
		m_pSprite->setColor(Color(1, 0, 0, 1));
	else
		m_pSprite->setColor(Color(0, 0, 1, 1));
}

void Magnet::writeMagMap()
{
	if (m_IsMove) return;

	if (m_MagOption == MAGNET_N)
		m_pNMapWrite->writeForce(getPosition().toVec2(), getSize().toVec2());
	else
		m_pSMapWrite->writeForce(getPosition().toVec2(), getSize().toVec2());
}

void Magnet::readMagMap()
{
	if (!m_IsMove) return;

	int nModifier = m_MagOption == MAGNET_N ? 1 : -1;
	int sModifier = -nModifier;

	Vec2 move;
	move += m_pNMapRead->getForce(getPosition().toVec2(), getSize().toVec2()) * nModifier;
	move += m_pSMapRead->getForce(getPosition().toVec2(), getSize().toVec2()) * sModifier;

	move = move * MAG_MOVE_SPEED * GameTime::getDeltaTime();

	setPosition(getPosition() + move.toVec3());
}
