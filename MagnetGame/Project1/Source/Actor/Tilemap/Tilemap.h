#pragma once
#include <string>
#include <vector>
#include "Math\Vec3.h"

class IGameMediator;
class CSVReader;
class Tile;

class Tilemap
{
public:
	Tilemap(IGameMediator* pGameMediator, float cellWidth = 64, float cellHeight = 64);
	~Tilemap();

	void load(std::string csvFileName);

	void setPosition(Vec3 pos);
	Vec3 getPosition();

	unsigned int getColumn() { return m_Column; }
	unsigned int getRow() { return m_Row; }

	float getWidth();
	float getHeight();

	void addTile(Tile* pTile);
	void removeTile(Tile* pTile);

private:
	void spawnObject(CSVReader& reader, std::string data, unsigned int x, unsigned int y);
	void spawnSingleBlock(CSVReader& reader, std::string data, unsigned int x, unsigned int y);
	void spawnMultiBlock(CSVReader& reader, std::vector<std::string>& groupList, unsigned int x, unsigned int y);

private:
	unsigned int m_Column;
	unsigned int m_Row;

	float m_MapWidth;
	float m_MapHeight;

	float m_CellWidth;
	float m_CellHeight;

	std::vector<Tile*> m_TileList;

	Vec3 m_Position;
	IGameMediator* m_pGameMediator;
};