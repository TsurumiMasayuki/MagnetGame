#include "Timer.h"
#include <cmath>
#include "Device\GameTime.h"

Timer::Timer()
	: m_UseUnscaledTime(false)
{
}

Timer::Timer(float maxTime, bool useUnscaledTime)
	: mMaxTime(maxTime), mCurrentTime(0.0f), m_UseUnscaledTime(useUnscaledTime)
{
}

Timer::~Timer()
{
}

void Timer::update()
{
	if (!m_UseUnscaledTime)
		mCurrentTime += GameTime::getDeltaTime();
	else
		mCurrentTime += GameTime::getUnscaledDeltaTime();
}

void Timer::setMaxTime(float value)
{
	mMaxTime = value;
}

void Timer::reset()
{
	mCurrentTime = 0.0f;
}

float Timer::getCurrentTime()
{
	return mCurrentTime;
}

float Timer::getMaxTime()
{
	return mMaxTime;
}

float Timer::getRatio()
{
	return mCurrentTime / mMaxTime;
}

float Timer::getRatioClamped()
{
	return std::fminf(getRatio(), 1.0f);
}

bool Timer::isTime()
{
	return mCurrentTime >= mMaxTime;
}
