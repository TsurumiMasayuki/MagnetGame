#include "ShaderManager.h"
#include "DirectXManager.h"
#include <unordered_map>

using namespace std;

static unordered_map<string, VertexShader*> vsList;
static unordered_map<string, PixelShader*> psList;

//HRESULT ShaderManager::LoadVertexShader(ID3D11Device * pDevice, const string key, const void * pShaderByteCode, SIZE_T byteCodeLength)
//{
//	ID3D11VertexShader* pVertexShader;
//	if (FAILED(pDevice->CreateVertexShader(pShaderByteCode, byteCodeLength, NULL, &pVertexShader)))
//		return E_FAIL;
//	vsList.emplace(key, pVertexShader);
//	return S_OK;
//}
//
//HRESULT ShaderManager::LoadPixelShader(ID3D11Device * pDevice, const string key, const void * pShaderByteCode, SIZE_T byteCodeLength)
//{
//	ID3D11PixelShader* pPixelShader;
//	if (FAILED(pDevice->CreatePixelShader(pShaderByteCode, byteCodeLength, NULL, &pPixelShader)))
//		return E_FAIL;
//	psList.emplace(key, pPixelShader);
//	return S_OK;
//}

HRESULT ShaderManager::LoadVertexShader_CSO(std::string key, const CHAR * filePath)
{
	auto pVertexShader = new VertexShader(filePath);
	vsList.emplace(key, pVertexShader);
	return S_OK;
}

HRESULT ShaderManager::LoadPixelShader_CSO(std::string key, const CHAR * filePath)
{
	auto pPixelShader = new PixelShader(filePath);
	psList.emplace(key, pPixelShader);
	return S_OK;
}

VertexShader * ShaderManager::GetVertexShader(const std::string key)
{
	return vsList.at(key);
}

PixelShader * ShaderManager::GetPixelShader(const std::string key)
{
	return psList.at(key);
}

ID3D11VertexShader * ShaderManager::GetVertexShaderInstance(const string key)
{
	return vsList.at(key)->getShader();
}

ID3D11PixelShader * ShaderManager::GetPixelShaderInstance(const string key)
{
	return psList.at(key)->getShader();
}

void ShaderManager::releaseAll()
{
	for (auto shader : vsList)
	{
		delete shader.second;
	}
	vsList.clear();

	for (auto shader : psList)
	{
		delete shader.second;
	}
	psList.clear();
}
