#include "Tilemap.h"
#include <sstream>

#include "Actor\GameObject.h"
#include "Actor\Tilemap\Block.h"
#include "Actor\Magnet\Magnet.h"
#include "Actor\Nobject\ObjN.h"
#include "Actor\Boots.h"
#include"Actor/Board.h"

#include "Device\File\CSVReader.h"
#include "Utility\StringUtility.h"
#include "Component\Tilemap\Tile.h"

Tilemap::Tilemap(IGameMediator* pGameMediator, float cellWidth, float cellHeight)
	: m_pGameMediator(pGameMediator),
	m_CellWidth(cellWidth),
	m_CellHeight(cellHeight)
{
}

Tilemap::~Tilemap()
{
	clear();
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
			else if (data[0] == 'o')
				spawnObject(reader, data, x, y);
			else
				spawnSingleBlock(reader, data, x, y);
		}
	}
}

void Tilemap::clear()
{
	for (auto tile : m_TileList)
	{
		tile->getUser()->destroy();
	}

	m_TileList.clear();
}

void Tilemap::setPosition(Vec3 pos)
{
	m_Position = pos;
}

Vec3 Tilemap::getPosition()
{
	return m_Position;
}

float Tilemap::getWidth()
{
	return m_MapWidth;
}

float Tilemap::getHeight()
{
	return m_MapHeight;
}

void Tilemap::addTile(Tile * pTile)
{
	m_TileList.emplace_back(pTile);
}

void Tilemap::removeTile(Tile * pTile)
{
	if (m_TileList.size() == 0) return;

	auto itr = std::find(m_TileList.begin(), m_TileList.end(), pTile);
	if (itr != m_TileList.end())
	{
		std::iter_swap(itr, m_TileList.end() - 1);
		m_TileList.pop_back();
	}
}

void Tilemap::spawnObject(CSVReader & reader, std::string data, unsigned int x, unsigned int y)
{
	GameObject* object = nullptr;

	std::vector<std::string> split;
	StringUtility::split(data, '|', split);

	float speed = 1.0f;
	//速度の設定があるかどうか
	if (split.size() > 2)
	{
		//速度を取得
		speed = strtof(split.at(2).c_str(), nullptr);
	}

	if (split.at(1) == "R")
		object = new ObjN(m_pGameMediator, 0, speed);
	else if (split.at(1) == "L")
		object = new ObjN(m_pGameMediator, 1, speed);
	else if (split.at(1) == "B")
		object = new Boots(m_pGameMediator);
	else if (split.at(1) == "H")
		object = new Board(m_pGameMediator);

	if (object != nullptr)
	{
		object->setPosition(Vec3(x * m_CellWidth + m_CellWidth * 0.5f, -(y * m_CellHeight + m_CellHeight * 0.5f), 0) + getPosition());

		//管理用にTileコンポーネントをアタッチ
		auto tile = new Tile(object);
	}
}

void Tilemap::spawnSingleBlock(CSVReader& reader, std::string data, unsigned int x, unsigned int y)
{
	GameObject* object = nullptr;
	bool isLeftExist = reader.getDataClampIndex(x - 1, y)	== "1";
	bool isRightExist = reader.getDataClampIndex(x + 1, y)	== "1";
	bool isUpExist = reader.getDataClampIndex(x, y - 1)		== "1";
	bool isDownExist = reader.getDataClampIndex(x, y + 1)	== "1";

	bool hasCollider = !isLeftExist || !isRightExist || !isUpExist || !isDownExist;

	TILE_IMAGE_TYPE imageType;

	if (!hasCollider)
		imageType = getImageTypeDiag(reader, x, y);
	else
		imageType = getImageType(isUpExist, isDownExist, isRightExist, isLeftExist);

	if (data == "1")
		object = new Block(m_pGameMediator, "BlockTest", m_CellWidth, m_CellHeight, imageType, hasCollider);

	if (object != nullptr)
	{
		object->setPosition(Vec3(x * m_CellWidth + m_CellWidth * 0.5f, -(y * m_CellHeight + m_CellHeight * 0.5f), 0) + getPosition());

		//管理用にTileコンポーネントをアタッチ
		auto tile = new Tile(object);
	}
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
	if (split.at(1) == "1")
	{
		object = new Block(m_pGameMediator, "BoxOutline", width, height, TILE_IMAGE_TYPE_NONE);
	}
	else if (split.at(1) == "N")
	{
		bool move = split.at(2) == "0";
		bool changeMag = split.at(3) == "0";
		object = new Magnet(m_pGameMediator, Magnet::MAGNET_N, move, changeMag, width, height);
	}
	else if (split.at(1) == "S")
	{
		bool move = split.at(2) == "0";
		bool changeMag = split.at(3) == "0";
		object = new Magnet(m_pGameMediator, Magnet::MAGNET_S, move, changeMag, width, height);
	}

	Vec3 tilePos = Vec3(
		x * m_CellWidth + width * 0.5f,
		-(y * m_CellHeight + height * 0.5f),
		0);
	Vec3 position = tilePos + getPosition();

	if (object != nullptr)
	{
		object->setPosition(position);

		//管理用にTileコンポーネントをアタッチ
		auto tile = new Tile(object);
	}
}

