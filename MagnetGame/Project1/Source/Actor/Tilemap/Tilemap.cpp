#include "Tilemap.h"
#include <sstream>
#include "Actor\Tilemap\Block.h"
#include "Actor\Magnet\Magnet.h"
#include "Device\File\CSVReader.h"
#include "Utility\StringUtility.h"

Tilemap::Tilemap(IGameMediator* pGameMediator, float cellWidth, float cellHeight)
	: GameObject(pGameMediator),
	m_CellWidth(cellWidth),
	m_CellHeight(cellHeight)
{
}

Tilemap::~Tilemap()
{
}

void Tilemap::load(std::string csvFileName)
{
	CSVReader reader;
	reader.open(csvFileName);

	std::vector<std::string> groupList;

	m_Column = reader.getColumnCount(0);
	m_Row = reader.getRowCount();
	m_MapWidth = reader.getColumnCount(0) * m_CellWidth;
	m_MapHeight = reader.getRowCount() * m_CellHeight;

	for (unsigned int y = 0; y < reader.getRowCount(); y++)
	{
		for (unsigned int x = 0; x < reader.getColumnCount(y); x++)
		{
			std::string data = reader.getData(x, y);

			if (data[0] == 'g')
				spawnMultiBlock(reader, groupList, x, y);
			else
				spawnSingleBlock(data, x, y);
		}
	}
}

float Tilemap::getWidth()
{
	return m_MapWidth;
}

float Tilemap::getHeight()
{
	return m_MapHeight;
}

void Tilemap::spawnSingleBlock(std::string data, unsigned int x, unsigned int y)
{
	GameObject* block = nullptr;

	if (data == "1")
		block = new Block(m_pGameMediator, "BoxFill", m_CellWidth, m_CellHeight);


	if (block != nullptr)
		block->setPosition(Vec3(x * m_CellWidth + m_CellWidth * 0.5f, -(y * m_CellHeight + m_CellHeight * 0.5f), 0) + getPosition());
}

void Tilemap::spawnMultiBlock(CSVReader& reader, std::vector<std::string>& groupList, unsigned int x, unsigned int y)
{
	std::string group(reader.getData(x, y));
	std::vector<std::string> split;
	StringUtility::split(group, '|', split);

	auto itr = std::find(groupList.begin(), groupList.end(), split.at(0));
	if (itr != groupList.end())
		return;

	groupList.emplace_back(split.at(0));

	int xCount = 0;
	while (x + xCount < reader.getColumnCount(y))
	{
		std::string readData(reader.getData(x + xCount, y));
		if (readData != group) break;
		xCount++;
	}

	int yCount = 0;
	while (y + yCount < reader.getRowCount())
	{
		std::string readData(reader.getData(x, y + yCount));
		if (readData != group) break;
		yCount++;
	}

	float width = xCount * m_CellWidth;
	float height = yCount * m_CellHeight;

	GameObject* object = nullptr;
	if (split.at(1) == "B")
	{
		object = new Block(m_pGameMediator, "BoxOutline", width, height);
	}
	else if (split.at(1) == "N")
	{
		bool move = split.at(2) == "0";
		object = new Magnet(m_pGameMediator, Magnet::MAGNET_N, move, width, height);
	}
	else if (split.at(1) == "S")
	{
		bool move = split.at(2) == "0";
		object = new Magnet(m_pGameMediator, Magnet::MAGNET_S, move, width, height);
	}

	Vec3 tilePos = Vec3(
		x * m_CellWidth + width * 0.5f,
		-(y * m_CellHeight + height * 0.5f),
		0);
	Vec3 position = tilePos + getPosition();

	object->setPosition(position);
}
