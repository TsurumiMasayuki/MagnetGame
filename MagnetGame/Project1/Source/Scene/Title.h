#pragma once
#include "AbstractScene.h"

class Title : 
	public AbstractScene {
public:
	Title();
	~Title();
	virtual void init() override;
	virtual void update() override;
	virtual void draw() override;
	virtual void shutdown() override;
	virtual std::string nextScene() override;
	virtual bool isEnd() override;
};