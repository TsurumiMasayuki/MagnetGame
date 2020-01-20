#include "Magnet.h"
#include "ForceMap.h"
#include "Component\SpriteRenderer.h"
#include "Component\MultiSpriteRenderer.h"
#include "Component\Physics\BoxCollider2D.h"
#include "Device\GameTime.h"
#include "Actor\IGameMediator.h"
#include "Actor\DetectHelper.h"
#include "Actor\Effect\SpreadEffect.h"
#include "Actor\Effect\LineEffect.h"
#include <DirectXColors.h>
#include "Math\MathUtility.h"

const float Magnet::MAG_MOVE_SPEED = 128.0f;

Magnet::Magnet(IGameMediator * pGameMediator, MagnetOption magOption, bool isMove, bool isMagChange, float width, float height)
	: GameObject(pGameMediator),
	m_MagOption(magOption),
	m_IsMove(isMove),
	m_IsMagChange(isMagChange),
	m_PrePosition(getPosition())
{
	setSize(Vec3(width, height, 0));
}

Magnet::~Magnet()
{
}

void Magnet::start()
{
	if (!m_IsMove)
	{
		auto noMagChangeSprite = new SpriteRenderer(this, 110);
		noMagChangeSprite->setTextureName("Cross");
		noMagChangeSprite->setColor(Color(DirectX::Colors::MediumPurple));
		noMagChangeSprite->setUVRect(RectF(0, 0, getSize().x / 32, getSize().y / 32));
	}

	m_pSprite = new MultiSpriteRenderer(this, 32);
	std::string lockTexture = m_IsMagChange ? "" : "Stop";

	if (m_MagOption == MAGNET_N)
		m_pSprite->setTextureName("NBlock" + lockTexture);
	else
		m_pSprite->setTextureName("SBlock" + lockTexture);

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
	{
		Vec3 vel = getPosition() - m_PrePosition;
		Vec3 move = Vec3(vel.x, MathUtility::clamp(m_Velocity.y, -128.0f, 0), 0);
		m_pRider->setPosition(m_pRider->getPosition() + move);
	}
	m_PrePosition = getPosition();
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
	//磁力変更不可ならreturn
	if (!m_IsMagChange) return;
	//変更が無いならreturn

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
		setTag("MagnetN");
		auto effect = new SpreadEffect(m_pGameMediator, Color(1, 0.3f, 0, 1));
		effect->setPosition(effectPos);
	}
	else
	{
		setTag("MagnetS");
		auto effect = new SpreadEffect(m_pGameMediator, Color(0.3f, 0.5f, 1.0f, 1));
		effect->setPosition(effectPos);
	}

	std::string lockTexture = m_IsMagChange ? "" : "Stop";

	if (m_MagOption == MAGNET_N)
		m_pSprite->setTextureName("NBlock" + lockTexture);
	else
		m_pSprite->setTextureName("SBlock" + lockTexture);
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

	Vec2 curNForce;
	Vec2 curSForce;

	m_Velocity = Vec2::zero();
	curNForce = m_pNMapRead->getForce(getPosition().toVec2(), getSize().toVec2()) * nModifier;
	curSForce = m_pSMapRead->getForce(getPosition().toVec2(), getSize().toVec2()) * sModifier;

	m_Velocity = (curNForce + curSForce) * MAG_MOVE_SPEED * GameTime::getDeltaTime();

	setPosition(getPosition() + m_Velocity.toVec3());

	Color nColor = Color(DirectX::Colors::Red);
	nColor.a = 0.5f;
	magForceEffect(curNForce, m_PreNForce, nColor);

	Color sColor = Color(DirectX::Colors::Blue);
	sColor.a = 0.5f;
	magForceEffect(curSForce, m_PreSForce, sColor);

	m_PreNForce = curNForce;
	m_PreSForce = curSForce;
}

void Magnet::magForceEffect(const Vec2& currentForce, const Vec2& previousForce, Color effectColor)
{
	float curSignX = MathUtility::sign(currentForce.x);
	float preSignX = MathUtility::sign(previousForce.x);

	//横方向の力を受けたら
	if (curSignX != preSignX && m_Velocity.x != 0)
	{
		float particleAngle = curSignX > 0 ? 0 : 180;

		auto effect = new LineEffect(m_pGameMediator, 90, particleAngle, 0.5f, getSize().y, 20, effectColor);
		effect->setPosition(getPosition());
	}

	float curSignY = MathUtility::sign(currentForce.y);
	float preSignY = MathUtility::sign(previousForce.y);

	//縦方向の力を受けたら
	if (curSignY != preSignY && m_Velocity.y != 0)
	{
		float particleAngle = curSignY > 0 ? 90 : 270;

		auto effect = new LineEffect(m_pGameMediator, 0, particleAngle, 0.5f, getSize().x, 20, effectColor);
		effect->setPosition(getPosition());
	}
}
