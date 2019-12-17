#pragma once
#include "Actor\GameObject.h"
#include "Utility\Timer.h"

class TestObject :
	public GameObject
{
public:
	TestObject(IGameMediator* pMediator);
	~TestObject();

	virtual void start() override;
	virtual void update() override;
};