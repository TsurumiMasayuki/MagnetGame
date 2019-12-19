#pragma once
#include <vector>
#include "Math\Vec2.h"

class ObstacleMap
{
public:
	ObstacleMap(float cellWidth, float cellHeight, int columnCount, int rowCount);

	void setPosition(Vec2 position);
	bool isObstacle(unsigned int row, unsigned int column);
	void writeStaticObstacle(const Vec2& position, const Vec2& size);
	void clear();

	//動的なマップが必要になるまで実装しない
	//void copyTo(ObstacleMap& other);

private:
	void toMapIndex(const Vec2& position, unsigned int& x, unsigned int& y);

private:
	Vec2 m_Position;

	float m_CellWidth;
	float m_CellHeight;

	unsigned int m_Column;
	unsigned int m_Row;

	std::vector<std::vector<int>> m_StaticObstacleMap;
};