#include "PhysicsWorld.h"
#include "Component\Physics\AbstractCollider2D.h"
#include "Physics\PhysicsLayer.h"

PhysicsWorld::PhysicsWorld(IGameMediator * pMediator)
	: m_pGameMediator(pMediator)
{
}

PhysicsWorld::~PhysicsWorld()
{
}

void PhysicsWorld::update()
{
	for (auto collider : m_ColliderList2D)
	{
		collider->checkHitStates();
		collider->clearHitStates();
	}
}

void PhysicsWorld::checkCollision(AbstractCollider2D * pCollider)
{
	//�A�N�e�B�u��ԂłȂ��Ȃ牽�����Ȃ�
	if (!pCollider->isActive()) return;

	//���̃R���C�_�[�Ƒ�������
	for (auto other : m_ColliderList2D)
	{
		//���C���[�̃`�F�b�N
		if (!PhysicsLayer::isHitLayer(pCollider->layer, other->layer)) continue;

		//���g�Ƃ͔�����s��Ȃ�
		if (pCollider == other) continue;
		//�A�N�e�B�u��ԂłȂ��R���C�_�[�Ƃ͉������Ȃ�
		if (!other->isActive()) continue;

		//�Փ˔���
		if (!pCollider->isCollision(other)) continue;
		//�ڐG���������Ăяo��
		pCollider->onCollision(other);

		if (other->isPlayer) continue;
		if (!pCollider->isMove) continue;
		if (pCollider->isTrigger || other->isTrigger) continue;

		//�ڐG�ɍ��킹�Ĉʒu��ύX
		pCollider->fixPosition(other);
	}
}

void PhysicsWorld::addCollider(AbstractCollider2D * pCollider)
{
	m_ColliderList2D.emplace_back(pCollider);
}

void PhysicsWorld::removeCollider(AbstractCollider2D * pCollider)
{
	//�����ɍ폜�Ώۂ��ړ�����popback;
	auto itr = std::find(m_ColliderList2D.begin(), m_ColliderList2D.end(), pCollider);
	if (itr != m_ColliderList2D.end())
	{
		std::iter_swap(itr, m_ColliderList2D.end() - 1);
		m_ColliderList2D.pop_back();
	}
}

bool PhysicsWorld::checkCollisionDistance(AbstractCollider2D* coll1, AbstractCollider2D* coll2)
{
	return true;
}
