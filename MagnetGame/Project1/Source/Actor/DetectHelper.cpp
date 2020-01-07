#include "DetectHelper.h"
#include "Component\Physics\BoxCollider2D.h"

DetectHelper::DetectHelper(IGameMediator* pGameMediator, GameObject* pUser, std::initializer_list<std::string> detectTags)
	: GameObject(pGameMediator)
{
	for (auto tag : detectTags)
	{
		m_DetectTags.emplace_back(tag);
	}
}

bool DetectHelper::isDetect()
{
	return m_DetectFlag;
}

bool DetectHelper::isDetect(std::string tag)
{
	int num = 0;
	for (auto collisionTag : m_CollisionTags) {
		if (collisionTag == tag)
			num++;
	}
	if (num != 0) return true;
	return false;
}

void DetectHelper::start()
{
	auto collider = new BoxCollider2D(this);
	collider->setWidth(getSize().x);
	collider->setHeight(getSize().y);
	collider->isMove = false;
	collider->isTrigger = true;
}

void DetectHelper::update()
{
	m_CollisionTags.clear();
	m_DetectFlag = false;
}

void DetectHelper::onCollisionEnter(GameObject * pHit)
{
	m_CollisionTags.emplace_back(pHit->getTag());
	if (compareTags(pHit->getTag()))
		m_DetectFlag = true;
}

void DetectHelper::onCollisionStay(GameObject * pHit)
{
	m_CollisionTags.emplace_back(pHit->getTag());
	if (compareTags(pHit->getTag()))
		m_DetectFlag = true;
}

bool DetectHelper::compareTags(std::string tag)
{
	for (auto compareTag : m_DetectTags)
	{
		if (compareTag == tag)
			return true;
	}

	return false;
}
