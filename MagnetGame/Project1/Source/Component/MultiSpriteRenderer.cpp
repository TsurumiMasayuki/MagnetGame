#include "MultiSpriteRenderer.h"
#include "Actor\GameObject.h"
#include "Component\SpriteRenderer.h"

const TILE_IMAGE_TYPE tileImageArray[9] = 
{
	TILE_IMAGE_TYPE_UP,			//��
	TILE_IMAGE_TYPE_DOWN,		//��
	TILE_IMAGE_TYPE_RIGHT,		//�E
	TILE_IMAGE_TYPE_LEFT,		//��

	TILE_IMAGE_TYPE_UPRIGHT,	//�E��
	TILE_IMAGE_TYPE_UPLEFT,		//����
	TILE_IMAGE_TYPE_DOWNRIGHT,	//�E��
	TILE_IMAGE_TYPE_DOWNLEFT,	//����

	TILE_IMAGE_TYPE_CENTER		//���S
};

const ImageInfo tileImageCoord[18] =
{
	//�f�t�H���g
	{ Vec2(0.0f, 0.0f),				 0.0f },

	//�[	
	{ Vec2(1.0f / 4.0f * 0, 0.0f),   0.0f},	//��
	{ Vec2(1.0f / 4.0f * 0, 0.0f), 180.0f},	//��
	{ Vec2(1.0f / 4.0f * 0, 0.0f), 270.0f}, //�E
	{ Vec2(1.0f / 4.0f * 0, 0.0f),  90.0f}, //��
				  
	//�p						     	 
	{ Vec2(1.0f / 4.0f * 1, 0.0f), 270.0f},	//�E��
	{ Vec2(1.0f / 4.0f * 1, 0.0f),   0.0f},	//����
	{ Vec2(1.0f / 4.0f * 1, 0.0f), 180.0f}, //�E��
	{ Vec2(1.0f / 4.0f * 1, 0.0f),  90.0f}, //����
				  
	//�R�̎�					   
	{ Vec2(1.0f / 4.0f * 2, 0.0f),   0.0f},	//��
	{ Vec2(1.0f / 4.0f * 2, 0.0f), 180.0f},	//��
	{ Vec2(1.0f / 4.0f * 2, 0.0f), 270.0f}, //�E
	{ Vec2(1.0f / 4.0f * 2, 0.0f),  90.0f}, //��
				  
	//�j�̎�		
	{ Vec2(1.0f / 4.0f * 3, 0.0f),   0.0f},	//��
	{ Vec2(1.0f / 4.0f * 3, 0.0f), 180.0f},	//��
	{ Vec2(1.0f / 4.0f * 3, 0.0f), 270.0f}, //�E
	{ Vec2(1.0f / 4.0f * 3, 0.0f),  90.0f}, //��
				  
	//���S			  	  
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

	//�p
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
