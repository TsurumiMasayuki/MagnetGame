#pragma once
#include <vector>
#include <string>

class CSVReader
{
public:
	CSVReader();
	~CSVReader();

	//現在読み込まれているCSVを破棄して新しく読み込む
	void open(std::string filePath, bool isExcelCSV = true);

	unsigned int getColumnCount(unsigned int row);
	unsigned int getRowCount();

	std::string getData(unsigned int column, unsigned int row);
	std::string getDataClampIndex(unsigned int column, unsigned int row);

private:
	std::vector<std::vector<std::string>> m_DataList;
};