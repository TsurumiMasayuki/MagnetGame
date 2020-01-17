#pragma once
#include <vector>
#include "Math\Vec3.h"
#include "Component\SpriteRenderer.h"
#include "Actor\Tilemap\TileImageType.h"

class MultiSpriteRenderer
	: public SpriteRenderer
{
public:
	MultiSpriteRenderer(GameObject* pUser, float baseSize = 32);

	virtual void onStart() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

private:
	float m_BaseSize;
	std::vector<Vec3> m_RenderPosList;
	std::vector<GameObject*> m_Renderers;
};