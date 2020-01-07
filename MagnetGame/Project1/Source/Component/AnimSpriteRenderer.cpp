#include "AnimSpriteRenderer.h"
#include "Utility\Timer.h"
#include "Math\MathUtility.h"

AnimSpriteRenderer::AnimSpriteRenderer(
	GameObject* pUser,
	float textureWidth,
	float textureHeight,
	float animTime,
	int columnCount,
	int rowCount)
	: SpriteRenderer(pUser),
	m_CellWidth(textureWidth / columnCount / textureWidth),
	m_CellHeight(textureHeight / rowCount / textureHeight),
	m_TextureWidth(textureWidth),
	m_TextureHeight(textureHeight),
	m_pTimer(new Timer(animTime)),
	m_XPos(0),
	m_YPos(0),
	m_AnimCount(columnCount)
{
}

AnimSpriteRenderer::~AnimSpriteRenderer()
{
	delete m_pTimer;
}

void AnimSpriteRenderer::onStart()
{
	m_pTimer->reset();

	setUVRect(RectF(m_XPos * m_CellWidth,
		m_YPos * m_CellHeight,
		(m_XPos + 1) * m_CellWidth,
		(m_YPos + 1 * m_CellHeight)));
}

void AnimSpriteRenderer::onUpdate()
{
	m_pTimer->update();

	if (m_pTimer->isTime())
	{
		m_XPos++;

		if (m_XPos >= m_AnimCount)
			m_XPos = m_AnimCount % m_XPos;

		setUVRect(RectF(m_XPos * m_CellWidth,
				m_YPos * m_CellHeight,
				m_CellWidth,
				m_CellHeight));

		m_pTimer->reset();
	}
}

AbstractComponent::TypeID AnimSpriteRenderer::getType() const
{
	return TypeID::TSpriteRenderer;
}
