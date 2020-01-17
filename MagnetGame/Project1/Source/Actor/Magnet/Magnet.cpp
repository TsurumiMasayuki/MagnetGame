#include "Magnet.h"
#include "ForceMap.h"
#include "Component\SpriteRenderer.h"
#include "Component\Physics\BoxCollider2D.h"
#include "Device\GameTime.h"
#include "Actor\IGameMediator.h"
#include "Actor\DetectHelper.h"
#include "Actor\Effect\SpreadEffect.h"
#include <DirectXColors.h>

const float Magnet::MAG_MOVE_SPEED = 128.0f;

Magnet::Magnet(IGameMediator * pGameMediator, MagnetOption magOption, bool isMove, bool isMagChange, float width, float height)
	: GameObject(pGameMediator),
	m_MagOption(magOption),
	m_IsMove(isMove),
	m_IsMagChange(isMagChange)
{
	setSize(Vec3(width, height, 0));
}

Magnet::~Magnet()
{
}

void Magnet::start()
{
	m_pSprite = new SpriteRenderer(this);
	if (m_IsMove)
		m_pSprite->setTextureName("BoxOutline");
	else
		m_pSprite->setTextureName("BoxFill");

	if (m_MagOption == MAGNET_N)
		m_pSprite->setColor(Color(1, 0, 0, 1));
	else
		m_pSprite->setColor(Color(0, 0, 1, 1));

	if (!m_IsMagChange)
	{
		auto noMagChangeSprite = new SpriteRenderer(this, 110);
		noMagChangeSprite->setTextureName("Cross");
		noMagChangeSprite->setColor(Color(DirectX::Colors::Brown));
		noMagChangeSprite->setUVRect(RectF(0, 0, getSize().x / 64, getSize().y / 64));
	}

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

	if (m_MagOption == MAGNET_N)
		setTag("MagnetN");
	else
		setTag("MagnetS");
}

void Magnet::update()
{
	writeMagMap();
	readMagMap();
	if (m_pRider != nullptr)
		m_pRider->setPosition(m_pRider->getPosition() + Vec3(m_Velocity.x, m_Velocity.y, 0));
}

void Magnet::onCollisionEnter(GameObject * pHit)
{
	setMagOption(pHit);

	if (pHit->compareTag("LandDetector"))
		m_pRider = ((DetectHelper*)pHit)->getUser();
}

void Magnet::onCollisionStay(GameObject * pHit)
{
	setMagOption(pHit);
}

void Magnet::onCollisionExit(GameObject * pHit)
{
	if (pHit->compareTag("LandDetector"))
		m_pRider = nullptr;
}

Magnet::MagnetOption Magnet::getMagOpition()
{
	return m_MagOption;
}

void Magnet::setMagOption(GameObject* pHit)
{
	//Ž¥—Í•ÏX•s‰Â‚È‚çreturn
	if (!m_IsMagChange) return;
	//•ÏX‚ª–³‚¢‚È‚çreturn

	MagnetOption magOption;

	if (pHit->compareTag("MagChangeS"))
		magOption = MAGNET_S;
	else if (pHit->compareTag("MagChangeN"))
		magOption = MAGNET_N;
	else
		return;

	if (m_MagOption == magOption) return;

	m_MagOption = magOption;
	Vec3 effectDir = (getPosition() - pHit->getPosition()).normalized();
	effectDir.x *= pHit->getSize().x / 2;
	effectDir.y *= pHit->getSize().y / 2;
	Vec3 effectPos = pHit->getPosition() + effectDir;

	if (m_MagOption == MAGNET_N)
	{
		m_pSprite->setColor(Color(1, 0, 0, 1));
		setTag("MagnetN");
		auto effect = new SpreadEffect(m_pGameMediator, Color(1, 0.3f, 0, 1));
		effect->setPosition(effectPos);
	}
	else
	{
		m_pSprite->setColor(Color(0, 0, 1, 1));
		setTag("MagnetS");
		auto effect = new SpreadEffect(m_pGameMediator, Color(0.3f, 0.5f, 1.0f, 1));
		effect->setPosition(effectPos);
	}
}

Vec2 Magnet::getVelocity()
{
	return m_Velocity;
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

	m_Velocity = Vec2::zero();
	m_Velocity += m_pNMapRead->getForce(getPosition().toVec2(), getSize().toVec2()) * nModifier;
	m_Velocity += m_pSMapRead->getForce(getPosition().toVec2(), getSize().toVec2()) * sModifier;

	m_Velocity = m_Velocity * MAG_MOVE_SPEED * GameTime::getDeltaTime();

	setPosition(getPosition() + m_Velocity.toVec3());
}
