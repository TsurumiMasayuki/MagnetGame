#pragma once
#include <vector>
#include "Math\Vec3.h"
#include "Utility\Color.h"
#include "Component\AbstractComponent.h"
#include "Actor\Tilemap\TileImageType.h"

class SpriteRenderer;

class MultiSpriteRenderer
	: public AbstractComponent
{
public:
	MultiSpriteRenderer(GameObject* pUser, float baseSize = 32);

	virtual void onStart() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

	void setTextureName(const std::string textureName);
	std::string getTextureName();

	void setColor(Color color);
	Color getColor();

	virtual TypeID getType() const override;

private:
	float m_BaseSize;
	float m_XPos;
	float m_YPos;

	std::vector<SpriteRenderer*> m_Renderers;

	std::string m_TextureName;
	Color m_Color;
};