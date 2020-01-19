#include "Letter.h"
#include "Component\SpriteRenderer.h"

Letter::Letter(IGameMediator * pMediator)
	:GameObject(pMediator)
{
}

Letter::~Letter()
{
}

void Letter::start()
{
	setSize(Vec3(32,32,0));
	sprite = new SpriteRenderer(this, 99);
	sprite->setTextureName("letter");
}

void Letter::update()
{
}

void Letter::onDestroy()
{
}
