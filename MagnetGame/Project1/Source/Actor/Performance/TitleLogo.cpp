#include "TitleLogo.h"
#include "Component\SpriteRenderer.h"

TitleLogo::TitleLogo(IGameMediator * pMediator, std::string TextureName)
	:GameObject(pMediator)
{
	name = TextureName;
}

TitleLogo::~TitleLogo()
{
	
}

void TitleLogo::start()
{

	sprite = new SpriteRenderer(this);
	sprite->setTextureName(name);

	isFade = false;
	alpha = 1;
}

void TitleLogo::update()
{
	sprite->setTextureName(name);

	if (isFade&&alpha>=0) {
		alpha-=0.01f;
		if (alpha <= 0) {
			alpha = 0;
		}
	}
	if (!isFade&&alpha<=1) {
		alpha+=0.01f;

		if (alpha >= 1) {
			alpha = 1;
		}
	}
	sprite->setColor(Color(1, 1, 1, alpha));
}

void TitleLogo::onDestroy()
{
}

void TitleLogo::setTextureName(std::string TextureName)
{
	name = TextureName;
}

void TitleLogo::setFade(bool value)
{
	isFade = value;
}
