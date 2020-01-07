#pragma once
#include "Component\AbstractComponent.h"

class Tile :
	public AbstractComponent
{
public:
	Tile(GameObject* pUser);
	~Tile();

	virtual void onStart() override;
	virtual void onUpdate() override;
	virtual TypeID getType() const override;
};