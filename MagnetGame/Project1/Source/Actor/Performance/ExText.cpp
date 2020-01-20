#include "ExText.h"
#include "Component\SpriteRenderer.h"

ExText::ExText(IGameMediator * pMediator, std::string TextureName)
	:GameObject(pMediator)
{
	name = TextureName;
}

ExText::~ExText()
{
}

void ExText::start()
{
	setSize(Vec3(1280, 800, 0));
	sprite = new SpriteRenderer(this, 110);
	sprite->setTextureName(name);

	stateNum = 0;
}

void ExText::update()
{
	sprite->setTextureName(name);
}

void ExText::onDestroy()
{
}

void ExText::UpdateStateNum()
{
}

void ExText::setTextureName(std::string TextureName)
{
}

void ExText::setStateNum(int value)
{
	stateNum = value;
}

void ExText::addStateNum()
{
	stateNum++;
}

int ExText::getStateNum()
{
	return stateNum;
}
