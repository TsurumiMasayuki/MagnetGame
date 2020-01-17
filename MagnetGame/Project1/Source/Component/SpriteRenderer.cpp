#include "SpriteRenderer.h"

#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include "Device\Camera.h"
#include "Device\DirectXManager.h"
#include "Device\GameDevice.h"
#include "Device\Renderer.h"
#include "Device\TextureManager.h"
#include "Device\ShaderManager.h"

#include "Device\Base\SpriteVertex.h"
#include "Device\Buffer\SpriteConstantBuffer.h"
#include "Device\Buffer\VertexBuffer.h"
#include "Device\Buffer\ConstantBuffer.h"

#include "Actor\GameObject.h"

using namespace DirectX;

unsigned int SpriteRenderer::componentCount;
ConstantBuffer* SpriteRenderer::pSpriteCB;
VertexBuffer* SpriteRenderer::pSpriteVerticesNormal;
VertexBuffer* SpriteRenderer::pSpriteVerticesInvert;

SpriteRenderer::SpriteRenderer(GameObject * pUser, int drawOrder)
	: AbstractComponent(pUser),
	m_DrawOrder(drawOrder),
	m_VSName("SpriteDefault"),
	m_PSName("SpriteDefault"),
	m_Color(DirectX::Colors::White),
	m_UVRect(0, 0, 1, 1),
	m_ImagePivot(0, 0)
{
	//Renderer�ɓo�^
	GameDevice::getRenderer()->addSprite(this);

	//�ŏ���SpriteRenderer�Ȃ�
	if (componentCount == 0)
	{
		pSpriteCB = new ConstantBuffer();
		SpriteConstantBuffer buffer;
		pSpriteCB->init(DirectXManager::getDevice(), sizeof(SpriteConstantBuffer), &buffer);

		float width = 0.5f;
		float height = 0.5f;

		//�l�p�̒��_���쐬
		SpriteVertex vertices[]
		{
			{{-width,  height, 0.0f}, {0.0f, 0.0f}},
			{{ width, -height, 0.0f}, {1.0f, 1.0f}},
			{{-width, -height, 0.0f}, {0.0f, 1.0f}},
			{{ width,  height, 0.0f}, {1.0f, 0.0f}},
		};

		pSpriteVerticesNormal = new VertexBuffer();
		pSpriteVerticesNormal->init(DirectXManager::getDevice(), sizeof(SpriteVertex) * 4, vertices);

		//�l�p�̒��_���쐬
		SpriteVertex verticesInv[]
		{
			{{-width,  height, 0.0f}, {1.0f, 0.0f}},
			{{ width, -height, 0.0f}, {0.0f, 1.0f}},
			{{-width, -height, 0.0f}, {1.0f, 1.0f}},
			{{ width,  height, 0.0f}, {0.0f, 0.0f}},
		};

		pSpriteVerticesInvert = new VertexBuffer();
		pSpriteVerticesInvert->init(DirectXManager::getDevice(), sizeof(SpriteVertex) * 4, verticesInv);
	}
	componentCount++;
}

SpriteRenderer::~SpriteRenderer()
{
	//Renderer����폜
	GameDevice::getRenderer()->removeSprite(this);

	componentCount--;

	if (componentCount == 0)
	{
		delete pSpriteCB;
		pSpriteCB = nullptr;

		delete pSpriteVerticesNormal;
		pSpriteVerticesNormal = nullptr;

		delete pSpriteVerticesInvert;
		pSpriteVerticesInvert = nullptr;
	}
}

void SpriteRenderer::onStart()
{
}

void SpriteRenderer::onUpdate()
{
}

AbstractComponent::TypeID SpriteRenderer::getType() const
{
	return TypeID::TSpriteRenderer;
}

int SpriteRenderer::getDrawOrder() const
{
	return m_DrawOrder;
}

void SpriteRenderer::draw()
{
	if (!isActive())
		return;

	auto pDeviceContext = DirectXManager::getDeviceContext();

	//VertexShader���Z�b�g
	pDeviceContext->VSSetShader(ShaderManager::GetVertexShaderInstance(m_VSName), NULL, 0);
	//PixelShader���Z�b�g
	pDeviceContext->PSSetShader(ShaderManager::GetPixelShaderInstance(m_PSName), NULL, 0);

	SpriteConstantBuffer constantBuffer;
	//�ړ�
	XMMATRIX translate = XMMatrixTranslationFromVector(m_pUser->getPosition().toXMVector());
	//��]
	XMMATRIX rotation = XMMatrixRotationRollPitchYawFromVector(m_pUser->getAngles().toXMVector());
	//�g��k��
	XMMATRIX scaling = XMMatrixScalingFromVector(m_pUser->getSize().toXMVector());
	//���[���h�s��쐬
	XMMATRIX world = scaling * rotation * translate;

	//�s�������+�]�u
	XMMATRIX wvp = XMMatrixTranspose(world * Camera::getViewOrthoMatrix());

	//���g�̊e��v���p�e�B���R���X�^���g�o�b�t�@�ɃZ�b�g
	//���[���h�s��
	XMStoreFloat4x4(&constantBuffer.wvpMatrix, wvp);
	//�s�{�b�g(���u��)
	constantBuffer.pivot = { m_ImagePivot.x, m_ImagePivot.y, 0.0f, 0.0f };
	//�F(���u��)
	XMStoreFloat4(&constantBuffer.color, m_Color.toXMFLOAT4());
	//UV�ݒ�̍���
	constantBuffer.uvOffset = { m_UVRect.x, m_UVRect.y };
	//UV�ݒ�̉E��
	constantBuffer.uvSize = { m_UVRect.width, m_UVRect.height };

	//UpdateSubresource�ŃR���X�^���g�o�b�t�@���X�V
	auto cBuffer = pSpriteCB->getBuffer();
	pDeviceContext->UpdateSubresource(cBuffer, 0, NULL, &constantBuffer, NULL, NULL);
	pDeviceContext->VSSetConstantBuffers(0, 1, &cBuffer);

	//�e�N�X�`����ݒ�
	auto texture = TextureManager::getTextureView(m_TextureName);
	pDeviceContext->PSSetShaderResources(0, 1, &texture);

	auto vertices = pSpriteVerticesInvert->getBuffer();
	UINT stride = sizeof(SpriteVertex);
	UINT offset = 0;

	if (m_FlipX)
	{
		vertices = pSpriteVerticesInvert->getBuffer();
	}
	else
	{
		vertices = pSpriteVerticesNormal->getBuffer();
	}

	pDeviceContext->IASetVertexBuffers(0, 1, &vertices, &stride, &offset);

	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pDeviceContext->DrawIndexed(6, 0, 0);
}

void SpriteRenderer::setTextureName(const std::string textureName)
{
	m_TextureName = textureName;
}

std::string SpriteRenderer::getTextureName()
{
	return m_TextureName;
}

Color SpriteRenderer::getColor()
{
	return m_Color;
}

void SpriteRenderer::setColor(Color color)
{
	m_Color = color;
}

void SpriteRenderer::setFlipX(bool flipX)
{
	m_FlipX = flipX;
}

void SpriteRenderer::setFlipY(bool flipY)
{
	m_FlipY = flipY;
}

Vec2 SpriteRenderer::getPivot()
{
	return m_ImagePivot;
}

void SpriteRenderer::setPivot(Vec2 pivot)
{
	m_ImagePivot = pivot;
}

RectF SpriteRenderer::getUVRect()
{
	return m_UVRect;
}

void SpriteRenderer::setUVRect(RectF uvRect)
{
	m_UVRect = uvRect;
}