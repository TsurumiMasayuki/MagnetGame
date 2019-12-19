#include "ObstacleMap.h"

ObstacleMap::ObstacleMap(float cellWidth, float cellHeight, int columnCount, int rowCount)
	: m_CellWidth(cellWidth), m_CellHeight(cellHeight), m_Column(columnCount), m_Row(rowCount)
{
	m_StaticObstacleMap.reserve(m_Row);
	while (m_StaticObstacleMap.size() < m_Row)
	{
		auto column = std::vector<int>();
		column.resize(m_Column);
		m_StaticObstacleMap.emplace_back(column);
	}
}

void ObstacleMap::setPosition(Vec2 position)
{
	m_Position = position;
}

bool ObstacleMap::isObstacle(unsigned int row, unsigned int column)
{
	return m_StaticObstacleMap.at(row).at(column) == 1;
}

void ObstacleMap::writeStaticObstacle(const Vec2 & position, const Vec2 & size)
{
	Vec2 leftUp(position.x - size.x / 2, position.y + size.y / 2);
	Vec2 rightDown(position.x + size.x / 2, position.y - size.y / 2);

	//障害物のマップ上での上下左右の座標を計算
	unsigned int upIndex = 0, downIndex = 0, leftIndex = 0, rightIndex = 0;
	toMapIndex(leftUp, leftIndex, upIndex);
	toMapIndex(rightDown, rightIndex, downIndex);

	unsigned int xIndex = 0, yIndex = 0;
	toMapIndex(position, xIndex, yIndex);

	//1ブロック分のサイズだったら座標を変更
	if (size.x - m_CellWidth == 0)
	{
		leftIndex = xIndex;
		rightIndex = xIndex;
	}

	//1ブロック分のサイズだったら座標を変更
	if (size.y - m_CellHeight == 0)
	{
		upIndex = yIndex;
		downIndex = yIndex;
	}

	//障害物の形で埋める
	for (int column = leftIndex; column <= rightIndex && column < m_Column; column++)
	{
		for (int row = upIndex; row <= downIndex && row < m_Row; row++)
		{
			m_StaticObstacleMap.at(row).at(column) = 1;
		}
	}
}

void ObstacleMap::clear()
{
	for (int i = 0; i < m_Row; i++)
	{
		//0で埋める
		std::fill(m_StaticObstacleMap.at(i).begin(), m_StaticObstacleMap.at(i).end(), 0);
	}
}

void ObstacleMap::toMapIndex(const Vec2 & position, unsigned int & x, unsigned int & y)
{
	//マップ上の座標系に変換(左上原点)
	float convX = position.x - m_Position.x;
	float convY = -(position.y - m_Position.y);
	x = convX / m_CellWidth;
	y = convY / m_CellHeight;
}
