#include "EventText.h"
#include "Component\SpriteRenderer.h"

EventText::EventText(IGameMediator * pMediator)
	:GameObject(pMediator)
{
}

EventText::~EventText()
{

}

void EventText::start()
{
	setSize(Vec3(1000, 250, 0));
	setPosition(Vec3(0,-235, 0));

	frame = new SpriteRenderer(this);
	frame->setTextureName("log_player");

	arrow = new SpriteRenderer(this);
	arrow->setTextureName("log_arrow"); 
	
	text = new SpriteRenderer(this);
	text->setTextureName("text0");

	text->setColor(Color(1, 1, 1, 1));
	frame->setColor(Color(1, 1, 1, 1));
	arrow->setColor(Color(1, 1, 1, 1));

	state = State::Hero;
	EventNum = 0;
	alpha = 1;
	a = 0;
}

void EventText::update()
{
	a += 0.15f;
	alpha += cos((double)a);
	arrow->setColor(Color(1,1,1,alpha));
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
}
