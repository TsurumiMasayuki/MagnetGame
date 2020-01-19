#include "Title_Sprite.h"

Title_Sprite::Title_Sprite(IGameMediator * pMediator):GameObject(pMediator)
{
}

void Title_Sprite::start()
{
	tree = new SpriteRenderer(this, 98);
	tree->setTextureName("op_background");
	setSize(Vec3(1280, 720, 0));
	setPosition(Vec3(0, 0, 0));

	tree = new SpriteRenderer(this,99);
	tree->setTextureName("op_tree");
	setSize(Vec3(1280, 720, 0));
	setPosition(Vec3(0, 0, 0));
	

	huusya = new SpriteRenderer(this,101);
	huusya->setTextureName("op_huusya");
	setSize(Vec3(1280, 720, 0));
	setPosition(Vec3(0, 0, 0));
}

void Title_Sprite::update()
{
}

void Title_Sprite::onDestroy()
{
}
