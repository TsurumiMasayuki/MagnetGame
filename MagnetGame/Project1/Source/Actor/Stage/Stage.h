#pragma once
#include <string>
#include "Math\Vec3.h"

class Tilemap;
class ObstacleMap;
class ForceMap;
class IGameMediator;

class Stage
{
public:
	Stage(IGameMediator* pMediator, float cellWidth = 64, float cellHeight = 64);
	~Stage();

	void setPosition(Vec3 pos);
	Vec3 getPosition();

	void load(std::string mapFileName);
	void clear();
	void update();

	Tilemap* getTilemap();
	ForceMap* getNMapRead();
	ForceMap* getSMapRead();
	ForceMap* getNMapWrite();
	ForceMap* getSMapWrite();
	ObstacleMap* getObstacle();

private:
	Tilemap* m_pTilemap;
	ObstacleMap* m_pObstacle;

	ForceMap* m_pNMapWrite;
	ForceMap* m_pSMapWrite;

	ForceMap* m_pNMapRead;
	ForceMap* m_pSMapRead;


	Vec3 m_Position;

	float m_CellWidth;
	float m_CellHeight;
};