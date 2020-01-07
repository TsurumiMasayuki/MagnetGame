#include "Stage.h"
#include "Actor\Tilemap\Tilemap.h"
#include "Actor\Magnet\ObstacleMap.h"
#include "Actor\Magnet\ForceMap.h"

Stage::Stage(IGameMediator* pMediator, float cellWidth, float cellHeight)
{
	m_pTilemap = new Tilemap(pMediator, cellWidth, cellHeight);

	m_pObstacle = new ObstacleMap(cellWidth, cellHeight, m_pTilemap->getColumn(), m_pTilemap->getRow());

	m_pForceMapN = new ForceMap(cellWidth, cellHeight, m_pTilemap->getColumn(), m_pTilemap->getRow(), m_pObstacle);
	m_pForceMapS = new ForceMap(cellWidth, cellHeight, m_pTilemap->getColumn(), m_pTilemap->getRow(), m_pObstacle);
}

Stage::~Stage()
{
	delete m_pTilemap;
	delete m_pObstacle;
	delete m_pForceMapN;
	delete m_pForceMapS;
}

void Stage::setPosition(Vec3 pos)
{
	m_Position = pos;
}

Vec3 Stage::getPosition()
{
	return m_Position;
}

void Stage::load(std::string mapFileName)
{
	m_pTilemap->setPosition(m_Position);
	m_pTilemap->load(mapFileName);

	m_pObstacle->setPosition(m_Position.toVec2());

	m_pForceMapN->setPosition(m_Position.toVec2());
	m_pForceMapS->setPosition(m_Position.toVec2());
}

Tilemap * Stage::getTilemap()
{
	return m_pTilemap;
}

ObstacleMap * Stage::getObstacle()
{
	return m_pObstacle;
}

ForceMap * Stage::getForceMapN()
{
	return m_pForceMapN;
}

ForceMap * Stage::getForceMapS()
{
	return m_pForceMapS;
}
