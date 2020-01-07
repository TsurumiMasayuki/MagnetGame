#include "Tile.h"
#include "Actor\GameObject.h"
#include "Actor\IGameMediator.h"
#include "Actor\Tilemap\Tilemap.h"

Tile::Tile(GameObject * pUser)
	: AbstractComponent(pUser)
{
	pUser->getGameMediator()->getTilemap()->addTile(this);
}

Tile::~Tile()
{
	m_pUser->getGameMediator()->getTilemap()->removeTile(this);
}

void Tile::onStart()
{
}

void Tile::onUpdate()
{
}

AbstractComponent::TypeID Tile::getType() const
{
	return TypeID::TNone;
}
