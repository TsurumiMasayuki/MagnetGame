#include "Actor\GameObject.h"

class Block
	: public GameObject
{
public:
	Block(IGameMediator* pGameMediator, std::string textureName, float width, float height);
	~Block();

	virtual void start() override;

private:
	float m_Width;
	float m_Height;

	std::string m_TextureName;
};