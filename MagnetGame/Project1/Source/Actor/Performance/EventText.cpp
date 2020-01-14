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
	setSize(Vec3(1200, 200, 0));
	setPosition(Vec3(0,-260,0));

	eventText = "";

	text = new SpriteRenderer(this);
	text->setTextureName(eventText);

	frame = new SpriteRenderer(this);

	state = State::Hero;
	EventNum = 0;
}

void EventText::update()
{
	switch (EventNum)
	{
	case 0:
		eventText = "";
		break;
	case 1:
		eventText = "";
		break;
	case 2:
		eventText = "";
		break;
	default:
		eventText = "";
		break;
	}

	switch (state)
	{
	case EventText::Hero:
		frame->setTextureName("");
		break;
	case EventText::Doctor:
		frame->setTextureName("");
		break;
	default:
		break;
	}
	text->setTextureName(eventText);
}

void EventText::onDestroy()
{
}

void EventText::setEventNum(int num)
{
	EventNum = num;
}

void EventText::addEventNum()
{
	EventNum++;
}
