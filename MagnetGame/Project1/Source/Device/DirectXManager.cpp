#include "DirectXManager.h"
#include "Def/Screen.h"

DirectXManager* DirectXManager::pInstance = nullptr;

#define SAFE_RELEASE(p) { if(p != nullptr) { (p)->Release(); (p)=nullptr; } }

void DirectXManager::initialize(HWND * pHWND)
{
#pragma region SWAPCHAIN
	IDXGISwapChain* pSwapChain;
	ID3D11Device* pDevice;
	ID3D11DeviceContext* pDeviceContext;

	DXGI_SWAP_CHAIN_DESC scDesc;
	ZeroMemory(&scDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	scDesc.BufferCount = 1;
	scDesc.BufferDesc.Width = Screen::getWindowWidth();
	scDesc.BufferDesc.Height = Screen::getWindowHeight();
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scDesc.BufferDesc.RefreshRate.Numerator = 60;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.OutputWindow = *pHWND;
	scDesc.SampleDesc.Count = 1;
	scDesc.Windowed = TRUE;

	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL* pFeatureLevel = NULL;

	UINT deviceFlags = 0;

#ifdef _DEBUG
	deviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		&pFeatureLevels,
		1,
		D3D11_SDK_VERSION,
		&scDesc,
		&pSwapChain,
		&pDevice,
		pFeatureLevel,
		&pDeviceContext
	);
#pragma endregion

#pragma region �A���t�@�u�����h�쐬

	D3D11_BLEND_DESC blendDesc;
	ID3D11BlendState* pBlendState;

	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
	blendDesc.IndependentBlendEnable = false;
	blendDesc.AlphaToCoverageEnable = false;

	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	pDevice->CreateBlendState(&blendDesc, &pBlendState);
	pDeviceContext->OMSetBlendState(pBlendState, NULL, 0x0f);

#pragma endregion

#pragma region �T���v���[�쐬

	D3D11_SAMPLER_DESC samDesc;
	ID3D11SamplerState* pSamplerState;

	ZeroMemory(&samDesc, sizeof(D3D11_SAMPLER_DESC));
	samDesc.Filter = D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
	samDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	pDevice->CreateSamplerState(&samDesc, &pSamplerState);
	pDeviceContext->PSSetSamplers(0, 1, &pSamplerState);

#pragma endregion

	//�V���O���g���̃C���X�^���X���쐬
	pInstance = new DirectXManager(
		pDevice,
		pDeviceContext,
		pSwapChain,
		pSamplerState,
		pBlendState
	);
}

void DirectXManager::shutdown()
{
	delete pInstance;
}

IDXGISwapChain * DirectXManager::getSwapChain()
{
	return pInstance->m_pSwapChain;
}

ID3D11Device * DirectXManager::getDevice()
{
	return pInstance->m_pDevice;
}

ID3D11DeviceContext * DirectXManager::getDeviceContext()
{
	return pInstance->m_pDeviceContext;
}

ID3D11SamplerState * DirectXManager::getSamplerState()
{
	return pInstance->getSamplerState();
}

void DirectXManager::clearScreen(const float clearColor[4])
{
}

void DirectXManager::presentSwapChain()
{
	pInstance->m_pSwapChain->Present(0, 0);
}

DirectXManager::DirectXManager(
	ID3D11Device * pDevice,
	ID3D11DeviceContext * pDeviceContext,
	IDXGISwapChain * pSwapChain,
	ID3D11SamplerState * pSamplerState,
	ID3D11BlendState * pBlendState)
	:m_pDevice(pDevice),
	m_pDeviceContext(pDeviceContext),
	m_pSwapChain(pSwapChain),
	m_pSamplerState(pSamplerState),
	m_pBlendState(pBlendState)
{
}

DirectXManager::~DirectXManager()
{
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pDeviceContext);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pSamplerState);
	SAFE_RELEASE(m_pBlendState);
}
