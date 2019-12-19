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

	m_ObstacleMap.reserve(m_Row);
	while (m_ObstacleMap.size() < m_Row)
	{
		auto column = std::vector<int>();
		column.resize(m_Column);
		m_ObstacleMap.emplace_back(column);
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

	//�c�����𖄂߂�
	for (int column = leftIndex; column < leftIndex + size.x / m_CellWidth && column < m_Column; column++)
	{
		//�㑤�𖄂߂�
		for (int row = upIndex; row > 0;row--)
		{
			//��Q�����������珑�����ݏI��
			if (m_ObstacleMap.at(row).at(column) != 0) break;

			m_VMap.at(row).at(column) = up;
		}

		//�����𖄂߂�
		for (int row = downIndex; row < m_Row; row++)
		{
			//��Q�����������珑�����ݏI��
			if (m_ObstacleMap.at(row).at(column) != 0) break;

			m_VMap.at(row).at(column) = down;
		}
	}

	//�������𖄂߂�
	for (int row = upIndex; row < upIndex + size.y / m_CellHeight && row < m_Row; row++)
	{
		//�����𖄂߂�(�C���f�b�N�X���������ɐi�߂�)
		for (int column = leftIndex; column > 0; column--)
		{
			//��Q�����������珑�����ݏI��
			if (m_ObstacleMap.at(row).at(column) != 0) break;

			m_HMap.at(row).at(column) = left;
		}

		//�E���𖄂߂�(�C���f�b�N�X���E�����ɐi�߂�)
		for (int column = rightIndex; column < m_Column; column++)
		{
			//��Q�����������珑�����ݏI��
			if (m_ObstacleMap.at(row).at(column) != 0) break;

			m_HMap.at(row).at(column) = right;
		}
	}
}

void ForceMap::writeObstacle(const Vec2 & position, const Vec2 & size)
{
	Vec2 leftUp(position.x - size.x / 2, position.y + size.y / 2);
	Vec2 rightDown(position.x + size.x / 2, position.y - size.y / 2);

	//��Q���̃}�b�v��ł̏㉺���E�̍��W���v�Z
	unsigned int upIndex = 0, downIndex = 0, leftIndex = 0, rightIndex = 0;
	toMapIndex(leftUp, leftIndex, upIndex);
	toMapIndex(rightDown, rightIndex, downIndex);

	unsigned int xIndex = 0, yIndex = 0;
	toMapIndex(position, xIndex, yIndex);

	//1�u���b�N���̃T�C�Y����������W��ύX
	if (size.x - m_CellWidth == 0)
	{
		leftIndex = xIndex;
		rightIndex = xIndex;
	}

	//1�u���b�N���̃T�C�Y����������W��ύX
	if (size.y - m_CellWidth == 0)
	{
		upIndex = yIndex;
		downIndex = yIndex;
	}

	//��Q���̌`�Ŗ��߂�
	for (int column = leftIndex; column <= rightIndex && column < m_Column; column++)
	{
		for (int row = upIndex; row <= downIndex && row < m_Row; row++)
		{
			m_ObstacleMap.at(row).at(column) = 1;
		}
	}
}

void ForceMap::clear()
{
	for (int i = 0; i < m_Row; i++)
	{
		std::fill(m_VMap.at(i).begin(), m_VMap.at(i).end(), 0);
		std::fill(m_HMap.at(i).begin(), m_HMap.at(i).end(), 0);
		//std::fill(m_ObstacleMap.at(i).begin(), m_ObstacleMap.at(i).end(), 0);
	}
}

Vec2 ForceMap::getForce(const Vec2 & position, const Vec2 & size)
{
	unsigned int x, y;
	toMapIndex(position, x, y);

	return Vec2(m_HMap.at(y).at(x), m_VMap.at(y).at(x));
}

void ForceMap::copyTo(ForceMap & other)
{
	for (int i = 0; i < m_VMap.size(); i++)
	{
		other.m_VMap.at(i).clear();
		other.m_HMap.at(i).clear();
		//other.m_ObstacleMap.at(i).clear();

		std::copy(m_VMap.at(i).begin(), m_VMap.at(i).end(), std::back_inserter(other.m_VMap.at(i)));
		std::copy(m_HMap.at(i).begin(), m_HMap.at(i).end(), std::back_inserter(other.m_HMap.at(i)));
		//std::copy(m_ObstacleMap.at(i).begin(), m_ObstacleMap.at(i).end(), std::back_inserter(other.m_ObstacleMap.at(i)));
	}
}

void ForceMap::toMapIndex(const Vec2& position, unsigned int& x, unsigned int& y)
{
	//�}�b�v��̍��W�n�ɕϊ�(���㌴�_)
	float convX = position.x - m_Position.x;
	float convY = -(position.y - m_Position.y);
	x = convX / m_CellWidth;
	y = convY / m_CellHeight;
}

void ForceMap::toMapIndices(const Vec2& position, unsigned int x[4], unsigned int y[4])
{
}