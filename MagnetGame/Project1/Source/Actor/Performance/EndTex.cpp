#include "EndTex.h"
#include "Component\SpriteRenderer.h"

EndTex::EndTex(IGameMediator * pMediator)
	:GameObject(pMediator)
{
}

EndTex::~EndTex()
{
}

void EndTex::start()
{
	setSize(Vec3(1280, 720, 0));

	sprite = new SpriteRenderer(this, 300);
	sprite->setTextureName("fin");

	alpha = 0;
	isEndFlag = false;
}

void EndTex::update()
{
	sprite->setColor(Color(1, 1, 1, alpha));
	if (alpha >= 4.0f) {
		isEndFlag = true;
	}
	else {
		alpha += 0.009f;
	}
}

void EndTex::onDestroy()
{
}

float EndTex::getAlpha()
{
	return alpha;
}
