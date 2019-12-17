#include "VertexShader.h"
#include <cstdio>
#include "Device\DirectXManager.h"

VertexShader::VertexShader(const char* filePath)
{
	FILE* pFile = nullptr;
	fopen_s(&pFile, filePath, "rb");	//�o�C�g�ǂݍ��݃��[�h�ɂ���

	fseek(pFile, 0, SEEK_END); 		//�t�@�C�������܂ňړ�
	long fileSize = ftell(pFile);	//���݂̈ʒu(���ňړ������̂Ŗ���)���擾
	fseek(pFile, 0, SEEK_SET);		//�t�@�C���̐擪�Ɉړ�

	m_pShaderByteCode = new unsigned char[fileSize];//�f�[�^�i�[�p�z����쐬
	fread(m_pShaderByteCode, fileSize, 1, pFile);					//�t�@�C���f�[�^��ǂݍ���
	fclose(pFile);											//�ǂݍ��݂��I������̂Ńt�@�C�������

	auto pDevice = DirectXManager::getDevice();

	pDevice->CreateVertexShader(m_pShaderByteCode, fileSize, NULL, &m_pVertexShader);
	m_ByteCodeLength = fileSize;
}

VertexShader::~VertexShader()
{
	m_pVertexShader->Release();
	delete[] m_pShaderByteCode;
}

ID3D11VertexShader * VertexShader::getShader()
{
	return m_pVertexShader;
}

HRESULT VertexShader::createInputLayout(ID3D11Device * pDevice, D3D11_INPUT_ELEMENT_DESC * pInputDesc, UINT numElements, ID3D11InputLayout ** ppInputLayout)
{
	return pDevice->CreateInputLayout(pInputDesc, numElements, m_pShaderByteCode, m_ByteCodeLength, ppInputLayout);
}
