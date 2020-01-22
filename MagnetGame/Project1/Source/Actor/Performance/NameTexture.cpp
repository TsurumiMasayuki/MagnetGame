#include "NameTexture.h"
#include "Component\SpriteRenderer.h"

NameTexture::NameTexture(IGameMediator * pMediator)
	:GameObject(pMediator)
{
}

NameTexture::~NameTexture()
{
}

void NameTexture::start()
{
	int size = 3;
	setSize(Vec3(106 * size, 14 * size, 0));
	setPosition(Vec3(-640 + 159, -164, 0));
	sprite = new SpriteRenderer(this, 312);
	sprite->setTextureName("lop");
}

void NameTexture::update()
{

	switch (EventNum)
	{
	case 0:
		nState = NameState::Hero;
		break;
	case 1:
		nState = NameState::Doctor;
		break;
	case 2:
		nState = NameState::Doctor;
		break;
	case 3:
		nState = NameState::Hero;
		break;
	case 4:
		nState = NameState::Hero;
		break;
	case 5:
		nState = NameState::Hero;
		break;
	case 6:
		nState = NameState::Hero;
		break;
	case 7:
		nState = NameState::Doctor;
		break;
	case 8:
		nState = NameState::Doctor;
		break;
	case 9:
		nState = NameState::Hero;
		break;
	case 10:
		nState = NameState::Hero;
		break;
	case 11:
		nState = NameState::Doctor;
		break;
	case 12:
		nState = NameState::Doctor;
		break;
	case 13:
		nState = NameState::Hero;
		break;
	case 14:
		nState = NameState::Hero;
		break;
	case 15:
		nState = NameState::Doctor;
		break;
	case 16:
		nState = NameState::Doctor;
		break;
	case 17:
		nState = NameState::Doctor;
		break;
	case 18:
		nState = NameState::Doctor;
		break;
	case 19:
		nState = NameState::Doctor;
		break;
	case 20:
		nState = NameState::Hero;
		break;
	case 21:
		nState = NameState::Doctor;
		break;

	case 27:
		nState = NameState::Doctor;
		break;
	case 28:
		nState = NameState::Doctor;
		break;
	case 29:
		nState = NameState::Doctor;
		break;
	case 30:
		nState = NameState::Doctor;
		break;
	case 31:
		nState = NameState::Doctor;
		break;
	case 32:
		nState = NameState::Doctor;
		break;
	case 33:
		nState = NameState::Doctor;
		break;
	case 34:
		nState = NameState::Doctor;
		break;
	case 35:
		nState = NameState::Doctor;
		break;
	case 36:
		nState = NameState::Doctor;
		break;
	case 50:
		nState = NameState::Hero;
		break;
	case 51:
		nState = NameState::Doctor;
		break;
	case 52:
		nState = NameState::Doctor;
		break;
	case 53:
		nState = NameState::Hero;
		break;
	case 54:
		nState = NameState::Doctor;
		break;
	case 55:
		nState = NameState::Hero;
		break;
	case 56:
		nState = NameState::Hero;
		break;
	case 57:
		nState = NameState::Doctor;
		break;
	case 58:
		nState = NameState::Hero;
		break;
	case 59:
		nState = NameState::Doctor;
		break;
	case 60:
		nState = NameState::Hero;
		break;
	case 61:
		nState = NameState::Doctor;
		break;
	case 62:
		nState = NameState::Hero;
		break;
	case 63:
		nState = NameState::Doctor;
		break;
	case 64:
		nState = NameState::Hero;
		break;
	case 65:
		nState = NameState::Hero;
		break;
	case 66:
		nState = NameState::Hero;
		break;
	case 67:
		nState = NameState::Doctor;
		break;
	case 68:
		nState = NameState::Doctor;
		break;
	case 69:
		nState = NameState::Doctor;
		break;
	case 70:
		nState = NameState::Hero;
		break;
	default:
		break;
	}
	switch (nState)
	{
	case NameTexture::Hero:
		sprite->setTextureName("lop");
		break;
	case NameTexture::Doctor:
		sprite->setTextureName("beard");
		break;
	case NameTexture::Doctor_Black:
		sprite->setTextureName("beard");
		break;
	default:
		break;
	}
}

void NameTexture::onDestroy()
{
}

void NameTexture::setEventNum(int num)
{
	EventNum = num;
}
