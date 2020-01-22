#include "BackGround.h"
#include "Component\SpriteRenderer.h"

BackGround::BackGround(IGameMediator * pMediator, std::string TextureName)
	:GameObject(pMediator)
{
	name = TextureName;
}

BackGround::~BackGround()
{
}

void BackGround::start()
{
	setSize(Vec3(640, 360, 0));
	setPosition(Vec3(150,65,0));

	sprite = new SpriteRenderer(this, 99);
	sprite->setTextureName(name);

}

void BackGround::update()
{
	sprite->setTextureName(name);
}

void BackGround::onDestroy()
{
}

void BackGround::setTextureName(std::string TextureName)
{
	name = TextureName;
}
