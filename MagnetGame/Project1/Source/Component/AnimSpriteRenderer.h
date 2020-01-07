#pragma once
#include "SpriteRenderer.h"

class Timer;

class AnimSpriteRenderer
	: public SpriteRenderer
{
public:
	AnimSpriteRenderer(GameObject* pUser, float textureWidth, float textureHeight, float animTime, int columnCount, int rowCount);
	~AnimSpriteRenderer();

	virtual void onStart() override;
	virtual void onUpdate() override;
	virtual TypeID getType() const override;

private:
	Timer* m_pTimer;

	int m_XPos;
	int m_YPos;

	int m_AnimCount;

	float m_CellWidth;
	float m_CellHeight;
	float m_TextureWidth;
	float m_TextureHeight;
};