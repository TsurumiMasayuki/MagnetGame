#include "ButtonTex.h"
#include "Component\SpriteRenderer.h"

ButtonTex::ButtonTex(IGameMediator * pMediator)
	:GameObject(pMediator)
{
}

ButtonTex::~ButtonTex()
{
}

void ButtonTex::start()
{
	setSize(Vec3(64, 64, 0));

	sprite = new SpriteRenderer(this, 310);
	sprite->setTextureName(name);
	//name="A";
	alpha = 1;

	
}

void ButtonTex::update()
{
	sprite->setTextureName(name);
	sprite->setColor(Color(1,1,1,alpha));
}

void ButtonTex::onDestroy()
{
}

void ButtonTex::setTextureName(std::string TextureName)
{
	name = TextureName;
}
void ButtonTex::setAlpha(float value)
{
	alpha = value;
}

