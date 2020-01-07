#include "CheckPoint.h"
#include "Component\Physics\BoxCollider2D.h"
#include "Actor\Player\Player.h"
#include "Component\SpriteRenderer.h"
#include <DirectXColors.h>

CheckPoint::CheckPoint(IGameMediator* pGameMediator, Vec3 RespawnPoint)
	: GameObject(pGameMediator),
	m_RespawnPoint(RespawnPoint)
{
}

CheckPoint::~CheckPoint()
{
}

void CheckPoint::start()
{
	setSize(Vec3(64, 64, 0));

	auto sprite = new SpriteRenderer(this);
	sprite->setTextureName("BoxOutline");
	sprite->setColor(Color(1, 1, 1, 1));

	auto collider = new BoxCollider2D(this);
	collider->isTrigger = true;
	collider->isMove = true;
	collider->setWidth(64);
	collider->setHeight(64);
	collider->layer = PhysicsLayer::Block;
	collider->isPlayer = true;
}

void CheckPoint::update()
{
}

//触れたら書き込む
void CheckPoint::onCollisionEnter(GameObject * pHit)
{
	if (pHit->getTag() != "Player")return;
	WriteRespawnPoint((Player*)pHit);
}

//playerにリスポ場所のデータを書き込み
void CheckPoint::WriteRespawnPoint(Player* pPlayer)
{
	pPlayer->SetRespawnPoint(m_RespawnPoint);
}
