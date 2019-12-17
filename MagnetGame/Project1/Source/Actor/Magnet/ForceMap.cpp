#include "ForceMap.h"

ForceMap::ForceMap(float cellWidth, float cellHeight, int columnCount, int rowCount)
	: m_CellWidth(cellWidth),
	m_CellHeight(cellHeight),
	m_Column(columnCount),
	m_Row(rowCount)
{
	m_VMap.reserve(m_Row);
	while (m_VMap.size() < m_Row)
	{
		auto column = std::vector<int>();
		column.resize(m_Column);
		m_VMap.emplace_back(column);
	}

	m_HMap.reserve(m_Row);
	while (m_HMap.size() < m_Row)
	{
		auto column = std::vector<int>();
		column.resize(m_Column);
		m_HMap.emplace_back(column);
	}
}

ForceMap::~ForceMap()
{
}

void ForceMap::setPosition(Vec2 position)
{
	m_Position = position;
}

void ForceMap::writeForce(const Vec2 & position, const Vec2 & size, int up, int down, int right, int left)
{
	Vec2 leftUp(position.x - size.x / 2, position.y + size.y / 2);
	Vec2 rightDown(position.x + size.x / 2, position.y - size.y / 2);

	unsigned int upIndex = 0, downIndex = 0, rightIndex = 0, leftIndex = 0;
	toMapIndex(leftUp, leftIndex, upIndex);
	toMapIndex(rightDown, rightIndex, downIndex);

	//縦方向を埋める
	for (int column = leftIndex; column < leftIndex + size.x / m_CellWidth && column < m_Column; column++)
	{
		//上側を埋める
		for (int row = 0; row < upIndex && row < m_Row; row++)
		{
			m_VMap.at(row).at(column) = up;
		}

		//下側を埋める
		for (int row = downIndex; row < m_Row; row++)
		{
			m_VMap.at(row).at(column) = down;
		}
	}

	//横方向を設定
	for (int row = upIndex; row < upIndex + size.y / m_CellHeight && row < m_Row; row++)
	{
		//左側を埋める
		for (int column = 0; column < leftIndex && column < m_Column; column++)
		{
			m_HMap.at(row).at(column) = left;
		}

		//右側を埋める
		for (int column = rightIndex; column < m_Column; column++)
		{
			m_HMap.at(row).at(column) = right;
		}
	}
}

void ForceMap::writeObstacle(const Vec2 & position, const Vec2 & size)
{
}

void ForceMap::clear()
{
	for (auto row : m_VMap)
	{
		std::fill(row.begin(), row.end(), 0);
	}

	for (auto row : m_HMap)
	{
		std::fill(row.begin(), row.end(), 0);
	}
}

Vec2 ForceMap::getForce(const Vec2 & position, const Vec2 & size)
{
	unsigned int x, y;
	toMapIndex(position, x, y);

	return Vec2(m_HMap.at(y).at(x), m_VMap.at(y).at(x));
}

void ForceMap::toMapIndex(const Vec2& position, unsigned int& x, unsigned int& y)
{
	//マップ上の座標系に変換(左上原点)
	float convX = position.x - m_Position.x;
	float convY = -(position.y - m_Position.y);
	x = convX / m_CellWidth;
	y = convY / m_CellHeight;
}

void ForceMap::toMapIndices(const Vec2& position, unsigned int x[4], unsigned int y[4])
{
	//範囲を超えていたら何もしない処理を書く
}