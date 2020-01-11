#pragma once
#include "Component\AbstractComponent.h"
#include "Utility\Color.h"
#include "Math\Vec2.h"
#include "Math\RectF.h"
#include <string>

class Renderer;
class ConstantBuffer;
class VertexBuffer;

class SpriteRenderer
	: public AbstractComponent
{
public:
	SpriteRenderer(GameObject* pUser, int drawOrder = 100);
	~SpriteRenderer();

	virtual void onStart() override;
	virtual void onUpdate() override;
	virtual TypeID getType() const override;

	int getDrawOrder() const;
	void draw();

	void setTextureName(const std::string textureName);
	std::string getTextureName();

	void setColor(Color color);
	void setFlipX(bool flipX);
	void setFlipY(bool flipY);

	Vec2 getPivot();
	void setPivot(Vec2 pivot);

	RectF getUVRect();
	void setUVRect(RectF uvRect);

private:
	int m_DrawOrder;

	std::string m_TextureName;
	std::string m_VSName;
	std::string m_PSName;

	Color m_Color;
	bool m_FlipX;
	bool m_FlipY;

	Vec2 m_ImagePivot;
	RectF m_UVRect;

	static unsigned int componentCount;
	static ConstantBuffer* pSpriteCB;
	static VertexBuffer* pSpriteVerticesNormal;
	static VertexBuffer* pSpriteVerticesInvert;
};