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

	switch (stateNum)
	{
	case 0:
		name = "Mag_Ex";
		break;
	case 1:
		name = "Punch_Ex";
		break;
	case 2:
		name = "sousa";
		break;
	case 3:
		name = "N_Ex";
		break;
	case 4:
		name = "Jump_Ex";
		break;
	default:
		break;
	}
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
