#include "FadeOut.h"
#include "Component\SpriteRenderer.h"

FadeOut::FadeOut(IGameMediator * pMediator)
	:GameObject(pMediator)
{
}

FadeOut::~FadeOut()
{
}

void FadeOut::start()
{
	setSize(Vec3(1280, 720, 0));

	sprite = new SpriteRenderer(this, 200);
	sprite->setTextureName("white");

	alpha = 1.5f;
	isEndFlag = false;
}


void FadeOut::update()
{
	sprite->setColor(Color(0, 0, 0, alpha));
	if (alpha <=-4.0f) {
		isEndFlag = true;
	}
	else {

		alpha -= 0.006f;
	}
}

void FadeOut::onDestroy()
{
}

float FadeOut::getAlpha()
{
	return alpha;
}
