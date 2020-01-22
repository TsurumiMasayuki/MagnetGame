#include "MultiSpriteRenderer.h"
#include "Actor\GameObject.h"
#include "Component\SpriteRenderer.h"
#include "Math\MathUtility.h"

const Vec3 renderPosList[9] = 
{
	Vec3(0.0f, 1.0f, 0.0f),
	Vec3(0.0f, -1.0f, 0.0f),
	Vec3(1.0f, 0.0f, 0.0f),
	Vec3(-1.0f, 0.0f, 0.0f),

	Vec3(1.0f, 1.0f, 0.0f),
	Vec3(-1.0f, 1.0f, 0.0f),
	Vec3(1.0f, -1.0f, 0.0f),
	Vec3(-1.0f, -1.0f, 0.0f),

	Vec3(0.0f, 0.0f, 0.0f)
};

const ImageInfo tileImageCoord[9] =
{
	//端	
	{ Vec2(1.0f / 4.0f * 0, 0.0f),   0.0f},	//上
	{ Vec2(1.0f / 4.0f * 0, 0.0f), 180.0f},	//下
	{ Vec2(1.0f / 4.0f * 0, 0.0f), 270.0f}, //右
	{ Vec2(1.0f / 4.0f * 0, 0.0f),  90.0f}, //左
				  
	//角						     	 
	{ Vec2(1.0f / 4.0f * 1, 0.0f), 270.0f},	//右上
	{ Vec2(1.0f / 4.0f * 1, 0.0f),   0.0f},	//左上
	{ Vec2(1.0f / 4.0f * 1, 0.0f), 180.0f}, //右下
	{ Vec2(1.0f / 4.0f * 1, 0.0f),  90.0f}, //左下
				  
	//中心			  	  
	{ Vec2(1.0f / 4.0f * 0, 0.0f),	0.0f},
};


MultiSpriteRenderer::MultiSpriteRenderer(GameObject * pUser, float baseSize)
	: AbstractComponent(pUser, 120),
	m_BaseSize(baseSize)
{
}

void MultiSpriteRenderer::onStart()
{
	float halfWidth = m_pUser->getSize().x / 2;
	float halfHeight = m_pUser->getSize().y / 2;
	float uvBase = 1.0f / 4.0f;

	GameObject* renderer = nullptr;
	SpriteRenderer* sprite = nullptr;

	//角
	for (int i = 0; i < 9; i++)
	{
		renderer = new GameObject(m_pUser->getGameMediator());
		sprite = new SpriteRenderer(renderer);
		sprite->setTextureName(getTextureName());
		sprite->setColor(getColor());

		Vec2 uv = tileImageCoord[i].imageCoord;
		sprite->setUVRect(RectF(uv.x, uv.y, 1.0f / 4.0f, 1));
		renderer->setAngleZ(MathUtility::toRadian(tileImageCoord[i].imageRotation));

		m_Renderers.emplace_back(sprite);
	}

	m_XPos = m_pUser->getSize().x / 2 - m_BaseSize / 2;
	m_YPos = m_pUser->getSize().y / 2 - m_BaseSize / 2;

	float xSize = m_pUser->getSize().x - m_BaseSize * 2;
	float ySize = m_pUser->getSize().y - m_BaseSize * 2;

	//上
	m_Renderers.at(0)->getUser()->setSize(Vec3(xSize, m_BaseSize, 0));
	//下
	m_Renderers.at(1)->getUser()->setSize(Vec3(xSize, m_BaseSize, 0));
	//右
	m_Renderers.at(2)->getUser()->setSize(Vec3(ySize, m_BaseSize , 0));
	//左
	m_Renderers.at(3)->getUser()->setSize(Vec3(ySize, m_BaseSize, 0));
	//右上
	m_Renderers.at(4)->getUser()->setSize(Vec3(m_BaseSize, m_BaseSize, 0));				  											  
	//左上
	m_Renderers.at(5)->getUser()->setSize(Vec3(m_BaseSize, m_BaseSize, 0));				 		
	//右下
	m_Renderers.at(6)->getUser()->setSize(Vec3(m_BaseSize, m_BaseSize, 0));
	//左下
	m_Renderers.at(7)->getUser()->setSize(Vec3(m_BaseSize, m_BaseSize, 0));
	//中心
	m_Renderers.at(8)->getUser()->setSize(Vec3(xSize, ySize, 0)); 
}

void MultiSpriteRenderer::onUpdate()
{
	for (int i = 0; i < 9; i++)
	{
		Vec3 renderPos = Vec3(renderPosList[i].x * m_XPos, renderPosList[i].y * m_YPos, 0);
		m_Renderers.at(i)->getUser()->setPosition(m_pUser->getPosition() + renderPos);
	}
}

void MultiSpriteRenderer::onDestroy()
{
	for (auto renderer : m_Renderers)
	{
		renderer->getUser()->destroy();
	}
}

void MultiSpriteRenderer::setTextureName(const std::string textureName)
{
	m_TextureName = textureName;
	for (auto renderer : m_Renderers)
	{
		renderer->setTextureName(textureName);
	}
}

std::string MultiSpriteRenderer::getTextureName()
{
	return m_TextureName;
}

Color MultiSpriteRenderer::getColor()
{
	return m_Color;
}

void MultiSpriteRenderer::setColor(Color color)
{
	m_Color = color;
}

AbstractComponent::TypeID MultiSpriteRenderer::getType() const
{
	return TypeID::TSpriteRenderer;
}
