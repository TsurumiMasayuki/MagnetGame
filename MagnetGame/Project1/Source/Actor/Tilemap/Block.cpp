#include "Block.h"
#include "Component\SpriteRenderer.h"
#include "Component\Physics\BoxCollider2D.h"
#include "Actor\IGameMediator.h"
#include "Actor\Magnet\ObstacleMap.h"
#include "Math\MathUtility.h"

const Vec2 UVRectSize(1.0f / 5.0f, 1);

const ImageInfo Block::tileImageCoord[22] =
{
	//�f�t�H���g
	{ Vec2(0.0f, 0.0f),				0.0f },

	//�[	
	{ Vec2(1.0f / 5.0f * 0, 0.0f),   0.0f},	//��
	{ Vec2(1.0f / 5.0f * 0, 0.0f), 180.0f},	//��
	{ Vec2(1.0f / 5.0f * 0, 0.0f), 270.0f}, //�E
	{ Vec2(1.0f / 5.0f * 0, 0.0f),  90.0f}, //��

	//�p						     	 
	{ Vec2(1.0f / 5.0f * 1, 0.0f), 270.0f},	//�E��
	{ Vec2(1.0f / 5.0f * 1, 0.0f),   0.0f},	//����
	{ Vec2(1.0f / 5.0f * 1, 0.0f), 180.0f}, //�E��
	{ Vec2(1.0f / 5.0f * 1, 0.0f),  90.0f}, //����

	//���p
	{ Vec2(1.0f / 5.0f * 4, 0.0f),  270.0f},	//�t�E��
	{ Vec2(1.0f / 5.0f * 4, 0.0f),    0.0f},	//�t����
	{ Vec2(1.0f / 5.0f * 4, 0.0f),  180.0f},	//�t�E��
	{ Vec2(1.0f / 5.0f * 4, 0.0f),   90.0f},	//�t����

	//�R�̎�					   
	{ Vec2(1.0f / 5.0f * 2, 0.0f),   0.0f},	//��
	{ Vec2(1.0f / 5.0f * 2, 0.0f), 180.0f},	//��
	{ Vec2(1.0f / 5.0f * 2, 0.0f), 270.0f}, //�E
	{ Vec2(1.0f / 5.0f * 2, 0.0f),  90.0f}, //��

	//�j�̎�					   
	{ Vec2(1.0f / 5.0f * 3, 0.0f),   0.0f},	//��
	{ Vec2(1.0f / 5.0f * 3, 0.0f), 180.0f},	//��
	{ Vec2(1.0f / 5.0f * 3, 0.0f), 270.0f}, //�E
	{ Vec2(1.0f / 5.0f * 3, 0.0f),  90.0f}, //��

	//���S					  	  
	{ Vec2(1.0f / 5.0f * 4.5, 0.0f), 0.0f},
};

Block::Block(IGameMediator* pGameMediator, std::string textureName, float width, float height, TILE_IMAGE_TYPE tileImageType, bool hasCollider)
	: GameObject(pGameMediator),
	m_TextureName(textureName),
	m_Width(width),
	m_Height(height),
	m_HasCollider(hasCollider),
	m_TileImageType(tileImageType)
{
}

Block::~Block()
{
}

void Block::start()
{
	setTag("Block");

	auto sprite = new SpriteRenderer(this);
	sprite->setTextureName(m_TextureName);

	//�^�C���p�؂蔲�����w��
	auto imageInfo = tileImageCoord[m_TileImageType];
	if (m_TileImageType != TILE_IMAGE_TYPE::TILE_IMAGE_TYPE_CENTER)
		sprite->setUVRect(RectF(imageInfo.imageCoord.x, imageInfo.imageCoord.y, UVRectSize.x, UVRectSize.y));
	else
		sprite->setUVRect(RectF(1.0f / 5.0f * 4.5f, 0.0f, 0.01f, 0.01f));

	setAngleZ(MathUtility::toRadian(imageInfo.imageRotation));

	if (m_HasCollider)
	{
		//�R���C�_�[���쐬
		auto collider = new BoxCollider2D(this);
		collider->isTrigger = false;
		collider->isMove = false;
		collider->setWidth(m_Width);
		collider->setHeight(m_Height);
		collider->layer = PhysicsLayer::Block;
	}

	setSize(Vec3(m_Width, m_Height, 0));
	getGameMediator()->getObstacleMap()->writeStaticObstacle(getPosition().toVec2(), getSize().toVec2());
}
