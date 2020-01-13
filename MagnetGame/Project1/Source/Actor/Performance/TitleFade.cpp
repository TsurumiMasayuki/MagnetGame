#include "TitleFade.h"
#include "Component\SpriteRenderer.h"

TitleFade::TitleFade(IGameMediator * pMediator)
	:GameObject(pMediator)
{

}

TitleFade::~TitleFade()
{
}

void TitleFade::start()
{
	setSize(Vec3(1280, 720, 0));

	sprite = new SpriteRenderer(this);
	sprite->setTextureName("white");

	alpha = 0;
	isFade = false;
}

void TitleFade::update()
{
	sprite->setColor(Color(0,0,0,alpha));
	alpha += 0.01f;
}

void TitleFade::onDestroy()
{
}
