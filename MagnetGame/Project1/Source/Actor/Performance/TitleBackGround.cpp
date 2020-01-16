#include "TitleBackGround.h"
#include "Component\SpriteRenderer.h"

TitleBackGround::TitleBackGround(IGameMediator*pMediator)
	:GameObject(pMediator)
{
}

TitleBackGround::~TitleBackGround()
{

}

void TitleBackGround::start()
{
	setSize(Vec3(1280, 720, 0));

    sprite = new SpriteRenderer(this);
	sprite->setTextureName("opening");

	isFade = false;
}

void TitleBackGround::update()
{
}

void TitleBackGround::onDestroy()
{
}
