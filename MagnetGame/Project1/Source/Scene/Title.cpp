#include "Title.h"
#include "Device\Input.h"

Title::Title()
{
}

Title::~Title()
{
}

void Title::init()
{
}

void Title::update()
{
	if (Input::isKeyDown(VK_SPACE)) {
		
	}
}

void Title::draw()
{
}

void Title::shutdown()
{
}

std::string Title::nextScene()
{
	return std::string();
}

bool Title::isEnd()
{
	return false;
}
