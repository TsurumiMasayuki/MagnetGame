#include "SpriteAnimation.h"
#include "Utility\Timer.h"

SpriteAnimation::SpriteAnimation(std::string textureName, float textureWidth, float textureHeight, float animTime, int animCount, int yPos)
	: m_TextureName(textureName),
	m_CellWidth(textureWidth / animCount / textureWidth),
	m_CellHeight(textureHeight / 1 / textureHeight),
	m_TextureWidth(textureWidth),
	m_TextureHeight(textureHeight),
	m_pTimer(new Timer(animTime)),
	m_XPos(0),
	m_YPos(yPos),
	m_AnimCount(animCount)
{
}

SpriteAnimation::~SpriteAnimation()
{
	delete m_pTimer;
}

void SpriteAnimation::reset()
{
	m_XPos = 0;
	m_pTimer->reset();
}

void SpriteAnimation::update()
{
	m_pTimer->update();

	if (m_pTimer->isTime())
	{
		m_XPos++;

		if (m_XPos >= m_AnimCount)
			m_XPos = m_AnimCount % m_XPos;

		m_pTimer->reset();
	}
}

std::string SpriteAnimation::getTextureName()
{
	return m_TextureName;
}

RectF SpriteAnimation::getAnimRect()
{
	return RectF(m_XPos * m_CellWidth,
		m_YPos * m_CellHeight,
		m_CellWidth,
		m_CellHeight);
}

Vec2 SpriteAnimation::getPivot()
{
	return Vec2(m_PivotX, m_PivotY);
}
