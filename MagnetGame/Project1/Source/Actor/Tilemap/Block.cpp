#include "Block.h"
#include "Component\SpriteRenderer.h"
#include "Component\Physics\BoxCollider2D.h"
#include "Actor\IGameMediator.h"
#include "Actor\Magnet\ObstacleMap.h"

const Vec2 Block::tileImageCoord[11] =
{
	Vec2( 0.0f, 0.0f),

	Vec2( 0.166f,  0.0f),
	Vec2( 0.166f, -0.166f),
	Vec2( 0.0f, 0.166f),
	Vec2(-0.166f, 0.166f),

	Vec2( 0.166f,  0.166f),

	Vec2(  0.0f,	0.0f),
	Vec2( -0.166f,	0.0f),
	Vec2(  0.0f,	-0.166f),
	Vec2( -0.166f,	-0.166f),

	Vec2( 0.0f,  0.0f),
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
	sprite->setColor(Color(0.25f, 0.25f, 0.25f, 1));

	//タイル用切り抜きを指定
	if (m_TileImageType != TILE_IMAGE_TYPE_NONE)
		sprite->setUVRect(RectF(tileImageCoord[m_TileImageType].x, tileImageCoord[m_TileImageType].y, 0.166f, 0.166f));

	if (m_HasCollider)
	{
		//コライダーを作成
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
