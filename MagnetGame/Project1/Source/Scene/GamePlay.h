#pragma once
#include "AbstractScene.h"

class GamePlay : AbstractScene {
public:
	virtual void init() override;
	virtual void update(float deltaTime) override;
	virtual void draw() override;
	virtual void shutdown() override;
	virtual std::string nextScene() override;
	virtual bool isEnd() override;
};