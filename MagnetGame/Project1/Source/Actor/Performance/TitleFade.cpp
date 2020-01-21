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

	sprite = new SpriteRenderer(this,129);
	sprite->setTextureName("white");

	alpha = 0;
	isEndFlag = false;
}

void TitleFade::update()
{
	sprite->setColor(Color(0, 0, 0, alpha));
	if (alpha >= 4.0f) {
		isEndFlag = true;
	}
	else {
		alpha += 0.01f;
	}
}

void TitleFade::onDestroy()
{
}

bool TitleFade::isEnd()
{
	return isEndFlag;
}

float TitleFade::getAlpha()
{
	return alpha;
}
