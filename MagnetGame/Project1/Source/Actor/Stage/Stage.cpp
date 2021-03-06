#include "Stage.h"
#include "Actor\Tilemap\Tilemap.h"
#include "Actor\Magnet\ObstacleMap.h"
#include "Actor\Magnet\ForceMap.h"

Stage::Stage(IGameMediator* pMediator, float cellWidth, float cellHeight) :
	m_CellWidth(cellWidth), m_CellHeight(cellHeight)
{
	m_pTilemap = new Tilemap(pMediator, cellWidth, cellHeight);
}

Stage::~Stage()
{
	delete m_pTilemap;
	delete m_pObstacle;
	delete m_pNMapRead;
	delete m_pSMapRead;
	delete m_pNMapWrite;
	delete m_pSMapWrite;
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

	m_pObstacle = new ObstacleMap(m_CellWidth, m_CellHeight, m_pTilemap->getColumn(), m_pTilemap->getRow());

	m_pNMapRead = new ForceMap(m_CellWidth, m_CellHeight, m_pTilemap->getColumn(), m_pTilemap->getRow(), m_pObstacle);
	m_pNMapWrite = new ForceMap(m_CellWidth, m_CellHeight, m_pTilemap->getColumn(), m_pTilemap->getRow(), m_pObstacle);
	m_pSMapRead = new ForceMap(m_CellWidth, m_CellHeight, m_pTilemap->getColumn(), m_pTilemap->getRow(), m_pObstacle);
	m_pSMapWrite = new ForceMap(m_CellWidth, m_CellHeight, m_pTilemap->getColumn(), m_pTilemap->getRow(), m_pObstacle);

	m_pObstacle->setPosition(m_Position.toVec2());

	m_pNMapRead->setPosition(m_Position.toVec2());
	m_pSMapRead->setPosition(m_Position.toVec2());
	m_pNMapWrite->setPosition(m_Position.toVec2());
	m_pSMapWrite->setPosition(m_Position.toVec2());
}

void Stage::clear()
{
	m_pTilemap->clear();
}

void Stage::update()
{
	m_pNMapRead->clear();
	m_pSMapRead->clear();

	m_pNMapWrite->copyTo(*m_pNMapRead);
	m_pSMapWrite->copyTo(*m_pSMapRead);

	m_pNMapWrite->clear();
	m_pSMapWrite->clear();
}

Tilemap * Stage::getTilemap()
{
	return m_pTilemap;
}

ForceMap * Stage::getNMapRead()
{
	return m_pNMapRead;
}

ForceMap * Stage::getSMapRead()
{
	return m_pSMapRead;
}

ForceMap * Stage::getNMapWrite()
{
	return m_pNMapWrite;
}

ForceMap * Stage::getSMapWrite()
{
	return m_pSMapWrite;
}

ObstacleMap * Stage::getObstacle()
{
	return m_pObstacle;
}