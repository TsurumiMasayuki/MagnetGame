#include "TitleBackGround.h"
#include "Component\SpriteRenderer.h"

TitleBackGround::TitleBackGround(IGameMediator*pMediator, std::string TextureName)
	:GameObject(pMediator)
{
	name = TextureName;
}

TitleBackGround::~TitleBackGround()
{

}

void TitleBackGround::start()
{
	setSize(Vec3(1280, 720, 0));

    sprite = new SpriteRenderer(this,99);
	sprite->setTextureName(name);

	isFade = false;
}

void TitleBackGround::update()
{
	sprite->setTextureName(name);
}

void TitleBackGround::onDestroy()
{
}

void TitleBackGround::setTextureName(std::string TextureName)
{
	name = TextureName;
}
