#include "PixelShader.h"
#include <cstdio>
#include "Device\DirectXManager.h"

PixelShader::PixelShader(const char * filePath)
{
	FILE* pFile = nullptr;
	fopen_s(&pFile, filePath, "rb");	//�o�C�g�ǂݍ��݃��[�h�ɂ���

	fseek(pFile, 0, SEEK_END); 		//�t�@�C�������܂ňړ�
	long fileSize = ftell(pFile);	//���݂̈ʒu(���ňړ������̂Ŗ���)���擾
	fseek(pFile, 0, SEEK_SET);		//�t�@�C���̐擪�Ɉړ�

	unsigned char* fileData = new unsigned char[fileSize];	//�f�[�^�i�[�p�z����쐬
	fread(fileData, fileSize, 1, pFile);					//�t�@�C���f�[�^��ǂݍ���
	fclose(pFile);											//�ǂݍ��݂��I������̂Ńt�@�C�������

	auto pDevice = DirectXManager::getDevice();

	pDevice->CreatePixelShader(fileData, fileSize, NULL, &m_pPixelShader);

	delete[] fileData;
}

PixelShader::~PixelShader()
{
	m_pPixelShader->Release();
}

ID3D11PixelShader * PixelShader::getShader()
{
	return m_pPixelShader;
}
