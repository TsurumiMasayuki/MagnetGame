#include "EventText.h"
#include "Component\SpriteRenderer.h"
#include"Device/SoundManager.h"

EventText::EventText(IGameMediator * pMediator)
	:GameObject(pMediator)
{
}

EventText::~EventText()
{

}

void EventText::start()
{
	setSize(Vec3(1280, 180, 0));
	setPosition(Vec3(0, -270, 0));

	frame = new SpriteRenderer(this,110);
	frame->setTextureName("log_player");

	arrow = new SpriteRenderer(this,112);
	arrow->setTextureName("log_arrow");

	text = new SpriteRenderer(this,111);
	text->setTextureName("text0");

	text->setColor(Color(1, 1, 1, 1));
	frame->setColor(Color(1, 1, 1, 1));
	arrow->setColor(Color(1, 1, 1, 1));

	state = State::Hero;
	alpha = 1;
	a = 0;
}

void EventText::update()
{
	a += 0.15f;
	alpha += cos((double)a);
	arrow->setColor(Color(1, 1, 1, alpha));
	switch (EventNum)
	{
	case 0:
		text->setTextureName("text0");
		state = State::Hero;
		break;
	case 1:
		text->setTextureName("text1");
		state = State::Doctor_Black;
		break;
	case 2:
		text->setTextureName("text2");
		state = State::Doctor_Black;
		break;
	case 3:
		text->setTextureName("text3");
		state = State::Hero;
		break;
	case 4:
		text->setTextureName("text4");
		state = State::Hero;
		break;
	case 5:
		text->setTextureName("text5");
		state = State::Hero;
		break;
	case 6:
		text->setTextureName("text6");
		state = State::Hero;
		break;
	case 7:
		text->setTextureName("text7");
		state = State::Doctor;
		break;
	case 8:
		text->setTextureName("text8");
		state = State::Doctor;
		break;
	case 9:
		text->setTextureName("text9");
		state = State::Hero;
		break;
	case 10:
		text->setTextureName("text10");
		state = State::Hero;
		break;
	case 11:
		text->setTextureName("text11");
		state = State::Doctor;
		break;
	case 12:
		text->setTextureName("text12");
		state = State::Doctor;
		break;
	case 13:
		text->setTextureName("text13");
		state = State::Hero;
		break;
	case 14:
		text->setTextureName("text14");
		state = State::Doctor;
		break;
	case 15:
		text->setTextureName("text15");
		state = State::Doctor;
		break;
	case 16:
		text->setTextureName("text16");
		state = State::Doctor;
		break;
	case 17:
		text->setTextureName("text17");
		state = State::Doctor;
		break;
	case 18:
		text->setTextureName("text18");
		state = State::Hero;
		break;

	default:
		break;
	}

	switch (state)
	{
	case EventText::Hero:
		frame->setTextureName("log_player");
		break;
	case EventText::Doctor:
		frame->setTextureName("log_hakase");
		break;
	case EventText::Doctor_Black:
		frame->setTextureName("log_hakase_black");
		break;
	}
}

void EventText::onDestroy()
{
}

void EventText::setEventNum(int num)
{
	EventNum = num;
}

int EventText::getEventNum()
{
	return EventNum;
}

void EventText::addEventNum()
{
	EventNum++;
	SoundManager::playSE("kettei");
}
