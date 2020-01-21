#include "Actor\GameObject.h"
#include "Actor\Tilemap\TileImageType.h"
#include "Math\Vec2.h"

class Block
	: public GameObject
{
public:
	Block(IGameMediator* pGameMediator, std::string textureName, float width, float height, TILE_IMAGE_TYPE tileImageType, bool hasCollider = true);
	~Block();

	virtual void start() override;

private:
	float m_Width;
	float m_Height;

	bool m_HasCollider;

	std::string m_TextureName;
	TILE_IMAGE_TYPE m_TileImageType;

	const static ImageInfo tileImageCoord[22];
};