TILE_IMAGE_TYPE Tilemap::getImageType(bool isUpExist, bool isDownExist, bool isRightExist, bool isLeftExist)
{
	TILE_IMAGE_TYPE imageType = TILE_IMAGE_TYPE_NONE;

	if (!isUpExist && isDownExist &&
		isLeftExist && isRightExist)
		imageType = TILE_IMAGE_TYPE_UP;
	else if (isUpExist && !isDownExist &&
		isLeftExist && isRightExist)
		imageType = TILE_IMAGE_TYPE_DOWN;
	else if (isUpExist && isDownExist &&
		!isLeftExist && isRightExist)
		imageType = TILE_IMAGE_TYPE_LEFT;
	else if (isUpExist && isDownExist &&
		isLeftExist && !isRightExist)
		imageType = TILE_IMAGE_TYPE_RIGHT;

	else if (!isUpExist && isDownExist &&
		isLeftExist && !isRightExist)
		imageType = TILE_IMAGE_TYPE_UPRIGHT;

	else if (!isUpExist && isDownExist &&
		!isLeftExist && isRightExist)
		imageType = TILE_IMAGE_TYPE_UPLEFT;

	else if (isUpExist && !isDownExist &&
		isLeftExist && !isRightExist)
		imageType = TILE_IMAGE_TYPE_DOWNRIGHT;

	else if (isUpExist && !isDownExist &&
		!isLeftExist && isRightExist)
		imageType = TILE_IMAGE_TYPE_DOWNLEFT;

	else if (!isUpExist && isDownExist &&
		!isLeftExist && !isRightExist)
		imageType = TILE_IMAGE_TYPE_UPCORNER;

	else if (isUpExist && !isDownExist &&
		!isLeftExist && !isRightExist)
		imageType = TILE_IMAGE_TYPE_DOWNCORNER;

	else if (!isUpExist && !isDownExist &&
		isLeftExist && !isRightExist)
		imageType = TILE_IMAGE_TYPE_RIGHTCORNER;

	else if (!isUpExist && !isDownExist &&
		!isLeftExist && isRightExist)
		imageType = TILE_IMAGE_TYPE_LEFTCORNER;

	else if (isUpExist && isDownExist &&
		!isLeftExist && !isRightExist)
		imageType = TILE_IMAGE_TYPE_UPCOLUMN;

	else if (!isUpExist && !isDownExist &&
		isLeftExist && isRightExist)
		imageType = TILE_IMAGE_TYPE_RIGHTCOLUMN;

	return imageType;
}

TILE_IMAGE_TYPE Tilemap::getImageTypeDiag(CSVReader& reader, unsigned int x, unsigned int y)
{
	bool isUpLeftExist = reader.getDataClampIndex(x - 1, y - 1) == "1";
	bool isUpRightExist = reader.getDataClampIndex(x + 1, y - 1) == "1";
	bool isDownLeftExist = reader.getDataClampIndex(x - 1, y + 1) == "1";
	bool isDownRightExist = reader.getDataClampIndex(x + 1, y + 1) == "1";

	TILE_IMAGE_TYPE imageType = TILE_IMAGE_TYPE_CENTER;
	
	if (!isUpLeftExist && isUpRightExist &&
		isDownLeftExist && isDownRightExist)
		imageType = TILE_IMAGE_TYPE_INVUPLEFT;

	else if (isUpLeftExist && !isUpRightExist &&
		isDownLeftExist && isDownRightExist)
		imageType = TILE_IMAGE_TYPE_INVUPRIGHT;

	else if (isUpLeftExist && isUpRightExist &&
		!isDownLeftExist && isDownRightExist)
		imageType = TILE_IMAGE_TYPE_INVDOWNLEFT;

	else if (isUpLeftExist && isUpRightExist &&
		isDownLeftExist && !isDownRightExist)
		imageType = TILE_IMAGE_TYPE_INVDOWNRIGHT;

	return imageType;
}
