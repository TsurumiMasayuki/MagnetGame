#include "Hint.h"
#include "Component\SpriteRenderer.h"

Hint::Hint(IGameMediator * pMediator)
	:GameObject(pMediator)
{
}

Hint::~Hint()
{
}

void Hint::start()
{
	setSize(Vec3(1280, 720, 0));

	sprite = new SpriteRenderer(this, 320);
	name = "hinto";
	sprite->setTextureName(name);
	text = new SpriteRenderer(this, 321);
	text->setTextureName(name);


}

void Hint::update()
{
	switch (m_HintNum)

	{
	case 1:
		name = "hint1";
		break;
	case 2:
		name = "hint2";
		break;
	case 3:
		name = "hint3";
		break;
	case 4:
		name = "hint4";
		break;
	case 5:
		name = "hint5";
		break;
	case 6:
		name = "hint6";
		break;
	case 7:
		name = "hint7";
		break;
	case 8:
		name = "hint8";
		break;
	case 9:
		name = "hint9";
		break;
	case 10:
		name = "hint10";
		break;
	case 11:
		name = "hint11";
		break;
	case 12:
		name = "hint12";
		break;
	case 13:
		name = "hint13";
		break;
	case 14:
		name = "hint14";
		break;
	case 15:
		name = "hint15";
		break;
	case 16:
		name = "hint16";
		break;
	case 17:
		name = "hint17";
		break;
	case 18:
		name = "hint18";
		break;

	default:
		break;
	}
	text->setTextureName(name);
}

void Hint::setHintNum(int value)
{
	m_HintNum = value;
}
