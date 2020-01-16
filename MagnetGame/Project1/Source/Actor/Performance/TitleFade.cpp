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
	isEndFlag = false;
}

void TitleFade::update()
{
	sprite->setColor(Color(10, 10, 10, alpha));
	alpha += 0.01f;
	if (alpha >= 2.0f) {
		isEndFlag = true;
	}
}

void TitleFade::onDestroy()
{
}

bool TitleFade::isEnd()
{
	return isEndFlag;
}
