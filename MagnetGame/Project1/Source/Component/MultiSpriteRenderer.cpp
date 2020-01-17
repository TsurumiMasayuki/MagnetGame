#include "MultiSpriteRenderer.h"
#include "Actor\GameObject.h"
#include "Component\SpriteRenderer.h"

const TILE_IMAGE_TYPE tileImageArray[9] = 
{
	TILE_IMAGE_TYPE_UP,			//上
	TILE_IMAGE_TYPE_DOWN,		//下
	TILE_IMAGE_TYPE_RIGHT,		//右
	TILE_IMAGE_TYPE_LEFT,		//左

	TILE_IMAGE_TYPE_UPRIGHT,	//右上
	TILE_IMAGE_TYPE_UPLEFT,		//左上
	TILE_IMAGE_TYPE_DOWNRIGHT,	//右下
	TILE_IMAGE_TYPE_DOWNLEFT,	//左下

	TILE_IMAGE_TYPE_CENTER		//中心
};

const ImageInfo tileImageCoord[18] =
{
	//デフォルト
	{ Vec2(0.0f, 0.0f),				 0.0f },

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
				  
	//コの字					   
	{ Vec2(1.0f / 4.0f * 2, 0.0f),   0.0f},	//上
	{ Vec2(1.0f / 4.0f * 2, 0.0f), 180.0f},	//下
	{ Vec2(1.0f / 4.0f * 2, 0.0f), 270.0f}, //右
	{ Vec2(1.0f / 4.0f * 2, 0.0f),  90.0f}, //左
				  
	//ニの字		
	{ Vec2(1.0f / 4.0f * 3, 0.0f),   0.0f},	//上
	{ Vec2(1.0f / 4.0f * 3, 0.0f), 180.0f},	//下
	{ Vec2(1.0f / 4.0f * 3, 0.0f), 270.0f}, //右
	{ Vec2(1.0f / 4.0f * 3, 0.0f),  90.0f}, //左
				  
	//中心			  	  
	{ Vec2(0.1f, 0.1f),				0.0f},
};


MultiSpriteRenderer::MultiSpriteRenderer(GameObject * pUser, float baseSize)
	: SpriteRenderer(pUser, 120),
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
	renderer = new GameObject(m_pUser->getGameMediator());
	sprite = new SpriteRenderer(renderer);
	sprite->setTextureName(getTextureName());
	sprite->setColor(getColor());
	sprite->setUVRect(RectF(uvBase * 2, 0, uvBase, 1));
}

void MultiSpriteRenderer::onUpdate()
{
}

void MultiSpriteRenderer::onDestroy()
{
}
