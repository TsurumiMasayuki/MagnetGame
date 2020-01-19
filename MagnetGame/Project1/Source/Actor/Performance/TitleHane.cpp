#include "TitleHane.h"

TitleHane::TitleHane( IGameMediator * pMediator):GameObject(pMediator)
{
}

void TitleHane::start()
{
	sprite = new SpriteRenderer(this,98);
	setSize(300);
	sprite->setTextureName("hane");
	angle = 0;
}

void TitleHane::update()
{
	angle += 0.01f;
	if (angle >= 360)angle = 0;
	setAngleZ(angle);
}

void TitleHane::onDestroy()
{
}
