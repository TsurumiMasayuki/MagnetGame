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

	Tilemap* getTilemap();
	ObstacleMap* getObstacle();
	ForceMap* getForceMapN();
	ForceMap* getForceMapS();

private:
	Tilemap* m_pTilemap;
	ObstacleMap* m_pObstacle;

	ForceMap* m_pForceMapN;
	ForceMap* m_pForceMapS;

	Vec3 m_Position;
};