#pragma once
#include "Actor/GameObject.h"

class SpriteRenderer;

class TitleLogo
	:public GameObject
{
public:
	TitleLogo(IGameMediator*pMediator, std::string TextureName);
	~TitleLogo();

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;

	bool isFade;
private:
	SpriteRenderer*sprite;
	std::string name;
	float alpha;
public:
	void setTextureName(std::string TextureName);
	void setFade(bool value);
};
