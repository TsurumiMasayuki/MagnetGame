#pragma once
#include <vector>

class SpriteRenderer;
class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;

struct ID3D11InputLayout;
struct ID3D11Texture2D;
struct ID3D11RenderTargetView;
struct ID3D11ShaderResourceView;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void init();
	void draw();

	//SpriteRenderer��o�^����B���������p�Ȃ̂Ŋ�{�g��Ȃ�
	void addSprite(SpriteRenderer* pSprite);
	//SpriteRenderer��o�^����B���������p�Ȃ̂Ŋ�{�g��Ȃ�
	void removeSprite(SpriteRenderer* pSprite);

private:
	void initBuffers();
	void initRenderTargets();

	void drawSprites();

private:
	std::vector<SpriteRenderer*> m_Sprites;

	ID3D11InputLayout* m_pSpriteInputLayout;
	VertexBuffer* m_pSpriteVertices;
	IndexBuffer* m_pSpriteIndices;

	ID3D11Texture2D* m_pRenderTexDefault;
	ID3D11RenderTargetView* m_pRTVDefault;
	ID3D11ShaderResourceView* m_pSRVDefault;

};