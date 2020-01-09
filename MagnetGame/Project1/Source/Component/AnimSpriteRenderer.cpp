#include "AnimSpriteRenderer.h"
#include "Utility\Timer.h"
#include "Component\SpriteAnimation.h"

AnimSpriteRenderer::AnimSpriteRenderer(GameObject* pUser)
	: SpriteRenderer(pUser)
{
}

AnimSpriteRenderer::~AnimSpriteRenderer()
{
	for (auto anim : m_Animations)
	{
		delete anim.second;
	}
}

void AnimSpriteRenderer::onStart()
{
}

void AnimSpriteRenderer::onUpdate()
{
	//アニメーション設定が初期状態だったら何もしない
	if (m_CurrentAnimation.empty()) return;

	auto current = m_Animations.at(m_CurrentAnimation);
	current->update();
	setUVRect(current->getAnimRect());
}

AbstractComponent::TypeID AnimSpriteRenderer::getType() const
{
	return TypeID::TSpriteRenderer;
}

void AnimSpriteRenderer::setAnimation(std::string key)
{	
#ifdef _DEBUG
	int find = m_Animations.count(key);
	assert(find == 0, "設定されたアニメーション名が登録されていません");
#endif

	m_CurrentAnimation = key;
	m_Animations.at(m_CurrentAnimation)->reset();
	setTextureName(m_Animations.at(m_CurrentAnimation)->getTextureName());
}

void AnimSpriteRenderer::addAnimation(std::string key, SpriteAnimation * pSpriteAnim)
{
	m_Animations.emplace(key, pSpriteAnim);
}
