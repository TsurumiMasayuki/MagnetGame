#include "Item.h"
#include "Component\SpriteRenderer.h"

Item::Item(IGameMediator * pMediator, std::string TextureName)
	:GameObject(pMediator)
{
	name = TextureName;
}

Item::~Item()
{
}

void Item::start()
{
	setSize(Vec3(96,96,0));
	sprite = new SpriteRenderer(this, 101);
	sprite->setTextureName(name);
}

void Item::update()
{
	sprite->setTextureName(name);
}

void Item::onDestroy()
{
}

void Item::setTextureName(std::string TextureName)
{
	name = TextureName;
}
