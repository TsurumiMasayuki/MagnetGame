#include "CSVReader.h"

#include <fstream>
#include "Utility\StringUtility.h"
#include "Math\MathUtility.h"

CSVReader::CSVReader()
{
}

CSVReader::~CSVReader()
{
}

void CSVReader::open(std::string filePath, bool isExcelCSV)
{
	//�f�[�^���N���A
	m_DataList.clear();

	//�ǂݍ��ݗp�X�g���[�����쐬
	std::ifstream reader(filePath);

	std::string line;
	while (!reader.eof())
	{
		std::getline(reader, line);
		std::vector<std::string> lineData;

		StringUtility::split(line, ',', lineData);

		m_DataList.push_back(lineData);
	}

	//�ǂݍ��ݏI������̂ŃX�g���[�������
	reader.close();

	//Excel�ŕۑ������ꍇ���ʂȈ�s�������ɒǉ������̂�pop
	if (isExcelCSV)
		m_DataList.pop_back();
}

unsigned int CSVReader::getColumnCount(unsigned int row)
{
	return m_DataList.at(row).size();
}

unsigned int CSVReader::getRowCount()
{
	return m_DataList.size();
}

std::string CSVReader::getData(unsigned int column, unsigned int row)
{
	return m_DataList.at(row).at(column);
}

std::string CSVReader::getDataClampIndex(unsigned int column, unsigned int row)
{
	//X, Y�C���f�b�N�X�𒴉߂��Ă�������Ԃ�
	if (row >= getRowCount())
		return "1";
	else if (column >= getColumnCount(row))
		return "1";

	return m_DataList.at(row).at(column);
}
