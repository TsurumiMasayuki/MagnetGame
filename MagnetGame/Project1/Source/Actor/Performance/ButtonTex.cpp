#include "ButtonTex.h"
#include "Component\SpriteRenderer.h"

ButtonTex::ButtonTex(IGameMediator * pMediator)
	:GameObject(pMediator)
{
	setSize(Vec3(64, 64, 0));

	sprite = new SpriteRenderer(this,110);
	sprite->setTextureName("A");
}

ButtonTex::~ButtonTex()
{
}

void ButtonTex::start()
{
}

void ButtonTex::update()
{
}

void ButtonTex::onDestroy()
{
}
