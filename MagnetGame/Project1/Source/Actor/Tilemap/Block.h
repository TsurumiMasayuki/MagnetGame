#include "Actor\GameObject.h"

class Block
	: public GameObject
{
public:
	Block(IGameMediator* pGameMediator, std::string textureName, float width, float height, bool hasCollider = true);
	~Block();

	virtual void start() override;

private:
	float m_Width;
	float m_Height;

	bool m_HasCollider;

	std::string m_TextureName;
};