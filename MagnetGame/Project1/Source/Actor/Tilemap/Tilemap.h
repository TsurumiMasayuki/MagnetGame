#pragma once
#include "Actor\GameObject.h"
#include <string>
#include <vector>

class CSVReader;

class Tilemap
	: public GameObject
{
public:
	Tilemap(IGameMediator* pGameMediator, float cellWidth = 64, float cellHeight = 64);
	~Tilemap();

	void load(std::string csvFileName);

	unsigned int getColumn() { return m_Column; }
	unsigned int getRow() { return m_Row; }

	float getWidth();
	float getHeight();

private:
	void spawnSingleBlock(CSVReader& reader, std::string data, unsigned int x, unsigned int y);
	void spawnMultiBlock(CSVReader& reader, std::vector<std::string>& groupList, unsigned int x, unsigned int y);

private:
	unsigned int m_Column;
	unsigned int m_Row;

	float m_MapWidth;
	float m_MapHeight;

	float m_CellWidth;
	float m_CellHeight;

	//std::vector<GameObject*> m_TileList;
};