#pragma once
#include <vector>
#include "Math\Vec2.h"

class ObstacleMap;

class ForceMap
{
public:
	ForceMap(float cellWidth, float cellHeight, int columnCount, int rowCount, ObstacleMap* pObstacles);
	~ForceMap();

	void setPosition(Vec2 position);
	void writeForce(const Vec2& position, const Vec2& size, int up = 1, int down = -1, int right = 1, int left = -1);
	void clear();

	Vec2 getForce(const Vec2& position, const Vec2& size);

	void copyTo(ForceMap& other);

private:
	void toMapIndex(const Vec2& position, unsigned int& x, unsigned int& y);

private:
	Vec2 m_Position;

	float m_CellWidth;
	float m_CellHeight;

	unsigned int m_Column;
	unsigned int m_Row;

	std::vector<std::vector<int>> m_VMap;
	std::vector<std::vector<int>> m_HMap;

	ObstacleMap* m_pObstacles;
};