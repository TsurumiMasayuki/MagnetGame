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
	//�A�j���[�V�����ݒ肪������Ԃ������牽�����Ȃ�
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
	assert(find == 0, "�ݒ肳�ꂽ�A�j���[�V���������o�^����Ă��܂���");
#endif

	m_CurrentAnimation = key;
	m_Animations.at(m_CurrentAnimation)->reset();
	setTextureName(m_Animations.at(m_CurrentAnimation)->getTextureName());
}

void AnimSpriteRenderer::addAnimation(std::string key, SpriteAnimation * pSpriteAnim)
{
	m_Animations.emplace(key, pSpriteAnim);
}
